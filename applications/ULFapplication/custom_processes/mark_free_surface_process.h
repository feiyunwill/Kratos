//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ \.
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Pavel Ryzhakov
#if !defined(KRATOS_MARK_FS_PROCESS_INCLUDED )
#define  KRATOS_MARK_FS_PROCESS_INCLUDED



// System includes
#include <string>
#include <iostream>
#include <algorithm>

// External includes


// Project includes
#include "includes/define.h"
#include "processes/process.h"
#include "includes/node.h"
#include "includes/element.h"
#include "includes/model_part.h"
//#include "custom_utilities/geometry_utilities2D.h"
#include "custom_elements/updated_lagrangian_fluid.h"


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

/// Short class definition.
/** Detail class definition.
	Update the PRESSURE_FORCE on the nodes


*/

class MarkFreeSurfaceProcess
    : public Process
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of PushStructureProcess
    KRATOS_CLASS_POINTER_DEFINITION(MarkFreeSurfaceProcess);

    ///@}
    ///@name Life Cycle
    ///@{

    /// Default constructor.
    MarkFreeSurfaceProcess(ModelPart& model_part)
        : mr_model_part(model_part)
    {
    }

    /// Destructor.
    ~MarkFreeSurfaceProcess() override
    {
    }


    ///@}
    ///@name Operators
    ///@{

    void operator()()
    {
        Execute();
    }


    ///@}
    ///@name Operations
    ///@{

    void Execute() override
    {
        KRATOS_TRY
        for(ModelPart::NodesContainerType::const_iterator in = mr_model_part.NodesBegin(); in!=mr_model_part.NodesEnd(); in++)
        {
            //marking wet nodes
            /*					if(in->FastGetSolutionStepValue(IS_STRUCTURE) )
            						if( (in->GetValue(NEIGHBOUR_ELEMENTS)).size() != 0)
            							in->FastGetSolutionStepValue(IS_FLUID) = 1.0;
            						else //it is not anymore of fluid
            							in->FastGetSolutionStepValue(IS_FLUID) = 0.0;
            					//marking as free surface the lonely nodes
            					else
            */						if( (in->GetValue(NEIGHBOUR_ELEMENTS)).size() == 0)
                in->FastGetSolutionStepValue(IS_BOUNDARY) = 1.0;
        }

        //identify the free surface
        for(ModelPart::NodeIterator i = mr_model_part.NodesBegin() ;
                i != mr_model_part.NodesEnd() ; ++i)
        {
            //reset the free surface
            i->FastGetSolutionStepValue(IS_FREE_SURFACE) = 0;
            //identify the free surface and fix the pressure accordingly
            if( i->FastGetSolutionStepValue(IS_BOUNDARY) != 0
                    &&
                    i->FastGetSolutionStepValue(IS_STRUCTURE) == 0)
            {
                i->FastGetSolutionStepValue(IS_FREE_SURFACE) = 1;
            }
        }


        KRATOS_CATCH("")
    }


    ///@}
    ///@name Access
    ///@{


    ///@}
    ///@name Inquiry
    ///@{


    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    std::string Info() const override
    {
        return "MarkFreeSurfaceProcess";
    }

    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << "MarkFreeSurfaceProcess";
    }

    /// Print object's data.
    void PrintData(std::ostream& rOStream) const override
    {
    }


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
    ModelPart& mr_model_part;

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

    /// Assignment operator.
//		MarkFreeSurfaceProcess& operator=(MarkFreeSurfaceProcess const& rOther);

    /// Copy constructor.
//		MarkFreeSurfaceProcess(MarkFreeSurfaceProcess const& rOther);


    ///@}

}; // Class MarkFreeSurfaceProcess

///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{


/// input stream function
inline std::istream& operator >> (std::istream& rIStream,
                                  MarkFreeSurfaceProcess& rThis);

/// output stream function
inline std::ostream& operator << (std::ostream& rOStream,
                                  const MarkFreeSurfaceProcess& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}


}  // namespace Kratos.

#endif // KRATOS_ULF_MARK_FS_PROCESS_INCLUDED  defined 


