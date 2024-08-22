// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/color_converter.h>
#include <kaos/assetfoo/colors/color_layout.h>
#include <kaos/assetfoo/exceptions.h>
#include <kaos/core/types/single_bitfield.h>
#include <kaos/core/types/empty_bitfield.h>
#include <kaos/assetfoo/test/base_fixture.h>
#include <kaos/test/gtest-extensions.h>
#include <kaos/test/mocked_bitfield.h>
#include <gtest/gtest.h>


namespace hypertech::kaos::assetfoo::colors::unittests
{

	class color_converter_with_alpha_fixture : public assetfoo::unittests::base_fixture
	{
	protected:

		using bitfield_type = core::types::single_bitfield<color_converter::bitfield_type::value_type>;

		color_converter_with_alpha_fixture()
			: converter_(std::make_unique<color_layout>(
				red_component_bitfield_,
				green_component_bitfield_,
				blue_component_bitfield_,
				alpha_component_bitfield_))
		{}


		struct packed_colors
		{
			static const color_converter::packed_color_type black = 0x000000ff;
			static const color_converter::packed_color_type white = 0xffffffff;

			static const color_converter::packed_color_type dark_red = 0x550000ff;
			static const color_converter::packed_color_type medium_red = 0xaa0000ff;
			static const color_converter::packed_color_type bright_red = 0xff0000ff;

			static const color_converter::packed_color_type dark_green = 0x005500ff;
			static const color_converter::packed_color_type medium_green = 0x00aa00ff;
			static const color_converter::packed_color_type bright_green = 0x00ff00ff;

			static const color_converter::packed_color_type dark_blue = 0x000055ff;
			static const color_converter::packed_color_type medium_blue = 0x0000aaff;
			static const color_converter::packed_color_type bright_blue = 0x0000ffff;
		};

		static const inline bitfield_type red_component_bitfield_{ "red", 8, 24 };
		static const inline bitfield_type green_component_bitfield_{ "green", 8, 16 };
		static const inline bitfield_type blue_component_bitfield_{ "blue", 8, 8 };
		static const inline bitfield_type alpha_component_bitfield_{ "alpha", 8, 0 };

		const color_converter converter_;
	};


	TEST_F(color_converter_with_alpha_fixture, to_color)
	{
		EXPECT_EQ(converter_.to_color(packed_colors::black), test_colors::black);

		EXPECT_EQ(converter_.to_color(packed_colors::dark_red), test_colors::dark_red);
		EXPECT_EQ(converter_.to_color(packed_colors::medium_red), test_colors::medium_red);
		EXPECT_EQ(converter_.to_color(packed_colors::bright_red), test_colors::bright_red);

		EXPECT_EQ(converter_.to_color(packed_colors::dark_green), test_colors::dark_green);
		EXPECT_EQ(converter_.to_color(packed_colors::medium_green), test_colors::medium_green);
		EXPECT_EQ(converter_.to_color(packed_colors::bright_green), test_colors::bright_green);

		EXPECT_EQ(converter_.to_color(packed_colors::dark_blue), test_colors::dark_blue);
		EXPECT_EQ(converter_.to_color(packed_colors::medium_blue), test_colors::medium_blue);
		EXPECT_EQ(converter_.to_color(packed_colors::bright_blue), test_colors::bright_blue);

		EXPECT_EQ(converter_.to_color(packed_colors::white), test_colors::white);
	}



	TEST_F(color_converter_with_alpha_fixture, from_color)
	{
		EXPECT_EQ(converter_.from_color(test_colors::black), packed_colors::black);

		EXPECT_EQ(converter_.from_color(test_colors::dark_red), packed_colors::dark_red);
		EXPECT_EQ(converter_.from_color(test_colors::medium_red), packed_colors::medium_red);
		EXPECT_EQ(converter_.from_color(test_colors::bright_red), packed_colors::bright_red);

		EXPECT_EQ(converter_.from_color(test_colors::dark_green), packed_colors::dark_green);
		EXPECT_EQ(converter_.from_color(test_colors::medium_green), packed_colors::medium_green);
		EXPECT_EQ(converter_.from_color(test_colors::bright_green), packed_colors::bright_green);

		EXPECT_EQ(converter_.from_color(test_colors::dark_blue), packed_colors::dark_blue);
		EXPECT_EQ(converter_.from_color(test_colors::medium_blue), packed_colors::medium_blue);
		EXPECT_EQ(converter_.from_color(test_colors::bright_blue), packed_colors::bright_blue);

		EXPECT_EQ(converter_.from_color(test_colors::white), packed_colors::white);
	}





	TEST_F(color_converter_with_alpha_fixture, from_rgb)
	{
		EXPECT_EQ(converter_.from_rgb(test_colors::black.r, test_colors::black.g, test_colors::black.b), packed_colors::black);

		EXPECT_EQ(converter_.from_rgb(test_colors::dark_red.r, test_colors::dark_red.g, test_colors::dark_red.b), packed_colors::dark_red);
		EXPECT_EQ(converter_.from_rgb(test_colors::medium_red.r, test_colors::medium_red.g, test_colors::medium_red.b), packed_colors::medium_red);
		EXPECT_EQ(converter_.from_rgb(test_colors::bright_red.r, test_colors::bright_red.g, test_colors::bright_red.b), packed_colors::bright_red);

		EXPECT_EQ(converter_.from_rgb(test_colors::dark_green.r, test_colors::dark_green.g, test_colors::dark_green.b), packed_colors::dark_green);
		EXPECT_EQ(converter_.from_rgb(test_colors::medium_green.r, test_colors::medium_green.g, test_colors::medium_green.b), packed_colors::medium_green);
		EXPECT_EQ(converter_.from_rgb(test_colors::bright_green.r, test_colors::bright_green.g, test_colors::bright_green.b), packed_colors::bright_green);

		EXPECT_EQ(converter_.from_rgb(test_colors::dark_blue.r, test_colors::dark_blue.g, test_colors::dark_blue.b), packed_colors::dark_blue);
		EXPECT_EQ(converter_.from_rgb(test_colors::medium_blue.r, test_colors::medium_blue.g, test_colors::medium_blue.b), packed_colors::medium_blue);
		EXPECT_EQ(converter_.from_rgb(test_colors::bright_blue.r, test_colors::bright_blue.g, test_colors::bright_blue.b), packed_colors::bright_blue);

		EXPECT_EQ(converter_.from_rgb(test_colors::white.r, test_colors::white.g, test_colors::white.g), packed_colors::white);
	}

}
