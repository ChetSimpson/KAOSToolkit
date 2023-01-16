// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/empty_bitfield.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech { namespace kaos { namespace core { namespace types { namespace unittests
{

	TEST(empty_bitfield, empty_name)
	{
		EXPECT_THROWS_MESSAGE(empty_bitfield<uint8_t>(""), std::invalid_argument, "Bitfield name cannot be empty");
	}

	TEST(empty_bitfield, valid_name)
	{
		EXPECT_EQ(empty_bitfield<uint8_t>("SomeName").name(), "SomeName");
	}

	TEST(empty_bitfield, anonymous_name)
	{
		EXPECT_EQ(empty_bitfield<uint8_t>().name(), "<anonymous>");
	}

	TEST(empty_bitfield, explicit_anonymous_name)
	{
		EXPECT_THROWS_MESSAGE(
			empty_bitfield<uint8_t>("<anonymous>"),
			std::invalid_argument,
			"Bitfield cannot be explicitly named `<anonymous>`");
	}
		
	TEST(empty_bitfield, equals_with_empty_name)
	{
		EXPECT_EQ(empty_bitfield<uint8_t>(), empty_bitfield<uint8_t>());
	}

	TEST(empty_bitfield, equals_with_name)
	{
		EXPECT_EQ(empty_bitfield<uint8_t>("red"), empty_bitfield<uint8_t>("red"));
	}

	TEST(empty_bitfield, not_equals_with_empty_name)
	{
		EXPECT_NE(empty_bitfield<uint8_t>(), empty_bitfield<uint8_t>("red"));
		EXPECT_NE(empty_bitfield<uint8_t>("red"), empty_bitfield<uint8_t>());
	}

	TEST(empty_bitfield, not_equals_with_different_names)
	{
		EXPECT_NE(empty_bitfield<uint8_t>("red"), empty_bitfield<uint8_t>("blue"));
	}

	TEST(empty_bitfield, all_properties)
	{
		empty_bitfield<uint8_t> bitfield;

		EXPECT_EQ(bitfield.size(), 0U);
		EXPECT_EQ(bitfield.max_value(), 0U);
		EXPECT_EQ(bitfield.mask(), 0U);
	}

	TEST(empty_bitfield, get_from)
	{
		empty_bitfield<uint8_t> bitfield;

		EXPECT_EQ(bitfield.get_from(std::numeric_limits<uint8_t>::max()), 0);
	}

	TEST(empty_bitfield, set_in)
	{
		empty_bitfield<uint8_t> bitfield;

		EXPECT_EQ(bitfield.set_in(0, 0), 0);

		for (uint8_t i(1U); i < std::numeric_limits<uint8_t>::max(); ++i)
		{
			ASSERT_THROWS_MESSAGE(
				bitfield.set_in(std::numeric_limits<uint8_t>::max(), i),
				std::overflow_error,
				"value is too large to fit in the null bitfield");
		}
	}


}}}}}
