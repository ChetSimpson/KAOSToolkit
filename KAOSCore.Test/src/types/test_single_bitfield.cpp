// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/single_bitfield.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech::kaos::core::types::unittests
{

	TEST(single_bitfield, empty_name)
	{
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>({}, 1, 0), std::invalid_argument, "Bitfield name cannot be empty");
	}

	TEST(single_bitfield, valid_name)
	{
		EXPECT_EQ(single_bitfield<uint8_t>("SomeName", 1, 0).name(), "SomeName");
	}

	TEST(single_bitfield, anonymous_name)
	{
		EXPECT_EQ(single_bitfield<uint8_t>(1, 0).name(), "<anonymous>");
	}

	TEST(single_bitfield, explicit_anonymous_name)
	{
		EXPECT_THROWS_MESSAGE(
			single_bitfield<uint8_t>("<anonymous>", 1, 0),
			std::invalid_argument,
			"Bitfield cannot be explicitly named `<anonymous>`");
	}

	TEST(single_bitfield, zero_field_size)
	{
		EXPECT_THROWS_MESSAGE(
			single_bitfield<uint8_t>(0, 0),
			std::invalid_argument,
			"Field size passed to single_bitfield cannot be 0");
	}

	TEST(single_bitfield, field_size_too_big)
	{
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(9, 0), std::overflow_error, "Field size passed to single_bitfield is too large");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint16_t>(17, 0), std::overflow_error, "Field size passed to single_bitfield is too large");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint32_t>(33, 0), std::overflow_error, "Field size passed to single_bitfield is too large");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint64_t>(65, 0), std::overflow_error, "Field size passed to single_bitfield is too large");
	}

	TEST(single_bitfield, field_position_overflow)
	{
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(1, 8), std::overflow_error, "Field position passed to single_bitfield exceeds bounds of storage type");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint16_t>(1, 16), std::overflow_error, "Field position passed to single_bitfield exceeds bounds of storage type");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint32_t>(1, 32), std::overflow_error, "Field position passed to single_bitfield exceeds bounds of storage type");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint64_t>(1, 64), std::overflow_error, "Field position passed to single_bitfield exceeds bounds of storage type");
	}

	TEST(single_bitfield, field_size_and_position_overflow)
	{
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(4, 5), std::overflow_error, "Field size passed to single_bitfield exceeds value type based on position");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint16_t>(4, 13), std::overflow_error, "Field size passed to single_bitfield exceeds value type based on position");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint32_t>(4, 29), std::overflow_error, "Field size passed to single_bitfield exceeds value type based on position");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint64_t>(4, 61), std::overflow_error, "Field size passed to single_bitfield exceeds value type based on position");
	}


	TEST(single_bitfield, equals_with_empty_name)
	{
		EXPECT_EQ(single_bitfield<uint8_t>(8, 0), single_bitfield<uint8_t>(8, 0));
		EXPECT_EQ(single_bitfield<uint8_t>(4, 0), single_bitfield<uint8_t>(4, 0));
		EXPECT_EQ(single_bitfield<uint8_t>(4, 4), single_bitfield<uint8_t>(4, 4));
		EXPECT_EQ(single_bitfield<uint8_t>(5, 1), single_bitfield<uint8_t>(5, 1));
	}

	TEST(single_bitfield, equals_with_name)
	{
		EXPECT_EQ(single_bitfield<uint8_t>("red", 8, 0), single_bitfield<uint8_t>("red", 8, 0));
		EXPECT_EQ(single_bitfield<uint8_t>("red", 4, 0), single_bitfield<uint8_t>("red", 4, 0));
		EXPECT_EQ(single_bitfield<uint8_t>("red", 4, 4), single_bitfield<uint8_t>("red", 4, 4));
		EXPECT_EQ(single_bitfield<uint8_t>("red", 5, 1), single_bitfield<uint8_t>("red", 5, 1));
	}

	TEST(single_bitfield, not_equals_with_empty_name)
	{
		EXPECT_NE(single_bitfield<uint8_t>("red", 8, 0), single_bitfield<uint8_t>(8, 0));
		EXPECT_NE(single_bitfield<uint8_t>("red", 4, 0), single_bitfield<uint8_t>(4, 0));
		EXPECT_NE(single_bitfield<uint8_t>("red", 4, 4), single_bitfield<uint8_t>(4, 4));
		EXPECT_NE(single_bitfield<uint8_t>("red", 5, 1), single_bitfield<uint8_t>(5, 1));

		EXPECT_NE(single_bitfield<uint8_t>(8, 0), single_bitfield<uint8_t>("red", 8, 0));
		EXPECT_NE(single_bitfield<uint8_t>(4, 0), single_bitfield<uint8_t>("red", 4, 0));
		EXPECT_NE(single_bitfield<uint8_t>(4, 4), single_bitfield<uint8_t>("red", 4, 4));
		EXPECT_NE(single_bitfield<uint8_t>(5, 1), single_bitfield<uint8_t>("red", 5, 1));
	}

	TEST(single_bitfield, not_equals_with_different_names)
	{
		EXPECT_NE(single_bitfield<uint8_t>("red", 8, 0), single_bitfield<uint8_t>("blue", 8, 0));
		EXPECT_NE(single_bitfield<uint8_t>("red", 4, 0), single_bitfield<uint8_t>("blue", 4, 0));
		EXPECT_NE(single_bitfield<uint8_t>("red", 4, 4), single_bitfield<uint8_t>("blue", 4, 4));
		EXPECT_NE(single_bitfield<uint8_t>("red", 5, 1), single_bitfield<uint8_t>("blue", 5, 1));

		EXPECT_NE(single_bitfield<uint8_t>("blue", 8, 0), single_bitfield<uint8_t>("red", 8, 0));
		EXPECT_NE(single_bitfield<uint8_t>("blue", 4, 0), single_bitfield<uint8_t>("red", 4, 0));
		EXPECT_NE(single_bitfield<uint8_t>("blue", 4, 4), single_bitfield<uint8_t>("red", 4, 4));
		EXPECT_NE(single_bitfield<uint8_t>("blue", 5, 1), single_bitfield<uint8_t>("red", 5, 1));
	}


	TEST(single_bitfield, size)
	{
		using value_type = uint64_t;

		for (auto size(1U); size < std::numeric_limits<value_type>::digits; ++size)
		{
			EXPECT_EQ(single_bitfield<value_type>(size, 0).size(), size);
		}
	}


	TEST(single_bitfield, max_value)
	{
		using value_type = uint64_t;

		for (auto size(1U); size < std::numeric_limits<value_type>::digits; ++size)
		{
			auto max_value = ~(~value_type(0) << (size - 1) << 1);
			EXPECT_EQ(single_bitfield<value_type>(size, 0).max_value(), max_value);
		}
	}


	TEST(single_bitfield, field_masks_for_sizes)
	{
		using value_type = uint64_t;
		for(auto size = 1U; size <= std::numeric_limits<value_type>::digits; ++size)
		{
			const auto expected_mask(~value_type(0) >> (std::numeric_limits<value_type>::digits - size));

			EXPECT_EQ(single_bitfield<value_type>(size, 0).mask(), expected_mask);
		}
	}

	TEST(single_bitfield, field_mask_for_field_positions)
	{
		using value_type = uint64_t;
		const value_type base_mask = 0b1111;
		const auto field_size = 4U;

		for (auto position(0U); position < std::numeric_limits<value_type>::digits - 4; ++position)
		{
			EXPECT_EQ(single_bitfield<value_type>(field_size, position).mask(), base_mask << position);
		}
	}

	TEST(single_bitfield, home_masks_for_sizes)
	{
		using value_type = uint64_t;
		for(auto size = 1U; size <= std::numeric_limits<value_type>::digits; ++size)
		{
			const auto expected_mask(~value_type(0) >> (std::numeric_limits<value_type>::digits - size));

			EXPECT_EQ(single_bitfield<value_type>(size, 0).mask(), expected_mask);
		}
	}




	TEST(single_bitfield, get_single_bit)
	{
		using value_type = uint64_t;
		const auto position(5U);

		single_bitfield<value_type> bitfield(1, position);
		for (auto bit_position(0U); bit_position < std::numeric_limits<value_type>::digits; ++bit_position)
		{
			const value_type expected_value = position == bit_position ? 0 : 1;
			//	The base value has every bit set except for the one at the current bit_position
			const value_type base_value = ~(value_type(1) << bit_position);

			EXPECT_EQ(bitfield.get_from(base_value), expected_value);
		}
	}


	TEST(single_bitfield, get_multiple_bits)
	{
		using value_type = uint64_t;
		const value_type base_mask = 0b111;
		const auto field_size = 3U;

		for (auto field_position(0U); field_position < std::numeric_limits<value_type>::digits - field_size; ++field_position)
		{
			for (value_type expected_value = 0U; expected_value <= base_mask; ++expected_value)
			{
				const value_type field_mask(base_mask << field_position);
				const value_type base_value(~field_mask | (expected_value << field_position));

				EXPECT_EQ(single_bitfield<value_type>(3, field_position).get_from(base_value), expected_value);
			}
		}
	}




	TEST(single_bitfield, set_value_overflow)
	{
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(1, 0).set_in(0, 0b00000011), std::overflow_error, "value is too large to fit in the allocated bitfield");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(2, 0).set_in(0, 0b00000111), std::overflow_error, "value is too large to fit in the allocated bitfield");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(3, 0).set_in(0, 0b00001111), std::overflow_error, "value is too large to fit in the allocated bitfield");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(4, 0).set_in(0, 0b00011111), std::overflow_error, "value is too large to fit in the allocated bitfield");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(5, 0).set_in(0, 0b00111111), std::overflow_error, "value is too large to fit in the allocated bitfield");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(6, 0).set_in(0, 0b01111111), std::overflow_error, "value is too large to fit in the allocated bitfield");
		EXPECT_THROWS_MESSAGE(single_bitfield<uint8_t>(7, 0).set_in(0, 0b11111111), std::overflow_error, "value is too large to fit in the allocated bitfield");
	}




	TEST(single_bitfield, set_single_bit_all_positions)
	{
		using value_type = uint64_t;

		for (auto position(0); position < std::numeric_limits<value_type>::digits - 1; ++position)
		{
			EXPECT_EQ(single_bitfield<value_type>(1, position).set_in(0, 1), value_type(1) << position);

		}
	}


	TEST(single_bitfield, set_multiple_bits_all_positions)
	{
		using value_type = uint64_t;
		const value_type base_mask = 0b111;
		const auto field_size = 3U;

		for (auto field_position(0U); field_position < std::numeric_limits<value_type>::digits - field_size; ++field_position)
		{
			for (value_type value = 0U; value <= base_mask; ++value)
			{
				const value_type expected_value(value << field_position);

				EXPECT_EQ(single_bitfield<value_type>(field_size, field_position).set_in(0, value), expected_value);
			}
		}
	}

}
