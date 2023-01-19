// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/png/png_image_reader.h>
#include <kaos/core/exceptions.h>
#include <kaos/assetfoo/test/load_tc1014_image_test_expectations.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace hypertech::kaos::assetfoo::images::png::unittests
{

	namespace
	{
		template<size_t Width_, size_t Height_, uint32_t Hash1_, uint32_t Hash2_, uint32_t Hash3_, uint32_t Hash4_>
		struct png_expectations
		{
			static const size_t width = Width_;
			static const size_t height = Height_;
			using image_type = hypertech::kaos::assetfoo::images::image;

			const std::array<uint32_t, 4> hash
			{
				Hash1_, Hash2_, Hash3_, Hash4_
			};
		};


		struct test1_base_png_expectations : png_expectations<320, 200, 0x7fa45014, 0xf02e5d2a, 0x7f836dd3, 0x56d75491>
		{
			static const inline auto filename = "TestData/images/png/test1_base.png";
		};

		struct ghouls_and_ghosts_png_expectations : png_expectations<320, 225, 0x08030356, 0x5edfcac5, 0x4251c751, 0x2541c215>
		{
			static const inline auto filename = "TestData/images/png/ghouls_and_ghosts.png";
		};

		struct aladdin_png_expectations : png_expectations<32, 90, 0x63eb9c98, 0x37bd220a, 0x549b6942, 0xecc74919>
		{
			static const inline auto filename = "TestData/images/png/aladdin.png";
		};

		struct bjoink_png_expectations : png_expectations<80, 90, 0x59df19bf, 0x63cdf609, 0x60de2bbe, 0x789ad90d>
		{
			static const inline auto filename = "TestData/images/png/bjoink.png";
		};

		struct ninja_gaiden_png_expectations : png_expectations<56, 63, 0xbc3d4839, 0xebd0aa96, 0xd2ffcc1f, 0xfd8197de>
		{
			static const inline auto filename = "TestData/images/png/ninja_gaiden.png";
		};


		template<class TestType_>
		class test_png_image_reader : public ::testing::Test {};

		using testing_types = testing::Types<
			test1_base_png_expectations,
			ghouls_and_ghosts_png_expectations,
			aladdin_png_expectations,
			bjoink_png_expectations,
			ninja_gaiden_png_expectations>;
	}

	TEST(test_png_image_reader, load_file_not_found)
	{
		const std::string filename("TestData/images/png/NOEXIST.png");
		EXPECT_THROWS_MESSAGE(
			png_image_reader().load(filename),
			core::exceptions::file_not_found_error,
			("Unable to open '" + filename + "'. File does not exist").c_str());
	}

	TEST(test_png_image_reader, load_past_end_of_image)
	{
		std::istringstream input(std::string(32, 0));

		EXPECT_THROWS_MESSAGE(
			png_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: unexpected error encountered while decoding `<TEST>`");
	}



	TYPED_TEST_CASE_P(test_png_image_reader);

	TYPED_TEST_P(test_png_image_reader, load)
	{
		TypeParam expectations;

		auto image(png_image_reader().load_as<images::image>(expectations.filename));

		ASSERT_NE(image, nullptr);
		EXPECT_FALSE(image->empty());
		EXPECT_EQ(image->width(), expectations.width);
		EXPECT_EQ(image->height(), expectations.height);
		EXPECT_EQ(calculate_md5_hash(*image), expectations.hash);
	}

	REGISTER_TYPED_TEST_CASE_P(test_png_image_reader, load);
	INSTANTIATE_TYPED_TEST_CASE_P(test_png_image_reader, test_png_image_reader, testing_types);

}
