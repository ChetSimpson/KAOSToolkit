// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/tc1014/tc1014_color_layout.h>
#include <kaos/assetfoo/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <array>


namespace hypertech::kaos::assetfoo::colors::tc1014::unittests	
{

	class tc1014_color_layout_fixture : public ::testing::Test
	{
	protected:

		const tc1014_color_layout layout_;
		static const std::array<unsigned, 4> valid_component_values_;
		static const std::array<unsigned, 4> red_color_levels_;
		static const std::array<unsigned, 4> green_color_levels_;
		static const std::array<unsigned, 4> blue_color_levels_;
	};

	const std::array<unsigned, 4> tc1014_color_layout_fixture::valid_component_values_{ 0, 85, 170, 255 };
	const std::array<unsigned, 4> tc1014_color_layout_fixture::red_color_levels_{ 0b00000000, 0b00000100, 0b00100000, 0b00100100 };
	const std::array<unsigned, 4> tc1014_color_layout_fixture::green_color_levels_{ 0b00000000, 0b00000010, 0b00010000, 0b00010010 };
	const std::array<unsigned, 4> tc1014_color_layout_fixture::blue_color_levels_{ 0b00000000, 0b00000001, 0b00001000, 0b00001001 };


	TEST_F(tc1014_color_layout_fixture, component_sizes)
	{
		EXPECT_EQ(layout_.red_component_size(), 2);
		EXPECT_EQ(layout_.green_component_size(), 2);
		EXPECT_EQ(layout_.blue_component_size(), 2);
	}


	TEST_F(tc1014_color_layout_fixture, max_values)
	{
		EXPECT_EQ(layout_.red_component_max_value(), 3);
		EXPECT_EQ(layout_.green_component_max_value(), 3);
		EXPECT_EQ(layout_.blue_component_max_value(), 3);
	}


	TEST_F(tc1014_color_layout_fixture, packed_color_bitmask)
	{
		EXPECT_EQ(layout_.packed_color_bitmask(), 0b00111111);
	}


	TEST_F(tc1014_color_layout_fixture, red_color_bitfields)
	{
		const auto& bitfield(layout_.red_component_bitfield());

		for (auto i(0U); i < red_color_levels_.size(); ++i)
		{
			EXPECT_EQ(red_color_levels_[i], bitfield.set_in(0, i));
		}
	}

	TEST_F(tc1014_color_layout_fixture, green_color_bitfields)
	{
		const auto& bitfield(layout_.green_component_bitfield());

		for (auto i(0U); i < green_color_levels_.size(); ++i)
		{
			EXPECT_EQ(green_color_levels_[i], bitfield.set_in(0, i));
		}
	}

	TEST_F(tc1014_color_layout_fixture, blue_color_bitfields)
	{
		const auto& bitfield(layout_.blue_component_bitfield());

		for (auto i(0U); i < blue_color_levels_.size(); ++i)
		{
			EXPECT_EQ(blue_color_levels_[i], bitfield.set_in(0, i));
		}
	}

}
