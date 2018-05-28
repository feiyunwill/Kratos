//    |  /           | 
//    ' /   __| _` | __|  _ \   __| 
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/ 
//                   Multi-Physics  
//
//  License:		 BSD License 
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Pooyan Dadvand
//

#if !defined(KRATOS_AMATRIX_INTERFACE_H_INCLUDED )
#define  KRATOS_AMATRIX_INTERFACE_H_INCLUDED



// System includes
#include <string>
#include <iostream>


// External includes
#include "amatrix.h"

// Project includes
#include "includes/define.h"
#include "includes/checks.h"


namespace Kratos
{

namespace Internals {

// This class is a modified copy of the AMatrix::Matrix to cover the backward compatibility with ublas in current Kratos implementation.
// The idea is to go step by step toward the original Matrix class and eliminate the differences. So please do not add new API to it.
template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class Matrix : public AMatrix::MatrixExpression<Matrix<TDataType, TSize1, TSize2>,
                   AMatrix::row_major_access>,
               public AMatrix::MatrixStorage<TDataType, TSize1, TSize2> {
   public:
    using data_type = TDataType;
    using base_type = AMatrix::MatrixStorage<TDataType, TSize1, TSize2>;
    using base_type::at;
    using base_type::data;
    using base_type::size;
    using base_type::size1;
    using base_type::size2;
    using base_type::operator();
    
    using iterator = AMatrix::RandomAccessIterator<TDataType>;
    using const_iterator = AMatrix::RandomAccessIterator<const TDataType>;

    //ublas compatibility definitions
    using value_type = TDataType;
    using size_type = std::size_t;
    using difference_type = std::size_t;
    using const_reference = const TDataType&;
    using reference = TDataType&;
    using const_pointer = TDataType*;
    using pointer = TDataType*;


    Matrix(): base_type(0, 0) {}

    explicit Matrix(std::size_t TheSize1, std::size_t TheSize2)
        : base_type(TheSize1, TheSize2) {}

    explicit Matrix(std::size_t TheSize)
        : base_type(TheSize) {}

    Matrix(Matrix const& Other) : base_type(Other) {}

    Matrix(Matrix&& Other) : base_type(Other) {}

    template <typename TExpressionType, std::size_t TCategory>
    Matrix(AMatrix::MatrixExpression<TExpressionType, TCategory> const& Other)
        : base_type(Other) {}

    // template <typename TOtherMatrixType>
    // explicit Matrix(TOtherMatrixType const& Other) : base_type(Other) {}

    explicit Matrix(std::initializer_list<TDataType> InitialValues)
        : base_type(InitialValues) {}

	template <typename TExpressionType, std::size_t TCategory>
	Matrix& operator=(
		MatrixExpression<TExpressionType, TCategory> const& Other) {
		base_type::operator=(Other.expression());
		return *this;
	}

    //template <typename TOtherMatrixType>
    //Matrix& operator=(TOtherMatrixType const& Other) {
    //    base_type::operator=(Other);
    //    return *this;
    //}

    Matrix& operator=(Matrix const& Other) {
        base_type::operator=(Other);
        return *this;
    }

    Matrix& operator=(Matrix&& Other) {
        base_type::operator=(Other);
        return *this;
    }

    TDataType& operator()(std::size_t i) { return at(i); }

    TDataType const& operator()(std::size_t i) const { return at(i); }

    friend bool operator==(Matrix const& First, Matrix const& Second) {
        for (std::size_t i = 0; i < First.size(); i++)
            if (First._data[i] != Second._data[i])
                return false;
        return true;
    }

    template <typename TExpressionType, std::size_t TCategory>
    Matrix& operator+=(
        AMatrix::MatrixExpression<TExpressionType, TCategory> const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) += Other.expression()(i, j);

        return *this;
    }

    template <typename TExpressionType>
    Matrix& operator+=(
        AMatrix::MatrixExpression<TExpressionType, AMatrix::row_major_access> const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            at(i) += Other.expression()[i];

        return *this;
    }

    template <typename TExpressionType, std::size_t TCategory>
    Matrix& operator-=(
        AMatrix::MatrixExpression<TExpressionType, TCategory> const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) -= Other(i, j);

        return *this;
    }

    template <typename TExpressionType>
    Matrix& operator-=(
        AMatrix::MatrixExpression<TExpressionType, AMatrix::row_major_access> const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            at(i) -= Other.expression()[i];

        return *this;
    }

    Matrix& operator*=(data_type TheValue) {
        for (std::size_t i = 0; i < size(); i++)
            at(i) *= TheValue;

        return *this;
    }

    Matrix& operator/=(data_type TheValue) {
        auto inverse_of_value = 1.00 / TheValue;
        for (std::size_t i = 0; i < size(); i++)
            at(i) *= inverse_of_value;

        return *this;
    }

    AMatrix::MatrixUnaryMinusExpression<Matrix> operator-() const {
        return AMatrix::MatrixUnaryMinusExpression<Matrix>(*this);
    }

    void resize(std::size_t NewSize1, std::size_t NewSize2, bool preserve = 0){
        KRATOS_DEBUG_ERROR_IF(preserve) << "The preserve is not supported anymore" << std::endl;

        base_type::resize(NewSize1,NewSize2);
    }

    void resize(std::size_t NewSize, bool preserve = 0){
        KRATOS_DEBUG_ERROR_IF(preserve) << "The preserve is not supported anymore" << std::endl;
        base_type::resize(NewSize);
    }

    void resize(std::size_t NewSize, TDataType const& TheValue){
        base_type::resize(NewSize);
         for (std::size_t i = 0; i < size(); i++)
            at(i) = TheValue;
     }

    iterator begin() { return iterator(data()); }

    iterator end() { return iterator(data() + size()); }

    const_iterator begin() const { return const_iterator(data()); }

    const_iterator end() const { return const_iterator(data() + size()); }

    template <typename TExpressionType>
    data_type dot(
        AMatrix::MatrixExpression<TExpressionType, AMatrix::row_major_access> const& Other)
        const {
        data_type result = data_type();
        for (std::size_t i = 0; i < size(); ++i) {
            result += at(i) * Other.expression()[i];
        }
        return result;
    }

    data_type squared_norm() const { return dot(*this); }

    data_type norm() const { return std::sqrt(dot(*this)); }

    void normalize() {
        auto the_norm = norm();
        if (the_norm > std::numeric_limits<data_type>::epsilon()) {
            const auto norm_inverse = 1.0 / the_norm;
            for (std::size_t i = 0; i < size(); ++i) {
                at(i) *= norm_inverse;
            }
        }
    }

    Matrix& noalias() { return *this; }

    AMatrix::TransposeMatrix<const Matrix<TDataType, TSize1, TSize2>> transpose() const {
        return AMatrix::TransposeMatrix<const Matrix<TDataType, TSize1, TSize2>>(*this);
    }

    AMatrix::TransposeMatrix<Matrix<TDataType, TSize1, TSize2>> transpose() {
        return AMatrix::TransposeMatrix<Matrix<TDataType, TSize1, TSize2>>(*this);
    }

    void clear(){
         for (std::size_t i = 0; i < size(); i++)
            at(i) = TDataType();
    }

    void swap(Matrix& Other){
        base_type::swap(Other);
    }
};

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
bool operator!=(Matrix<TDataType, TSize1, TSize2> const& First,
    Matrix<TDataType, TSize1, TSize2> const& Second) {
    return !(First == Second);
}

/// output stream function
///  format for a vector : [size](value1, value2, ...., valueN)
///  format for a matrix : [size1, size2](()()...()) 
template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
inline std::ostream& operator<<(std::ostream& rOStream,
	Matrix<TDataType, TSize1, TSize2> const& TheMatrix) {

	if ((TSize1 == 1) || (TSize2 == 1)) { // writing in vector format
		const std::size_t size = TheMatrix.size();
		rOStream << "[" << size << "](";
		if (size > 0)
			rOStream << TheMatrix[0];
		for (std::size_t i = 1; i < size; i++) {
			rOStream << "," << TheMatrix[i];
		}
		rOStream << ")";
	}
	else // writing in matrix format
	{
		const std::size_t size2 = TheMatrix.size2();
		rOStream << "[" << TheMatrix.size1() << "," << TheMatrix.size2() << "](";
		if (TheMatrix.size1() > 0) {
			rOStream << "(";
			if (size2 > 0)
				rOStream << TheMatrix(0, 0);
			for (std::size_t j = 1; j < size2; j++) {
				rOStream << "," << TheMatrix(0, j);
			}
			rOStream << ")";
		}
		for (std::size_t i = 1; i < TheMatrix.size1(); i++) {
			rOStream << ",(";
			if (size2 > 0)
				rOStream << TheMatrix(i, 0);
			for (std::size_t j = 1; j < size2; j++) {
				rOStream << "," << TheMatrix(i, j);
			}
			rOStream << ")";
		}
		rOStream << ")";
	}
	return rOStream;
}

/// input stream function for matrix using the ublas style for backward compatibility
///  format for a matrix : [size1, size2](()()...()) 
///  NOTE: it deosnot support white spaces, tab, etc.
template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
inline std::istream& operator>>(std::istream& rIStream,
	Matrix<TDataType, TSize1, TSize2>& TheMatrix) {

	std::size_t size1;
	std::size_t size2;

	char c;

	rIStream >> c; // skipping the '['
	KRATOS_DEBUG_CHECK(c == '[');

	rIStream >> size1;

	rIStream >> c; // skipping the ','
	KRATOS_DEBUG_CHECK(c == ',');

	rIStream >> size2;

	rIStream >> c; // skipping the ']'
	KRATOS_DEBUG_CHECK(c == ']');

	TheMatrix.resize(size1, size2);

	rIStream >> c; // skipping the '('
	KRATOS_DEBUG_CHECK(c == '(');

	for (std::size_t i = 0; i < size1; i++) {
		if (i > 0) {
			rIStream >> c; // skipping the row ','
			KRATOS_DEBUG_CHECK(c == ',');
		}
		rIStream >> c; // skipping the row '('
		KRATOS_DEBUG_CHECK(c == '(');

		for (std::size_t j = 0; j < size2; j++) {
			if (j > 0) {
				rIStream >> c; // skipping the ','
				KRATOS_DEBUG_CHECK(c == ',');
			}
			rIStream >> TheMatrix(i, j);
		}

		rIStream >> c; // skipping the row ')'
		KRATOS_DEBUG_CHECK(c == ')');
	}

	rIStream >> c; // skipping the final ')'
	KRATOS_DEBUG_CHECK(c == ')');

	return rIStream;
}

/// input stream function for vector using the ublas style for backward compatibility
///  format for a vector : [size](value1, value2, ...., valueN)
///  NOTE: it deosnot support white spaces, tab, etc.
template <typename TDataType, std::size_t TSize1>
inline std::istream& operator>>(std::istream& rIStream,
	Matrix<TDataType, TSize1, 1>& TheMatrix) {

	std::size_t size1;


	char c;

	rIStream >> c; // skipping the '['
	KRATOS_DEBUG_CHECK(c == '[');

	rIStream >> size1;

	rIStream >> c; // skipping the ']'
	KRATOS_DEBUG_CHECK(c == ']');

	TheMatrix.resize(size1);

	rIStream >> c; // skipping the '('
	KRATOS_DEBUG_CHECK(c == '(');

	for (std::size_t i = 0; i < size1; i++) {
		if (i > 0) {
			rIStream >> c; // skipping the ','
			KRATOS_DEBUG_CHECK(c == ',');
		}
		rIStream >> TheMatrix[i];
	}

	rIStream >> c; // skipping the ')'
	KRATOS_DEBUG_CHECK(c == ')');

	return rIStream;
}


} // namespace Internals

///@name Type Definitions
///@{

using Matrix = Internals::Matrix<double,AMatrix::dynamic, AMatrix::dynamic>;

using Vector = Internals::Matrix<double,AMatrix::dynamic, 1>;

template <typename TDataType> using DenseMatrix=Internals::Matrix<TDataType,AMatrix::dynamic, AMatrix::dynamic>;

template <typename TDataType> using DenseVector=Internals::Matrix<TDataType,AMatrix::dynamic, 1>;

template <typename TDataType, std::size_t TSize> using BoundedVector=Internals::Matrix<TDataType,TSize, 1>;

template <typename TDataType, std::size_t TSize1, std::size_t TSize2> using BoundedMatrix=Internals::Matrix<TDataType,TSize1, TSize2>;

template <typename TDataType, std::size_t TSize> using BoundedVector=Internals::Matrix<TDataType,TSize, 1>;

template <typename T> T& noalias(T& TheMatrix){return TheMatrix.noalias();}

template <typename T> AMatrix::TransposeMatrix<const T> trans(const T& TheMatrix){return TheMatrix.transpose();}

template <typename T> AMatrix::TransposeMatrix<T> trans(T& TheMatrix){return TheMatrix.transpose();}

template <typename TExpressionType> using vector_expression = AMatrix::MatrixExpression<TExpressionType>;

using ZeroMatrix = AMatrix::ZeroMatrix<double>;

using ZeroVector = AMatrix::ZeroMatrix<double>;

using IdentityMatrix = AMatrix::IdentityMatrix<double>;

template <typename TExpression1Type, typename TExpression2Type,
    std::size_t TCategory1, std::size_t TCategory2>
AMatrix::MatrixProductExpression<TExpression1Type, TExpression2Type> prod(
    AMatrix::MatrixExpression<TExpression1Type, TCategory1> const& First,
    AMatrix::MatrixExpression<TExpression2Type, TCategory2> const& Second) {
    return AMatrix::MatrixProductExpression<TExpression1Type, TExpression2Type>(
        First.expression(), Second.expression());
}

template <typename TExpression1Type, typename TExpression2Type,
    std::size_t TCategory1, std::size_t TCategory2>
AMatrix::VectorOuterProductExpression<TExpression1Type, TExpression2Type> outer_prod(
    AMatrix::MatrixExpression<TExpression1Type, TCategory1> const& First,
    AMatrix::MatrixExpression<TExpression2Type, TCategory2> const& Second) {
    return AMatrix::VectorOuterProductExpression<TExpression1Type, TExpression2Type>(
        First.expression(), Second.expression());
}

template <typename TExpression1Type, typename TExpression2Type,
    std::size_t TCategory1, std::size_t TCategory2>
typename TExpression1Type::data_type inner_prod(
    AMatrix::MatrixExpression<TExpression1Type, TCategory1> const& First,
    AMatrix::MatrixExpression<TExpression2Type, TCategory2> const& Second) {

        using data_type = typename TExpression1Type::data_type;
        auto& the_expression1 = First.expression();
        auto& the_expression2 = Second.expression();
        data_type result = data_type();
        for (std::size_t i = 0; i < the_expression1.size(); ++i) {
            result += the_expression1[i] * the_expression2[i];
        }
    return result;

}

template <typename TExpressionType, std::size_t TCategory> 
    typename TExpressionType::data_type norm_2(
    AMatrix::MatrixExpression<TExpressionType, TCategory> const& TheExpression) {
        using data_type = typename TExpressionType::data_type;
        auto& the_expression = TheExpression.expression();
        data_type result = data_type();
        for (std::size_t i = 0; i < the_expression.size(); ++i) {
            result += the_expression[i] * the_expression[i];
        }
    return std::sqrt(result);
}

template <typename TExpressionType, std::size_t TCategory> 
    AMatrix::SubVector<const TExpressionType> row(
    AMatrix::MatrixExpression<TExpressionType, TCategory> const& TheExpression, std::size_t RowIndex) {
    return AMatrix::SubVector<const TExpressionType>(TheExpression.expression(), RowIndex * TheExpression.expression().size2() , (RowIndex + 1) * TheExpression.expression().size2());
}

template <typename TExpressionType, std::size_t TCategory> 
    AMatrix::SubVector<TExpressionType> row(
    AMatrix::MatrixExpression<TExpressionType, TCategory>& TheExpression, std::size_t RowIndex) {
    return AMatrix::SubVector<TExpressionType>(TheExpression.expression(), RowIndex * TheExpression.expression().size2() , (RowIndex + 1) * TheExpression.expression().size2());
}

template <typename TExpressionType, std::size_t TCategory> 
    AMatrix::SubVector<const TExpressionType> subrange(
    AMatrix::MatrixExpression<TExpressionType, TCategory> const& TheExpression, std::size_t From, std::size_t To) {
    return AMatrix::SubVector<const TExpressionType>(TheExpression.expression(), From,To - From);
}

template <typename TExpressionType, std::size_t TCategory> 
    AMatrix::SubVector<TExpressionType> subrange(
    AMatrix::MatrixExpression<TExpressionType, TCategory>& TheExpression, std::size_t From, std::size_t To) {
    return AMatrix::SubVector<TExpressionType>(TheExpression.expression(), From,To - From);
}

template <typename TExpressionType, std::size_t TCategory> 
    typename TExpressionType::data_type norm_frobenius(
    AMatrix::MatrixExpression<TExpressionType, TCategory> const& TheExpression) {
        using data_type = typename TExpressionType::data_type;
        auto& the_expression = TheExpression.expression();
        data_type result = data_type();
        for (std::size_t i = 0; i < the_expression.size(); ++i) {
            result += the_expression[i] * the_expression[i];
        }
    return std::sqrt(result);
}

	template <typename TDataType>
	class scalar_matrix
		: public AMatrix::MatrixExpression<scalar_matrix<TDataType>, AMatrix::row_major_access> {
		std::size_t _size1;
		std::size_t _size2;
		const TDataType _value;

	public:
		using data_type = TDataType;

		scalar_matrix() = delete;

		scalar_matrix(std::size_t Size1, std::size_t Size2, TDataType const& Value)
			: _size1(Size1), _size2(Size2), _value(Value) {}

		inline TDataType operator()(std::size_t i, std::size_t j) const {
			return _value;
		}

		inline TDataType operator[](std::size_t i) const { return TDataType(); }

		inline std::size_t size1() const { return _size1; }
		inline std::size_t size2() const { return _size2; }
	};

	using ScalarMatrix = scalar_matrix<double>;

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

}  // namespace Kratos.

#endif // KRATOS_AMATRIX_INTERFACE_H_INCLUDED  defined 



