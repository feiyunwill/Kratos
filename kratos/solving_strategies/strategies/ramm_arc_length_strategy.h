
//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Ignasi de Pouplana
//                   Alejandro Cornejo
//


#if !defined(KRATOS_RAMM_ARC_LENGTH_STRATEGY)
#define KRATOS_RAMM_ARC_LENGTH_STRATEGY

// Project includes
#include "solving_strategies/residualbased_newton_raphson_strategy.h"

// Application includes
// #include "poromechanics_application_variables.h"

namespace Kratos
{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}

///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/**
 * @class RammArcLengthStrategy
 * @ingroup KratosCore
 * @brief This is the base Newton Raphson strategy
 * @details This strategy iterates until the convergence is achieved (or the maximum number of iterations is surpassed) using a Newton Raphson algorithm
 * @author Ignasi de Pouplana and Alejandro Cornejo
 */
template<class TSparseSpace,
         class TDenseSpace,
         class TLinearSolver
         >
class RammArcLengthStrategy 
    : public ResidualBasedNewtonRaphsonStrategy<TSparseSpace, TDenseSpace, TLinearSolver>
{

public:

    KRATOS_CLASS_POINTER_DEFINITION(RammArcLengthStrategy);

    ///@name Type Definitions
    ///@{
    typedef SolvingStrategy<TSparseSpace, TDenseSpace, TLinearSolver> BaseType;

    typedef ResidualBasedNewtonRaphsonStrategy<TSparseSpace, TDenseSpace, TLinearSolver> BaseType;

    typedef ResidualBasedNewtonRaphsonStrategy<TSparseSpace, TDenseSpace, TLinearSolver> BaseType;

    typedef ConvergenceCriteria<TSparseSpace, TDenseSpace> TConvergenceCriteriaType;

    typedef typename BaseType::TBuilderAndSolverType TBuilderAndSolverType;

    typedef typename BaseType::TSchemeType TSchemeType;

    typedef TSparseSpace SparseSpaceType;

    typedef typename BaseType::DofsArrayType DofsArrayType;

    typedef typename BaseType::TSystemMatrixType TSystemMatrixType;

    typedef typename BaseType::TSystemVectorType TSystemVectorType;

    typedef typename BaseType::TSystemVectorPointerType TSystemVectorPointerType;

    using BaseType::mpScheme;

    using BaseType::mpBuilderAndSolver;

    using BaseType::mpConvergenceCriteria;

    using BaseType::mpA; //Tangent matrix

    using BaseType::mpb; //Residual vector of iteration i

    using BaseType::mpDx; //Delta x of iteration i

    using BaseType::mReformDofSetAtEachStep;

    using BaseType::mCalculateReactionsFlag;

    using BaseType::mSolutionStepIsInitialized;

    using BaseType::mMaxIterationNumber;

    using BaseType::mInitializeWasPerformed;

    using BaseType::mSubModelPartList;

    using BaseType::mVariableNames;

    ///@}
    ///@name Life Cycle
    ///@{


    /**
     * Default constructor
     * @param rModelPart The model part of the problem
     * @param pScheme The integration scheme
     * @param pNewLinearSolver The linear solver employed
     * @param pNewConvergenceCriteria The convergence criteria employed
     * @param MaxIterations The maximum number of non-linear iterations to be considered when solving the problem
     * @param CalculateReactions The flag for the reaction calculation
     * @param ReformDofSetAtEachStep The flag that allows to compute the modification of the DOF
     * @param MoveMeshFlag The flag that allows to move the mesh
     */
    RammArcLengthStrategy(
        ModelPart& model_part,
        typename TSchemeType::Pointer pScheme,
        typename TLinearSolver::Pointer pNewLinearSolver,
        typename TConvergenceCriteriaType::Pointer pNewConvergenceCriteria,
        typename TBuilderAndSolverType::Pointer pNewBuilderAndSolver,
        Parameters& rParameters,
        int MaxIterations = 30,
        bool CalculateReactions = false,
        bool ReformDofSetAtEachStep = false,
        bool MoveMeshFlag = false
        ) : ResidualBasedNewtonRaphsonStrategy<TSparseSpace, TDenseSpace, TLinearSolver>(model_part, pScheme, pNewLinearSolver,
                pNewConvergenceCriteria, pNewBuilderAndSolver, rParameters, MaxIterations, CalculateReactions, ReformDofSetAtEachStep, MoveMeshFlag)
        {
            Parameters default_parameters( R"({
                "desired_iterations": 4,
                "max_radius_factor": 20.0,
                "min_radius_factor": 0.5,
                "body_domain_sub_model_part_list": [],
                "loads_sub_model_part_list": [],
                "loads_variable_list" : []
            }  )");

            // Validate agains defaults
            rParameters.ValidateAndAssignDefaults(default_parameters);

            mpParameters = &rParameters;

            // Set Load SubModelParts and Variable names
            if (rParameters["loads_sub_model_part_list"].size() > 0) {
                mSubModelPartList.resize(rParameters["loads_sub_model_part_list"].size());
                mVariableNames.resize(rParameters["loads_variable_list"].size());

                if (mSubModelPartList.size() != mVariableNames.size())
                    KRATOS_THROW_ERROR( std::logic_error, "For each SubModelPart there must be a corresponding nodal Variable", "" )

                for(unsigned int i = 0; i < mVariableNames.size(); i++) {
                    mSubModelPartList[i] = &( model_part.GetSubModelPart(rParameters["loads_sub_model_part_list"][i].GetString()) );
                    º[i] = rParameters["loads_variable_list"][i].GetString();
                }
            }

            mDesiredIterations = rParameters["desired_iterations"].GetInt();
            mMaxRadiusFactor = rParameters["max_radius_factor"].GetDouble();
            mMinRadiusFactor = rParameters["min_radius_factor"].GetDouble();

            mInitializeArcLengthWasPerformed = false;
        }


    /**
     * @brief Destructor.
     * @details In trilinos third party library, the linear solver's preconditioner should be freed before the system matrix. We control the deallocation order with Clear().
     */
    ~RammArcLengthStrategy() override {}


    /**
     * @brief Initialization of member variables and prior operations
     */
    void Initialize() override
    {
        KRATOS_TRY

        if (mInitializeWasPerformed == false) {
            BaseType::Initialize();

            if (mInitializeArcLengthWasPerformed == false) {
                //set up the system
                if (mpBuilderAndSolver->GetDofSetIsInitializedFlag() == false) {
                    //setting up the list of the DOFs to be solved
                    mpBuilderAndSolver->SetUpDofSet(mpScheme, BaseType::GetModelPart());

                    //shaping correctly the system
                    mpBuilderAndSolver->SetUpSystem(BaseType::GetModelPart());
                }

                // Compute initial radius (mRadius_0)
                mpBuilderAndSolver->ResizeAndInitializeVectors(mpScheme, mpA, mpDx, mpb, BaseType::GetModelPart());
                TSystemMatrixType& mA = *mpA;
                TSystemVectorType& mDx = *mpDx;
                TSystemVectorType& mb = *mpb;
                TSparseSpace::SetToZero(mA);
                TSparseSpace::SetToZero(mDx);
                TSparseSpace::SetToZero(mb);

                mpBuilderAndSolver->BuildAndSolve(mpScheme, BaseType::GetModelPart(), mA, mDx, mb);

                mRadius_0 = TSparseSpace::TwoNorm(mDx);
                mRadius = mRadius_0;

                // Compute vector of reference external force (mf)
                this->InitializeSystemVector(mpf);
                TSystemVectorType& mf = *mpf;
                TSparseSpace::SetToZero(mf);

                mpBuilderAndSolver->BuildRHS(mpScheme, BaseType::GetModelPart(), mf);

                //Initialize the loading factor Lambda
                mLambda = 0.0;
                mLambda_old = 1.0;

                // Initialize Norm of solution
                mNormxEquilibrium = 0.0;

                mInitializeArcLengthWasPerformed = true;

                KRATOS_INFO("Ramm's Arc Length Strategy") << "Strategy Initialized" << std::endl;
            }
        }

        KRATOS_CATCH( "" )
    }

    /**
     * @brief Performs all the required operations that should be done (for each step) before solving the solution step.
     * @details A member variable should be used as a flag to make sure this function is called only once per step.
     */
    void InitializeSolutionStep() override
    {
        KRATOS_TRY

		if (mSolutionStepIsInitialized == false) {
            BaseType::InitializeSolutionStep();

            this->SaveInitializeSystemVector(mpf);
            this->InitializeSystemVector(mpDxf);
            this->InitializeSystemVector(mpDxb);
            this->InitializeSystemVector(mpDxPred);
            this->InitializeSystemVector(mpDxStep);
        }
        KRATOS_CATCH( "" )
    }


    /**
     * @brief Solves the current step. This function returns true if a solution has been found, false otherwise.
     */
	bool SolveSolutionStep() override
	{
        // Prediction phase
        KRATOS_INFO("Ramm's Arc Length Strategy") << "ARC-LENGTH RADIUS: " << mRadius/mRadius_0 << " X initial radius" << std::endl;

        // Initialize variables
		DofsArrayType& rDofSet = mpBuilderAndSolver->GetDofSet();
        TSystemMatrixType& mA = *mpA;
        TSystemVectorType& mDx = *mpDx;
        TSystemVectorType& mb = *mpb;
        TSystemVectorType& mf = *mpf;
        TSystemVectorType& mDxb = *mpDxb;
        TSystemVectorType& mDxf = *mpDxf;
        TSystemVectorType& mDxPred = *mpDxPred;
        TSystemVectorType& mDxStep = *mpDxStep;

        // Initializing the parameters of the iteration loop
        double NormDx;
        unsigned int iteration_number = 1;
        BaseType::GetModelPart().GetProcessInfo()[NL_ITERATION_NUMBER] = iteration_number;
        bool is_converged = false;
        mpScheme->InitializeNonLinIteration(BaseType::GetModelPart(), mA, mDx, mb);
        is_converged = mpConvergenceCriteria->PreCriteria(BaseType::GetModelPart(), rDofSet, mA, mDx, mb);

        TSparseSpace::SetToZero(mA);
        TSparseSpace::SetToZero(mb);
        TSparseSpace::SetToZero(mDxf);

        // Note: This is not so efficient, but I want to solve mA*mDxf=mf without losing mf
        this->BuildWithDirichlet(mA, mDxf, mb);
        noalias(mb) = mf;
        mpBuilderAndSolver->SystemSolve(mA, mDxf, mb);

        // Update results
        double DLambda = mRadius/TSparseSpace::TwoNorm(mDxf);
        mDLambdaStep = DLambda;
        mLambda += DLambda;
        noalias(mDxPred) = DLambda*mDxf;
        noalias(mDxStep) = mDxPred;
        this->Update(rDofSet, mA, mDxPred, mb);

        // Move the mesh if needed
        if(BaseType::MoveMeshFlag() == true) BaseType::MoveMesh();

        // Correction phase
        if (is_converged == true) {
            mpConvergenceCriteria->InitializeSolutionStep(BaseType::GetModelPart(), rDofSet, mA, mDxf, mb);
            if (mpConvergenceCriteria->GetActualizeRHSflag() == true) {
                TSparseSpace::SetToZero(mb);
                mpBuilderAndSolver->BuildRHS(mpScheme, BaseType::GetModelPart(), mb);
            }
            is_converged = mpConvergenceCriteria->PostCriteria(BaseType::GetModelPart(), rDofSet, mA, mDxf, mb);
        }

        while (is_converged == false && iteration_number++ < mMaxIterationNumber) {
            // Setting the number of iterations
            BaseType::GetModelPart().GetProcessInfo()[NL_ITERATION_NUMBER] = iteration_number;

            mpScheme->InitializeNonLinIteration(BaseType::GetModelPart(), mA, mDx, mb);

            is_converged = mpConvergenceCriteria->PreCriteria(BaseType::GetModelPart(), rDofSet, mA, mDx, mb);

            TSparseSpace::SetToZero(mA);
            TSparseSpace::SetToZero(mb);
            TSparseSpace::SetToZero(mDxf);

            // Note: This is not so efficient, but I want to solve mA*mDxf=mf without losing mf
            this->BuildWithDirichlet(mA, mDxf, mb);
            noalias(mb) = mf;
            mpBuilderAndSolver->SystemSolve(mA, mDxf, mb);

            TSparseSpace::SetToZero(mA);
            TSparseSpace::SetToZero(mb);
            TSparseSpace::SetToZero(mDxb);

            mpBuilderAndSolver->BuildAndSolve(mpScheme, BaseType::GetModelPart(), mA, mDxb, mb);

            DLambda = -TSparseSpace::Dot(mDxPred, mDxb)/TSparseSpace::Dot(mDxPred, mDxf);

            noalias(mDx) = mDxb + DLambda*mDxf;

            //Check solution before update
            if ( mNormxEquilibrium > 1.0e-10 ) {
                NormDx = TSparseSpace::TwoNorm(mDx);

                if( (NormDx/mNormxEquilibrium) > 1.0e3 || (std::abs(DLambda)/std::abs(mLambda-mDLambdaStep)) > 1.0e3 ) {
                    is_converged = false;
                    break;
                }
            }

            // Update results
            mDLambdaStep += DLambda;
            mLambda += DLambda;
            noalias(mDxStep) += mDx;
            this->Update(rDofSet, mA, mDx, mb);

            // Move the mesh if needed
            if (BaseType::MoveMeshFlag() == true) 
                BaseType::MoveMesh();

            mpScheme->FinalizeNonLinIteration(BaseType::GetModelPart(), mA, mDx, mb);

            // Check convergence
            if (is_converged == true) {
                if (mpConvergenceCriteria->GetActualizeRHSflag() == true) {
                    TSparseSpace::SetToZero(mb);
                    mpBuilderAndSolver->BuildRHS(mpScheme, BaseType::GetModelPart(), mb);
                }
                is_converged = mpConvergenceCriteria->PostCriteria(BaseType::GetModelPart(), rDofSet, mA, mDx, mb);
            }

        } // While loop

        // Check iteration_number
        if (iteration_number >= mMaxIterationNumber) {
            is_converged = true;
            // Plots a warning if the maximum number of iterations is exceeded
            if (BaseType::GetModelPart().GetCommunicator().MyPID() == 0)
                this->MaxIterationsExceeded();
        }

        //calculate reactions if required
        if (mCalculateReactionsFlag)
            mpBuilderAndSolver->CalculateReactions(mpScheme, BaseType::GetModelPart(), mA, mDx, mb);

        BaseType::GetModelPart().GetProcessInfo()[IS_CONVERGED] = is_converged;

		return is_converged;
    }


    /**
     * @brief Performs all the required operations that should be done (for each step) after solving the solution step.
     * @details A member variable should be used as a flag to make sure this function is called only once per step.
     */
	void FinalizeSolutionStep() override
	{
		KRATOS_TRY

        unsigned int iteration_number = BaseType::GetModelPart().GetProcessInfo()[NL_ITERATION_NUMBER];

        // Update the radius
        mRadius = mRadius*sqrt(double(mDesiredIterations)/double(iteration_number));

        DofsArrayType& rDofSet = mpBuilderAndSolver->GetDofSet();
        TSystemMatrixType& mA = *mpA;
        TSystemVectorType& mDx = *mpDx;
        TSystemVectorType& mb = *mpb;

        if (BaseType::GetModelPart().GetProcessInfo()[IS_CONVERGED] == true) {
            // Modify the radius to advance faster when convergence is achieved
            if (mRadius > mMaxRadiusFactor*mRadius_0)
                mRadius = mMaxRadiusFactor*mRadius_0;
            else if(mRadius < mMinRadiusFactor*mRadius_0)
                mRadius = mMinRadiusFactor*mRadius_0;

            // Update Norm of x
            mNormxEquilibrium = this->CalculateReferenceDofsNorm(rDofSet);
        } else {
            KRATOS_INFO("Ramm's Arc Length Strategy") << "************ NO CONVERGENCE: restoring equilibrium path ************" << std::endl;
            TSystemVectorType& mDxStep = *mpDxStep;

            //update results
            mLambda -= mDLambdaStep;
            noalias(mDx) = -mDxStep;
            this->Update(rDofSet, mA, mDx, mb);

            //move the mesh if needed
            if(BaseType::MoveMeshFlag() == true) BaseType::MoveMesh();
        }

        BaseType::GetModelPart().GetProcessInfo()[ARC_LENGTH_LAMBDA] = mLambda;
        BaseType::GetModelPart().GetProcessInfo()[ARC_LENGTH_RADIUS_FACTOR] = mRadius/mRadius_0;

        mpScheme->FinalizeSolutionStep(BaseType::GetModelPart(), mA, mDx, mb);
        mpBuilderAndSolver->FinalizeSolutionStep(BaseType::GetModelPart(), mA, mDx, mb);

        //Cleaning memory after the solution
        mpScheme->Clean();

        //reset flags for next step
        mSolutionStepIsInitialized = false;

        if (mReformDofSetAtEachStep == true) { // Deallocate the system vectors
            this->ClearStep();
        }

		KRATOS_CATCH("")
	}

    /**
     * @brief Clears the internal storage
     */
    void Clear() override
    {
        KRATOS_TRY

        SparseSpaceType::Clear(mpf);
        SparseSpaceType::Clear(mpDxf);
        SparseSpaceType::Clear(mpDxb);
        SparseSpaceType::Clear(mpDxPred);
        SparseSpaceType::Clear(mpDxStep);

        TSystemVectorType& mf = *mpf;
        TSystemVectorType& mDxf = *mpDxf;
        TSystemVectorType& mDxb = *mpDxb;
        TSystemVectorType& mDxPred = *mpDxPred;
        TSystemVectorType& mDxStep = *mpDxStep;

        SparseSpaceType::Resize(mf, 0);
        SparseSpaceType::Resize(mDxf, 0);
        SparseSpaceType::Resize(mDxb, 0);
        SparseSpaceType::Resize(mDxPred, 0);
        SparseSpaceType::Resize(mDxStep, 0);

        BaseType::Clear();

        KRATOS_CATCH( "" )
    }

    /**
     * @brief This should be considered as a "post solution" convergence check which is useful for coupled analysis - the convergence criteria used is the one used inside the "solve" step
     */
    bool IsConverged() override
    {
        KRATOS_TRY

        bool IsConverged = true;

        // Note: Initialize() needs to be called beforehand
		this->InitializeSolutionStep();

		this->Predict();

        // Solve the problem with constant load
		IsConverged = this->CheckConvergence();

		this->FinalizeSolutionStep();

        return IsConverged;

        KRATOS_CATCH("")
    }

    /**
     * @brief This method updates the value of the external loads according to the arc-length load factor mLambda
     */
    virtual void UpdateLoads()
    {
        KRATOS_TRY

        mLambda = BaseType::GetModelPart().GetProcessInfo()[ARC_LENGTH_LAMBDA];
        mRadius = (BaseType::GetModelPart().GetProcessInfo()[ARC_LENGTH_RADIUS_FACTOR])*mRadius_0;

        // Update External Loads
        this->UpdateExternalLoads();

        KRATOS_CATCH("")
    }


protected:
    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    TSystemVectorPointerType mpf;      /// Vector of reference external forces
    TSystemVectorPointerType mpDxf;    /// Delta x of A*Dxf=f
    TSystemVectorPointerType mpDxb;    /// Delta x of A*Dxb=b
    TSystemVectorPointerType mpDxPred; /// Delta x of prediction phase
    TSystemVectorPointerType mpDxStep; /// Delta x of the current step

    unsigned int mDesiredIterations;   /// This is used to calculate the radius of the next step

    bool mInitializeArcLengthWasPerformed;

    double mMaxRadiusFactor, mMinRadiusFactor; /// Used to limit the radius of the arc length strategy
    double mRadius, mRadius_0;                 /// Radius of the arc length strategy
    double mLambda, mLambda_old;               /// Loading factor
    double mNormxEquilibrium;                  /// Norm of the solution vector in equilibrium
    double mDLambdaStep;                       /// Delta lambda of the current step

    Parameters* mpParameters;
    std::vector<ModelPart*> mSubModelPartList; // List of every SubModelPart associated to an external load
    std::vector<std::string> mVariableNames;   // Name of the nodal variable associated to every SubModelPart

    /**
     * @brief Function to perform expensive checks.
     * @details It is designed to be called ONCE to verify that the input is correct.
     */
    int Check() override
    {
        KRATOS_TRY

        int ierr = BaseType::Check();
        if(ierr != 0) return ierr;

        KRATOS_CHECK_VARIABLE_KEY(ARC_LENGTH_LAMBDA);
        KRATOS_CHECK_VARIABLE_KEY(ARC_LENGTH_RADIUS_FACTOR);

        return ierr;

        KRATOS_CATCH( "" )
    }

    /**
     * @brief Function to initialize a system vector
     */
    void InitializeSystemVector(TSystemVectorPointerType& pv)
    {
        if (pv == NULL) {
            TSystemVectorPointerType pNewv = TSystemVectorPointerType(new TSystemVectorType(0));
            pv.swap(pNewv);
        }

        TSystemVectorType& v = *pv;

        if (v.size() != mpBuilderAndSolver->GetEquationSystemSize())
            v.resize(mpBuilderAndSolver->GetEquationSystemSize(), false);
    }

    /**
     * @brief Function to storage the initial system vector
     */
    void SaveInitializeSystemVector(TSystemVectorPointerType& pv)
    {
        if (pv == NULL) {
            TSystemVectorPointerType pNewv = TSystemVectorPointerType(new TSystemVectorType(0));
            pv.swap(pNewv);
        }

        TSystemVectorType& v = *pv;

        if (v.size() != mpBuilderAndSolver->GetEquationSystemSize())
            v.resize(mpBuilderAndSolver->GetEquationSystemSize(), true);
    }

    /**
     * @brief Function to build the system applying Dirichlet conditions
     * @param mA The LHS matrix
     * @param mDx The displacement increment vector
     * @param mb The residual vector
     */
    void BuildWithDirichlet(TSystemMatrixType& mA, TSystemVectorType& mDx, TSystemVectorType& mb)
    {
        KRATOS_TRY

        mpBuilderAndSolver->Build(mpScheme, BaseType::GetModelPart(), mA, mb);
        mpBuilderAndSolver->ApplyDirichletConditions(mpScheme, BaseType::GetModelPart(), mA, mDx, mb);

        KRATOS_CATCH( "" )
    }

    /**
     * @brief Function to Update the database and the external loads
     * @param rDofSet The degrees of freedom
     * @param mA The LHS matrix
     * @param mDx The displacement increment vector
     * @param mb The residual vector
     */
    virtual void Update(DofsArrayType& rDofSet, TSystemMatrixType& mA, TSystemVectorType& mDx, TSystemVectorType& mb)
    {
        KRATOS_TRY

        // Update scheme
        mpScheme->Update(BaseType::GetModelPart(), rDofSet, mA, mDx, mb);

        // Update External Loads
        this->UpdateExternalLoads();

        KRATOS_CATCH( "" )
    }

    /**
     * @brief Function to clear all the member system vectors
     */
    void ClearStep()
    {
        KRATOS_TRY

        SparseSpaceType::Clear(mpDxf);
        SparseSpaceType::Clear(mpDxb);
        SparseSpaceType::Clear(mpDxPred);
        SparseSpaceType::Clear(mpDxStep);

        TSystemVectorType& mDxf = *mpDxf;
        TSystemVectorType& mDxb = *mpDxb;
        TSystemVectorType& mDxPred = *mpDxPred;
        TSystemVectorType& mDxStep = *mpDxStep;

        SparseSpaceType::Resize(mDxf, 0);
        SparseSpaceType::Resize(mDxb, 0);
        SparseSpaceType::Resize(mDxPred, 0);
        SparseSpaceType::Resize(mDxStep, 0);

        BaseType::Clear();

        KRATOS_CATCH("");
    }

    /**
     * @brief Function to modify the value of the external loads according to the load factor mLambda
     */
    void UpdateExternalLoads()
    {
        // Update External Loads
        for(unsigned int i = 0; i < mVariableNames.size(); i++)
        {
            ModelPart& rSubModelPart = *(mSubModelPartList[i]);
            const std::string& VariableName = mVariableNames[i];

            if( KratosComponents< Variable<double> >::Has( VariableName ) )
            {
                Variable<double> var = KratosComponents< Variable<double> >::Get( VariableName );

                #pragma omp parallel
                {
                    ModelPart::NodeIterator NodesBegin;
                    ModelPart::NodeIterator NodesEnd;
                    OpenMPUtils::PartitionedIterators(rSubModelPart.Nodes(),NodesBegin,NodesEnd);

                    for (ModelPart::NodeIterator itNode = NodesBegin; itNode != NodesEnd; ++itNode)
                    {
                        double& rvalue = itNode->FastGetSolutionStepValue(var);
                        rvalue *= (mLambda/mLambda_old);
                    }
                }
            }
            else if( KratosComponents< Variable<array_1d<double,3> > >::Has(VariableName) )
            {
                typedef VariableComponent< VectorComponentAdaptor<array_1d<double, 3> > > component_type;
                component_type varx = KratosComponents< component_type >::Get(VariableName+std::string("_X"));
                component_type vary = KratosComponents< component_type >::Get(VariableName+std::string("_Y"));
                component_type varz = KratosComponents< component_type >::Get(VariableName+std::string("_Z"));

                #pragma omp parallel
                {
                    ModelPart::NodeIterator NodesBegin;
                    ModelPart::NodeIterator NodesEnd;
                    OpenMPUtils::PartitionedIterators(rSubModelPart.Nodes(),NodesBegin,NodesEnd);

                    for (ModelPart::NodeIterator itNode = NodesBegin; itNode != NodesEnd; ++itNode)
                    {
                        double& rvaluex = itNode->FastGetSolutionStepValue(varx);
                        rvaluex *= (mLambda/mLambda_old);
                        double& rvaluey = itNode->FastGetSolutionStepValue(vary);
                        rvaluey *= (mLambda/mLambda_old);
                        double& rvaluez = itNode->FastGetSolutionStepValue(varz);
                        rvaluez *= (mLambda/mLambda_old);
                    }
                }
            }
            else
            {
                KRATOS_THROW_ERROR( std::logic_error, "One variable of the applied loads has a non supported type. Variable: ", VariableName )
            }
        }

        // Save the applied Lambda factor
        mLambda_old = mLambda;
    }

}; /* Class RammArcLengthStrategy */

} // namespace Kratos

#endif // KRATOS_RAMM_ARC_LENGTH_STRATEGY  defined