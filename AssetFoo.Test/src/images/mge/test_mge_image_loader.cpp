// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/mge/mge_image_reader.h>
#include <kaos/assetfoo/images/mge/mge_image.h>
#include <kaos/core/exceptions.h>
#include <kaos/assetfoo/test/load_tc1014_image_test_expectations.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace
{
	using hypertech::kaos::assetfoo::images::mge::mge_image;
	using hypertech::kaos::assetfoo::unittests::load_tc1014_image_test_expectations;

	struct load_mge_image_test_expectations : load_tc1014_image_test_expectations<320, 200>
	{};
		
	struct test1_uncompressed_mge_expectations : load_mge_image_test_expectations
	{
		static const inline auto filename = "TestData/images/mge/test1-uncompressed.mge";
		static const inline std::string title = "THIS IS AN UNCOMPRESSED IMAGE";

		const mge_image::native_color_map_type native_colormap
		{
			0x00, 0x07, 0x1f, 0x26, 0x12, 0x0b, 0x24, 0x3a,
			0x14, 0x28, 0x2f, 0x3c, 0x27, 0x34, 0x1a, 0x3f
		};
		const std::array<uint32_t, 4> hash
		{
			0x7fa45014, 0xf02e5d2a, 0x7f836dd3, 0x56d75491
		};
	};

	struct test1_compressed_mge_expectations : test1_uncompressed_mge_expectations
	{
		static const inline auto filename = "TestData/images/mge/test1-compressed.mge";
		static const inline std::string title = "THIS IS A COMPRESSED IMAGE!!!";
	};

	struct titlepage_mge_expectations : load_mge_image_test_expectations
	{
		static const inline auto filename = "TestData/images/mge/cmd_titlepage.mge";
		static const inline std::string title = "Color Max Deluxe title page";

		const mge_image::native_color_map_type native_colormap
		{
			0x00, 0x20, 0x08, 0x10, 0x16, 0x24, 0x36, 0x3e,
			0x07, 0x18, 0x2a, 0x22, 0x36, 0x0f, 0x2d, 0x3f
		};
		const std::array<uint32_t, 4> hash
		{
			0xba812ac6, 0xc5a0389a, 0x74794674, 0x6ce3d1b2
		};
	};


	template<class TestType_>
	class test_mge_image_reader : public ::testing::Test {};

	using testing_types = testing::Types<
		test1_uncompressed_mge_expectations,
		test1_compressed_mge_expectations,
		titlepage_mge_expectations>;
}

namespace hypertech::kaos::assetfoo::images::mge::unittests
{

	TEST(test_mge_image_reader, load_file_not_found)
	{
		const std::string filename("TestData/images/mge/NOEXIST.mge");
		EXPECT_THROWS_MESSAGE(
			mge_image_reader().load(filename),
			core::exceptions::file_not_found_error,
			("Unable to open '" + filename + "'. File does not exist").c_str());
	}

	TEST(test_mge_image_reader, load_invalid_image_type)
	{
		std::istringstream input("\xff");

		EXPECT_THROWS_MESSAGE(
			mge_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"unknown image type specified in <TEST>");
	}

	TEST(test_mge_image_reader, load_past_end_of_header)
	{
		std::istringstream input("\x0", 1);

		EXPECT_THROWS_MESSAGE(
			mge_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file `<TEST>`");
	}

	TEST(test_mge_image_reader, load_past_end_of_uncompressed_image)
	{
		std::istringstream input(std::string(64, 0));

		EXPECT_THROWS_MESSAGE(
			mge_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing compressed image data of `<TEST>`");
	}

	TEST(test_mge_image_reader, load_past_end_of_compressed_image)
	{
		std::istringstream input(std::string(18, 0) + "\x01" + std::string(64, 0));

		EXPECT_THROWS_MESSAGE(
			mge_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing uncompressed image data of `<TEST>`");
	}



	TYPED_TEST_CASE_P(test_mge_image_reader);

	TYPED_TEST_P(test_mge_image_reader, load)
	{
		TypeParam expectations;

		auto image(mge_image_reader().load_as<mge_image>(expectations.filename));

		expectations.print_diagnostics(*image);

		ASSERT_NE(image, nullptr);
		EXPECT_FALSE(image->empty());
		EXPECT_EQ(image->width(), expectations.width);
		EXPECT_EQ(image->height(), expectations.height);
		EXPECT_EQ(image->title(), expectations.title);
		EXPECT_EQ(image->native_color_space(), expectations.colorspace);
		EXPECT_EQ(image->native_colormap().size(), expectations.native_colormap.size());
		EXPECT_EQ(image->native_colormap(), expectations.native_colormap);
		EXPECT_EQ(calculate_md5_hash(*image), expectations.hash);
	}

	REGISTER_TYPED_TEST_CASE_P(test_mge_image_reader, load);
	INSTANTIATE_TYPED_TEST_CASE_P(test_mge_image_reader, test_mge_image_reader, testing_types);

}
