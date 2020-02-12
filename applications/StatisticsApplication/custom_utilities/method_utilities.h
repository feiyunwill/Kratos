//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya (https://github.com/sunethwarna)
//

#if !defined(KRATOS_METHOD_UTILITIES_H_INCLUDED)
#define KRATOS_METHOD_UTILITIES_H_INCLUDED

// System includes
#include <functional>

// External includes

// Project includes
#include "includes/model_part.h"

// Application includes

#ifndef ADD_TEMPORAL_VALUE_METHOD_ONE_OUTPUT_VARIABLE_OBJECT
#define ADD_TEMPORAL_VALUE_METHOD_ONE_OUTPUT_VARIABLE_OBJECT(model_part, norm_type, input_variable, output_variable, object_list, method)                \
{                                                                                                                                           \
    if (KratosComponents<Variable<double>>::Has(input_variable))                                                                            \
    {                                                                                                                                       \
        const Variable<double>& r_variable_input = KratosComponents<Variable<double>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output = KratosComponents<Variable<double>>::Get(output_variable);                               \
        object_list.push_back(std::make_shared<method<double>>(model_part, norm_type, r_variable_input, r_variable_output));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<array_1d<double, 3>>>::Has(input_variable))                                                          \
    {                                                                                                                                       \
        const Variable<array_1d<double, 3>>& r_variable_input = KratosComponents<Variable<array_1d<double, 3>>>::Get(input_variable);       \
        const Variable<array_1d<double, 3>>& r_variable_output = KratosComponents<Variable<array_1d<double, 3>>>::Get(output_variable);     \
        object_list.push_back(std::make_shared<method<array_1d<double, 3>>>(model_part, norm_type, r_variable_input, r_variable_output));   \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Vector>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Vector>& r_variable_input = KratosComponents<Variable<Vector>>::Get(input_variable);                                 \
        const Variable<Vector>& r_variable_output = KratosComponents<Variable<Vector>>::Get(output_variable);                               \
        object_list.push_back(std::make_shared<method<Vector>>(model_part, norm_type, r_variable_input, r_variable_output));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Matrix>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Matrix>& r_variable_input = KratosComponents<Variable<Matrix>>::Get(input_variable);                                 \
        const Variable<Matrix>& r_variable_output = KratosComponents<Variable<Matrix>>::Get(output_variable);                               \
        object_list.push_back(std::make_shared<method<Matrix>>(model_part, norm_type, r_variable_input, r_variable_output));                \
    }                                                                                                                                       \
}
#endif

#ifndef ADD_TEMPORAL_NORM_METHOD_ONE_OUTPUT_VARIABLE_OBJECT
#define ADD_TEMPORAL_NORM_METHOD_ONE_OUTPUT_VARIABLE_OBJECT(model_part, norm_type, input_variable, output_variable, object_list, method)                \
{                                                                                                                                           \
    if (KratosComponents<Variable<double>>::Has(input_variable))                                                                            \
    {                                                                                                                                       \
        const Variable<double>& r_variable_input = KratosComponents<Variable<double>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output = KratosComponents<Variable<double>>::Get(output_variable);                               \
        object_list.push_back(std::make_shared<method<double>>(model_part, norm_type, r_variable_input, r_variable_output));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<array_1d<double, 3>>>::Has(input_variable))                                                          \
    {                                                                                                                                       \
        const Variable<array_1d<double, 3>>& r_variable_input = KratosComponents<Variable<array_1d<double, 3>>>::Get(input_variable);       \
        const Variable<double>& r_variable_output = KratosComponents<Variable<double>>::Get(output_variable);     \
        object_list.push_back(std::make_shared<method<array_1d<double, 3>>>(model_part, norm_type, r_variable_input, r_variable_output));   \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Vector>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Vector>& r_variable_input = KratosComponents<Variable<Vector>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output = KratosComponents<Variable<double>>::Get(output_variable);                               \
        object_list.push_back(std::make_shared<method<Vector>>(model_part, norm_type, r_variable_input, r_variable_output));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Matrix>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Matrix>& r_variable_input = KratosComponents<Variable<Matrix>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output = KratosComponents<Variable<double>>::Get(output_variable);                               \
        object_list.push_back(std::make_shared<method<Matrix>>(model_part, norm_type, r_variable_input, r_variable_output));                \
    }                                                                                                                                       \
}
#endif

#ifndef ADD_TEMPORAL_VALUE_METHOD_TWO_OUTPUT_VARIABLE_OBJECT
#define ADD_TEMPORAL_VALUE_METHOD_TWO_OUTPUT_VARIABLE_OBJECT(model_part, norm_type, input_variable, output_variable_1, output_variable_2, object_list, method)                \
{                                                                                                                                           \
    if (KratosComponents<Variable<double>>::Has(input_variable))                                                                            \
    {                                                                                                                                       \
        const Variable<double>& r_variable_input = KratosComponents<Variable<double>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output_1 = KratosComponents<Variable<double>>::Get(output_variable_1);                               \
        const Variable<double>& r_variable_output_2 = KratosComponents<Variable<double>>::Get(output_variable_2);                               \
        object_list.push_back(std::make_shared<method<double>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<array_1d<double, 3>>>::Has(input_variable))                                                          \
    {                                                                                                                                       \
        const Variable<array_1d<double, 3>>& r_variable_input = KratosComponents<Variable<array_1d<double, 3>>>::Get(input_variable);       \
        const Variable<array_1d<double, 3>>& r_variable_output_1 = KratosComponents<Variable<array_1d<double, 3>>>::Get(output_variable_1);     \
        const Variable<array_1d<double, 3>>& r_variable_output_2 = KratosComponents<Variable<array_1d<double, 3>>>::Get(output_variable_1);     \
        object_list.push_back(std::make_shared<method<array_1d<double, 3>>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));   \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Vector>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Vector>& r_variable_input = KratosComponents<Variable<Vector>>::Get(input_variable);                                 \
        const Variable<Vector>& r_variable_output_1 = KratosComponents<Variable<Vector>>::Get(output_variable_1);                               \
        const Variable<Vector>& r_variable_output_2 = KratosComponents<Variable<Vector>>::Get(output_variable_2);                               \
        object_list.push_back(std::make_shared<method<Vector>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Matrix>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Matrix>& r_variable_input = KratosComponents<Variable<Matrix>>::Get(input_variable);                                 \
        const Variable<Matrix>& r_variable_output_1 = KratosComponents<Variable<Matrix>>::Get(output_variable_1);                               \
        const Variable<Matrix>& r_variable_output_2 = KratosComponents<Variable<Matrix>>::Get(output_variable_2);                               \
        object_list.push_back(std::make_shared<method<Matrix>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));                \
    }                                                                                                                                       \
}
#endif

#ifndef ADD_TEMPORAL_NORM_METHOD_TWO_OUTPUT_VARIABLE_OBJECT
#define ADD_TEMPORAL_NORM_METHOD_TWO_OUTPUT_VARIABLE_OBJECT(model_part, norm_type, input_variable, output_variable_1, output_variable_2, object_list, method)                \
{                                                                                                                                           \
    if (KratosComponents<Variable<double>>::Has(input_variable))                                                                            \
    {                                                                                                                                       \
        const Variable<double>& r_variable_input = KratosComponents<Variable<double>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output_1 = KratosComponents<Variable<double>>::Get(output_variable_1);                               \
        const Variable<double>& r_variable_output_2 = KratosComponents<Variable<double>>::Get(output_variable_2);                               \
        object_list.push_back(std::make_shared<method<double>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<array_1d<double, 3>>>::Has(input_variable))                                                          \
    {                                                                                                                                       \
        const Variable<array_1d<double, 3>>& r_variable_input = KratosComponents<Variable<array_1d<double, 3>>>::Get(input_variable);       \
        const Variable<double>& r_variable_output_1 = KratosComponents<Variable<double>>::Get(output_variable_1);     \
        const Variable<double>& r_variable_output_2 = KratosComponents<Variable<double>>::Get(output_variable_1);     \
        object_list.push_back(std::make_shared<method<array_1d<double, 3>>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));   \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Vector>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Vector>& r_variable_input = KratosComponents<Variable<Vector>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output_1 = KratosComponents<Variable<double>>::Get(output_variable_1);                               \
        const Variable<double>& r_variable_output_2 = KratosComponents<Variable<double>>::Get(output_variable_2);                               \
        object_list.push_back(std::make_shared<method<Vector>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));                \
    }                                                                                                                                       \
    else if (KratosComponents<Variable<Matrix>>::Has(input_variable))                                                                       \
    {                                                                                                                                       \
        const Variable<Matrix>& r_variable_input = KratosComponents<Variable<Matrix>>::Get(input_variable);                                 \
        const Variable<double>& r_variable_output_1 = KratosComponents<Variable<double>>::Get(output_variable_1);                               \
        const Variable<double>& r_variable_output_2 = KratosComponents<Variable<double>>::Get(output_variable_2);                               \
        object_list.push_back(std::make_shared<method<Matrix>>(model_part, norm_type, r_variable_input, r_variable_output_1, r_variable_output_2));                \
    }                                                                                                                                       \
}
#endif

namespace Kratos
{
///@addtogroup RANSApplication
///@{

///@name Kratos Globals
///@{

namespace MethodsUtilities
{
using NodeType = ModelPart::NodeType;
using ConditionType = ModelPart::ConditionType;
using ElementType = ModelPart::ElementType;

using NodesContainerType = ModelPart::NodesContainerType;
using ConditionsContainerType = ModelPart::ConditionsContainerType;
using ElementsContainerType = ModelPart::ElementsContainerType;

template <typename TDataType>
TDataType RaiseToPower(const TDataType& rData, const double Power);

template <typename TContainerItemType>
class NonHistoricalDataValueRetrievalFunctor
{
public:
    template <typename TDataType>
    TDataType& operator()(TContainerItemType& rDataItem, const Variable<TDataType>& rVariable)
    {
        return rDataItem.GetValue(rVariable);
    }

    template <typename TDataType>
    TDataType operator()(const TContainerItemType& rDataItem,
                         const Variable<TDataType>& rVariable)
    {
        return rDataItem.GetValue(rVariable);
    }
};

template <typename TContainerItemType>
class HistoricalDataValueRetrievalFunctor
{
public:
    template <typename TDataType>
    TDataType& operator()(TContainerItemType& rDataItem, const Variable<TDataType>& rVariable)
    {
        KRATOS_TRY

        return rDataItem.FastGetSolutionStepValue(rVariable);

        KRATOS_CATCH("");
    }

    template <typename TDataType>
    TDataType operator()(const TContainerItemType& rDataItem,
                         const Variable<TDataType>& rVariable)
    {
        KRATOS_TRY

        return rDataItem.FastGetSolutionStepValue(rVariable);

        KRATOS_CATCH("");
    }
};

double GetDoubleValue(const std::string& rInput);

int GetIntegerValue(const std::string& rInput);

void SplitString(std::string& rOutput1, std::string& rOutput2, const std::string& rInput);

template <typename TDataType>
void DataTypeSizeInitializer(TDataType& rData, const TDataType& rReferenceData);

template <typename TDataType>
void DataTypeSizeChecker(const TDataType& rData, const TDataType& rReferenceData);

template <typename TContainerType>
TContainerType& GetLocalDataContainer(ModelPart& rModelPart);

template <typename TContainerType>
const TContainerType& GetLocalDataContainer(const ModelPart& rModelPart);

template <typename TContainerType>
TContainerType& GetDataContainer(ModelPart& rModelPart);

template <typename TContainerType>
const TContainerType& GetDataContainer(const ModelPart& rModelPart);

template <typename TDataType>
const std::function<double(const TDataType&)> GetNormMethod(const Variable<TDataType>& rVariable,
                                                            const std::string& rNormType);

template<typename TDataType>
void CheckVariableType(const std::vector<std::string>& rVariableNamesList);

void CheckInputOutputVariables(const std::vector<std::string>& rInputVariableNamesList,
                               const std::vector<std::string>& rOutputVariableNamesList);

} // namespace MethodsUtilities

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

///@}

///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

///@}

///@} addtogroup block

} // namespace Kratos.

#endif // KRATOS_METHOD_UTILITIES_H_INCLUDED defined
