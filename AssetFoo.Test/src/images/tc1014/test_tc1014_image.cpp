// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/tc1014/tc1014_image.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace tc1014 { namespace unittests
{

	namespace
	{
		namespace defaults
		{
			const tc1014_image::size_type width(256);
			const tc1014_image::size_type height(192);
			const tc1014_image::size_type length(width * height);
			const tc1014_image::dimensions_type dimensions(width, height);

			const auto native_colormap(tc1014_image::native_color_map_type{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
			const auto native_colorspace(tc1014_image::color_space_type::rgb);

			const auto colormap = tc1014_image::color_map_type
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
		const tc1014_image::dimensions_type empty_dimensions(0, 0);
	}


	TEST(test_tc1014_image, default_constructor)
	{
		tc1014_image image;

		EXPECT_TRUE(image.empty());
		EXPECT_EQ(image.dimensions(), empty_dimensions);
		EXPECT_EQ(image.width(), 0U);
		EXPECT_EQ(image.height(), 0U);
		EXPECT_EQ(image.length(), 0U);
		EXPECT_EQ(image.data(), nullptr);
		EXPECT_THROWS_MESSAGE(DEBUG_DiscardResult(image.colormap()), std::runtime_error, "colormap is null");
		EXPECT_EQ(image.native_color_space(), tc1014_image::color_space_type());
		EXPECT_EQ(image.native_colormap(), tc1014_image::native_color_map_type());
	}

	TEST(test_tc1014_image, value_constructor)
	{
		auto colormap(std::make_unique<colors::color_map>(defaults::colormap));
		auto colormap_ptr(colormap.get());

		tc1014_image image(
			defaults::dimensions,
			move(colormap),
			defaults::native_colorspace,
			defaults::native_colormap);

		EXPECT_FALSE(image.empty());
		EXPECT_EQ(image.dimensions(), defaults::dimensions);
		EXPECT_EQ(image.width(), defaults::width);
		EXPECT_EQ(image.height(), defaults::height);
		EXPECT_EQ(image.length(), defaults::length);
		EXPECT_NE(image.data(), nullptr);
		EXPECT_EQ(&image.colormap(), colormap_ptr);
		EXPECT_TRUE(std::equal(image.colormap().begin(), image.colormap().end(), defaults::colormap.begin(), defaults::colormap.end()));
		EXPECT_EQ(image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(image.native_color_space(), defaults::native_colorspace);
	}

	TEST(test_tc1014_image, value_constructor_no_colormap)
	{
		const auto native_colormap(std::vector<tc1014_image::native_packed_color_type>{ 0, 0, 0, 0, 0 });
		const auto native_colorspace(tc1014_image::color_space_type::rgb);
		const auto dimensions(tc1014_image::dimensions_type(8, 8));

		EXPECT_THROWS_MESSAGE(
			tc1014_image(dimensions, nullptr, native_colorspace, native_colormap),
			std::invalid_argument,
			"colormap passed to tc1014 based image cannot be null");
	}

	TEST(test_tc1014_image, value_constructor_toomany_in_native_colormap)
	{
		auto colormap(std::make_unique<colors::color_map>(4, 4));
		const auto native_colormap(std::vector<tc1014_image::native_packed_color_type>{ 0, 0, 0, 0, 0 });
		const auto native_colorspace(tc1014_image::color_space_type::rgb);
		const auto dimensions(tc1014_image::dimensions_type(8, 8));

		EXPECT_THROWS_MESSAGE(
			tc1014_image(dimensions, move(colormap), native_colorspace, native_colormap),
			std::invalid_argument,
			"Number of colors in native colormap do not match RGBA colormap");
	}

	TEST(test_tc1014_image, value_constructor_toofew_in_native_colormap)
	{
		auto colormap(std::make_unique<colors::color_map>(4, 4));
		const auto native_colormap(std::vector<tc1014_image::native_packed_color_type>{ 0, 0, 0 });
		const auto native_colorspace(tc1014_image::color_space_type::rgb);
		const auto dimensions(tc1014_image::dimensions_type(8, 8));

		EXPECT_THROWS_MESSAGE(
			tc1014_image(dimensions, move(colormap), native_colorspace, native_colormap),
			std::invalid_argument,
			"Number of colors in native colormap do not match RGBA colormap");
	}

	TEST(test_tc1014_image, copy_constructor)
	{
		auto colormap(std::make_unique<colors::color_map>(defaults::colormap));
		auto colormap_ptr(colormap.get());

		tc1014_image original_image(
			defaults::dimensions,
			move(colormap),
			defaults::native_colorspace,
			defaults::native_colormap);
		tc1014_image image(original_image);

		EXPECT_FALSE(original_image.empty());
		EXPECT_EQ(original_image.dimensions(), defaults::dimensions);
		EXPECT_EQ(original_image.width(), defaults::width);
		EXPECT_EQ(original_image.height(), defaults::height);
		EXPECT_EQ(original_image.length(), defaults::length);
		EXPECT_NE(original_image.data(), nullptr);
		EXPECT_EQ(&original_image.colormap(), colormap_ptr);
		EXPECT_TRUE(std::equal(original_image.colormap().begin(), original_image.colormap().end(), defaults::colormap.begin(), defaults::colormap.end()));
		EXPECT_EQ(original_image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(original_image.native_color_space(), defaults::native_colorspace);

		EXPECT_FALSE(image.empty());
		EXPECT_EQ(image.dimensions(), defaults::dimensions);
		EXPECT_EQ(image.width(), defaults::width);
		EXPECT_EQ(image.height(), defaults::height);
		EXPECT_EQ(image.length(), defaults::length);
		EXPECT_NE(image.data(), nullptr);
		EXPECT_NE(&image.colormap(), colormap_ptr);
		EXPECT_TRUE(std::equal(image.colormap().begin(), image.colormap().end(), defaults::colormap.begin(), defaults::colormap.end()));
		EXPECT_EQ(image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(image.native_color_space(), defaults::native_colorspace);
	}

	TEST(test_tc1014_image, move_constructor)
	{
		auto colormap(std::make_unique<colors::color_map>(defaults::colormap));
		auto colormap_ptr(colormap.get());

		tc1014_image original_image(
			defaults::dimensions,
			move(colormap),
			defaults::native_colorspace,
			defaults::native_colormap);
		tc1014_image image(move(original_image));

		EXPECT_TRUE(original_image.empty());
		EXPECT_EQ(original_image.dimensions(), empty_dimensions);
		EXPECT_EQ(original_image.width(), 0U);
		EXPECT_EQ(original_image.height(), 0U);
		EXPECT_EQ(original_image.length(), 0U);
		EXPECT_EQ(original_image.data(), nullptr);
		EXPECT_THROWS_MESSAGE(DEBUG_DiscardResult(original_image.colormap()), std::runtime_error, "colormap is null");
		EXPECT_EQ(original_image.native_color_space(), tc1014_image::color_space_type());
		EXPECT_EQ(original_image.native_colormap(), tc1014_image::native_color_map_type());

		EXPECT_FALSE(image.empty());
		EXPECT_EQ(image.dimensions(), defaults::dimensions);
		EXPECT_EQ(image.width(), defaults::width);
		EXPECT_EQ(image.height(), defaults::height);
		EXPECT_EQ(image.length(), defaults::length);
		EXPECT_NE(image.data(), nullptr);
		EXPECT_EQ(&image.colormap(), colormap_ptr);
		EXPECT_TRUE(std::equal(image.colormap().begin(), image.colormap().end(), defaults::colormap.begin(), defaults::colormap.end()));
		EXPECT_EQ(image.native_colormap(), defaults::native_colormap);
		EXPECT_EQ(image.native_color_space(), defaults::native_colorspace);
	}

}}}}}}