// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/color_converter.h>
#include <kaos/assetfoo/colors/color_layout.h>
#include <kaos/assetfoo/exceptions.h>
#include <kaos/core/types/split_bitfield.h>
#include <kaos/core/types/empty_bitfield.h>
#include <kaos/assetfoo/test/base_fixture.h>
#include <kaos/test/gtest-extensions.h>
#include <kaos/test/mocked_bitfield.h>
#include <gtest/gtest.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors { namespace unittests
{

	class color_converter_withoutalpha_fixture : public assetfoo::unittests::base_fixture
	{
	protected:

		using mockedbitfield_type = core::types::unittests::mocks::mocked_bitfield<uint64_t>;
		using alphabitfield_type = core::types::empty_bitfield<color_converter::bitfield_type::value_type>;
		using bitfield_type = core::types::split_bitfield<color_converter::bitfield_type::value_type>;
		using color_type = color_converter::color_type;


		color_converter_withoutalpha_fixture()
			: converter_(std::make_unique<color_layout>(
				red_component_bitfield_,
				green_component_bitfield_,
				blue_component_bitfield_,
				alpha_component_bitfield_))
		{}


		struct packed_colors
		{
			static const color_converter::packed_color_type black = 0b00000000;
			static const color_converter::packed_color_type white = 0b00111111;

			static const color_converter::packed_color_type dark_red = 0b00000100;
			static const color_converter::packed_color_type medium_red = 0b00100000;
			static const color_converter::packed_color_type bright_red = 0b00100100;

			static const color_converter::packed_color_type dark_green = 0b00000010;
			static const color_converter::packed_color_type medium_green = 0b00010000;
			static const color_converter::packed_color_type bright_green = 0b00010010;

			static const color_converter::packed_color_type dark_blue = 0b00000001;
			static const color_converter::packed_color_type medium_blue = 0b00001000;
			static const color_converter::packed_color_type bright_blue = 0b00001001;
		};

		static const inline bitfield_type red_component_bitfield_ = bitfield_type({ "red", 1, 5, 1, 2 });
		static const inline bitfield_type green_component_bitfield_ = bitfield_type({ "green", 1, 4, 1, 1});
		static const inline bitfield_type blue_component_bitfield_ = bitfield_type({ "blue", 1, 3, 1, 0 });
		static const inline alphabitfield_type alpha_component_bitfield_ = alphabitfield_type("alpha");

		const color_converter converter_;
	};


	TEST_F(color_converter_withoutalpha_fixture, to_color_invalid_packed_color_bits)
	{
		EXPECT_THROWS_MESSAGE(
			converter_.to_color(std::numeric_limits<color_converter::packed_color_type>::max()),
			exceptions::packed_color_format_error,
			"packed color value contains unsupported bits");
	}


	TEST_F(color_converter_withoutalpha_fixture, to_color)
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

		for (auto i = 0; i < 0b00111111; ++i)
		{
			ASSERT_NO_THROW(converter_.to_color(i));
		}
	}


	TEST_F(color_converter_withoutalpha_fixture, from_color_loss_of_red_precision)
	{
		//	Test invalid red component values
		for (auto i = 0U; i <= converter_.max_component_value(); ++i)
		{
			if (i % 85 == 0)
			{
				continue;
			}

			ASSERT_THROWS_MESSAGE(
				converter_.from_color(color_type(i, 0, 0)),
				std::range_error,
				"Conversion of red component value to packed component results in loss of color precision");
		}
	}

	TEST_F(color_converter_withoutalpha_fixture, from_color_loss_of_green_precision)
	{
		//	Test invalid green component values
		for (auto i = 0U; i <= converter_.max_component_value(); ++i)
		{
			if (i % 85 == 0)
			{
				continue;
			}

			ASSERT_THROWS_MESSAGE(
				converter_.from_color(color_type(0, i, 0)),
				std::range_error,
				"Conversion of green component value to packed component results in loss of color precision");
		}
	}

	TEST_F(color_converter_withoutalpha_fixture, from_color_loss_of_blue_precision)
	{
		//	Test invalid blue component values
		for (auto i = 0U; i <= converter_.max_component_value(); ++i)
		{
			if (i % 85 == 0)
			{
				continue;
			}

			ASSERT_THROWS_MESSAGE(
				converter_.from_color(color_type(0, 0, i)),
				std::range_error,
				"Conversion of blue component value to packed component results in loss of color precision");
		}
	}

	TEST_F(color_converter_withoutalpha_fixture, from_color)
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




	TEST_F(color_converter_withoutalpha_fixture, from_rgb_loss_of_red_precision)
	{
		//	Test invalid red component values
		for (auto i = 0U; i <= converter_.max_component_value(); ++i)
		{
			if (i % 85 == 0)
			{
				continue;
			}

			ASSERT_THROWS_MESSAGE(
				converter_.from_rgb(i, 0, 0),
				std::range_error,
				"Conversion of red component value to packed component results in loss of color precision");
		}
	}

	TEST_F(color_converter_withoutalpha_fixture, from_rgb_loss_of_green_precision)
	{
		//	Test invalid green component values
		for (auto i = 0U; i <= converter_.max_component_value(); ++i)
		{
			if (i % 85 == 0)
			{
				continue;
			}

			ASSERT_THROWS_MESSAGE(
				converter_.from_rgb(0, i, 0),
				std::range_error,
				"Conversion of green component value to packed component results in loss of color precision");
		}
	}

	TEST_F(color_converter_withoutalpha_fixture, from_rgb_loss_of_blue_precision)
	{
		//	Test invalid blue component values
		for (auto i = 0U; i <= converter_.max_component_value(); ++i)
		{
			if (i % 85 == 0)
			{
				continue;
			}

			ASSERT_THROWS_MESSAGE(
				converter_.from_rgb(0, 0, i),
				std::range_error,
				"Conversion of blue component value to packed component results in loss of color precision");
		}
	}

	TEST_F(color_converter_withoutalpha_fixture, from_rgb)
	{
		EXPECT_EQ(converter_.from_rgb(test_colors::black.R, test_colors::black.G, test_colors::black.B), packed_colors::black);

		EXPECT_EQ(converter_.from_rgb(test_colors::dark_red.R, test_colors::dark_red.G, test_colors::dark_red.B), packed_colors::dark_red);
		EXPECT_EQ(converter_.from_rgb(test_colors::medium_red.R, test_colors::medium_red.G, test_colors::medium_red.B), packed_colors::medium_red);
		EXPECT_EQ(converter_.from_rgb(test_colors::bright_red.R, test_colors::bright_red.G, test_colors::bright_red.B), packed_colors::bright_red);

		EXPECT_EQ(converter_.from_rgb(test_colors::dark_green.R, test_colors::dark_green.G, test_colors::dark_green.B), packed_colors::dark_green);
		EXPECT_EQ(converter_.from_rgb(test_colors::medium_green.R, test_colors::medium_green.G, test_colors::medium_green.B), packed_colors::medium_green);
		EXPECT_EQ(converter_.from_rgb(test_colors::bright_green.R, test_colors::bright_green.G, test_colors::bright_green.B), packed_colors::bright_green);

		EXPECT_EQ(converter_.from_rgb(test_colors::dark_blue.R, test_colors::dark_blue.G, test_colors::dark_blue.B), packed_colors::dark_blue);
		EXPECT_EQ(converter_.from_rgb(test_colors::medium_blue.R, test_colors::medium_blue.G, test_colors::medium_blue.B), packed_colors::medium_blue);
		EXPECT_EQ(converter_.from_rgb(test_colors::bright_blue.R, test_colors::bright_blue.G, test_colors::bright_blue.B), packed_colors::bright_blue);

		EXPECT_EQ(converter_.from_rgb(test_colors::white.R, test_colors::white.G, test_colors::white.G), packed_colors::white);
	}

}}}}}
