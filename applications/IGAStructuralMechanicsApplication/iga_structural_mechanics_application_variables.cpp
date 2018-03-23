#include "iga_structural_mechanics_application_variables.h"

namespace Kratos
{
	//
	KRATOS_CREATE_VARIABLE(double, INTEGRATION_WEIGHT)
	//Values of Shapefunctions N
	KRATOS_CREATE_VARIABLE(Vector, SHAPE_FUNCTION_VALUES)
	//Values of Shapefunctionderivatives in local space DN_De
	KRATOS_CREATE_VARIABLE(Matrix, SHAPE_FUNCTION_LOCAL_DERIVATIVES)
	KRATOS_CREATE_VARIABLE(Matrix, SHAPE_FUNCTION_LOCAL_SECOND_DERIVATIVES)

	KRATOS_CREATE_VARIABLE(Vector, SHAPE_FUNCTION_VALUES_SLAVE)
	KRATOS_CREATE_VARIABLE(Matrix, SHAPE_FUNCTION_LOCAL_DERIVATIVES_SLAVE)
	//KRATOS_CREATE_VARIABLE(Matrix, SHAPE_FUNCTION_LOCAL_DERIVATIVES_MASTER)
	//KRATOS_CREATE_VARIABLE(Matrix, SHAPE_FUNCTION_LOCAL_DERIVATIVES_SLAVE)

	KRATOS_CREATE_VARIABLE(double, PENALTY_FACTOR)
	KRATOS_CREATE_VARIABLE(Vector, TANGENTS)
	KRATOS_CREATE_VARIABLE(Vector, TANGENTS_SLAVE)

	KRATOS_CREATE_VARIABLE(int, DISPLACEMENT_ROTATION_FIX)
	KRATOS_CREATE_VARIABLE(int, LOAD_TYPE)

	//KRATOS_CREATE_VARIABLE(std::string, CONDITION_TYPE_DEFINITION)
	KRATOS_CREATE_VARIABLE(double, DISTRIBUTED_LOAD_FACTOR)

	// for damage constitutive law
	KRATOS_CREATE_VARIABLE(Vector, GAP_INTERFACE)
	KRATOS_CREATE_VARIABLE(double, CONVECTION_DEGRADATION)
	KRATOS_CREATE_VARIABLE(int, EXPONENTIAL_DAMAGE)

	KRATOS_CREATE_VARIABLE(double, DAMAGE_T_INTERFACE)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_C_INTERFACE)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_T)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_T_INSIDE)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_T_OUTSIDE)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_C)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_C_INSIDE)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_C_OUTSIDE)
	KRATOS_CREATE_VARIABLE(double, FRACTURE_ENERGY_T)
	KRATOS_CREATE_VARIABLE(double, FRACTURE_ENERGY_C)
	KRATOS_CREATE_VARIABLE(double, YIELD_STRESS_T)
	KRATOS_CREATE_VARIABLE(double, YIELD_STRESS_C)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_STRESS_T_0)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_STRESS_C_0)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_STRESS_C_P)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_STRESS_C_M)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_STRESS_C_R)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_STRAIN_C_P)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_STRAIN_C_M)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_COMPRESSIVE_LAW_C1)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_COMPRESSIVE_LAW_C2)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_COMPRESSIVE_LAW_C3)
	KRATOS_CREATE_VARIABLE(double, BIAXIAL_COMPRESSION_MULTIPLIER)
	KRATOS_CREATE_VARIABLE(double, SHEAR_COMPRESSION_REDUCTION)
	KRATOS_CREATE_VARIABLE(double, DAMAGE_TENSILE_SURFACE_S1)
	KRATOS_CREATE_VARIABLE(double, LUBLINER_SURFACE_PARAM_KC)
	KRATOS_CREATE_VARIABLE(double, GENRANKINE_SURFACE_PARAM_A)
	KRATOS_CREATE_VARIABLE(double, GENRANKINE_SURFACE_PARAM_B)
	KRATOS_CREATE_VARIABLE(double, GENRANKINE_SURFACE_PARAM_C)
	KRATOS_CREATE_VARIABLE(int, DAMAGE_SECANT_MATRIX)
	KRATOS_CREATE_VARIABLE(int, DAMAGE_MODEL)
	KRATOS_CREATE_VARIABLE(int, DAMAGE_TENSILE_MODEL)
}
