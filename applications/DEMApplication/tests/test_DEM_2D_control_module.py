import os
import KratosMultiphysics
from KratosMultiphysics import Logger
Logger.GetDefaultOutput().SetSeverity(Logger.Severity.WARNING)
import KratosMultiphysics.DEMApplication as DEM
import KratosMultiphysics.KratosUnittest as KratosUnittest
from KratosMultiphysics.DEMApplication.sp_2d_rigid_fem_algorithm import DEMAnalysisStage2DSpRigidFem

import KratosMultiphysics.kratos_utilities as kratos_utils

this_working_dir_backup = os.getcwd()

def GetFilePath(fileName):
    return os.path.join(os.path.dirname(os.path.realpath(__file__)), fileName)

def CreateAndRunStageInOneOpenMPThread(my_obj, model, parameters_file_name):

    # os.environ['OMP_NUM_THREADS']='1'
    # os.system("echo Unittest will be running on $OMP_NUM_THREADS cpu")

    omp_utils = KratosMultiphysics.OpenMPUtils()
    if "OMP_NUM_THREADS" in os.environ:
        initial_number_of_threads = os.environ['OMP_NUM_THREADS']
        omp_utils.SetNumThreads(1)

    with open(parameters_file_name,'r') as parameter_file:
        project_parameters = KratosMultiphysics.Parameters(parameter_file.read())

    my_obj(model, project_parameters).Run()

    if "OMP_NUM_THREADS" in os.environ:
        omp_utils.SetNumThreads(int(initial_number_of_threads))



class DEM2D_ControlModuleTestSolution(DEMAnalysisStage2DSpRigidFem):

    @classmethod
    def GetMainPath(self):
        return os.path.join(os.path.dirname(os.path.realpath(__file__)), "DEM2D_control_module_tests_files")

    def GetProblemNameWithPath(self):
        return os.path.join(self.main_path, self.DEM_parameters["problem_name"].GetString())

    def __init__(self, model, project_parameters):
        super(DEMAnalysisStage2DSpRigidFem, self).__init__(model, project_parameters)

        path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "DEM2D_control_module_tests_files")
        sp_project_parameters_file_name = os.path.join(path, "sp_2d_rigid_fem_parameters.json")

        with open(sp_project_parameters_file_name,'r') as parameters_file:
            self.sp_project_parameters = KratosMultiphysics.Parameters(parameters_file.read())

        # TEST NUMBER:
        # 1. CTW16, 2. CTW10, 3. CTW13, 4. CTW12, 5.Blind
        self.test_number = self.sp_project_parameters["test_number"].GetInt()
        self.inner_mesh_diameter = self.sp_project_parameters["inner_mesh_diameter"].GetDouble() # This depends on the particular GiD mesh (diameter of the finer mesh)
        self.outer_mesh_diameter = self.sp_project_parameters["outer_mesh_diameter"].GetDouble() # This depends on the particular GiD mesh (diameter of the coarser mesh)
        # The two values that follow may depend on the GiD mesh used. The higher the value, the more skin particles
        self.inner_skin_factor = self.sp_project_parameters["inner_skin_factor"].GetDouble() # 2.4
        self.outer_skin_factor = self.sp_project_parameters["outer_skin_factor"].GetDouble() # 0.8
        self.respect_preprocessor_marked_skin = self.sp_project_parameters["respect_preprocessor_marked_skin"].GetBool()

        self.automatic_skin_computation = project_parameters["AutomaticSkinComputation"].GetBool()

    def Initialize(self):
        super(DEMAnalysisStage2DSpRigidFem, self).Initialize()

        from KratosMultiphysics.DEMApplication.multiaxial_control_module_generalized_2d_utility import MultiaxialControlModuleGeneralized2DUtility
        self.multiaxial_control_module = MultiaxialControlModuleGeneralized2DUtility(self.model, self.sp_project_parameters)
        self.multiaxial_control_module.ExecuteInitialize()

    def PrintResultsForGid(self, time):
        super(DEMAnalysisStage2DSpRigidFem, self).PrintResultsForGid(time)

        self.multiaxial_control_module.PrintResults()

    def Finalize(self):
        tolerance = 1.001
        for node in self.rigid_face_model_part.Nodes:
            if node.Id == 5:
                node_force_x = node.GetSolutionStepValue(DEM.CONTACT_FORCES_X)
                print(node_force_x)
                expected_value = 316.79
                self.CheckForceX(node_force_x, expected_value, tolerance)
            elif node.Id == 6:
                node_force_y = node.GetSolutionStepValue(DEM.CONTACT_FORCES_Y)
                print(node_force_y)
                expected_value = 150.1
                self.CheckForceY(node_force_y, expected_value, tolerance)

        super(DEM2D_ControlModuleTestSolution, self).Finalize()

    @classmethod
    def CheckForceX(self, force, expected_value, tolerance):
        if abs(expected_value) > abs(force*tolerance) or abs(expected_value) < abs(force/tolerance):
            raise ValueError('Incorrect value for CONTACT_FORCES_X: expected value was '+ str(expected_value) + ' but received ' + str(force))

    @classmethod
    def CheckForceY(self, force, expected_value, tolerance):
        if abs(expected_value) > abs(force*tolerance) or abs(expected_value) < abs(force/tolerance):
            raise ValueError('Incorrect value for CONTACT_FORCES_Y: expected value was '+ str(expected_value) + ' but received ' + str(force))


class TestDEM2DControlModule(KratosUnittest.TestCase):

    def setUp(self):
        pass

    @classmethod
    def test_DEM2D_control_module(self):
        path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "DEM2D_control_module_tests_files")
        parameters_file_name = os.path.join(path, "ProjectParametersDEM.json")
        model = KratosMultiphysics.Model()
        CreateAndRunStageInOneOpenMPThread(DEM2D_ControlModuleTestSolution, model, parameters_file_name)

    def tearDown(self):
        file_to_remove = os.path.join("DEM2D_control_module_tests_files", "TimesPartialRelease")
        kratos_utils.DeleteFileIfExisting(GetFilePath(file_to_remove))
        os.chdir(this_working_dir_backup)


if __name__ == "__main__":
    Logger.GetDefaultOutput().SetSeverity(Logger.Severity.WARNING)
    KratosUnittest.main()
