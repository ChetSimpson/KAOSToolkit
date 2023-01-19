// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/xml/pugixml_extensions.h>
#include <pugixml/pugixml.hpp>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech { namespace kaos { namespace core { namespace xml {  namespace unittests
{

	using pugi::xml_document;
	using pugi::xml_node;
	using pugi::xml_attribute;

	namespace
	{
		template<class TestDataType_>
		class test_get_attribute_fixture : public ::testing::Test
		{
		protected:
			xml_node create_node(const std::string& value)
			{
				doc = xml_document();
				xml_node node(doc.append_child("node"));
				xml_attribute attribute(node.append_attribute(attribute_name_.c_str()));
				
				attribute.set_value(value.c_str());

				return node;
			}

			static const inline std::string attribute_name_ = "hello";
			xml_document doc;
		};

		template<class Type_>
		struct test_expectations;

		template<>
		struct test_expectations<bool>
		{
			static const inline std::string valid_attribute_string = "true";
			static const inline std::string incomplete_attribute_string = "true true";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "500";
			static const inline std::string negative_overflow_attribute_string = "-500";
			static const bool expected_value = true;
		};

		template<>
		struct test_expectations<char>
		{
			static const inline std::string valid_attribute_string = "-100";
			static const inline std::string incomplete_attribute_string = "-100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "500";
			static const inline std::string negative_overflow_attribute_string = "-500";
			static const char expected_value = -100;
		};

		template<>
		struct test_expectations<int8_t> : test_expectations<char>
		{};

		template<>
		struct test_expectations<uint8_t>
		{
			static const inline std::string valid_attribute_string = "100";
			static const inline std::string incomplete_attribute_string = "100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "500";
			static const inline std::string negative_overflow_attribute_string = "-1";
			static const uint8_t expected_value = 100;
		};

		template<>
		struct test_expectations<int16_t>
		{
			static const inline std::string valid_attribute_string = "-100";
			static const inline std::string incomplete_attribute_string = "-100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "32768";
			static const inline std::string negative_overflow_attribute_string = "-32769";
			static const int16_t expected_value = -100;
		};

		template<>
		struct test_expectations<uint16_t>
		{
			static const inline std::string valid_attribute_string = "100";
			static const inline std::string incomplete_attribute_string = "100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "65536";
			static const inline std::string negative_overflow_attribute_string = "-1";
			static const uint16_t expected_value = 100;
		};

		template<>
		struct test_expectations<int32_t>
		{
			static const inline std::string valid_attribute_string = "-100";
			static const inline std::string incomplete_attribute_string = "-100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "2147483648";
			static const inline std::string negative_overflow_attribute_string = "-2147483649";
			static const int32_t expected_value = -100;
		};

		template<>
		struct test_expectations<uint32_t>
		{
			static const inline std::string valid_attribute_string = "100";
			static const inline std::string incomplete_attribute_string = "100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "4294967296";
			static const inline std::string negative_overflow_attribute_string = "-1";
			static const uint32_t expected_value = 100;
		};

		template<>
		struct test_expectations<int64_t>
		{
			static const inline std::string valid_attribute_string = "-100";
			static const inline std::string incomplete_attribute_string = "-100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "9223372036854775808";
			static const inline std::string negative_overflow_attribute_string = "-9223372036854775809";
			static const int64_t expected_value = -100;
		};

		template<>
		struct test_expectations<uint64_t>
		{
			static const inline std::string valid_attribute_string = "100";
			static const inline std::string incomplete_attribute_string = "100 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = "184467440737095516105";
			static const inline std::string negative_overflow_attribute_string = "-1";
			static const uint64_t expected_value = 100;
		};

		template<>
		struct test_expectations<float>
		{
			static const inline std::string valid_attribute_string = "100.375";
			static const inline std::string incomplete_attribute_string = "100.375 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = std::string(512, '9');
			static const inline std::string negative_overflow_attribute_string = "-" + std::string(512, '9');
			static const inline float expected_value = 100.375f;
		};

		template<>
		struct test_expectations<double>
		{
			static const inline std::string valid_attribute_string = "100.375";
			static const inline std::string incomplete_attribute_string = "100.375 100";
			static const inline std::string invalid_attribute_string = "abcde";
			static const inline std::string overflow_attribute_string = std::string(512, '9');
			static const inline std::string negative_overflow_attribute_string = "-" + std::string(512, '9');
			static const inline double expected_value = 100.375f;
		};
	}




	using test_try_get_attribute_as_string = test_get_attribute_fixture<std::string>;

	TEST_F(test_try_get_attribute_as_string, no_exist)
	{
		EXPECT_FALSE(try_get_attribute_as<std::string>(xml_node(), this->attribute_name_).has_value());
	}

	TEST_F(test_try_get_attribute_as_string, convert_valid_value)
	{
		auto node(this->create_node("big blue world"));

		auto value(try_get_attribute_as<std::string>(node, this->attribute_name_));
		ASSERT_TRUE(value.has_value());
		EXPECT_EQ(value.value(), "big blue world");
	}


	template<class Type_>
	using test_try_get_attribute_as = test_get_attribute_fixture<Type_>;

	TYPED_TEST_CASE_P(test_try_get_attribute_as);

	TYPED_TEST_P(test_try_get_attribute_as, no_exist)
	{
		EXPECT_FALSE(try_get_attribute_as<TypeParam>(xml_node(), this->attribute_name_).has_value());
	}

	TYPED_TEST_P(test_try_get_attribute_as, convert_valid_value)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.valid_attribute_string));

		auto value(try_get_attribute_as<TypeParam>(node, this->attribute_name_, false));
		ASSERT_TRUE(value.has_value());
		EXPECT_EQ(value.value(), expectations.expected_value);
	}

	TYPED_TEST_P(test_try_get_attribute_as, convert_valid_value_allow_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.valid_attribute_string));

		auto value(try_get_attribute_as<TypeParam>(node, this->attribute_name_));
		ASSERT_TRUE(value.has_value());
		EXPECT_EQ(value.value(), expectations.expected_value);
	}

	TYPED_TEST_P(test_try_get_attribute_as, convert_valid_value_but_incomplete)
	{
		auto node(this->create_node(test_expectations<TypeParam>().incomplete_attribute_string));

		EXPECT_FALSE(try_get_attribute_as<TypeParam>(node, this->attribute_name_, false).has_value());
	}

	TYPED_TEST_P(test_try_get_attribute_as, convert_valid_value_but_incomplete_throws)
	{
		auto node(this->create_node(test_expectations<TypeParam>().incomplete_attribute_string));

		auto expected_message =
			"partial conversion error encountered while converting attribute `"
			+ this->attribute_name_
			+ "` to `"
			+ typeid(TypeParam).name() + "`";

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(try_get_attribute_as<TypeParam>(node, this->attribute_name_)),
			exceptions::attribute_conversion_error,
			expected_message.c_str());
	}

	TYPED_TEST_P(test_try_get_attribute_as, invalid_lexical_input)
	{
		auto node(this->create_node(test_expectations<TypeParam>().invalid_attribute_string));

		EXPECT_FALSE(try_get_attribute_as<TypeParam>(node, this->attribute_name_, false).has_value());
	}

	TYPED_TEST_P(test_try_get_attribute_as, invalid_lexical_input_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.invalid_attribute_string));

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(try_get_attribute_as<TypeParam>(node, this->attribute_name_)),
			exceptions::attribute_conversion_error,
			("invalid input error encountered while converting attribute `"
				+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
	}

	TYPED_TEST_P(test_try_get_attribute_as, positive_overflow_cast_error)
	{
		auto node(this->create_node(test_expectations<TypeParam>().overflow_attribute_string));

		EXPECT_FALSE(try_get_attribute_as<TypeParam>(node, this->attribute_name_, false).has_value());
	}

	TYPED_TEST_P(test_try_get_attribute_as, positive_overflow_cast_error_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.overflow_attribute_string));

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(try_get_attribute_as<TypeParam>(node, this->attribute_name_)),
			exceptions::attribute_conversion_error,
			("positive overflow error encountered while converting attribute `"
				+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
	}

	TYPED_TEST_P(test_try_get_attribute_as, negative_overflow_cast_error)
	{
		auto node(this->create_node(test_expectations<TypeParam>().negative_overflow_attribute_string));

		EXPECT_FALSE(try_get_attribute_as<TypeParam>(node, this->attribute_name_, false).has_value());
	}

	TYPED_TEST_P(test_try_get_attribute_as, negative_overflow_cast_error_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.negative_overflow_attribute_string));

		if constexpr (std::is_signed_v<TypeParam>)
		{
			EXPECT_THROWS_MESSAGE(
				DEBUG_DiscardResult(try_get_attribute_as<TypeParam>(node, this->attribute_name_)),
				exceptions::attribute_conversion_error,
				("negative overflow error encountered while converting attribute `"
					+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
		}
		else
		{
			EXPECT_THROWS_MESSAGE(
				DEBUG_DiscardResult(try_get_attribute_as<TypeParam>(node, this->attribute_name_)),
				exceptions::attribute_conversion_error,
				("mismatched type error encountered while converting attribute `"
					+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
		}
	}


	REGISTER_TYPED_TEST_CASE_P(
		test_try_get_attribute_as,
		no_exist,
		convert_valid_value,
		convert_valid_value_allow_throws,
		convert_valid_value_but_incomplete,
		convert_valid_value_but_incomplete_throws,
		invalid_lexical_input,
		invalid_lexical_input_throws,
		positive_overflow_cast_error,
		positive_overflow_cast_error_throws,
		negative_overflow_cast_error,
		negative_overflow_cast_error_throws);


	using try_get_attribute_as_testing_types = testing::Types<
		bool,
		char,
		int8_t,
		uint8_t,
		int16_t,
		uint16_t,
		int32_t,
		uint32_t,
		int64_t,
		uint64_t,
		float,
		double>;

	INSTANTIATE_TYPED_TEST_CASE_P(
		test_try_get_attribute_as,
		test_try_get_attribute_as,
		try_get_attribute_as_testing_types);





	template<class Type_>
	using test_get_attribute_as = test_get_attribute_fixture<Type_>;

	TYPED_TEST_CASE_P(test_get_attribute_as);

	TYPED_TEST_P(test_get_attribute_as, no_exist)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(get_attribute_as<std::string>(xml_node(), this->attribute_name_)),
			exceptions::attribute_not_found_error,
			("attribute `" + this->attribute_name_ + "` not found").c_str());
	}

	TYPED_TEST_P(test_get_attribute_as, convert_valid_value)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.valid_attribute_string));

		EXPECT_EQ(get_attribute_as<TypeParam>(node, this->attribute_name_), expectations.expected_value);
	}

	TYPED_TEST_P(test_get_attribute_as, convert_valid_value_allow_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.valid_attribute_string));

		EXPECT_NO_THROW(DEBUG_DiscardResult(get_attribute_as<TypeParam>(node, this->attribute_name_)));
	}

	TYPED_TEST_P(test_get_attribute_as, convert_valid_value_but_incomplete_throws)
	{
		auto node(this->create_node(test_expectations<TypeParam>().incomplete_attribute_string));

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(get_attribute_as<TypeParam>(node, this->attribute_name_)),
			exceptions::attribute_conversion_error,
			("partial conversion error encountered while converting attribute `"
				+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
	}

	TYPED_TEST_P(test_get_attribute_as, invalid_lexical_input_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.invalid_attribute_string));

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(get_attribute_as<TypeParam>(node, this->attribute_name_)),
			exceptions::attribute_conversion_error,
			("invalid input error encountered while converting attribute `"
				+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
	}

	TYPED_TEST_P(test_get_attribute_as, positive_overflow_cast_error_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.overflow_attribute_string));

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(get_attribute_as<TypeParam>(node, this->attribute_name_)),
			exceptions::attribute_conversion_error,
			("positive overflow error encountered while converting attribute `"
				+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
	}

	TYPED_TEST_P(test_get_attribute_as, negative_overflow_cast_error_throws)
	{
		test_expectations<TypeParam> expectations;

		auto node(this->create_node(expectations.negative_overflow_attribute_string));

		if constexpr (std::is_signed_v<TypeParam>)
		{
			EXPECT_THROWS_MESSAGE(
				DEBUG_DiscardResult(get_attribute_as<TypeParam>(node, this->attribute_name_)),
				exceptions::attribute_conversion_error,
				("negative overflow error encountered while converting attribute `"
					+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
		}
		else
		{
			EXPECT_THROWS_MESSAGE(
				DEBUG_DiscardResult(get_attribute_as<TypeParam>(node, this->attribute_name_)),
				exceptions::attribute_conversion_error,
				("mismatched type error encountered while converting attribute `"
					+ this->attribute_name_ + "` to `" + typeid(TypeParam).name() + "`").c_str());
		}
	}


	REGISTER_TYPED_TEST_CASE_P(
		test_get_attribute_as,
		no_exist,
		convert_valid_value,
		convert_valid_value_allow_throws,
		convert_valid_value_but_incomplete_throws,
		invalid_lexical_input_throws,
		positive_overflow_cast_error_throws,
		negative_overflow_cast_error_throws);


	using get_attribute_as_testing_types = testing::Types<
		bool,
		char,
		int8_t,
		uint8_t,
		int16_t,
		uint16_t,
		int32_t,
		uint32_t,
		int64_t,
		uint64_t,
		float,
		double>;

	INSTANTIATE_TYPED_TEST_CASE_P(
		test_get_attribute_as,
		test_get_attribute_as,
		get_attribute_as_testing_types);



}}}}}
