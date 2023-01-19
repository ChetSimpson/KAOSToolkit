// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/colors/tc1014/tc1014_color_converter.h>
#include <kaos/core/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <array>


namespace hypertech::kaos::assetfoo::colors::tc1014::unittests	
{

	namespace
	{
		using native_color_map_type = tc1014_color_converter::native_color_map_type;
		using color_space_type = tc1014_color_converter::color_space_type;

		const tc1014_color_converter::native_color_map_type unconverted_native_colormap =
		{
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
			0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
			0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
			0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
		};

		std::array<tc1014_color_converter::color_type, 64> expected_rgb_to_rgba_colors = {
			tc1014_color_converter::color_type(0x00, 0x00, 0x00),
			tc1014_color_converter::color_type(0x00, 0x00, 0x55),
			tc1014_color_converter::color_type(0x00, 0x55, 0x00),
			tc1014_color_converter::color_type(0x00, 0x55, 0x55),
			tc1014_color_converter::color_type(0x55, 0x00, 0x00),
			tc1014_color_converter::color_type(0x55, 0x00, 0x55),
			tc1014_color_converter::color_type(0x55, 0x55, 0x00),
			tc1014_color_converter::color_type(0x55, 0x55, 0x55),
			tc1014_color_converter::color_type(0x00, 0x00, 0xAA),
			tc1014_color_converter::color_type(0x00, 0x00, 0xFF),
			tc1014_color_converter::color_type(0x00, 0x55, 0xAA),
			tc1014_color_converter::color_type(0x00, 0x55, 0xFF),
			tc1014_color_converter::color_type(0x55, 0x00, 0xAA),
			tc1014_color_converter::color_type(0x55, 0x00, 0xFF),
			tc1014_color_converter::color_type(0x55, 0x55, 0xAA),
			tc1014_color_converter::color_type(0x55, 0x55, 0xFF),
			tc1014_color_converter::color_type(0x00, 0xAA, 0x00),
			tc1014_color_converter::color_type(0x00, 0xAA, 0x55),
			tc1014_color_converter::color_type(0x00, 0xFF, 0x00),
			tc1014_color_converter::color_type(0x00, 0xFF, 0x55),
			tc1014_color_converter::color_type(0x55, 0xAA, 0x00),
			tc1014_color_converter::color_type(0x55, 0xAA, 0x55),
			tc1014_color_converter::color_type(0x55, 0xFF, 0x00),
			tc1014_color_converter::color_type(0x55, 0xFF, 0x55),
			tc1014_color_converter::color_type(0x00, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0x00, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0x00, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0x00, 0xFF, 0xFF),
			tc1014_color_converter::color_type(0x55, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0x55, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0x55, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0x55, 0xFF, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0x00, 0x00),
			tc1014_color_converter::color_type(0xAA, 0x00, 0x55),
			tc1014_color_converter::color_type(0xAA, 0x55, 0x00),
			tc1014_color_converter::color_type(0xAA, 0x55, 0x55),
			tc1014_color_converter::color_type(0xFF, 0x00, 0x00),
			tc1014_color_converter::color_type(0xFF, 0x00, 0x55),
			tc1014_color_converter::color_type(0xFF, 0x55, 0x00),
			tc1014_color_converter::color_type(0xFF, 0x55, 0x55),
			tc1014_color_converter::color_type(0xAA, 0x00, 0xAA),
			tc1014_color_converter::color_type(0xAA, 0x00, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0x55, 0xAA),
			tc1014_color_converter::color_type(0xAA, 0x55, 0xFF),
			tc1014_color_converter::color_type(0xFF, 0x00, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0x00, 0xFF),
			tc1014_color_converter::color_type(0xFF, 0x55, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0x55, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0x00),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0x55),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0x00),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0x55),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0x00),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0x55),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0x00),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0x55),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0xFF),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0xFF),
		};

		std::array<tc1014_color_converter::color_type, 64> expected_composite_to_rgba_colors = {
			tc1014_color_converter::color_type(0x00, 0x00, 0x00),
			tc1014_color_converter::color_type(0x00, 0x55, 0x00),
			tc1014_color_converter::color_type(0x00, 0x55, 0x00),
			tc1014_color_converter::color_type(0x55, 0x55, 0x00),
			tc1014_color_converter::color_type(0x00, 0x00, 0x00),
			tc1014_color_converter::color_type(0x55, 0x00, 0x00),
			tc1014_color_converter::color_type(0xAA, 0x00, 0x55),
			tc1014_color_converter::color_type(0xAA, 0x00, 0x00),
			tc1014_color_converter::color_type(0xAA, 0x00, 0x00),
			tc1014_color_converter::color_type(0xFF, 0x00, 0xFF),
			tc1014_color_converter::color_type(0x55, 0x00, 0x55),
			tc1014_color_converter::color_type(0x00, 0x00, 0xFF),
			tc1014_color_converter::color_type(0x55, 0x00, 0xFF),
			tc1014_color_converter::color_type(0x00, 0x00, 0xAA),
			tc1014_color_converter::color_type(0x00, 0x00, 0x55),
			tc1014_color_converter::color_type(0x00, 0x00, 0x00),
			tc1014_color_converter::color_type(0x55, 0x55, 0x55),
			tc1014_color_converter::color_type(0x00, 0xAA, 0x00),
			tc1014_color_converter::color_type(0x00, 0xFF, 0x00),
			tc1014_color_converter::color_type(0x55, 0xAA, 0x55),
			tc1014_color_converter::color_type(0x55, 0xAA, 0x00),
			tc1014_color_converter::color_type(0xAA, 0x55, 0x00),
			tc1014_color_converter::color_type(0xFF, 0x55, 0x00),
			tc1014_color_converter::color_type(0xFF, 0x00, 0x00),
			tc1014_color_converter::color_type(0xFF, 0x00, 0x55),
			tc1014_color_converter::color_type(0xFF, 0x00, 0xAA),
			tc1014_color_converter::color_type(0xAA, 0x00, 0xAA),
			tc1014_color_converter::color_type(0xAA, 0x55, 0xAA),
			tc1014_color_converter::color_type(0x00, 0x55, 0xFF),
			tc1014_color_converter::color_type(0x55, 0x55, 0xFF),
			tc1014_color_converter::color_type(0x00, 0x55, 0xAA),
			tc1014_color_converter::color_type(0x00, 0xFF, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0x55, 0xFF, 0x55),
			tc1014_color_converter::color_type(0x00, 0xFF, 0x55),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0x55),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0x00),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0x55),
			tc1014_color_converter::color_type(0xFF, 0x55, 0x00),
			tc1014_color_converter::color_type(0xFF, 0x55, 0x55),
			tc1014_color_converter::color_type(0xFF, 0x00, 0x55),
			tc1014_color_converter::color_type(0xFF, 0x55, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0x55, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0x00, 0xFF),
			tc1014_color_converter::color_type(0x00, 0x55, 0xFF),
			tc1014_color_converter::color_type(0x00, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0x00, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0x00, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0x00),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0x55),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0x00),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0x55),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0x55, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0xFF, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0xAA, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0xFF),
			tc1014_color_converter::color_type(0xAA, 0xFF, 0xAA),
			tc1014_color_converter::color_type(0xFF, 0xFF, 0xFF)
		};

	}

	TEST(test_tc1014_color_converter, convert_color_to_colorspace_same_colorspace)
	{
		native_color_map_type native_colormap = unconverted_native_colormap;
		tc1014_color_converter converter;

		converter.convert_color_to_colorspace(color_space_type::rgb, color_space_type::rgb, native_colormap);
		EXPECT_EQ(native_colormap, unconverted_native_colormap);
		converter.convert_color_to_colorspace(color_space_type::composite, color_space_type::composite, native_colormap);
		EXPECT_EQ(native_colormap, unconverted_native_colormap);
	}

	TEST(test_tc1014_color_converter, convert_color_to_colorspace_from_composite_to_rgb)
	{
		native_color_map_type native_colormap = unconverted_native_colormap;
		tc1014_color_converter converter;

		converter.convert_color_to_colorspace(color_space_type::composite, color_space_type::rgb, native_colormap);
		EXPECT_EQ(native_colormap, converter.composite_to_rgb_table());
	}

	TEST(test_tc1014_color_converter, convert_color_to_colorspace_from_rgb_to_composite)
	{
		native_color_map_type native_colormap = unconverted_native_colormap;
		tc1014_color_converter converter;

		EXPECT_THROWS_MESSAGE(
			converter.convert_color_to_colorspace(color_space_type::rgb, color_space_type::composite, native_colormap),
			std::runtime_error,
			"converting to colorspace other than RGB is not supported");
	}

	TEST(test_tc1014_color_converter, convert_colors_to_rgb_colors)
	{
		native_color_map_type native_colormap = unconverted_native_colormap;
		tc1014_color_converter converter;

		const auto converted_colormap = converter.convert_colors(color_space_type::rgb, native_colormap);
		ASSERT_EQ(converted_colormap.size(), native_colormap.size());
		
		for (auto i(0U); i < converted_colormap.size(); ++i)
		{
			ASSERT_EQ(converted_colormap[i], expected_rgb_to_rgba_colors[i]);
		}
	}

	TEST(test_tc1014_color_converter, convert_colors_to_composite_colors)
	{
		native_color_map_type native_colormap = unconverted_native_colormap;
		tc1014_color_converter converter;

		const auto converted_colormap = converter.convert_colors(color_space_type::composite, native_colormap);
		ASSERT_EQ(converted_colormap.size(), native_colormap.size());

		for (auto i(0U); i < converted_colormap.size(); ++i)
		{
			ASSERT_EQ(converted_colormap[i], expected_composite_to_rgba_colors[i]);
		}
	}

	TEST(test_tc1014_color_converter, convert_colors_to_rgb_colormap)
	{
		native_color_map_type native_colormap = unconverted_native_colormap;
		tc1014_color_converter converter;

		const auto converted_colormap = converter.create_colormap(color_space_type::rgb, native_colormap);
		ASSERT_EQ(converted_colormap->size(), native_colormap.size());

		for (auto i(0U); i < converted_colormap->size(); ++i)
		{
			ASSERT_EQ((*converted_colormap)[i], expected_rgb_to_rgba_colors[i]);
		}
	}

	TEST(test_tc1014_color_converter, convert_colors_to_composite_colormap)
	{
		native_color_map_type native_colormap = unconverted_native_colormap;
		tc1014_color_converter converter;

		const auto converted_colormap = converter.create_colormap(color_space_type::composite, native_colormap);
		ASSERT_EQ(converted_colormap->size(), native_colormap.size());

		for (auto i(0U); i < converted_colormap->size(); ++i)
		{
			ASSERT_EQ((*converted_colormap)[i], expected_composite_to_rgba_colors[i]);
		}
	}

}
