// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/cm3/cm3_image.h>
#include <kaos/assetfoo/images/monochrome_pattern.h>
#include <kaos/assetfoo/test/images/cm3/default_patterns.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace hypertech::kaos::assetfoo::images::cm3::unittests
{
	namespace
	{

		namespace defaults
		{
			const auto native_colormap(cm3_image::native_color_map_type{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
			const auto native_colorspace(cm3_image::color_space_type::rgb);
			const auto dimensions(cm3_image::dimensions_type(8, 8));
			const auto animation_rate(20);
			const auto cycle_rate(10);
			const auto cycle_colors = cm3_image::cycle_colors_list_type
			{
				cm3_image::color_type(0, 0, 0),
				cm3_image::color_type(1, 0, 0),
				cm3_image::color_type(2, 0, 0),
				cm3_image::color_type(3, 0, 0),
				cm3_image::color_type(4, 0, 0),
				cm3_image::color_type(5, 0, 0),
				cm3_image::color_type(6, 0, 0),
				cm3_image::color_type(7, 0, 0),
			};

			const auto colormap = cm3_image::color_map_type
			{
				{ 0, 0, 0 },
				{ 1, 0, 0 },
				{ 2, 0, 0 },
				{ 3, 0, 0 },
				{ 4, 0, 0 },
				{ 5, 0, 0 },
				{ 6, 0, 0 },
				{ 7, 0, 0 },
				{ 8, 0, 0 },
				{ 9, 0, 0 },
				{ 10, 0, 0 },
				{ 11, 0, 0 },
				{ 12, 0, 0 },
				{ 13, 0, 0 },
				{ 14, 0, 0 },
				{ 15, 0, 0 },
			};

		}

		const image::dimensions_type empty_dimensions(0, 0);
	}


	TEST(test_cm3_image, default_constructor)
	{
		cm3_image image;

		EXPECT_TRUE(image.empty());
		EXPECT_EQ(image.dimensions(), empty_dimensions);
		EXPECT_EQ(image.width(), 0U);
		EXPECT_EQ(image.height(), 0U);
		EXPECT_EQ(image.length(), 0U);
		EXPECT_EQ(image.data(), nullptr);
		EXPECT_THROWS_MESSAGE(DEBUG_DiscardResult(image.colormap()), std::runtime_error, "colormap is null");
		EXPECT_EQ(image.native_color_space(), cm3_image::color_space_type());
		EXPECT_EQ(image.native_colormap(), cm3_image::native_color_map_type());
		EXPECT_EQ(image.animation_rate(), 0);
		EXPECT_EQ(image.cycle_rate(), 0);
		EXPECT_EQ(image.cycle_colors(), cm3_image::cycle_colors_list_type());
		EXPECT_EQ(image.patterns(), cm3_image::pattern_list_type());
	}

	TEST(test_cm3_image, value_constructor)
	{
		auto colormap(std::make_unique<colors::color_map>(defaults::colormap));
		auto colormap_ptr(colormap.get());

		cm3_image image(
			defaults::dimensions,
			move(colormap),
			defaults::native_colorspace,
			defaults::native_colormap,
			defaults::animation_rate,
			defaults::cycle_rate,
			defaults::cycle_colors,
			default_pattern_set);

		EXPECT_FALSE(image.empty());
		EXPECT_EQ(image.dimensions(), defaults::dimensions);
		EXPECT_EQ(image.width(), defaults::dimensions.width);
		EXPECT_EQ(image.height(), defaults::dimensions.height);
		EXPECT_NE(image.data(), nullptr);
		EXPECT_EQ(&image.colormap(), colormap_ptr);
		EXPECT_EQ(image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(image.native_color_space(), defaults::native_colorspace);
		EXPECT_EQ(image.animation_rate(), defaults::animation_rate);
		EXPECT_EQ(image.cycle_rate(), defaults::cycle_rate);
		EXPECT_EQ(image.cycle_colors(), defaults::cycle_colors);
		EXPECT_EQ(image.patterns(), default_pattern_set);
	}

	TEST(test_cm3_image, value_constructor_not_enough_colormap_entries)
	{
		auto colormap(std::make_unique<colors::color_map>(1, 1));
		cm3_image::native_color_map_type native_colormap(1, 1);

		EXPECT_THROWS_MESSAGE(
			cm3_image image(
				defaults::dimensions,
				move(colormap),
				defaults::native_colorspace,
				native_colormap,
				defaults::animation_rate,
				defaults::cycle_rate,
				defaults::cycle_colors,
				default_pattern_set),
			std::out_of_range,
			"colormap must contain 16 colors");
	}

	TEST(test_cm3_image, value_constructor_too_many_colormap_entries)
	{
		auto colormap(std::make_unique<colors::color_map>(
			cm3_image::feature_details::max_colormap_size + 1,
			cm3_image::feature_details::max_colormap_size + 1));
		cm3_image::native_color_map_type native_colormap(cm3_image::feature_details::max_colormap_size + 1);

		EXPECT_THROWS_MESSAGE(
			cm3_image image(
				defaults::dimensions,
				move(colormap),
				defaults::native_colorspace,
				native_colormap,
				defaults::animation_rate,
				defaults::cycle_rate,
				defaults::cycle_colors,
				default_pattern_set),
			std::out_of_range,
			"colormap must contain 16 colors");
	}

	TEST(test_cm3_image, value_constructor_animation_rate_out_of_range)
	{
		EXPECT_THROWS_MESSAGE(
			cm3_image image(
				defaults::dimensions,
				std::make_unique<colors::color_map>(defaults::colormap),
				defaults::native_colorspace,
				defaults::native_colormap,
				cm3_image::feature_details::max_animation_rate + 1,
				defaults::cycle_rate,
				defaults::cycle_colors,
				default_pattern_set),
			std::out_of_range,
			"animation rate is too large");
	}

	TEST(test_cm3_image, value_constructor_cycle_rate_out_of_range)
	{
		EXPECT_THROWS_MESSAGE(
			cm3_image image(
				defaults::dimensions,
				std::make_unique<colors::color_map>(defaults::colormap),
				defaults::native_colorspace,
				defaults::native_colormap,
				defaults::animation_rate,
				cm3_image::feature_details::max_cycle_rate + 1,
				defaults::cycle_colors,
				default_pattern_set),
			std::out_of_range,
			"cycle rate is too large");
	}

	TEST(test_cm3_image, value_constructor_cycle_colors_too_few)
	{
		cm3_image::cycle_colors_list_type cycle_colors = { cm3_image::color_type() };

		EXPECT_THROWS_MESSAGE(
			cm3_image image(
				defaults::dimensions,
				std::make_unique<colors::color_map>(defaults::colormap),
				defaults::native_colorspace,
				defaults::native_colormap,
				defaults::animation_rate,
				defaults::cycle_rate,
				cycle_colors,
				default_pattern_set),
			std::out_of_range,
			"cycle color list must contain 0 or 8 colors");
	}

	TEST(test_cm3_image, copy_constructor)
	{
		auto colormap(std::make_unique<colors::color_map>(defaults::colormap));
		auto colormap_ptr(colormap.get());

		cm3_image original_image(
			defaults::dimensions,
			move(colormap),
			defaults::native_colorspace,
			defaults::native_colormap,
			defaults::animation_rate,
			defaults::cycle_rate,
			defaults::cycle_colors,
			default_pattern_set);

		cm3_image image(original_image);

		EXPECT_FALSE(original_image.empty());
		EXPECT_EQ(original_image.dimensions(), defaults::dimensions);
		EXPECT_EQ(original_image.width(), defaults::dimensions.width);
		EXPECT_EQ(original_image.height(), defaults::dimensions.height);
		EXPECT_NE(original_image.data(), nullptr);
		EXPECT_EQ(&original_image.colormap(), colormap_ptr);
		EXPECT_TRUE(std::equal(image.colormap().begin(), image.colormap().end(), colormap_ptr->begin(), colormap_ptr->end()));
		EXPECT_EQ(original_image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(original_image.native_color_space(), defaults::native_colorspace);
		EXPECT_EQ(original_image.animation_rate(), defaults::animation_rate);
		EXPECT_EQ(original_image.cycle_rate(), defaults::cycle_rate);
		EXPECT_EQ(original_image.cycle_colors(), defaults::cycle_colors);
		EXPECT_EQ(original_image.patterns(), default_pattern_set);

		EXPECT_FALSE(image.empty());
		EXPECT_EQ(image.dimensions(), defaults::dimensions);
		EXPECT_EQ(image.width(), defaults::dimensions.width);
		EXPECT_EQ(image.height(), defaults::dimensions.height);
		EXPECT_NE(image.data(), nullptr);
		EXPECT_NE(&image.colormap(), colormap_ptr);
		EXPECT_TRUE(std::equal(image.colormap().begin(), image.colormap().end(), colormap_ptr->begin(), colormap_ptr->end()));
		EXPECT_EQ(image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(image.native_color_space(), defaults::native_colorspace);
		EXPECT_EQ(image.animation_rate(), defaults::animation_rate);
		EXPECT_EQ(image.cycle_rate(), defaults::cycle_rate);
		EXPECT_EQ(image.cycle_colors(), defaults::cycle_colors);
		EXPECT_EQ(image.patterns(), default_pattern_set);
	}

	TEST(test_cm3_image, move_constructor)
	{
		auto colormap(std::make_unique<colors::color_map>(defaults::colormap));
		auto colormap_ptr(colormap.get());

		cm3_image original_image(
			defaults::dimensions,
			move(colormap),
			defaults::native_colorspace,
			defaults::native_colormap,
			defaults::animation_rate,
			defaults::cycle_rate,
			defaults::cycle_colors,
			default_pattern_set);
		
		cm3_image image(move(original_image));

		EXPECT_TRUE(original_image.empty());
		EXPECT_EQ(original_image.dimensions(), cm3_image::dimensions_type());
		EXPECT_EQ(original_image.width(), 0);
		EXPECT_EQ(original_image.height(), 0);
		EXPECT_EQ(original_image.data(), nullptr);
		EXPECT_THROWS_MESSAGE(DEBUG_DiscardResult(original_image.colormap()), std::runtime_error, "colormap is null");
		EXPECT_EQ(original_image.native_colormap(), cm3_image::native_color_map_type());
		EXPECT_EQ(original_image.native_color_space(), cm3_image::color_space_type());
		EXPECT_EQ(original_image.animation_rate(), 0);
		EXPECT_EQ(original_image.cycle_rate(), 0);
		EXPECT_EQ(original_image.cycle_colors(), cm3_image::cycle_colors_list_type());
		EXPECT_EQ(original_image.patterns(), cm3_image::pattern_list_type());

		EXPECT_FALSE(image.empty());
		EXPECT_EQ(image.dimensions(), defaults::dimensions);
		EXPECT_EQ(image.width(), defaults::dimensions.width);
		EXPECT_EQ(image.height(), defaults::dimensions.height);
		EXPECT_NE(image.data(), nullptr);
		EXPECT_EQ(&image.colormap(), colormap_ptr);
		EXPECT_EQ(image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(image.native_color_space(), defaults::native_colorspace);
		EXPECT_EQ(image.animation_rate(), defaults::animation_rate);
		EXPECT_EQ(image.cycle_rate(), defaults::cycle_rate);
		EXPECT_EQ(image.cycle_colors(), defaults::cycle_colors);
		EXPECT_EQ(image.patterns(), default_pattern_set);
	}

}
