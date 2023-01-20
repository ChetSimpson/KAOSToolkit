// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/vef/vef_image_reader.h>
#include <kaos/core/exceptions.h>
#include <kaos/assetfoo/test/load_tc1014_image_test_expectations.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace hypertech::kaos::assetfoo::images::vef::unittests
{

	namespace
	{

		template<size_t Width_>
		using vef_image_reader_test_expectations = assetfoo::unittests::tc1014_image_reader_test_expectations<Width_, 200>;

		struct batman_vef_expectations : vef_image_reader_test_expectations<320>
		{
			static const inline auto filename = "TestData/images/vef/batman.vef";

			static const inline native_color_map_type native_colormap
			{
				0x00, 0x36, 0x39, 0x24, 0x20, 0x07, 0x3f, 0x04,
				0x34, 0x34, 0x36, 0x34, 0x34, 0x34, 0x36, 0x34
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0x3411b060, 0x806db66e, 0x03ed47b5, 0x5e417ce5
			};
		};

		struct darth_vef_expectations : vef_image_reader_test_expectations<320>
		{
			static const inline auto filename = "TestData/images/vef/darth.vef";

			static const inline native_color_map_type native_colormap
			{
				0x00, 0x01, 0x04, 0x05, 0x03, 0x07, 0x22, 0x23,
				0x1c, 0x27, 0x38, 0x3c, 0x1b, 0x3d, 0x3b, 0x3f
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0xd230140d, 0x5a31bce5, 0xb8eff974, 0x0204b487
			};
		};

		struct elf_vef_expectations : vef_image_reader_test_expectations<640>
		{
			static const inline auto filename = "TestData/images/vef/elf.vef";

			static const inline native_color_map_type native_colormap
			{
				0x3f, 0x38, 0x07, 0x00
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0x0fd98625, 0x96e1210c, 0x2a3aa59c, 0x3079f546
			};
		};

		struct owlcasl_vef_expectations : vef_image_reader_test_expectations<640>
		{
			static const inline auto filename = "TestData/images/vef/owlcasl.vef";

			static const inline native_color_map_type native_colormap
			{
				0x00, 0x3e, 0x07, 0x38
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0x7e88a376, 0xb9c5f87f, 0xf45b160d, 0x32fbbd7a
			};
		};

		struct raph_vef_expectations : vef_image_reader_test_expectations<640>
		{
			static const inline auto filename = "TestData/images/vef/raph.vef";

			static const inline native_color_map_type native_colormap
			{
				0x00, 0x3f, 0x00, 0x12
			};

			static const inline std::array<uint32_t, 4> hash
			{
				0x97dfef24, 0xcfc99a40, 0x164a7115, 0x9691bb04
			};
		};

		struct rrabbit_vef_expectations : vef_image_reader_test_expectations<640>
		{
			static const inline auto filename = "TestData/images/vef/rrabbit.vef";

			static const inline native_color_map_type native_colormap
			{
				0x3f, 0x38, 0x07, 0x00
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0x9e634599, 0x40eff36d, 0x34d067ac, 0x5d943cec
			};
		};

		struct simpson_vef_expectations : vef_image_reader_test_expectations<320>
		{
			static const inline auto filename = "TestData/images/vef/simpson.vef";

			static const inline native_color_map_type native_colormap
			{
				0x00, 0x01, 0x03, 0x04, 0x0c, 0x07, 0x1c, 0x06,
				0x07, 0x22, 0x38, 0x22, 0x38, 0x3f, 0x34, 0x3f
			};

			static const inline std::array<uint32_t, 4> hash
			{
				0x9b7b32f6, 0x193d9e45, 0xe590bb7d, 0x3d08d6ed
			};
		};

		struct trekies_vef_expectations : vef_image_reader_test_expectations<320>
		{
			static const inline auto filename = "TestData/images/vef/trekies.vef";

			static const inline native_color_map_type native_colormap
			{
				0x00, 0x04, 0x23, 0x38, 0x07, 0x20, 0x22, 0x3f,
				0x05, 0x3c, 0x22, 0x03, 0x01, 0x07, 0x3b, 0x38
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0x8c1a106d, 0x86b2c401, 0x8bf8f0ca, 0xe75b24d4
			};
		};

		struct unicorn2_vef_expectations : vef_image_reader_test_expectations<640>
		{
			static const inline auto filename = "TestData/images/vef/unicorn2.vef";

			static const inline native_color_map_type native_colormap
			{
				0x3f, 0x38, 0x03, 0x0e
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0xf3ff6fcc, 0x689c22e2, 0xb77c2ca2, 0x40ac7538
			};
		};

		struct zebra_vef_expectations : vef_image_reader_test_expectations<320>
		{
			static const inline auto filename = "TestData/images/vef/zebra.vef";

			static const inline native_color_map_type native_colormap
			{
				0x3f, 0x07, 0x38, 0x36, 0x34, 0x26, 0x24, 0x05,
				0x2d, 0x2b, 0x34, 0x19, 0x10, 0x32, 0x3e, 0x00
			};
			static const inline std::array<uint32_t, 4> hash
			{
				0xcbfa3dfa, 0xce61071f, 0x21d684f8, 0x7f250afc
			};
		};


		template<class TestType_>
		class test_vef_image_reader : public ::testing::Test {};

		using testing_types = testing::Types<
			batman_vef_expectations,
			darth_vef_expectations,
			elf_vef_expectations,
			owlcasl_vef_expectations,
			raph_vef_expectations,
			rrabbit_vef_expectations,
			simpson_vef_expectations,
			trekies_vef_expectations,
			unicorn2_vef_expectations,
			zebra_vef_expectations>;
	}

	TEST(test_vef_image_reader, load_file_not_found)
	{
		const std::string filename("TestData/images/vef/NOEXIST.vef");
		EXPECT_THROWS_MESSAGE(
			vef_image_reader().load(filename),
			core::exceptions::file_not_found_error,
			("Unable to open '" + filename + "'. File does not exist").c_str());
	}

	TEST(test_vef_image_reader, load_invalid_image_type)
	{
		std::istringstream input(std::string("\x00\x05", 2));

		EXPECT_THROWS_MESSAGE(
			vef_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"invalid image type in `<TEST>`");
	}

	TEST(test_vef_image_reader, load_past_end_of_header)
	{
		std::istringstream input("\x0", 1);

		EXPECT_THROWS_MESSAGE(
			vef_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file `<TEST>`");
	}

	TEST(test_vef_image_reader, load_past_end_of_uncompressed_image)
	{
		std::istringstream input(std::string("\x00\x00", 2) + std::string(64, 0));

		EXPECT_THROWS_MESSAGE(
			vef_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing uncompressed image data of `<TEST>`");
	}

	TEST(test_vef_image_reader, load_past_end_of_compressed_image)
	{
		std::istringstream input(std::string("\x80\x00", 2) + std::string(64, 0));

		EXPECT_THROWS_MESSAGE(
			vef_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing compressed image data of `<TEST>`");
	}



	TYPED_TEST_CASE_P(test_vef_image_reader);

	TYPED_TEST_P(test_vef_image_reader, load)
	{
		using properties = vef_image_reader::properties;
		TypeParam expectations;

		auto image(vef_image_reader().load_as<vef_image_reader::image_type>(expectations.filename));

		ASSERT_NE(image, nullptr);
		EXPECT_FALSE(image->empty());
		EXPECT_EQ(image->width(), expectations.width);
		EXPECT_EQ(image->height(), expectations.height);
		EXPECT_EQ(image->get_property(properties::native_color_space), expectations.colorspace);
		EXPECT_EQ(image->get_property(properties::native_color_map), expectations.native_colormap);
		EXPECT_EQ(calculate_md5_hash(*image), expectations.hash);
	}

	REGISTER_TYPED_TEST_CASE_P(test_vef_image_reader, load);
	INSTANTIATE_TYPED_TEST_CASE_P(test_vef_image_reader, test_vef_image_reader, testing_types);

}
