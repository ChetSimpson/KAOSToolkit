// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/gimp/gimp_palette_reader.h>
#include <kaos/assetfoo/colors/color_map.h>
#include <kaos/core/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <filesystem>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors { namespace gimp { namespace unittests
{

	namespace test_colors
	{
		using color_type = color_map::color_type;

		static const color_type color0(0, 0, 0);
		static const color_type color1(85, 85, 85);
		static const color_type color2(170, 170, 170);
		static const color_type color3(85, 85, 170);
		static const color_type color4(0, 85, 170);
		static const color_type color5(85, 170, 255);
		static const color_type color6(170, 170, 255);
		static const color_type color7(0, 85, 0);
		static const color_type color8(0, 170, 0);
		static const color_type color9(170, 0, 0);
		static const color_type color10(255, 0, 0);
		static const color_type color11(170, 85, 0);
		static const color_type color12(255, 170, 0);
		static const color_type color13(170, 0, 170);
		static const color_type color14(255, 0, 255);
		static const color_type color15(255, 255, 255);
	}



	TEST(gimp_palette_reader, load_non_existent_palette_from_file)
	{
		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load("TestData/Palettes/NOPALETTEFILE"),
			core::exceptions::file_not_found_error,
			"Unable to open 'TestData/Palettes/NOPALETTEFILE'. File does not exist");
	}


	//	FIXME: fix or delete
	//TEST(gimp_palette_reader, load_unopenable_palette_from_file)
	//{
	//	std::string filename(std::tmpnam(nullptr));
	//	std::ofstream locked_file(filename, std::ios_base::out);

	//	ASSERT_TRUE(locked_file.is_open());

	//	EXPECT_THROWS_MESSAGE(
	//		gimp_palette_reader().load(filename),
	//		core::exceptions::file_access_error,
	//		("Unable to open 'TestData/Palettes/'" + filename + ".").c_str());

	//	locked_file.close();
	//	EXPECT_TRUE(std::filesystem::remove(filename));
	//}


	TEST(gimp_palette_reader, load_palette_from_file)
	{
		auto palette(dynamic_pointer_cast<color_map>(gimp_palette_reader().load("TestData/Palettes/TestPalette1.gpl")));

		ASSERT_NE(palette, nullptr);
		EXPECT_EQ(palette->at(0), test_colors::color0);
		EXPECT_EQ(palette->at(1), test_colors::color1);
		EXPECT_EQ(palette->at(2), test_colors::color2);
		EXPECT_EQ(palette->at(3), test_colors::color3);
		EXPECT_EQ(palette->at(4), test_colors::color4);
		EXPECT_EQ(palette->at(5), test_colors::color5);
		EXPECT_EQ(palette->at(6), test_colors::color6);
		EXPECT_EQ(palette->at(7), test_colors::color7);
		EXPECT_EQ(palette->at(8), test_colors::color8);
		EXPECT_EQ(palette->at(9), test_colors::color9);
		EXPECT_EQ(palette->at(10), test_colors::color10);
		EXPECT_EQ(palette->at(11), test_colors::color11);
		EXPECT_EQ(palette->at(12), test_colors::color12);
		EXPECT_EQ(palette->at(13), test_colors::color13);
		EXPECT_EQ(palette->at(14), test_colors::color14);
		EXPECT_EQ(palette->at(15), test_colors::color15);
	}


	TEST(gimp_palette_reader, load_palette_from_stream)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"Name: KAOS Game - Shooter Mew\n"
			"Columns: 16\n"
			"#\n"
			"  0   0   0	#1\n"
			" 85  85  85	#2\n"
			"170 170 170	#3\n"
			" 85  85 170	#4\n"
			"  0  85 170	#5\n"
			" 85 170 255	#6\n"
			"170 170 255	#7\n"
			"  0  85   0	#8\n"
			"  0 170   0	#9\n"
			"170   0   0	#10\n"
			"255   0   0	#11\n"
			"170  85   0	#12\n"
			"255 170   0	#13\n"
			"170   0 170	#14\n"
			"255   0 255	#15\n"
			"255 255 255	#16\n";

		std::istringstream input_stream(file_in_string);

		auto palette(dynamic_pointer_cast<color_map>(gimp_palette_reader().load(input_stream, "<string stream>")));

		ASSERT_NE(palette, nullptr);
		EXPECT_EQ(palette->at(0), test_colors::color0);
		EXPECT_EQ(palette->at(1), test_colors::color1);
		EXPECT_EQ(palette->at(2), test_colors::color2);
		EXPECT_EQ(palette->at(3), test_colors::color3);
		EXPECT_EQ(palette->at(4), test_colors::color4);
		EXPECT_EQ(palette->at(5), test_colors::color5);
		EXPECT_EQ(palette->at(6), test_colors::color6);
		EXPECT_EQ(palette->at(7), test_colors::color7);
		EXPECT_EQ(palette->at(8), test_colors::color8);
		EXPECT_EQ(palette->at(9), test_colors::color9);
		EXPECT_EQ(palette->at(10), test_colors::color10);
		EXPECT_EQ(palette->at(11), test_colors::color11);
		EXPECT_EQ(palette->at(12), test_colors::color12);
		EXPECT_EQ(palette->at(13), test_colors::color13);
		EXPECT_EQ(palette->at(14), test_colors::color14);
		EXPECT_EQ(palette->at(15), test_colors::color15);
	}


	TEST(gimp_palette_reader, empty_file)
	{
		std::istringstream input_stream;

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Unable to load empty GIMP palette file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_header)
	{
		std::string file_in_string =
			"GUMP Palette\n"
			"#\n"
			"  0   0   0	#1\n"
			" 85  85  85	#2\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Incorrect header in GIMP palette file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_red_level_single_space_in_line)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			" \n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Unable to parse red color component in line ' ' from file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_red_level_non_int)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"--- 255 255\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Unable to parse red color component in line '--- 255 255' from file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_red_level)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"265 255 255\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Red color level is outside the expected range of 0 to 255 in line '265 255 255' from file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_green_level_missinglevel)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"255\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Unable to parse green color component in line '255' from file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_green_level_nonint)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"255 --- 255\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Unable to parse green color component in line '255 --- 255' from file '<string stream>'");
	}

	TEST(gimp_palette_reader, invalid_green_level)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"255 265 255\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Green color level is outside the expected range of 0 to 255 in line '255 265 255' from file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_blue_level_missing_level)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"255 255\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Unable to parse blue color component in line '255 255' from file '<string stream>'");
	}


	TEST(gimp_palette_reader, invalid_blue_level_non_int)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"255 255 ---\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Unable to parse blue color component in line '255 255 ---' from file '<string stream>'");
	}

	TEST(gimp_palette_reader, invalid_blue_level)
	{
		std::string file_in_string =
			"GIMP Palette\n"
			"#\n"
			"255 255 265\n";

		std::istringstream input_stream(file_in_string);

		EXPECT_THROWS_MESSAGE(
			gimp_palette_reader().load(input_stream, "<string stream>"),
			core::exceptions::file_format_error,
			"Blue color level is outside the expected range of 0 to 255 in line '255 255 265' from file '<string stream>'");
	}

}}}}}}
