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

#include "fluid_dynamics_application_variables.h"
#include "custom_utilities/statistics_data.h"
#include "custom_utilities/statistics_record.h"

namespace Kratos
{
KRATOS_CREATE_VARIABLE(int,PATCH_INDEX)
KRATOS_CREATE_VARIABLE(double,TAUONE)
KRATOS_CREATE_VARIABLE(double,TAUTWO)
KRATOS_CREATE_VARIABLE(double,PRESSURE_MASSMATRIX_COEFFICIENT)
KRATOS_CREATE_VARIABLE(Vector, FLUID_STRESS)
KRATOS_CREATE_VARIABLE(Vector, GAPS)
KRATOS_CREATE_VARIABLE(double, DIVERGENCE)
KRATOS_CREATE_VARIABLE(double, AUX_DISTANCE)
KRATOS_CREATE_VARIABLE(double, FS_PRESSURE_GRADIENT_RELAXATION_FACTOR)

//KRATOS_CREATE_VARIABLE(double,Y_WALL)
KRATOS_CREATE_VARIABLE(double,SUBSCALE_PRESSURE)
KRATOS_CREATE_VARIABLE(double, C_DES)
//    KRATOS_CREATE_VARIABLE(double, C_SMAGORINSKY)
KRATOS_CREATE_VARIABLE(double, CHARACTERISTIC_VELOCITY)


KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(SUBSCALE_VELOCITY)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(COARSE_VELOCITY)

KRATOS_CREATE_VARIABLE(double,FIC_BETA)

// Adjoint variables
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(ADJOINT_FLUID_VECTOR_1)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(ADJOINT_FLUID_VECTOR_2)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(ADJOINT_FLUID_VECTOR_3)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(AUX_ADJOINT_FLUID_VECTOR_1)
KRATOS_CREATE_VARIABLE(double, ADJOINT_FLUID_SCALAR_1)

// Non-Newtonian constitutive relations
KRATOS_CREATE_VARIABLE(double, REGULARIZATION_COEFFICIENT)

KRATOS_CREATE_VARIABLE(double, BINGHAM_SMOOTHER)
KRATOS_CREATE_VARIABLE(double, GEL_STRENGTH )

// Q-Criterion (for vortex visualization)
KRATOS_CREATE_VARIABLE(double, Q_VALUE)

// Vorticity
KRATOS_CREATE_VARIABLE(double, VORTICITY_MAGNITUDE)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(RECOVERED_PRESSURE_GRADIENT)

// For swimming DEM
KRATOS_CREATE_VARIABLE(Vector, NODAL_WEIGHTS)

// Embedded fluid variables
KRATOS_CREATE_VARIABLE(int, EMBEDDED_IS_ACTIVE)
KRATOS_CREATE_VARIABLE(double, SLIP_LENGTH)
KRATOS_CREATE_VARIABLE(double, PENALTY_COEFFICIENT)
KRATOS_CREATE_VARIABLE(double, VEL_GRAD_PENALTY_COEFFICIENT)
KRATOS_CREATE_VARIABLE(double, EMBEDDED_WET_PRESSURE)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(EMBEDDED_WET_VELOCITY)

// Compressible fluid variables
KRATOS_CREATE_VARIABLE(bool, DENSITY_PAD)
KRATOS_CREATE_VARIABLE(bool, INTERNAL_ENERGY_PAD)
KRATOS_CREATE_VARIABLE(double, HEAT_CAPACITY_RATIO)
KRATOS_CREATE_VARIABLE(double, REACTION_DENSITY)
KRATOS_CREATE_VARIABLE(double, REACTION_ENERGY)
KRATOS_CREATE_VARIABLE(double, MACH)
KRATOS_CREATE_VARIABLE(double, DENSITY_TIME_DERIVATIVE)
KRATOS_CREATE_VARIABLE(double, TOTAL_ENERGY_TIME_DERIVATIVE)
KRATOS_CREATE_VARIABLE(double, SHOCK_SENSOR)
KRATOS_CREATE_VARIABLE(double, SHOCK_CAPTURING_VISCOSITY)
KRATOS_CREATE_VARIABLE(double, SHOCK_CAPTURING_CONDUCTIVITY)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(DENSITY_GRADIENT)
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(MOMENTUM_TIME_DERIVATIVE)

// Turbulence statistics
KRATOS_CREATE_VARIABLE( StatisticsRecord::Pointer, STATISTICS_CONTAINER)
KRATOS_CREATE_VARIABLE( StatisticsData, TURBULENCE_STATISTICS_DATA)
KRATOS_CREATE_VARIABLE( double, UPDATE_STATISTICS )

// Auxiliary variables
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(DRAG_FORCE_CENTER)
KRATOS_CREATE_VARIABLE( double, SMOOTHING_COEFFICIENT )

}
