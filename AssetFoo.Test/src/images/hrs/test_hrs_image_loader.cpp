// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/hrs/hrs_image_reader.h>
#include <kaos/core/exceptions.h>
#include <kaos/assetfoo/test/load_tc1014_image_test_expectations.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace hypertech::kaos::assetfoo::images::hrs::unittests
{

	namespace
	{
		using hypertech::kaos::assetfoo::images::hrs::hrs_image;
		using hypertech::kaos::assetfoo::unittests::load_tc1014_image_test_expectations;

		struct load_hrs_image_test_expectations : load_tc1014_image_test_expectations<
			320,
			192,
			hrs_image::color_space_type::composite>
		{};
		
		struct monalisa_hrs_expectations : load_hrs_image_test_expectations
		{
			static const inline auto filename = "TestData/images/hrs/monalisa.hrs";
		
			const hrs_image::native_color_map_type native_colormap
			{
				0x04, 0x03, 0x14, 0x24, 0x05, 0x15, 0x25, 0x35,
				0x06, 0x16, 0x26, 0x36, 0x17, 0x1f, 0x31, 0x34
			};
			const std::array<uint32_t, 4> hash
			{
				0xe8ed5818, 0x4780fec3, 0xbfb03b96, 0xe48b1691
			};
		};



		template<class TestType_>
		class test_hrs_image_reader : public ::testing::Test {};

		using testing_types = testing::Types<monalisa_hrs_expectations>;
	}

	TEST(test_hrs_image_reader, load_file_not_found)
	{
		const std::string filename("TestData/images/hrs/NOEXIST.hrs");
		EXPECT_THROWS_MESSAGE(
			hrs_image_reader().load(filename),
			core::exceptions::file_not_found_error,
			("Unable to open '" + filename + "'. File does not exist").c_str());
	}

	TEST(test_hrs_image_reader, load_past_end_of_header)
	{
		std::istringstream input("0");

		EXPECT_THROWS_MESSAGE(
			hrs_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file `<TEST>`");
	}

	TEST(test_hrs_image_reader, load_past_end_of_image)
	{
		std::istringstream input(std::string(32, 0));

		EXPECT_THROWS_MESSAGE(
			hrs_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing uncompressed image data of `<TEST>`");
	}




	TYPED_TEST_CASE_P(test_hrs_image_reader);

	TYPED_TEST_P(test_hrs_image_reader, load)
	{
		TypeParam expectations;

		auto image(hrs_image_reader().load_as<hrs_image>(expectations.filename));
		//if (expectations.should_print_diagnostics())
		//{
		//	std::ofstream output(expectations.filename + std::string(".data"));
		//	output.write(reinterpret_cast<char*>(image->data()), image->get_sequence().size_bytes());
		//}

		expectations.print_diagnostics(*image);

		ASSERT_NE(image, nullptr);
		EXPECT_FALSE(image->empty());
		EXPECT_EQ(image->width(), expectations.width);
		EXPECT_EQ(image->height(), expectations.height);
		EXPECT_EQ(image->native_color_space(), expectations.colorspace);
		EXPECT_EQ(image->native_colormap().size(), expectations.native_colormap.size());
		EXPECT_EQ(image->native_colormap(), expectations.native_colormap);
		EXPECT_EQ(calculate_md5_hash(*image), expectations.hash);
	}

	REGISTER_TYPED_TEST_CASE_P(test_hrs_image_reader, load);
	INSTANTIATE_TYPED_TEST_CASE_P(test_hrs_image_reader, test_hrs_image_reader, testing_types);

}
