//  KratosAdjointFluidApplication
//
//  License:		 BSD License
//					 license: AdjointFluidApplication/license.txt
//
//  Main authors:    Michael Andre, https://github.com/msandre
//

#if !defined(KRATOS_ADJOINT_BOSSAK_SCHEME)
#define KRATOS_ADJOINT_BOSSAK_SCHEME

// System includes
#include <vector>

// External includes

// Project includes
#include "includes/define.h"
#include "includes/element.h"
#include "includes/condition.h"
#include "includes/communicator.h"
#include "includes/model_part.h"
#include "includes/process_info.h"
#include "includes/kratos_parameters.h"
#include "includes/ublas_interface.h"
#include "utilities/openmp_utils.h"
#include "solving_strategies/schemes/scheme.h"
#include "containers/variable.h"

// Application includes
#include "../../AdjointFluidApplication/custom_utilities/response_function.h"

namespace Kratos
{
///@addtogroup AdjointFluidApplication
///@{

///@name Kratos Classes
///@{

/// A scheme for unsteady adjoint equations using Bossak time discretization.
/**
 * The forward Bossak equations are:
 * \f[
 * \mathbf{M}\dot{\mathbf{w}}^{n-\alpha} = \mathbf{f}(\mathbf{w}^{n};\mathbf{s})
 * \f]
 * \f[
 * \dot{\mathbf{w}}^{n-\alpha}
 * = (1 - \alpha) \dot{\mathbf{w}}^n + \alpha \dot{\mathbf{w}}^{n-1}
 * \f]
 * \f[
 * \dot{\mathbf{w}}^n
 * = \frac{\mathbf{w}^n - \mathbf{w}^{n-1}}{\gamma \Delta t}
 * + \frac{\gamma - 1}{\gamma}\dot{\mathbf{w}}^{n-1}
 * \f]
 *
 * The adjoint Bossak equations are:
 * \f[
 * \frac{1}{\gamma - 1} (\dot{\lambda}^n - \dot{\lambda}^{n+1})
 * + (\partial_{\mathbf{w}^n}\mathbf{f}^n
 * -\partial_{\mathbf{w}^n}(\mathbf{M}^n\dot{\mathbf{w}}^{n-\alpha}))^T\lambda^n
 * = -\partial_{\mathbf{w}^n}J^{nT}
 * \f]
 * \f[
 * \frac{1}{\gamma - 1} \dot{\lambda}^n
 * = \frac{1}{\gamma} \dot{\lambda}^{n+1}
 * - \frac{1 - \alpha}{\gamma \Delta t}M^{nT} \lambda^n
 * - \frac{\alpha}{\gamma \Delta t}M^{(n+1)T} \lambda^{n+1}
 * + \frac{1}{\gamma \Delta t}\partial_{\dot{\mathbf{w}}^n}J^{nT}
 * + \frac{1}{\gamma \Delta t}\partial_{\dot{\mathbf{w}}^n}J^{(n+1)T}
 * \f]
 *
 * with response function
 *\f$J^n=J(\mathbf{w}^n,\dot{\mathbf{w}}^n,\dot{\mathbf{w}}^{n-1};\mathbf{s})\f$.
 */
template <class TSparseSpace, class TDenseSpace>
class AdjointBossakScheme : public Scheme<TSparseSpace, TDenseSpace>
{
public:
    ///@name Type Definitions
    ///@{

    KRATOS_CLASS_POINTER_DEFINITION(AdjointBossakScheme);

    typedef Scheme<TSparseSpace, TDenseSpace> BaseType;

    typedef typename BaseType::TSystemMatrixType SystemMatrixType;

    typedef typename BaseType::TSystemVectorType SystemVectorType;

    typedef typename BaseType::LocalSystemVectorType LocalSystemVectorType;

    typedef typename BaseType::LocalSystemMatrixType LocalSystemMatrixType;

    typedef typename BaseType::DofsArrayType DofsArrayType;

    ///@}
    ///@name Life Cycle
    ///@{

    /// Constructor.
    AdjointBossakScheme(Parameters& rParameters, ResponseFunction::Pointer pResponseFunction)
        : Scheme<TSparseSpace, TDenseSpace>()
    {
        KRATOS_TRY

        Parameters DefaultParams(R"(
        {
            "scheme_type": "bossak",
            "alpha_bossak": -0.3
        })");

        rParameters.ValidateAndAssignDefaults(DefaultParams);

        mAlphaBossak = rParameters["alpha_bossak"].GetDouble();
        mGammaNewmark = 0.5 - mAlphaBossak;
        mInvGamma = 1.0 / mGammaNewmark;
        mInvGammaMinusOne = 1.0 / (mGammaNewmark - 1.0);

        mpResponseFunction = pResponseFunction;

        // Allocate auxiliary memory
        int NumThreads = OpenMPUtils::GetNumThreads();
        mAdjointValues.resize(NumThreads);
        mAdjointAcceleration.resize(NumThreads);
        mResponseGradient.resize(NumThreads);
        mAdjointMassMatrix.resize(NumThreads);

        KRATOS_CATCH("")
    }

    /// Destructor.
    ~AdjointBossakScheme() override
    {
    }

    ///@}
    ///@name Operators
    ///@{

    ///@}
    ///@name Operations
    ///@{

    void Initialize(ModelPart& rModelPart) override
    {
        KRATOS_TRY

        BaseType::Initialize(rModelPart);

        // check domain dimension and element
        const unsigned int WorkingSpaceDimension =
            rModelPart.Elements().begin()->WorkingSpaceDimension();

        ProcessInfo& rCurrentProcessInfo = rModelPart.GetProcessInfo();
        const unsigned int DomainSize =
            static_cast<unsigned int>(rCurrentProcessInfo[DOMAIN_SIZE]);
        if (DomainSize != 2 && DomainSize != 3)
            KRATOS_THROW_ERROR(std::runtime_error, "invalid DOMAIN_SIZE: ", DomainSize)
        if (DomainSize != WorkingSpaceDimension)
            KRATOS_THROW_ERROR(
                std::runtime_error, "DOMAIN_SIZE != WorkingSpaceDimension", "")

        // initialize the variables to zero.
        for (auto it = rModelPart.NodesBegin(); it != rModelPart.NodesEnd(); ++it)
        {
            it->FastGetSolutionStepValue(ADJOINT_VELOCITY) = ADJOINT_VELOCITY.Zero();
            it->FastGetSolutionStepValue(ADJOINT_PRESSURE) = ADJOINT_PRESSURE.Zero();
            it->FastGetSolutionStepValue(ADJOINT_ACCELERATION) = ADJOINT_ACCELERATION.Zero();
            it->FastGetSolutionStepValue(AUX_ADJOINT_ACCELERATION) = AUX_ADJOINT_ACCELERATION.Zero();
        }

        mpResponseFunction->Initialize();

        KRATOS_CATCH("")
    }

    void InitializeSolutionStep(ModelPart& rModelPart,
                                SystemMatrixType& rA,
                                SystemVectorType& rDx,
                                SystemVectorType& rb) override
    {
        KRATOS_TRY

        BaseType::InitializeSolutionStep(rModelPart, rA, rDx, rb);

        ProcessInfo& rCurrentProcessInfo = rModelPart.GetProcessInfo();
        double DeltaTime = -rCurrentProcessInfo[DELTA_TIME]; // DELTA_TIME < 0

        if (DeltaTime <= 0.0)
        {
            KRATOS_THROW_ERROR(std::runtime_error,
                               "detected for adjoint solution DELTA_TIME >= 0",
                               "")
        }

        mInvDt = 1.0 / DeltaTime;

        for (auto it = rModelPart.NodesBegin(); it != rModelPart.NodesEnd(); ++it)
            it->GetValue(NUMBER_OF_NEIGHBOUR_ELEMENTS) = 0.0; // todo: define application variable

        for (auto it = rModelPart.ElementsBegin(); it != rModelPart.ElementsEnd(); ++it)
            for (unsigned int iNode = 0; iNode < it->GetGeometry().PointsNumber(); ++iNode)
                it->GetGeometry()[iNode].GetValue(NUMBER_OF_NEIGHBOUR_ELEMENTS) += 1.0;

        rModelPart.GetCommunicator().AssembleNonHistoricalData(NUMBER_OF_NEIGHBOUR_ELEMENTS);

        mpResponseFunction->InitializeSolutionStep();

        KRATOS_CATCH("")
    }

    void FinalizeSolutionStep(ModelPart& rModelPart,
                              SystemMatrixType& rA,
                              SystemVectorType& rDx,
                              SystemVectorType& rb) override
    {
        KRATOS_TRY

        BaseType::FinalizeSolutionStep(rModelPart, rA, rDx, rb);

        for (auto it = rModelPart.NodesBegin(); it != rModelPart.NodesEnd(); ++it)
            it->FastGetSolutionStepValue(AUX_ADJOINT_ACCELERATION) =
                AUX_ADJOINT_ACCELERATION.Zero();

        ProcessInfo& rCurrentProcessInfo = rModelPart.GetProcessInfo();
        const unsigned int DomainSize =
            static_cast<unsigned int>(rCurrentProcessInfo[DOMAIN_SIZE]);

        // Calculate and store old contributions for solution of next time step.
        const int NumThreads = OpenMPUtils::GetNumThreads();
        OpenMPUtils::PartitionVector Partition;
        OpenMPUtils::DivideInPartitions(rModelPart.NumberOfElements(), NumThreads, Partition);
#pragma omp parallel
        {
            int k = OpenMPUtils::ThisThread();

            ModelPart::ElementIterator ElementsBegin =
                rModelPart.ElementsBegin() + Partition[k];
            ModelPart::ElementIterator ElementsEnd =
                rModelPart.ElementsBegin() + Partition[k + 1];

            for (auto it = ElementsBegin; it != ElementsEnd; ++it)
            {
                // transposed gradient of element residual w.r.t.
                // acceleration
                it->CalculateSecondDerivativesLHS(mAdjointMassMatrix[k], rCurrentProcessInfo);
                mAdjointMassMatrix[k] = -mAlphaBossak * mAdjointMassMatrix[k];

                // d (response) / d (primal acceleration)
                mpResponseFunction->CalculateSecondDerivativesGradient(
                    *it, mAdjointMassMatrix[k], mResponseGradient[k], rCurrentProcessInfo);

                // adjoint velocity
                it->GetValuesVector(mAdjointValues[k]);

                // terms depending on the mass matrix
                mAdjointAcceleration[k] =
                    prod(mAdjointMassMatrix[k], mAdjointValues[k]) +
                    mResponseGradient[k];

                // write to aux variable for use in next time step.
                unsigned int LocalIndex = 0;
                for (unsigned int iNode = 0;
                     iNode < it->GetGeometry().PointsNumber(); ++iNode)
                {
                    array_1d<double, 3>& rAuxAdjointAcceleration =
                        it->GetGeometry()[iNode].FastGetSolutionStepValue(AUX_ADJOINT_ACCELERATION);
                    it->GetGeometry()[iNode].SetLock();
                    for (unsigned int d = 0; d < DomainSize; ++d)
                        rAuxAdjointAcceleration[d] +=
                            mAdjointAcceleration[k][LocalIndex++];
                    it->GetGeometry()[iNode].UnSetLock();
                    ++LocalIndex; // pressure dof
                }
            }
        }

        rModelPart.GetCommunicator().AssembleCurrentData(AUX_ADJOINT_ACCELERATION);

        mpResponseFunction->FinalizeSolutionStep();

        KRATOS_CATCH("")
    }

    /// Update adjoint and adjoint acceleration.
    void Update(ModelPart& rModelPart,
                DofsArrayType& rDofSet,
                SystemMatrixType& rA,
                SystemVectorType& rDx,
                SystemVectorType& rb) override
    {
        KRATOS_TRY

        ProcessInfo& rCurrentProcessInfo = rModelPart.GetProcessInfo();
        const unsigned int DomainSize =
            static_cast<unsigned int>(rCurrentProcessInfo[DOMAIN_SIZE]);
        Communicator& rComm = rModelPart.GetCommunicator();

        if (rComm.TotalProcesses() == 1)
        {
            for (auto it = rDofSet.begin(); it != rDofSet.end(); ++it)
                if (it->IsFree() == true)
                    it->GetSolutionStepValue() +=
                        TSparseSpace::GetValue(rDx, it->EquationId());

            for (auto it = rModelPart.NodesBegin(); it != rModelPart.NodesEnd(); ++it)
            {
                array_1d<double, 3>& rCurrentAdjointAcceleration =
                    it->FastGetSolutionStepValue(ADJOINT_ACCELERATION);
                const array_1d<double, 3>& rOldAdjointAcceleration =
                    it->FastGetSolutionStepValue(ADJOINT_ACCELERATION, 1);
                const array_1d<double, 3>& rAuxAdjointAcceleration =
                    it->FastGetSolutionStepValue(AUX_ADJOINT_ACCELERATION, 1);
                for (unsigned int d = 0; d < DomainSize; ++d)
                    rCurrentAdjointAcceleration[d] = (mGammaNewmark - 1.0) * mInvGamma *
                        (rOldAdjointAcceleration[d] + mInvDt * rAuxAdjointAcceleration[d]);
            }
        }
        else
        {
            for (auto it = rDofSet.begin(); it != rDofSet.end(); ++it)
                if (it->GetSolutionStepValue(PARTITION_INDEX) == rComm.MyPID())
                    if (it->IsFree() == true)
                        it->GetSolutionStepValue() +=
                            TSparseSpace::GetValue(rDx, it->EquationId());

            // todo: add a function Communicator::SynchronizeDofVariables() to
            // reduce communication here.
            rComm.SynchronizeNodalSolutionStepsData();

            for (auto it = rModelPart.NodesBegin(); it != rModelPart.NodesEnd(); ++it)
            {
                array_1d<double, 3>& rCurrentAdjointAcceleration =
                    it->FastGetSolutionStepValue(ADJOINT_ACCELERATION);

                // in the end we need to assemble so we only compute this part
                // on the process that owns the node.
                if (it->FastGetSolutionStepValue(PARTITION_INDEX) == rComm.MyPID())
                {
                    const array_1d<double, 3>& rOldAdjointAcceleration =
                        it->FastGetSolutionStepValue(ADJOINT_ACCELERATION, 1);
                    const array_1d<double, 3>& rAuxAdjointAcceleration =
                        it->FastGetSolutionStepValue(AUX_ADJOINT_ACCELERATION, 1);
                    for (unsigned int d = 0; d < DomainSize; ++d)
                        rCurrentAdjointAcceleration[d] = (mGammaNewmark - 1.0) * mInvGamma *
                            (rOldAdjointAcceleration[d] + mInvDt * rAuxAdjointAcceleration[d]);
                }
                else
                {
                    for (unsigned int d = 0; d < DomainSize; ++d)
                        rCurrentAdjointAcceleration[d] = 0.0;
                }
            }
        }

        const int NumThreads = OpenMPUtils::GetNumThreads();
        OpenMPUtils::PartitionVector Partition;
        OpenMPUtils::DivideInPartitions(rModelPart.NumberOfElements(), NumThreads, Partition);
#pragma omp parallel
        {
            int k = OpenMPUtils::ThisThread();

            ModelPart::ElementIterator ElementsBegin =
                rModelPart.ElementsBegin() + Partition[k];
            ModelPart::ElementIterator ElementsEnd =
                rModelPart.ElementsBegin() + Partition[k + 1];

            for (auto it = ElementsBegin; it != ElementsEnd; ++it)
            {
                // transposed gradient of element residual w.r.t. acceleration
                it->CalculateSecondDerivativesLHS(mAdjointMassMatrix[k], rCurrentProcessInfo);
                mAdjointMassMatrix[k] = -(1.0 - mAlphaBossak) * mAdjointMassMatrix[k];

                // d (response) / d (primal acceleration)
                mpResponseFunction->CalculateSecondDerivativesGradient(
                    *it, mAdjointMassMatrix[k], mResponseGradient[k], rCurrentProcessInfo);

                // adjoint velocity
                it->GetValuesVector(mAdjointValues[k]);

                // terms depending on the mass matrix
                mAdjointAcceleration[k] = (mGammaNewmark - 1.0) * mInvGamma * mInvDt *
                    (prod(mAdjointMassMatrix[k], mAdjointValues[k]) + mResponseGradient[k]);

                unsigned int LocalIndex = 0;
                for (unsigned int iNode = 0; iNode < it->GetGeometry().PointsNumber(); ++iNode)
                {
                    it->GetGeometry()[iNode].SetLock();
                    array_1d<double, 3>& rCurrentAdjointAcceleration =
                        it->GetGeometry()[iNode].FastGetSolutionStepValue(ADJOINT_ACCELERATION);
                    for (unsigned int d = 0; d < DomainSize; ++d)
                    {
                        rCurrentAdjointAcceleration[d] +=
                            mAdjointAcceleration[k][LocalIndex++];
                    }
                    it->GetGeometry()[iNode].UnSetLock();
                    ++LocalIndex; // pressure dof
                }
            }
        }

        rModelPart.GetCommunicator().AssembleCurrentData(ADJOINT_ACCELERATION);

        KRATOS_CATCH("")
    }

    /// Calculate residual based element contributions to transient adjoint.
    void CalculateSystemContributions(Element::Pointer pCurrentElement,
                                      LocalSystemMatrixType& rLHS_Contribution,
                                      LocalSystemVectorType& rRHS_Contribution,
                                      Element::EquationIdVectorType& rEquationId,
                                      ProcessInfo& rCurrentProcessInfo) override
    {
        KRATOS_TRY

        int ThreadId = OpenMPUtils::ThisThread();

        // old adjoint acceleration
        pCurrentElement->GetSecondDerivativesVector(rRHS_Contribution, 1);
        unsigned int LocalIndex = 0;
        const int DomainSize = rCurrentProcessInfo[DOMAIN_SIZE];
        for (unsigned int iNode = 0; iNode < pCurrentElement->GetGeometry().PointsNumber(); ++iNode)
        {
            const array_1d<double, 3>& rAuxAdjointAcceleration =
                        pCurrentElement->GetGeometry()[iNode].FastGetSolutionStepValue(AUX_ADJOINT_ACCELERATION, 1);
            double InvNodalArea = 1.0 / pCurrentElement->GetGeometry()[iNode].GetValue(NUMBER_OF_NEIGHBOUR_ELEMENTS);
            for (int d = 0; d < DomainSize; ++d)
            {
                rRHS_Contribution[LocalIndex] = mInvGamma * InvNodalArea *
                    (mInvGammaMinusOne * rRHS_Contribution[LocalIndex] - mInvDt * rAuxAdjointAcceleration[d]);
                ++LocalIndex;
            }
            ++LocalIndex; // pressure dof
        }

        // transposed gradient of element residual w.r.t. acceleration
        pCurrentElement->CalculateSecondDerivativesLHS(mAdjointMassMatrix[ThreadId], rCurrentProcessInfo);
        mAdjointMassMatrix[ThreadId] = -(1.0 - mAlphaBossak) * mAdjointMassMatrix[ThreadId];

        // d (response) / d (primal acceleration)
        mpResponseFunction->CalculateSecondDerivativesGradient(
            *pCurrentElement, mAdjointMassMatrix[ThreadId], mResponseGradient[ThreadId], rCurrentProcessInfo);
        noalias(rRHS_Contribution) -= mInvGamma * mInvDt * mResponseGradient[ThreadId];

        // transposed gradient of element residual w.r.t. primal
        pCurrentElement->CalculateFirstDerivativesLHS(rLHS_Contribution, rCurrentProcessInfo);

        // d (response) / d (primal)
        mpResponseFunction->CalculateFirstDerivativesGradient(
            *pCurrentElement, rLHS_Contribution, mResponseGradient[ThreadId], rCurrentProcessInfo);
        noalias(rRHS_Contribution) -= mResponseGradient[ThreadId];

        noalias(rLHS_Contribution) += mInvGamma * mInvDt * mAdjointMassMatrix[ThreadId];

        // residual form
        pCurrentElement->GetValuesVector(mAdjointValues[ThreadId]);
        noalias(rRHS_Contribution) -= prod(rLHS_Contribution, mAdjointValues[ThreadId]);

        pCurrentElement->EquationIdVector(rEquationId, rCurrentProcessInfo);

        KRATOS_CATCH("")
    }

    void Calculate_LHS_Contribution(Element::Pointer pCurrentElement,
                                    LocalSystemMatrixType& LHS_Contribution,
                                    Element::EquationIdVectorType& EquationId,
                                    ProcessInfo& CurrentProcessInfo) override
    {
        KRATOS_TRY

        LocalSystemVectorType RHS_Contribution;

        RHS_Contribution.resize(LHS_Contribution.size1(), false);

        CalculateSystemContributions(
            pCurrentElement, LHS_Contribution, RHS_Contribution, EquationId, CurrentProcessInfo);

        KRATOS_CATCH("")
    }

    void Condition_CalculateSystemContributions(Condition::Pointer pCurrentCondition,
                                                LocalSystemMatrixType& LHS_Contribution,
                                                LocalSystemVectorType& RHS_Contribution,
                                                Condition::EquationIdVectorType& EquationId,
                                                ProcessInfo& CurrentProcessInfo) override
    {
        KRATOS_TRY

        BaseType::Condition_CalculateSystemContributions(
            pCurrentCondition, LHS_Contribution, RHS_Contribution, EquationId, CurrentProcessInfo);

        KRATOS_CATCH("")
    }

    void Condition_Calculate_LHS_Contribution(Condition::Pointer pCurrentCondition,
                                              LocalSystemMatrixType& LHS_Contribution,
                                              Condition::EquationIdVectorType& EquationId,
                                              ProcessInfo& CurrentProcessInfo) override
    {
        KRATOS_TRY

        BaseType::Condition_Calculate_LHS_Contribution(
            pCurrentCondition, LHS_Contribution, EquationId, CurrentProcessInfo);

        KRATOS_CATCH("")
    }

    void GetElementalDofList(Element::Pointer rCurrentElement,
                             Element::DofsVectorType& ElementalDofList,
                             ProcessInfo& CurrentProcessInfo) override
    {
        rCurrentElement->GetDofList(ElementalDofList, CurrentProcessInfo);
    }

    ///@}
    ///@name Access
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Friends
    ///@{

    ///@}

protected:
    ///@name Protected static Member Variables
    ///@{

    ///@}
    ///@name Protected member Variables
    ///@{

    ///@}
    ///@name Protected Operators
    ///@{

    ///@}
    ///@name Protected Operations
    ///@{

    ///@}
    ///@name Protected  Access
    ///@{

    ///@}
    ///@name Protected Inquiry
    ///@{

    ///@}
    ///@name Protected LifeCycle
    ///@{

    ///@}

private:
    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    double mAlphaBossak;
    double mGammaNewmark;
    double mInvDt;
    double mInvGamma;
    double mInvGammaMinusOne;
    ResponseFunction::Pointer mpResponseFunction;
    std::vector<LocalSystemVectorType> mAdjointValues;
    std::vector<LocalSystemVectorType> mAdjointAcceleration;
    std::vector<LocalSystemVectorType> mResponseGradient;
    std::vector<LocalSystemMatrixType> mAdjointMassMatrix;

    ///@}
    ///@name Private Operators
    ///@{

    ///@}
    ///@name Private Operations
    ///@{

    ///@}
    ///@name Private  Access
    ///@{

    ///@}
    ///@name Private Inquiry
    ///@{

    ///@}
    ///@name Un accessible methods
    ///@{

    ///@}

}; /* Class Scheme */

///@}

///@name Type Definitions
///@{

///@}

///@} // Adjoint Fluid Application group

} /* namespace Kratos.*/

#endif /* KRATOS_ADJOINT_BOSSAK_SCHEME defined */
