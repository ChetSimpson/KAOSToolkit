// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/vector2.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech { namespace kaos { namespace core { namespace types { namespace unittests
{

	template<class TestType_>
	class vector2_test : public ::testing::Test
	{
	public:
		static inline const TestType_ test_vector{ 100, 300 };
		static inline const TestType_ other_test_vector{ 25, 75 };

	};

	TYPED_TEST_CASE_P(vector2_test);

	TYPED_TEST_P(vector2_test, create_empty)
	{
		const TypeParam v;

		EXPECT_EQ(v.x, 0);
		EXPECT_EQ(v.y, 0);
	}

	TYPED_TEST_P(vector2_test, create)
	{
		const TypeParam v(5, 7);

		EXPECT_EQ(v.x, 5);
		EXPECT_EQ(v.y, 7);
	}

	TYPED_TEST_P(vector2_test, create_copy)
	{
		const TypeParam copy(this->test_vector);

		EXPECT_EQ(copy.x, this->test_vector.x);
		EXPECT_EQ(copy.y, this->test_vector.y);
	}

	TYPED_TEST_P(vector2_test, copy_assignment)
	{
		TypeParam result_vector;

		result_vector = this->test_vector;
		EXPECT_EQ(result_vector, this->test_vector);
	}

	TYPED_TEST_P(vector2_test, move_assignment)
	{
		TypeParam result_vector;

		result_vector = TypeParam(this->test_vector);
		EXPECT_EQ(result_vector, this->test_vector);
	}

	TYPED_TEST_P(vector2_test, add_operator)
	{
		const auto result_vector(this->test_vector + this->other_test_vector);
		EXPECT_EQ(result_vector.x, this->test_vector.x + this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y + this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, assign_by_sum_operator)
	{
		TypeParam result_vector(this->test_vector);

		result_vector += this->other_test_vector;
		EXPECT_EQ(result_vector.x, this->test_vector.x + this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y + this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, subtract_operator)
	{
		const auto result_vector(this->test_vector - this->other_test_vector);
		EXPECT_EQ(result_vector.x, this->test_vector.x - this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y - this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, assign_by_difference_operator)
	{
		TypeParam result_vector(this->test_vector);

		result_vector -= this->other_test_vector;
		EXPECT_EQ(result_vector.x, this->test_vector.x - this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y - this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, multiply_operator)
	{
		const auto result_vector(this->test_vector * this->other_test_vector);
		EXPECT_EQ(result_vector.x, this->test_vector.x * this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y * this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, assign_by_product_operator)
	{
		TypeParam result_vector(this->test_vector);

		result_vector *= this->other_test_vector;
		EXPECT_EQ(result_vector.x, this->test_vector.x * this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y * this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, divide_operator)
	{
		const auto result_vector(this->test_vector / this->other_test_vector);
		EXPECT_EQ(result_vector.x, this->test_vector.x / this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y / this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, assign_by_quotient_operator)
	{
		TypeParam result_vector(this->test_vector);

		result_vector /= this->other_test_vector;
		EXPECT_EQ(result_vector.x, this->test_vector.x / this->other_test_vector.x);
		EXPECT_EQ(result_vector.y, this->test_vector.y / this->other_test_vector.y);
	}

	TYPED_TEST_P(vector2_test, compare_equals)
	{
		EXPECT_EQ(TypeParam(), TypeParam());
		EXPECT_EQ(TypeParam(55, 77), TypeParam(55, 77));
		EXPECT_EQ(TypeParam(100, 200), TypeParam(100, 200));
	}

	TYPED_TEST_P(vector2_test, compare_not_equals)
	{
		EXPECT_NE(TypeParam(55, 77), TypeParam(100, 200));
		EXPECT_NE(TypeParam(100, 200), TypeParam(55, 77));
	}


	REGISTER_TYPED_TEST_CASE_P(
		vector2_test,
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

	using testing_types = testing::Types<vector2i, vector2u, vector2f, vector2d, vector2f_fast, vector2d_fast>;
	INSTANTIATE_TYPED_TEST_CASE_P(vector2_tests, vector2_test, testing_types);




	TEST(vector2_conversion, convert_integer_to_unsigned)
	{
		EXPECT_EQ(vector2u(vector2i(55, 77)), vector2u(55, 77));
		EXPECT_THROW(vector2u(vector2i(std::numeric_limits<vector2i::value_type>::min(), 77)), boost::numeric::negative_overflow);
	}

	TEST(vector2_conversion, convert_integer_to_float)
	{
		EXPECT_EQ(vector2f(vector2i(55, 77)), vector2f(55, 77));
		//EXPECT_THROW(vector2f(vector2i(std::numeric_limits<vector2i::value_type>::max(), 77)), boost::numeric::positive_overflow);
		//EXPECT_THROW(vector2f(vector2i(std::numeric_limits<vector2i::value_type>::min(), 77)), boost::numeric::negative_overflow);
	}

	TEST(vector2_conversion, convert_integer_to_double)
	{
		EXPECT_EQ(vector2d(vector2i(55, 77)), vector2d(55, 77));
	}


	TEST(vector2_conversion, convert_unsigned_to_integer)
	{
		EXPECT_EQ(vector2i(vector2u(55, 77)), vector2i(55, 77));
		EXPECT_THROW(vector2i(vector2u(std::numeric_limits<vector2u::value_type>::max(), 77)), boost::numeric::positive_overflow);
	}

	TEST(vector2_conversion, convert_unsigned_to_float)
	{
		EXPECT_EQ(vector2f(vector2u(55, 77)), vector2f(55, 77));
		//EXPECT_THROW(vector2f(vector2u(std::numeric_limits<vector2u::value_type>::max(), 77)), boost::numeric::positive_overflow);
	}

	TEST(vector2_conversion, convert_unsigned_to_double)
	{
		EXPECT_EQ(vector2d(vector2u(55, 77)), vector2d(55, 77));
		//EXPECT_THROW(vector2d(vector2u(std::numeric_limits<vector2u::value_type>::max(), 77)), boost::numeric::positive_overflow);
	}


	TEST(vector2_conversion, convert_float_to_integer)
	{
		EXPECT_EQ(vector2i(vector2f(55.5, 77.5)), vector2i(55, 77));
		EXPECT_THROW(vector2i(vector2f(std::numeric_limits<vector2f::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
	}

	TEST(vector2_conversion, convert_float_to_unsigned)
	{
		EXPECT_EQ(vector2u(vector2f(55.5, 77.5)), vector2u(55, 77));
		EXPECT_THROW(vector2u(vector2f(std::numeric_limits<vector2f::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
		EXPECT_THROW(vector2u(vector2f(-std::numeric_limits<vector2f::value_type>::max(), 77.5)), boost::numeric::negative_overflow);
	}

	TEST(vector2_conversion, convert_float_to_double)
	{
		EXPECT_EQ(vector2d(vector2f(55.5, 77.5)), vector2d(55.5, 77.5));
	}


	TEST(vector2_conversion, convert_double_to_integer)
	{
		EXPECT_EQ(vector2i(vector2f(55.5, 77.5)), vector2i(55, 77));
		EXPECT_THROW(vector2i(vector2f(std::numeric_limits<vector2f::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
	}

	TEST(vector2_conversion, convert_double_to_unsigned)
	{
		EXPECT_EQ(vector2u(vector2d(55.5, 77.5)), vector2u(55, 77));
		EXPECT_THROW(vector2u(vector2d(std::numeric_limits<vector2d::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
		EXPECT_THROW(vector2u(vector2d(-std::numeric_limits<vector2d::value_type>::max(), 77.5)), boost::numeric::negative_overflow);
	}

	TEST(vector2_conversion, convert_double_to_float)
	{
		EXPECT_EQ(vector2f(vector2d(55.5, 77.5)), vector2f(55.5, 77.5));
		EXPECT_THROW(vector2f(vector2d(std::numeric_limits<vector2d::value_type>::max(), 77.5)), boost::numeric::positive_overflow);
		EXPECT_THROW(vector2f(vector2d(-std::numeric_limits<vector2d::value_type>::max(), 77.5)), boost::numeric::negative_overflow);
	}

}}}}}
