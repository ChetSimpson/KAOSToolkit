// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/dimension2.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech::kaos::core::types::unittests
{

	template<class TestType_>
	class dimension2_test : public ::testing::Test
	{
	public:
		static inline const TestType_ test_dimension{ 100, 300 };
		static inline const TestType_ other_test_dimension{ 25, 75 };

	};

	TYPED_TEST_CASE_P(dimension2_test);

	TYPED_TEST_P(dimension2_test, create_empty)
	{
		const TypeParam v;

		EXPECT_EQ(v.width, 0);
		EXPECT_EQ(v.height, 0);
	}

	TYPED_TEST_P(dimension2_test, create)
	{
		const TypeParam v(5, 7);

		EXPECT_EQ(v.width, 5);
		EXPECT_EQ(v.height, 7);
	}

	TYPED_TEST_P(dimension2_test, create_copy)
	{
		const TypeParam copy(this->test_dimension);

		EXPECT_EQ(copy.width, this->test_dimension.width);
		EXPECT_EQ(copy.height, this->test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, copy_assignment)
	{
		TypeParam result_dimension;

		result_dimension = this->test_dimension;
		EXPECT_EQ(result_dimension, this->test_dimension);
	}

	TYPED_TEST_P(dimension2_test, move_assignment)
	{
		TypeParam result_dimension;

		result_dimension = TypeParam(this->test_dimension);
		EXPECT_EQ(result_dimension, this->test_dimension);
	}

	TYPED_TEST_P(dimension2_test, add_operator)
	{
		const auto result_dimension(this->test_dimension + this->other_test_dimension);
		EXPECT_EQ(result_dimension.width, this->test_dimension.width + this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height + this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, assign_by_sum_operator)
	{
		TypeParam result_dimension(this->test_dimension);

		result_dimension += this->other_test_dimension;
		EXPECT_EQ(result_dimension.width, this->test_dimension.width + this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height + this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, subtract_operator)
	{
		const auto result_dimension(this->test_dimension - this->other_test_dimension);
		EXPECT_EQ(result_dimension.width, this->test_dimension.width - this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height - this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, assign_by_difference_operator)
	{
		TypeParam result_dimension(this->test_dimension);

		result_dimension -= this->other_test_dimension;
		EXPECT_EQ(result_dimension.width, this->test_dimension.width - this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height - this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, multiply_operator)
	{
		const auto result_dimension(this->test_dimension * this->other_test_dimension);
		EXPECT_EQ(result_dimension.width, this->test_dimension.width * this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height * this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, assign_by_product_operator)
	{
		TypeParam result_dimension(this->test_dimension);

		result_dimension *= this->other_test_dimension;
		EXPECT_EQ(result_dimension.width, this->test_dimension.width * this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height * this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, divide_operator)
	{
		const auto result_dimension(this->test_dimension / this->other_test_dimension);
		EXPECT_EQ(result_dimension.width, this->test_dimension.width / this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height / this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, assign_by_quotient_operator)
	{
		TypeParam result_dimension(this->test_dimension);

		result_dimension /= this->other_test_dimension;
		EXPECT_EQ(result_dimension.width, this->test_dimension.width / this->other_test_dimension.width);
		EXPECT_EQ(result_dimension.height, this->test_dimension.height / this->other_test_dimension.height);
	}

	TYPED_TEST_P(dimension2_test, compare_equals)
	{
		EXPECT_EQ(TypeParam(), TypeParam());
		EXPECT_EQ(TypeParam(55, 77), TypeParam(55, 77));
		EXPECT_EQ(TypeParam(100, 200), TypeParam(100, 200));
	}

	TYPED_TEST_P(dimension2_test, compare_not_equals)
	{
		EXPECT_NE(TypeParam(55, 77), TypeParam(100, 200));
		EXPECT_NE(TypeParam(100, 200), TypeParam(55, 77));
	}


	REGISTER_TYPED_TEST_CASE_P(
		dimension2_test,
		create_empty,
		create,
		create_copy,
		copy_assignment,
		move_assignment,
		add_operator,
		assign_by_sum_operator,
		subtract_operator,
		assign_by_difference_operator,
		multiply_operator,
		assign_by_product_operator,
		divide_operator,
		assign_by_quotient_operator,
		compare_equals,
		compare_not_equals);

	using testing_types = testing::Types<dimension2i, dimension2u, dimension2f, dimension2d, dimension2f_fast, dimension2d_fast>;
	INSTANTIATE_TYPED_TEST_CASE_P(dimension2_tests, dimension2_test, testing_types);




	TEST(dimension2_conversion, convert_integer_to_unsigned)
	{
		EXPECT_EQ(dimension2u(dimension2i(55, 77)), dimension2u(55, 77));
		EXPECT_THROW(dimension2u(dimension2i(std::numeric_limits<dimension2i::value_type>::min(), 77)), boost::numeric::negative_overflow);
	}

	TEST(dimension2_conversion, convert_integer_to_float)
	{
		EXPECT_EQ(dimension2f(dimension2i(55, 77)), dimension2f(55, 77));
		//EXPECT_THROW(dimension2f(dimension2i(std::numeric_limits<dimension2i::value_type>::max(), 77)), boost::numeric::positive_overflow);
		//EXPECT_THROW(dimension2f(dimension2i(std::numeric_limits<dimension2i::value_type>::min(), 77)), boost::numeric::negative_overflow);
	}

	TEST(dimension2_conversion, convert_integer_to_double)
	{
		EXPECT_EQ(dimension2d(dimension2i(55, 77)), dimension2d(55, 77));
	}


	TEST(dimension2_conversion, convert_unsigned_to_integer)
	{
		EXPECT_EQ(dimension2i(dimension2u(55, 77)), dimension2i(55, 77));
		EXPECT_THROW(dimension2i(dimension2u(std::numeric_limits<dimension2u::value_type>::max(), 77)), boost::numeric::positive_overflow);
	}

	TEST(dimension2_conversion, convert_unsigned_to_float)
	{
		EXPECT_EQ(dimension2f(dimension2u(55, 77)), dimension2f(55, 77));
		//EXPECT_THROW(dimension2f(dimension2u(std::numeric_limits<dimension2u::value_type>::max(), 77)), boost::numeric::positive_overflow);
	}

	TEST(dimension2_conversion, convert_unsigned_to_double)
	{
		EXPECT_EQ(dimension2d(dimension2u(55, 77)), dimension2d(55, 77));
		//EXPECT_THROW(dimension2d(dimension2u(std::numeric_limits<dimension2u::value_type>::max(), 77)), boost::numeric::positive_overflow);
	}


	TEST(dimension2_conversion, convert_float_to_integer)
	{
		EXPECT_EQ(dimension2i(dimension2f(55.5, 77.5)), dimension2i(55, 77));
		EXPECT_THROW(dimension2i(dimension2f(std::numeric_limits<dimension2f::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
	}

	TEST(dimension2_conversion, convert_float_to_unsigned)
	{
		EXPECT_EQ(dimension2u(dimension2f(55.5, 77.5)), dimension2u(55, 77));
		EXPECT_THROW(dimension2u(dimension2f(std::numeric_limits<dimension2f::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
		EXPECT_THROW(dimension2u(dimension2f(-std::numeric_limits<dimension2f::value_type>::max(), 77.5)), boost::numeric::negative_overflow);
	}

	TEST(dimension2_conversion, convert_float_to_double)
	{
		EXPECT_EQ(dimension2d(dimension2f(55.5, 77.5)), dimension2d(55.5, 77.5));
	}


	TEST(dimension2_conversion, convert_double_to_integer)
	{
		EXPECT_EQ(dimension2i(dimension2f(55.5, 77.5)), dimension2i(55, 77));
		EXPECT_THROW(dimension2i(dimension2f(std::numeric_limits<dimension2f::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
	}

	TEST(dimension2_conversion, convert_double_to_unsigned)
	{
		EXPECT_EQ(dimension2u(dimension2d(55.5, 77.5)), dimension2u(55, 77));
		EXPECT_THROW(dimension2u(dimension2d(std::numeric_limits<dimension2d::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
		EXPECT_THROW(dimension2u(dimension2d(-std::numeric_limits<dimension2d::value_type>::max(), 77.5)), boost::numeric::negative_overflow);
	}

	TEST(dimension2_conversion, convert_double_to_float)
	{
		EXPECT_EQ(dimension2f(dimension2d(55.5, 77.5)), dimension2f(55.5, 77.5));
		EXPECT_THROW(dimension2f(dimension2d(std::numeric_limits<dimension2d::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
		EXPECT_THROW(dimension2f(dimension2d(-std::numeric_limits<dimension2d::value_type>::max(), 77.5)), boost::numeric::negative_overflow);
	}

}
