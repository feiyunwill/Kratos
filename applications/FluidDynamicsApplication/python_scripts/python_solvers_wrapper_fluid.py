from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import KratosMultiphysics
from importlib import import_module

def CreateSolverByParameters(model, solver_settings, parallelism):

    solver_type = solver_settings["solver_type"].GetString()

    if not solver_settings.Has("time_integration_method"):
        KratosMultiphysics.Logger.PrintWarning("Time integration method was not provided. Setting \'implicit\' as default.")
        solver_settings.AddEmptyValue("time_integration_method").SetString("implicit")
    time_integration_method = solver_settings["time_integration_method"].GetString()

    if solver_type == "ale_fluid":
        # This include NEEDS to be here bcs of its dependencies
        from KratosMultiphysics.FluidDynamicsApplication import navier_stokes_ale_fluid_solver
        return navier_stokes_ale_fluid_solver.CreateSolver(model, solver_settings, parallelism)

    # Solvers for OpenMP parallelism
    if (parallelism == "OpenMP"):
        if time_integration_method == "semiexplicit":
            solver_module_name = "navier_stokes_solver_fractionalstep_semiexplicit"
        elif time_integration_method == "implicit":
            if (solver_type == "Monolithic"):
                solver_module_name = "navier_stokes_solver_vmsmonolithic"

            elif (solver_type == "MonolithicStokes"):
                solver_module_name = "stokes_solver_monolithic"

            elif (solver_type == "FractionalStep"):
                solver_module_name = "navier_stokes_solver_fractionalstep"

            elif (solver_type == "Embedded"):
                solver_module_name = "navier_stokes_embedded_solver"

            elif (solver_type == "Compressible"):
                solver_module_name = "navier_stokes_compressible_solver"

            elif (solver_type == "ConjugateHeatTransfer"):
                solver_module_name = "conjugate_heat_transfer_solver"

            elif (solver_type == "TwoFluids"):
                solver_module_name = "navier_stokes_two_fluids_solver"
            else:
                raise Exception("the requested solver type is not in the python solvers wrapper. Solver type is : " + solver_type)
        else:
            err_msg =  "The requested time integration method {} is not in the Python solvers wrapper\n".format(time_integration_method)
            err_msg += "Available options are: \"explicit\", \"implicit\""
            raise Exception(err_msg)

    # Solvers for MPI parallelism
    elif (parallelism == "MPI"):
        if (solver_type == "Monolithic"):
            solver_module_name = "trilinos_navier_stokes_solver_vmsmonolithic"

        elif (solver_type == "FractionalStep"):
            solver_module_name = "trilinos_navier_stokes_solver_fractionalstep"

        elif (solver_type == "Embedded"):
            solver_module_name = "trilinos_navier_stokes_embedded_solver"

        elif (solver_type == "TwoFluids"):
            solver_module_name = "trilinos_navier_stokes_two_fluids_solver"

        else:
            raise Exception("the requested solver type is not in the python solvers wrapper. Solver type is : " + solver_type)

    else:
        raise Exception("parallelism is neither OpenMP nor MPI")

    module_full = 'KratosMultiphysics.FluidDynamicsApplication.' + solver_module_name
    solver = import_module(module_full).CreateSolver(model, solver_settings)

    return solver

def CreateSolver(model, custom_settings):

    if (type(model) != KratosMultiphysics.Model):
        raise Exception("input is expected to be provided as a Kratos Model object")#

    if (type(custom_settings) != KratosMultiphysics.Parameters):
        raise Exception("input is expected to be provided as a Kratos Parameters object")

    solver_settings = custom_settings["solver_settings"]
    parallelism = custom_settings["problem_data"]["parallel_type"].GetString()

    return CreateSolverByParameters(model, solver_settings, parallelism)
