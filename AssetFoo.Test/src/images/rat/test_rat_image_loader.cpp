// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/rat/rat_image_reader.h>
#include <kaos/assetfoo/images/rat/rat_image.h>
#include <kaos/core/exceptions.h>
#include <kaos/assetfoo/test/load_tc1014_image_test_expectations.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace
{
	using hypertech::kaos::assetfoo::images::rat::rat_image;
	using hypertech::kaos::assetfoo::unittests::load_tc1014_image_test_expectations;

	struct load_rat_image_test_expectations : load_tc1014_image_test_expectations<320, 199>
	{};
		
	struct rattitle_rat_expectations : load_rat_image_test_expectations
	{
		static const inline auto filename = "TestData/images/rat/rat.rat";
		static const inline auto background_color = rat_image::color_type (0, 0, 85);
		const rat_image::native_color_map_type native_colormap
		{
			0x01, 0x10, 0x36, 0x20, 0x02, 0x38, 0x3e, 0x22,
			0x34, 0x31, 0x04, 0x31, 0x24, 0x00, 0x07, 0x3f
		};
		const std::array<uint32_t, 4> hash
		{
			0x50a13ed3, 0x12fec005, 0x332969cf, 0x5515d217
		};
	};


	struct title1_rat_expectations : load_rat_image_test_expectations
	{
		static const inline auto filename = "TestData/images/rat/rat1.rat";
		static const inline auto background_color = rat_image::color_type (255, 0, 0);

		const rat_image::native_color_map_type native_colormap
		{
			0x24, 0x1a, 0x00, 0x02, 0x06, 0x3c, 0x3e, 0x22,
			0x34, 0x31, 0x04, 0x00, 0x00, 0x00, 0x03, 0x3f
		};
		const std::array<uint32_t, 4> hash
		{
			0x348d2524, 0xfbe1fc03, 0xb1c81e2a, 0x785f69df
		};
	};


	template<class TestType_>
	class test_rat_image_reader : public ::testing::Test {};

	using testing_types = testing::Types<
		rattitle_rat_expectations,
		title1_rat_expectations>;
}

namespace hypertech::kaos::assetfoo::images::rat::unittests
{

	TEST(test_rat_image_reader, load_file_not_found)
	{
		const std::string filename("TestData/images/rat/NOEXIST.rat");
		EXPECT_THROWS_MESSAGE(
			rat_image_reader().load(filename),
			core::exceptions::file_not_found_error,
			("Unable to open '" + filename + "'. File does not exist").c_str());
	}

	TEST(test_rat_image_reader, load_past_end_of_header)
	{
		std::istringstream input("\x0", 1);

		EXPECT_THROWS_MESSAGE(
			rat_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file `<TEST>`");
	}

	TEST(test_rat_image_reader, load_past_end_of_uncompressed_image)
	{
		std::istringstream input(std::string("\x01\x00", 2) + std::string(64, 0));

		EXPECT_THROWS_MESSAGE(
			rat_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing uncompressed image data of `<TEST>`");
	}

	TEST(test_rat_image_reader, load_past_end_of_compressed_image)
	{
		std::istringstream input(std::string(64, 1));

		EXPECT_THROWS_MESSAGE(
			rat_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing compressed image data of `<TEST>`");
	}




	TYPED_TEST_CASE_P(test_rat_image_reader);

	TYPED_TEST_P(test_rat_image_reader, load)
	{
		TypeParam expectations;

		auto image(rat_image_reader().load_as<rat_image>(expectations.filename));

		ASSERT_NE(image, nullptr);
		EXPECT_FALSE(image->empty());
		EXPECT_EQ(image->width(), expectations.width);
		EXPECT_EQ(image->height(), expectations.height);
		EXPECT_EQ(image->native_color_space(), expectations.colorspace);
		EXPECT_EQ(image->native_colormap().size(), expectations.native_colormap.size());
		EXPECT_EQ(image->native_colormap(), expectations.native_colormap);
		EXPECT_EQ(image->background_color(), expectations.background_color);
		EXPECT_EQ(calculate_md5_hash(*image), expectations.hash);
	}

	REGISTER_TYPED_TEST_CASE_P(test_rat_image_reader, load);
	INSTANTIATE_TYPED_TEST_CASE_P(test_rat_image_reader, test_rat_image_reader, testing_types);

}
