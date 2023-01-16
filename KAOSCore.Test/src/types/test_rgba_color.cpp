// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/rgba_color.h>
#include <gtest/gtest.h>


namespace hypertech { namespace kaos { namespace core { namespace types { namespace unittests
{

	TEST(rgba_color, default_ctor)
	{
		rgba_color color;

		EXPECT_EQ(color.R, 0);
		EXPECT_EQ(color.G, 0);
		EXPECT_EQ(color.B, 0);
		EXPECT_EQ(color.A, 255);
	}

	TEST(rgba_color, rgb_ctor)
	{
		rgba_color color(0, 85, 170);

		EXPECT_EQ(color.R, 0);
		EXPECT_EQ(color.G, 85);
		EXPECT_EQ(color.B, 170);
		EXPECT_EQ(color.A, 255);
	}

	TEST(rgba_color, RGBA_Ctor)
	{
		rgba_color color(85, 170, 255, 100);

		EXPECT_EQ(color.R, 85);
		EXPECT_EQ(color.G, 170);
		EXPECT_EQ(color.B, 255);
		EXPECT_EQ(color.A, 100);
	}

	TEST(rgba_color, unsigned_packed_rgba_ctor)
	{
		rgba_color color(rgba_color::unsigned_packed_color_type(0x55AAFF80));

		EXPECT_EQ(color.R, 0x55);
		EXPECT_EQ(color.G, 0xaa);
		EXPECT_EQ(color.B, 0xff);
		EXPECT_EQ(color.A, 0x80);
	}

	TEST(rgba_color, signed_packed_rgba_ctor)
	{
		rgba_color color(rgba_color::signed_packed_color_type(0x55AAFF80));

		EXPECT_EQ(color.R, 0x55);
		EXPECT_EQ(color.G, 0xaa);
		EXPECT_EQ(color.B, 0xff);
		EXPECT_EQ(color.A, 0x80);
	}

	TEST(rgba_color, Equals)
	{
		rgba_color color1(85, 170, 255, 100);
		rgba_color color2(85, 170, 255, 100);

		EXPECT_EQ(color1, color2);
	}

	TEST(rgba_color, Not_Equals_On_Red)
	{
		rgba_color color1(85, 170, 255, 100);
		rgba_color color2(0, 170, 255, 100);

		EXPECT_NE(color1, color2);
	}

	TEST(rgba_color, Not_Equals_On_Green)
	{
		rgba_color color1(85, 170, 255, 100);
		rgba_color color2(85, 0, 255, 100);

		EXPECT_NE(color1, color2);
	}

	TEST(rgba_color, Not_Equals_On_Blue)
	{
		rgba_color color1(85, 170, 255, 100);
		rgba_color color2(85, 170, 0, 100);

		EXPECT_NE(color1, color2);
	}

	TEST(rgba_color, Not_Equals_On_Alpha)
	{
		rgba_color color1(85, 170, 255, 100);
		rgba_color color2(85, 170, 255, 0);

		EXPECT_NE(color1, color2);
	}

	TEST(rgba_color, to_unsigned)
	{
		EXPECT_EQ(rgba_color(0x00, 0x55, 0xAA, 0xFF).to_unsigned(), 0x0055AAFFU);
		EXPECT_EQ(rgba_color(0xFF, 0xAA, 0x55, 0x00).to_unsigned(), 0xFFAA5500U);
	}

	TEST(rgba_color, to_signed)
	{
		EXPECT_EQ(rgba_color(0x00, 0x55, 0xAA, 0xFF).to_signed(), 0x0055AAFF);
		EXPECT_EQ(rgba_color(0xFF, 0xAA, 0x55, 0x00).to_signed(), int32_t(0xFFAA5500));
	}

	TEST(rgba_color, brightness)
	{
		EXPECT_EQ(rgba_color(0, 0, 0).brightness(), 0);
		EXPECT_EQ(rgba_color(128, 128, 128).brightness(), .501960814f);
		EXPECT_EQ(rgba_color(255, 255, 255).brightness(), 1.0f);

		EXPECT_EQ(rgba_color(255, 0, 0).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(255, 128, 0).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(255, 0, 128).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(255, 128, 128).brightness(), 0.750980377f);

		EXPECT_EQ(rgba_color(0, 255, 0).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(128, 255, 0).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(0, 255, 128).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(128, 255, 128).brightness(), 0.750980377f);

		EXPECT_EQ(rgba_color(0, 0, 255).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(128, 0, 255).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(0, 128, 255).brightness(), 0.5f);
		EXPECT_EQ(rgba_color(128, 128, 255).brightness(), 0.750980377f);
	}

}}}}}
