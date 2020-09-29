from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import KratosMultiphysics
from importlib import import_module

def CreateSolver(model, custom_settings):

    if (type(model) != KratosMultiphysics.Model):
        raise Exception("input is expected to be provided as a Kratos Model object")

    if (type(custom_settings) != KratosMultiphysics.Parameters):
        raise Exception("input is expected to be provided as a Kratos Parameters object")

    parallelism = custom_settings["problem_data"]["parallel_type"].GetString()
    solver_type = custom_settings["solver_settings"]["solver_type"].GetString()

    # Solvers for OpenMP parallelism
    if (parallelism == "OpenMP"):
        if (solver_type == "dynamic" or solver_type == "Dynamic"):
            time_integration_method = custom_settings["solver_settings"]["time_integration_method"].GetString()
            if (time_integration_method == "implicit"):
                solver_module_name = "geomechanics_implicit_dynamic_solver"
            elif ( time_integration_method == "explicit"):
                solver_module_name = "geomechanics_explicit_dynamic_solver"
            else:
                err_msg =  "The requested time integration method \"" + time_integration_method + "\" is not in the python solvers wrapper\n"
                err_msg += "Available options are: \"implicit\", \"explicit\""
                raise Exception(err_msg)

        elif (solver_type == "U_Pw" or solver_type == "geomechanics_U_Pw_solver" or
              solver_type == "TwoPhase" or solver_type == "twoPhase"):
            custom_settings["solver_settings"]["time_stepping"].AddValue("end_time", custom_settings["problem_data"]["end_time"])
            solver_module_name = "geomechanics_U_Pw_solver"

        else:
            err_msg =  "The requested solver type \"" + solver_type + "\" is not in the python solvers wrapper\n"
            err_msg += "Available options are: \"geomechanics_U_Pw_solver\""
            raise Exception(err_msg)

    # Solvers for MPI parallelism
    elif (parallelism == "MPI"):
        if (solver_type == "dynamic" or solver_type == "Dynamic"):
            time_integration_method = custom_settings["solver_settings"]["time_integration_method"].GetString()
            if (time_integration_method == "implicit"):
                solver_module_name = "trilinos_geomechanics_implicit_dynamic_solver"
            else:
                err_msg =  "The requested time integration method \"" + time_integration_method + "\" is not in the python solvers wrapper\n"
                err_msg += "Available options are: \"implicit\""
                raise Exception(err_msg)

        else:
            err_msg =  "The requested solver type \"" + solver_type + "\" is not in the python solvers wrapper\n"
            raise Exception(err_msg)
    else:
        err_msg =  "The requested parallel type \"" + parallelism + "\" is not available!\n"
        err_msg += "Available options are: \"OpenMP\", \"MPI\""
        raise Exception(err_msg)

    # Remove settings that are not needed any more
    custom_settings["solver_settings"].RemoveValue("solver_type")
    custom_settings["solver_settings"].RemoveValue("time_integration_method") # does not throw even if the value is not existing

    module_full_name = 'KratosMultiphysics.GeoMechanicsApplication.' + solver_module_name
    solver = import_module(module_full_name).CreateSolver(model, custom_settings["solver_settings"])

    # solver_module = __import__(solver_module_name)
    # solver = solver_module.CreateSolver(model, custom_settings["solver_settings"])

    return solver
