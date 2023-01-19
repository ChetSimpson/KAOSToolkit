// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/utility/bit_reader.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>
#include <array>
#include <vector>



namespace hypertech::kaos::core::utility::unittests
{

	namespace
	{
		template<class TestDataType_>
		class test_bit_reader : public ::testing::Test
		{
		};

		template<class Type_>
		struct typed_test_data;

		template<>
		struct typed_test_data<uint8_t>
		{
			static const inline std::vector<uint8_t> data = {
				0b10101010U,
				0b11111111U,
				0b00000000U,
				0b11110000U,
				0b11001100U,
				0b00110011U,
				0b11100111U,
				0b00011000U,
				0b10000000U,
				0b01000000U,
				0b00100000U,
				0b00010000U,
				0b00001000U,
				0b00000100U,
				0b00000010U,
				0b00000001U,
			};
		};

		template<>
		struct typed_test_data<uint16_t>
		{
			static const inline std::vector<uint16_t> data = {
				0b1010101011111111U,
				0b0000000011110000U,
				0b1100110000110011U,
				0b1110011100011000U,
				0b1000000001000000U,
				0b0010000000010000U,
				0b0000100000000100U,
				0b0000001000000001U,
			};
		};

		template<>
		struct typed_test_data<uint32_t>
		{
			static const inline std::vector<uint32_t> data = {
				0b10101010111111110000000011110000U,
				0b11001100001100111110011100011000U,
				0b10000000010000000010000000010000U,
				0b00001000000001000000001000000001U,
			};

		};

		template<>
		struct typed_test_data<uint64_t>
		{
			static const inline std::vector<uint64_t> data = {
				0b1010101011111111000000001111000011001100001100111110011100011000U,
				0b1000000001000000001000000001000000001000000001000000001000000001U,
			};
		};

	}

	TEST(test_bit_reader, construct_default)
	{
		bit_reader<uint8_t> reader;

		EXPECT_FALSE(reader.is_open());
		ASSERT_TRUE(reader.empty());
		EXPECT_THROWS_MESSAGE(
			reader.read(),
			std::runtime_error,
			"attempt to read from closed bit reader");
		EXPECT_NO_THROW(reader.close());
	}

	TEST(test_bit_reader, construct_range)
	{
		std::array<uint8_t, 10> data;
		bit_reader<uint8_t> reader(data);

		ASSERT_FALSE(reader.empty());
		EXPECT_TRUE(reader.is_open());
		EXPECT_NO_THROW(reader.read());
		EXPECT_NO_THROW(reader.close());
	}

	TEST(test_bit_reader, construct_range_then_open)
	{
		std::array<uint8_t, 10> data;
		bit_reader<uint8_t> reader(data);

		EXPECT_THROWS_MESSAGE(
			reader.open(data),
			std::runtime_error,
			"attempt to open bit reader that's already open");
	}

	TEST(test_bit_reader, open_empty_range)
	{
		bit_reader<uint8_t> reader;

		EXPECT_THROWS_MESSAGE(
			reader.open(std::vector<uint8_t>()),
			std::invalid_argument,
			"attempt to open bit reader with empty range");
	}

	TEST(test_bit_reader, open_then_close)
	{
		std::array<uint8_t, 10> data;
		bit_reader<uint8_t> reader;

		ASSERT_TRUE(reader.empty());
		reader.open(data);
		EXPECT_TRUE(reader.is_open());
		ASSERT_FALSE(reader.empty());
		reader.close();
		EXPECT_FALSE(reader.is_open());
		ASSERT_TRUE(reader.empty());
		EXPECT_THROWS_MESSAGE(
			reader.read(),
			std::runtime_error,
			"attempt to read from closed bit reader");
	}

	TYPED_TEST_CASE_P(test_bit_reader);

	TYPED_TEST_P(test_bit_reader, read)
	{
		using value_type = TypeParam;
		const auto digits = std::numeric_limits<value_type>::digits;

		std::vector<value_type> data = typed_test_data<value_type>::data;
		bit_reader<value_type> reader(data);

		for (const auto& test_value : data)
		{
			for (auto i(digits); i > 0U; --i)
			{
				auto value = reader.read();
				ASSERT_EQ(value, ((test_value >> (i - 1)) & 1) != 0);
			}
		}

		ASSERT_TRUE(reader.empty());

		EXPECT_THROWS_MESSAGE(
			reader.read(),
			exceptions::end_of_file_error,
			"file error: attempt to read past end of bit reader range");
	}


	REGISTER_TYPED_TEST_CASE_P(test_bit_reader, read);
	using read_testing_types = testing::Types<uint8_t, uint16_t, uint32_t, uint64_t>;

	INSTANTIATE_TYPED_TEST_CASE_P(test_bit_reader, test_bit_reader, read_testing_types);

}
