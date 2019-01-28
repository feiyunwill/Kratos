#ifndef KRATOS_UNV_OUTPUT_H_INCLUDED
#define KRATOS_UNV_OUTPUT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <includes/model_part.h>
#include "includes/exception.h"

namespace Kratos {


class UnvOutput {
public:
    
    enum class DatasetLocation {
        DATA_AT_NODES               = 1,
        DATA_AT_ELEMENTS            = 2,
        DATA_AT_NODES_ON_ELEMENTS   = 3,
        DATA_AT_POINTS              = 5,
        DATA_ON_ELEMENTS_AT_NODES   = 6
    };

    enum class ModelType {
        UNKNOWN         = 0,
        STRUCTURAL      = 1,
        HEAT_TRANSFER   = 2,
        FLUID_FLOW      = 3
    };

    enum class AnalysisType {
        UNKNOWN                             = 0,
        STATIC                              = 1,
        NORMAL_MODE                         = 2,
        COMPLEX_EIGENVALUE_FIRST_ORDER      = 3,
        TRANSIENT                           = 4,
        FREQUENCY_RESPONSE                  = 5,
        BUCKLING                            = 6,
        COMPLEX_EIGENVALUE_SECOND_ORDER     = 7,
        STATIC_NON_LINEAR                   = 9,
        CRAIG_BAMPTON_CONSTRAINT_MODES      = 10,
        EQUIVALENT_ATTACHMENT_MODES         = 11,
        EFFECTIVE_MASS_MODES                = 12,
        EFFECTIVE_MASS_MATRIX               = 13,
        EFFECTIVE_MASS_MATRIX_COPY          = 14,   // This record is duplicared intentionally
        DISTRIBUTED_LOAD_LOAD_DISTRIBUTION  = 15,
        DISTRIBUTED_LOAD_ATTACHMENT_MODES   = 16
    };

    // 3_DOF_* Records have their name changed to D3_DOF to avoid conflicts.
    enum class DataCharacteristics {
        UNKNOWN = 0,
        SCALAR = 1,
        D3_DOF_GLOBAL_TRANSLATION_VECTOR = 2,
        D3_DOF_GLOBAL_TRANSLATION_ROTATION_VECTOR = 3,
        SYMMETRIC_GLOBAL_TENSOR = 4,
        STRESS_RESULTANTS = 6
    };

    // This record is to big, I will consider moving these enums to another file.
    // enum class ResultType {

    // };

    enum class DataType {
        INTEGER = 1,
        SINGLE_PRECISION_FLOATING_POINT = 2,
        DOUBLE_PRECISION_FLOATING_POINT = 4,
        SINGLE_PRECISION_COMPLEX = 5,
        DOUBLE_PRECISION_COMPLEX = 6
    };

    KRATOS_CLASS_POINTER_DEFINITION(UnvOutput);

    template <typename Enumeration>
    auto as_integer(Enumeration const value)
        -> typename std::underlying_type<Enumeration>::type
    {
        return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    }

    UnvOutput(Kratos::ModelPart &modelPart, const std::string &outFileWithoutExtension);


    void InitializeOutputFile();

    void WriteMesh();
    void WriteNodes();
    void WriteElements();
    void WriteResult();

    void WriteNodalResults(const Variable<bool>& rVariable);
    void WriteNodalResults(const Variable<int>& rVariable);
    void WriteNodalResults(const Variable<double>& rVariable);
    void WriteNodalResults(const Variable<array_1d<double,3>>& rVariable);
    void WriteNodalResults(const Variable<Vector>& rVariable);
    void WriteNodalResults(const Variable<Matrix>& rVariable);

    // Partially extracted from: http://users.ices.utexas.edu
    // # beginning of dataset
    // # type of dataset: data at mesh entities
    // # R.  1: unique number of dataset (dataset_label)
    // # R.  2: text describing content (dataset_name)
    // # R.  3: data belongs to: nodes, elements,...
    // #        (dataset_location)
    // # R.  4: user-specified text (id_lines_1_to_5[0])
    // # R.  5: user-specified text (id_lines_1_to_5[1])
    // # R.  6: user-specified text (id_lines_1_to_5[2])
    // # R.  7: user-specified text (id_lines_1_to_5[3])
    // # R.  8: user-specified text (id_lines_1_to_5[4])
    // # R.  9: (model_type) (analysis_type)
    // #        (data_characteristic) (result_type)
    // #        (data_type) (nvaldc)
    // # R. 10: analysis-specific data (record_10)
    // # R. 11: analysis-specific data (record_11)
    // # R. 12: analysis-specific data (record_12)
    // # R. 13: analysis-specific data (record_13)

    void WriteNodalResultValues(const std::ofstream &outputFile, const Node<3>& node, const Variable<bool>& rVariable);
    void WriteNodalResultValues(const std::ofstream &outputFile, const Node<3>& node, const Variable<int>& rVariable);
    void WriteNodalResultValues(const std::ofstream &outputFile, const Node<3>& node, const Variable<double>& rVariable);
    void WriteNodalResultValues(const std::ofstream &outputFile, const Node<3>& node, const Variable<array_1d<double,3>>& rVariable);
    void WriteNodalResultValues(const std::ofstream &outputFile, const Node<3>& node, const Variable<Vector>& rVariable);
    void WriteNodalResultValues(const std::ofstream &outputFile, const Node<3>& node, const Variable<Matrix>& rVariable);

    template<class TVariablebleType>
    void WriteNodalResults(const TVariablebleType rVariable, const int numComponents, const int timeStep) {
        std::ofstream outputFile;
        outputFile.open(mOutputFileName, std::ios::out | std::ios::app);

        const int dataSetNumberForResults = 2414;
        std::string dataSetName = "NodalResults";
        std::string dataSetLabel = rVariable.Name() + timeStep;

        outputFile << std::setw(6)  << "-1" << "\n";                                                // Begin block
        outputFile << std::setw(6)  << dataSetNumberForResults << "\n";                             // DatasetID

        outputFile << std::setw(10) << dataSetLabel << "\n";                                        // Record 1 - Label
        outputFile << std::setw(6)  << dataSetName << "\n";                                         // Record 2 - Name
        outputFile << std::setw(10) << as_integer(DatasetLocation::DATA_AT_NODES) << "\n";          // Record 3

        // String records, seems like you can put anything you want.
        outputFile << "" << "\n";                                                                   // Record 4
        outputFile << "NONE" << "\n";                                                               // Record 5
        outputFile << "NONE" << "\n";                                                               // Record 6
        outputFile << "NONE" << "\n";                                                               // Record 7
        outputFile << "NONE" << "\n";                                                               // Record 8
        
        // ModelType, AnalysisType, DataCharacteristic, ResultType, DataType, NumberOfDataValues    // Record 9
        outputFile << std::setw(10) << as_integer(ModelType::STRUCTURAL); 
        outputFile << std::setw(10) << as_integer(AnalysisType::STATIC);
        outputFile << std::setw(10) << as_integer(DataCharacteristics::SCALAR);
        outputFile << std::setw(10) << 5;
        outputFile << std::setw(10) << as_integer(DataType::SINGLE_PRECISION_FLOATING_POINT);
        outputFile << std::setw(10) << numComponents; 
        outputFile << "\n";

        // ????
        outputFile << std::setw(10) << 0;                                                           // Record 10
        outputFile << std::setw(10) << 0;
        outputFile << std::setw(10) << 0;
        outputFile << std::setw(10) << 0;
        outputFile << std::setw(10) << 0;
        outputFile << std::setw(10) << 1;
        outputFile << std::setw(10) << 0;
        outputFile << std::setw(10) << 0;
        outputFile << "\n";

        outputFile << std::setw(10) << 0;                                                           // Record 11
        outputFile << std::setw(10) << 0;
        outputFile << "\n";

        outputFile << std::setw(13) << "0.00000E+00";                                               // Record 12
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << "\n";

        outputFile << std::setw(13) << "0.00000E+00";                                               // Record 13
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << std::setw(13) << "0.00000E+00";
        outputFile << "\n";

        // Data at nodes:
        for (auto &node_i : mrOutputModelPart.Nodes()) {
            int node_label = node_i.Id();
            outputFile << std::setw(6) << node_label << "\n";                                       // Record 14 - Node Number
            outputFile << std::setw(6) << node_i.FastGetSolutionStepValue(TEMPERATURE) << "\n";     // Record 15 - NumberOfDataValues' data of the node
        }
        
        outputFile << std::setw(6) << "-1" << "\n";
        outputFile.close();
    }

private:
    Kratos::ModelPart &mrOutputModelPart;
    std::string mOutputFileName;
};
}

#endif //KRATOS_UNV_OUTPUT_H_INCLUDED
