//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    @{KRATOS_APP_AUTHOR}
//

#include "mor_application_variables.h"

namespace Kratos
{
KRATOS_CREATE_VARIABLE( double, FREQUENCY )
KRATOS_CREATE_VARIABLE(int, BUILD_LEVEL)

KRATOS_CREATE_VARIABLE( double, SCALAR_OUTPUT )
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( COMPONENT_OUTPUT)

KRATOS_CREATE_VARIABLE(Vector, EIGENVALUE_VECTOR)
KRATOS_CREATE_VARIABLE(Matrix, EIGENVECTOR_MATRIX)
KRATOS_CREATE_VARIABLE(Vector, REAL_EIGENVALUE_VECTOR)
KRATOS_CREATE_VARIABLE(Matrix, REAL_EIGENVECTOR_MATRIX)
KRATOS_CREATE_VARIABLE(Vector, IMAG_EIGENVALUE_VECTOR)
KRATOS_CREATE_VARIABLE(Matrix, IMAG_EIGENVECTOR_MATRIX)

// complex dof variables
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( REAL_DISPLACEMENT )
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( IMAG_DISPLACEMENT )
KRATOS_CREATE_VARIABLE( double, REAL_PRESSURE )
KRATOS_CREATE_VARIABLE( double, IMAG_PRESSURE )

}
