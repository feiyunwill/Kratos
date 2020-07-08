//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Jordi Cotela
//


#if !defined(KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED )
#define  KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes


// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/variables.h"
#include "includes/dem_variables.h"  //TODO: must be removed eventually
#include "includes/legacy_structural_app_vars.h"  //TODO: must be removed eventually

#include "custom_utilities/statistics_record.h"
#include "custom_utilities/statistics_data.h"

namespace Kratos
{
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, int,PATCH_INDEX)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,TAUONE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,TAUTWO)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,PRESSURE_MASSMATRIX_COEFFICIENT)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,SUBSCALE_PRESSURE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,C_DES)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,CHARACTERISTIC_VELOCITY)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, SUBSCALE_VELOCITY)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, COARSE_VELOCITY)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,FIC_BETA)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Vector, FLUID_STRESS )
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, DIVERGENCE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, AUX_DISTANCE)

// Adjoint variables
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, ADJOINT_FLUID_VECTOR_1 )
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, ADJOINT_FLUID_VECTOR_2 )
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, ADJOINT_FLUID_VECTOR_3 )
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, AUX_ADJOINT_FLUID_VECTOR_1 )
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, ADJOINT_FLUID_SCALAR_1 )

// Non-Newtonian constitutive relations
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, REGULARIZATION_COEFFICIENT)

// To be removed
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, BINGHAM_SMOOTHER)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, GEL_STRENGTH)

// Q-Criterion (for vortex visualization)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,Q_VALUE)

// Vorticity
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,VORTICITY_MAGNITUDE)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS(FLUID_DYNAMICS_APPLICATION, RECOVERED_PRESSURE_GRADIENT)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Vector,NODAL_WEIGHTS)

// Embedded fluid variables
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, int, EMBEDDED_IS_ACTIVE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, SLIP_LENGTH)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, PENALTY_COEFFICIENT)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, EMBEDDED_WET_PRESSURE)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, EMBEDDED_WET_VELOCITY)

// Compressible fluid variable
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, HEAT_CAPACITY_RATIO)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, REACTION_DENSITY)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, REACTION_ENERGY)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, MACH)

// Turbulence statistics
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, StatisticsRecord::Pointer, STATISTICS_CONTAINER)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, StatisticsData, TURBULENCE_STATISTICS_DATA)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, UPDATE_STATISTICS )

// Level-set convective velocity
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, CONVECTIVE_VELOCITY)

// Curvature
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, CURVATURE);

// Smoothing surface auxiliary distance
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, DISTANCE_AUX)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, DISTANCE_AUX2) //For re-distancing
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, DISTANCE_GRADIENT_AUX)

// Parallel levelset distance calculator needs an AREA_VARIABLE_AUX
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, AREA_VARIABLE_AUX)

// A variable to check if node is on cut element (maybe in a layer farther for future!)
//KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, IS_NEAR_CUT)

// Contact line calculation
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, NORMAL_VECTOR)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, TANGENT_VECTOR)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, CONTACT_VECTOR)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, CONTACT_ANGLE)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, CONTACT_VECTOR_MICRO)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, CONTACT_ANGLE_MICRO)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, CONTACT_VELOCITY)

// Enriched pressure is an array of NumNodes components defined for elements. Access it using Element.GetValue()
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, ENRICHED_PRESSURE_1)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, ENRICHED_PRESSURE_2)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, ENRICHED_PRESSURE_3)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, ENRICHED_PRESSURE_4)

// Last known velocity and pressure to recalculate the last increment
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, VELOCITY_STAR)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, PRESSURE_STAR)

// Pressure gradient to calculate its jump over interface
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, PRESSURE_GRADIENT_AUX)
}

#endif	/* KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED */
