from __future__ import absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

# Importing the Kratos Library
import KratosMultiphysics

# Import applications
import KratosMultiphysics.FluidDynamicsApplication as KratosCFD
from KratosMultiphysics.FluidDynamicsApplication import navier_stokes_solver_vmsmonolithic as NavierMonolithic
import KratosMultiphysics.SwimmingDEMApplication as KratosSDEM

# Import base class file
from KratosMultiphysics.SwimmingDEMApplication.fluid_DEM_coupling_solver import FluidDEMSolver

class StabilizedFormulationDEMCoupled(NavierMonolithic.StabilizedFormulation):
    """Helper class to define stabilization-dependent parameters."""
    def __init__(self, settings):
        super(StabilizedFormulationDEMCoupled, self).__init__(settings)
        if settings.Has("element_type"):
            formulation = settings["element_type"].GetString()
            if formulation == "qsvmsDEM":
                self._SetUpQSVMSDEM(settings)
            if formulation == "MonolithicDEM":
                self._SetUpVMSDEM(settings)

    def _SetUpQSVMSDEM(self,settings):
        default_settings = KratosMultiphysics.Parameters(r"""{
            "element_type": "qsvmsDEM",
            "use_orthogonal_subscales": false,
            "dynamic_tau": 0.01,
            "element_name": "QSVMSDEMCoupled"
        }""")
        settings.ValidateAndAssignDefaults(default_settings)

        self.element_name = settings["element_name"].GetString()
        self.element_has_nodal_properties = True
        
        self.process_data[KratosMultiphysics.DYNAMIC_TAU] = settings["dynamic_tau"].GetDouble()
        use_oss = settings["use_orthogonal_subscales"].GetBool()
        self.process_data[KratosMultiphysics.OSS_SWITCH] = int(use_oss)

    def _SetUpVMSDEM(self,settings):
        default_settings = KratosMultiphysics.Parameters(r"""{
            "element_type": "MonolithicDEM",
            "use_orthogonal_subscales": false,
            "dynamic_tau": 0.01,
            "element_name": "MonolithicDEMCoupled"
        }""")
        settings.ValidateAndAssignDefaults(default_settings)

        self.element_name = settings["element_name"].GetString()
        self.element_has_nodal_properties = True

        self.process_data[KratosMultiphysics.DYNAMIC_TAU] = settings["dynamic_tau"].GetDouble()
        use_oss = settings["use_orthogonal_subscales"].GetBool()
        self.process_data[KratosMultiphysics.OSS_SWITCH] = int(use_oss)

def CreateSolver(model, custom_settings):
    return NavierStokesSolverMonolithicDEM(model, custom_settings)

class NavierStokesSolverMonolithicDEM(FluidDEMSolver):

    @classmethod
    def GetDefaultSettings(cls):

        ##settings string in json format
        default_settings = KratosMultiphysics.Parameters("""
        {
            "solver_type": "MonolithicDEM",
            "model_part_name": "FluidModelPart",
            "domain_size": -1,
            "model_import_settings": {
                "input_type": "mdpa",
                "input_filename": "unknown_name",
                "reorder": false
            },
            "material_import_settings": {
                "materials_filename": "unknown_materials.json"
            },
            "formulation": {
                "element_type": "vms"
            },
            "maximum_iterations": 10,
            "echo_level": 0,
            "consider_periodic_conditions": false,
            "compute_reactions": false,
            "reform_dofs_at_each_step": true,
            "relative_velocity_tolerance": 1e-3,
            "absolute_velocity_tolerance": 1e-5,
            "relative_pressure_tolerance": 1e-3,
            "absolute_pressure_tolerance": 1e-5,
            "linear_solver_settings"        : {
                "solver_type" : "amgcl"
            },
            "volume_model_part_name" : "volume_model_part",
            "skin_parts": [""],
            "assign_neighbour_elements_to_conditions": false,
            "no_skin_parts":[""],
            "time_stepping"                : {
                "automatic_time_step" : false,
                "CFL_number"          : 1,
                "minimum_delta_time"  : 1e-4,
                "maximum_delta_time"  : 0.01,
                "time_step"           : 0.0
            },
            "time_scheme":"bossak",
            "alpha":-0.3,
            "velocity_relaxation":0.9,
            "pressure_relaxation":0.9,
            "move_mesh_strategy": 0,
            "periodic": "periodic",
            "move_mesh_flag": false,
            "turbulence_model": "None"
        }""")

        default_settings.AddMissingParameters(super(NavierStokesSolverMonolithicDEM, cls).GetDefaultSettings())
        return default_settings

    def _BackwardsCompatibilityHelper(self,settings):
        ## Backwards compatibility -- deprecation warnings
        if settings.Has("stabilization"):
            msg  = "Input JSON data contains deprecated setting \'stabilization\'.\n"
            msg += "Please rename it to \'formulation\' (and rename \'stabilization/formulation\' to \'formulation/element_type\' if it exists).\n"
            KratosMultiphysics.Logger.PrintWarning("NavierStokesVMSMonolithicSolver",msg)
            settings.AddValue("formulation", settings["stabilization"])
            settings.RemoveValue("stabilization")
            settings["formulation"].AddValue("element_type", settings["formulation"]["formulation"])
            settings["formulation"].RemoveValue("formulation")

        if settings.Has("oss_switch"):
            msg  = "Input JSON data contains deprecated setting \'oss_switch\' (int).\n"
            msg += "Please define \'formulation/element_type\' (set it to \'vms\')\n"
            msg += "and set \'formulation/use_orthogonal_subscales\' (bool) instead."
            KratosMultiphysics.Logger.PrintWarning("NavierStokesVMSMonolithicSolver",msg)
            if not settings.Has("formulation"):
                settings.AddValue("formulation",KratosMultiphysics.Parameters(r'{"element_type":"vms"}'))
            settings["formulation"].AddEmptyValue("use_orthogonal_subscales")
            settings["formulation"]["use_orthogonal_subscales"].SetBool(bool(settings["oss_switch"].GetInt()))
            settings.RemoveValue("oss_switch")
        if settings.Has("dynamic_tau"):
            msg  = "Input JSON data contains deprecated setting \'dynamic_tau\' (float).\n"
            msg += "Please define \'formulation/element_type\' (set it to \'vms\') and \n"
            msg += "set \'formulation/dynamic_tau\' (float) instead."
            KratosMultiphysics.Logger.PrintWarning("NavierStokesVMSMonolithicSolver",msg)
            if not settings.Has("formulation"):
                settings.AddValue("formulation",KratosMultiphysics.Parameters(r'{"element_type":"vms"}'))
            settings["formulation"].AddEmptyValue("dynamic_tau")
            settings["formulation"]["dynamic_tau"].SetDouble(settings["dynamic_tau"].GetDouble())
            settings.RemoveValue("dynamic_tau")
        return settings


    def __init__(self, model, custom_settings):

        self._validate_settings_in_baseclass=True
        custom_settings = self._BackwardsCompatibilityHelper(custom_settings)

        super(NavierStokesSolverMonolithicDEM,self).__init__(model, custom_settings)

        self.formulation = StabilizedFormulationDEMCoupled(self.settings["formulation"])
        self.AddVariables()
        self.element_name = self.formulation.element_name
        self.condition_name = self.formulation.condition_name
        self.element_integrates_in_time = self.formulation.element_integrates_in_time
        self.element_has_nodal_properties = self.formulation.element_has_nodal_properties

        scheme_type = self.settings["time_scheme"].GetString()
        if scheme_type == "bossak":
            self.min_buffer_size = 2
        elif scheme_type == "bdf2":
            self.min_buffer_size = 3
        elif scheme_type == "steady":
            self.min_buffer_size = 1
            self._SetUpSteadySimulation()
        else:
            msg  = "Unknown time_scheme option found in project parameters:\n"
            msg += "\"" + scheme_type + "\"\n"
            msg += "Accepted values are \"bossak\", \"bdf2\" or \"steady\".\n"
            raise Exception(msg)

        ## Construct the linear solver
        import KratosMultiphysics.python_linear_solver_factory as linear_solver_factory
        self.linear_solver = linear_solver_factory.ConstructSolver(self.settings["linear_solver_settings"])

        KratosMultiphysics.Logger.PrintInfo("NavierStokesSolverMonolithicDEM", "Construction of NavierStokesSolverMonolithicDEM finished.")


    def AddVariables(self):
        ## Add base class variables
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.VELOCITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.ACCELERATION)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.MESH_VELOCITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.PRESSURE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.IS_STRUCTURE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DISPLACEMENT)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DYNAMIC_VISCOSITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.VISCOSITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DENSITY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.C_SMAGORINSKY)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.BODY_FORCE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.NODAL_AREA)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.NODAL_H)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.ADVPROJ)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DIVPROJ)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.REACTION)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.REACTION_WATER_PRESSURE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.EXTERNAL_PRESSURE)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.NORMAL)
        self.main_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.Y_WALL)
        self.main_model_part.AddNodalSolutionStepVariable(KratosCFD.Q_VALUE)
        if self.settings["consider_periodic_conditions"].GetBool() == True:
            self.main_model_part.AddNodalSolutionStepVariable(KratosCFD.PATCH_INDEX)

        KratosMultiphysics.Logger.PrintInfo("NavierStokesSolverMonolithicDEM", "Fluid solver variables added correctly.")

    def AddDofs(self):
        super(NavierStokesSolverMonolithicDEM, self).AddDofs()

    def PrepareModelPart(self):
        if not self.main_model_part.ProcessInfo[KratosMultiphysics.IS_RESTARTED]:
            self._set_physical_properties()
        super(NavierStokesSolverMonolithicDEM, self).PrepareModelPart()

    def Initialize(self):

        self.computing_model_part = self.GetComputingModelPart()

        # If needed, create the estimate time step utility
        if (self.settings["time_stepping"]["automatic_time_step"].GetBool()):
            self.EstimateDeltaTimeUtility = self._GetAutomaticTimeSteppingUtility()

        # Creating the solution strategy
        self.conv_criteria = KratosCFD.VelPrCriteria(self.settings["relative_velocity_tolerance"].GetDouble(),
                                                    self.settings["absolute_velocity_tolerance"].GetDouble(),
                                                    self.settings["relative_pressure_tolerance"].GetDouble(),
                                                    self.settings["absolute_pressure_tolerance"].GetDouble())

        (self.conv_criteria).SetEchoLevel(self.settings["echo_level"].GetInt())

        # Creating the time integration scheme
        if (self.element_integrates_in_time):
            # "Fake" scheme for those cases in where the element manages the time integration
            # It is required to perform the nodal update once the current time step is solved
            self.time_scheme = KratosMultiphysics.ResidualBasedIncrementalUpdateStaticSchemeSlip(
                self.computing_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE],
                self.computing_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE]+1)
            # In case the BDF2 scheme is used inside the element, the BDF process is required to update the BDF coefficients
            if (self.settings["time_scheme"].GetString() == "bdf2"):
                time_order = 2
                self.bdf_process = KratosMultiphysics.ComputeBDFCoefficientsProcess(self.computing_model_part, time_order)
            else:
                err_msg = "Requested elemental time scheme " + self.settings["time_scheme"].GetString() + " is not available.\n"
                err_msg += "Available options are: \"bdf2\""
                raise Exception(err_msg)
        else:
            if self.settings["turbulence_model"].GetString() == "None":
                # Bossak time integration scheme
                if self.settings["time_scheme"].GetString() == "bossak":
                    if self.settings["consider_periodic_conditions"].GetBool() == True:
                        self.time_scheme = KratosSDEM.ResidualBasedPredictorCorrectorVelocityBossakSchemeTurbulentDEMCoupled(
                            self.settings["alpha"].GetDouble(),
                            self.computing_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE],
                            KratosCFD.PATCH_INDEX)
                    else:
                        self.time_scheme = KratosSDEM.ResidualBasedPredictorCorrectorVelocityBossakSchemeTurbulentDEMCoupled(
                            self.settings["alpha"].GetDouble(),
                            self.settings["move_mesh_strategy"].GetInt(),
                            self.computing_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE])
                # BDF2 time integration scheme
                elif self.settings["time_scheme"].GetString() == "bdf2":
                    self.time_scheme = KratosCFD.GearScheme()
                # Time scheme for steady state fluid solver
                elif self.settings["time_scheme"].GetString() == "steady":
                    self.time_scheme = KratosCFD.ResidualBasedSimpleSteadyScheme(
                            self.settings["velocity_relaxation"].GetDouble(),
                            self.settings["pressure_relaxation"].GetDouble(),
                            self.computing_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE])
                else:
                    err_msg = "Requested time scheme " + self.settings["time_scheme"].GetString() + " is not available.\n"
                    err_msg += "Available options are: \"bossak\", \"bdf2\" and \"steady\""
                    raise Exception(err_msg)
            else:
                raise Exception("Turbulence models are not added yet.")

        if self.settings["consider_periodic_conditions"].GetBool() == True:
            builder_and_solver = KratosCFD.ResidualBasedBlockBuilderAndSolverPeriodic(self.linear_solver,
                                                                                KratosCFD.PATCH_INDEX)
        else:
            builder_and_solver = KratosMultiphysics.ResidualBasedBlockBuilderAndSolver(self.linear_solver)


        self.solver = KratosMultiphysics.ResidualBasedNewtonRaphsonStrategy(self.computing_model_part,
                                                                            self.time_scheme,
                                                                            self.linear_solver,
                                                                            self.conv_criteria,
                                                                            builder_and_solver,
                                                                            self.settings["maximum_iterations"].GetInt(),
                                                                            self.settings["compute_reactions"].GetBool(),
                                                                            self.settings["reform_dofs_at_each_step"].GetBool(),
                                                                            self.settings["move_mesh_flag"].GetBool())

        (self.solver).SetEchoLevel(self.settings["echo_level"].GetInt())

        self.formulation.SetProcessInfo(self.computing_model_part)

        (self.solver).Initialize()

        KratosMultiphysics.Logger.PrintInfo("NavierStokesSolverMonolithicDEM", "Solver initialization finished.")

    def InitializeSolutionStep(self):
        if self._TimeBufferIsInitialized():
            # If required, compute the BDF coefficients
            if hasattr(self, 'bdf_process'):
                (self.bdf_process).Execute()
            # Perform the solver InitializeSolutionStep
            (self.solver).InitializeSolutionStep()

    def _set_physical_properties(self):
        # Check if fluid properties are provided using a .json file
        materials_filename = self.settings["material_import_settings"]["materials_filename"].GetString()
        if (materials_filename != ""):
            # Add constitutive laws and material properties from .json file to model parts
            material_settings = KratosMultiphysics.Parameters("""{"Parameters": {"materials_filename": ""}} """)
            material_settings["Parameters"]["materials_filename"].SetString(materials_filename)
            KratosMultiphysics.ReadMaterialsUtility(material_settings, self.model)

            if self.element_has_nodal_properties:
                self._SetNodalProperties()
        
        else:
            # Get density and dynamic viscostity from the properties and transfer them to the nodes
            for el in self.main_model_part.Elements:
                rho = el.Properties.GetValue(KratosMultiphysics.DENSITY)
                if rho <= 0.0:
                    raise Exception("DENSITY set to {0} in Properties {1}, positive number expected.".format(rho,el.Properties.Id))
                dyn_viscosity = el.Properties.GetValue(KratosMultiphysics.DYNAMIC_VISCOSITY)
                if dyn_viscosity <= 0.0:
                    raise Exception("DYNAMIC_VISCOSITY set to {0} in Properties {1}, positive number expected.".format(dyn_viscosity,el.Properties.Id))
                kin_viscosity = dyn_viscosity / rho
                break
            else:
                raise Exception("No fluid elements found in the main model part.")

            KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.DENSITY, rho, self.main_model_part.Nodes)
            KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.DYNAMIC_VISCOSITY, dyn_viscosity, self.main_model_part.Nodes)
            KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.VISCOSITY, kin_viscosity, self.main_model_part.Nodes)

    def _SetNodalProperties(self):
        for el in self.main_model_part.Elements:
            rho = el.Properties.GetValue(KratosMultiphysics.DENSITY)
            if rho <= 0.0:
                raise Exception("DENSITY set to {0} in Properties {1}, positive number expected.".format(rho,el.Properties.Id))
            dyn_viscosity = el.Properties.GetValue(KratosMultiphysics.DYNAMIC_VISCOSITY)
            if dyn_viscosity <= 0.0:
                raise Exception("DYNAMIC_VISCOSITY set to {0} in Properties {1}, positive number expected.".format(dyn_viscosity,el.Properties.Id))
            kin_viscosity = dyn_viscosity / rho
            break
        else:
            raise Exception("No fluid elements found in the main model part.")
        # Transfer the obtained properties to the nodes
        KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.DENSITY, rho, self.main_model_part.Nodes)
        KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.DYNAMIC_VISCOSITY, dyn_viscosity, self.main_model_part.Nodes)
        KratosMultiphysics.VariableUtils().SetScalarVar(KratosMultiphysics.VISCOSITY, kin_viscosity, self.main_model_part.Nodes)

    def _SetUpSteadySimulation(self):
        '''Overwrite time stepping parameters so that they do not interfere with steady state simulations.'''
        self.settings["time_stepping"]["automatic_time_step"].SetBool(False)
        if self.settings["formulation"].Has("dynamic_tau"):
            self.settings["formulation"]["dynamic_tau"].SetDouble(0.0)