// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/split_bitfield.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech { namespace kaos { namespace core { namespace types { namespace unittests
{

	namespace
	{
		const split_bitfield<size_t> bitfield_3_0({ 1, 3, 1, 0 });
		const split_bitfield<size_t> bitfield_4_1({ 1, 4, 1, 1 });
		const split_bitfield<size_t> bitfield_5_2({ 1, 5, 1, 2 });
	}


	TEST(split_bitfield, empty_name)
	{
		EXPECT_THROWS_MESSAGE(split_bitfield<uint8_t>({}, 1, 3, 1, 0), std::invalid_argument, "Split bitfield name cannot be empty");
	}

	TEST(split_bitfield, valid_name)
	{
		EXPECT_EQ(split_bitfield<uint8_t>("SomeName", 1, 3, 1, 0).name(), "SomeName");
	}

	TEST(split_bitfield, anonymous_name)
	{
		EXPECT_EQ(split_bitfield<uint8_t>(1, 3, 1, 0).name(), "<anonymous>");
	}

	TEST(split_bitfield, explicit_anonymous_name)
	{
		EXPECT_THROWS_MESSAGE(
			split_bitfield<uint8_t>("<anonymous>", 1, 3, 1, 0),
			std::invalid_argument,
			"Split bitfield cannot be explicitly named `<anonymous>`");
	}


	TEST(split_bitfield, equals_with_empty_name)
	{
		EXPECT_EQ(split_bitfield<uint16_t>(4, 8, 8, 0), split_bitfield<uint16_t>(4, 8, 8, 0));
		EXPECT_EQ(split_bitfield<uint16_t>(5, 8, 4, 0), split_bitfield<uint16_t>(5, 8, 4, 0));
		EXPECT_EQ(split_bitfield<uint16_t>(6, 9, 4, 4), split_bitfield<uint16_t>(6, 9, 4, 4));
		EXPECT_EQ(split_bitfield<uint16_t>(7, 9, 5, 1), split_bitfield<uint16_t>(7, 9, 5, 1));
	}

	TEST(split_bitfield, equals_with_name)
	{
		EXPECT_EQ(split_bitfield<uint16_t>("red", 4, 8, 8, 0), split_bitfield<uint16_t>("red", 4, 8, 8, 0));
		EXPECT_EQ(split_bitfield<uint16_t>("red", 5, 8, 4, 0), split_bitfield<uint16_t>("red", 5, 8, 4, 0));
		EXPECT_EQ(split_bitfield<uint16_t>("red", 6, 9, 4, 4), split_bitfield<uint16_t>("red", 6, 9, 4, 4));
		EXPECT_EQ(split_bitfield<uint16_t>("red", 7, 9, 5, 1), split_bitfield<uint16_t>("red", 7, 9, 5, 1));
	}

	TEST(split_bitfield, not_equals_with_empty_name)
	{
		EXPECT_NE(split_bitfield<uint16_t>("red", 4, 8, 8, 0), split_bitfield<uint16_t>(4, 8, 8, 0));
		EXPECT_NE(split_bitfield<uint16_t>("red", 5, 8, 4, 0), split_bitfield<uint16_t>(4, 8, 4, 0));
		EXPECT_NE(split_bitfield<uint16_t>("red", 6, 9, 4, 4), split_bitfield<uint16_t>(4, 8, 4, 4));
		EXPECT_NE(split_bitfield<uint16_t>("red", 7, 9, 5, 1), split_bitfield<uint16_t>(4, 8, 4, 1));

		EXPECT_NE(split_bitfield<uint16_t>(4, 8, 8, 0), split_bitfield<uint16_t>("red", 4, 8, 8, 0));
		EXPECT_NE(split_bitfield<uint16_t>(4, 8, 4, 0), split_bitfield<uint16_t>("red", 4, 8, 4, 0));
		EXPECT_NE(split_bitfield<uint16_t>(4, 8, 4, 4), split_bitfield<uint16_t>("red", 4, 8, 4, 4));
		EXPECT_NE(split_bitfield<uint16_t>(4, 8, 5, 1), split_bitfield<uint16_t>("red", 4, 8, 5, 1));
	}

	TEST(split_bitfield, not_equals_with_different_names)
	{
		EXPECT_NE(split_bitfield<uint16_t>("red", 4, 8, 8, 0), split_bitfield<uint16_t>("blue", 4, 8, 8, 0));
		EXPECT_NE(split_bitfield<uint16_t>("red", 4, 8, 4, 0), split_bitfield<uint16_t>("blue", 4, 8, 4, 0));
		EXPECT_NE(split_bitfield<uint16_t>("red", 4, 8, 4, 4), split_bitfield<uint16_t>("blue", 4, 8, 4, 4));
		EXPECT_NE(split_bitfield<uint16_t>("red", 4, 8, 5, 1), split_bitfield<uint16_t>("blue", 4, 8, 5, 1));

		EXPECT_NE(split_bitfield<uint16_t>("blue", 4, 8, 8, 0), split_bitfield<uint16_t>("red", 4, 8, 8, 0));
		EXPECT_NE(split_bitfield<uint16_t>("blue", 4, 8, 4, 0), split_bitfield<uint16_t>("red", 4, 8, 4, 0));
		EXPECT_NE(split_bitfield<uint16_t>("blue", 4, 8, 4, 4), split_bitfield<uint16_t>("red", 4, 8, 4, 4));
		EXPECT_NE(split_bitfield<uint16_t>("blue", 4, 8, 5, 1), split_bitfield<uint16_t>("red", 4, 8, 5, 1));
	}


	TEST(split_bitfield, size)
	{
		EXPECT_EQ(split_bitfield<uint64_t>({ 1, 3, 1, 0 }).size(), 2U);
		EXPECT_EQ(split_bitfield<uint64_t>({ 1, 0, 3, 1 }).size(), 4U);
		EXPECT_EQ(split_bitfield<uint64_t>({ 4, 0, 4, 4 }).size(), 8U);
		EXPECT_EQ(split_bitfield<uint64_t>({ 32, 32, 32, 0 }).size(), 64U);
	}


	TEST(split_bitfield, field_bit_mask)
	{
		EXPECT_EQ(bitfield_3_0.mask(), 0b00001001U);
		EXPECT_EQ(bitfield_4_1.mask(), 0b00010010U);
		EXPECT_EQ(bitfield_5_2.mask(), 0b00100100U);
	}


	TEST(split_bitfield, get)
	{
		EXPECT_EQ(bitfield_3_0.get_from(0b00000000), 0b00000000U);
		EXPECT_EQ(bitfield_3_0.get_from(0b00000001), 0b00000001U);
		EXPECT_EQ(bitfield_3_0.get_from(0b00001000), 0b00000010U);
		EXPECT_EQ(bitfield_3_0.get_from(0b00001001), 0b00000011U);

		EXPECT_EQ(bitfield_4_1.get_from(0b00000000), 0b00000000U);
		EXPECT_EQ(bitfield_4_1.get_from(0b00000010), 0b00000001U);
		EXPECT_EQ(bitfield_4_1.get_from(0b00010000), 0b00000010U);
		EXPECT_EQ(bitfield_4_1.get_from(0b00010010), 0b00000011U);

		EXPECT_EQ(bitfield_5_2.get_from(0b00000000), 0b00000000U);
		EXPECT_EQ(bitfield_5_2.get_from(0b00000100), 0b00000001U);
		EXPECT_EQ(bitfield_5_2.get_from(0b00100000), 0b00000010U);
		EXPECT_EQ(bitfield_5_2.get_from(0b00100100), 0b00000011U);
	}

	TEST(split_bitfield, set)
	{
		EXPECT_EQ(bitfield_3_0.set_in(0, 0b00000000), 0b00000000U);
		EXPECT_EQ(bitfield_3_0.set_in(0, 0b00000001), 0b00000001U);
		EXPECT_EQ(bitfield_3_0.set_in(0, 0b00000010), 0b00001000U);
		EXPECT_EQ(bitfield_3_0.set_in(0, 0b00000011), 0b00001001U);

		EXPECT_EQ(bitfield_4_1.set_in(0, 0b00000000), 0b00000000U);
		EXPECT_EQ(bitfield_4_1.set_in(0, 0b00000001), 0b00000010U);
		EXPECT_EQ(bitfield_4_1.set_in(0, 0b00000010), 0b00010000U);
		EXPECT_EQ(bitfield_4_1.set_in(0, 0b00000011), 0b00010010U);

		EXPECT_EQ(bitfield_5_2.set_in(0, 0b00000000), 0b00000000U);
		EXPECT_EQ(bitfield_5_2.set_in(0, 0b00000001), 0b00000100U);
		EXPECT_EQ(bitfield_5_2.set_in(0, 0b00000010), 0b00100000U);
		EXPECT_EQ(bitfield_5_2.set_in(0, 0b00000011), 0b00100100U);
	}

	TEST(split_bitfield, set_value_overflow)
	{
		EXPECT_THROWS_MESSAGE(split_bitfield<uint8_t>(1, 1, 1, 0).set_in(0, 0b00000111), std::overflow_error, "value is too large to fit in the allocated split bitfields");
		EXPECT_THROWS_MESSAGE(split_bitfield<uint8_t>(2, 1, 1, 0).set_in(0, 0b00001111), std::overflow_error, "value is too large to fit in the allocated split bitfields");
		EXPECT_THROWS_MESSAGE(split_bitfield<uint8_t>(3, 1, 1, 0).set_in(0, 0b00011111), std::overflow_error, "value is too large to fit in the allocated split bitfields");
		EXPECT_THROWS_MESSAGE(split_bitfield<uint8_t>(4, 1, 1, 0).set_in(0, 0b00111111), std::overflow_error, "value is too large to fit in the allocated split bitfields");
		EXPECT_THROWS_MESSAGE(split_bitfield<uint8_t>(5, 1, 1, 0).set_in(0, 0b01111111), std::overflow_error, "value is too large to fit in the allocated split bitfields");
		EXPECT_THROWS_MESSAGE(split_bitfield<uint8_t>(6, 1, 1, 0).set_in(0, 0b11111111), std::overflow_error, "value is too large to fit in the allocated split bitfields");
	}

}}}}}
