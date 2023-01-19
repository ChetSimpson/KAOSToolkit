// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/cm3/cm3_image_reader.h>
#include <kaos/assetfoo/images/cm3/cm3_image.h>
#include <kaos/core/exceptions.h>
#include <kaos/assetfoo/test/images/cm3/default_patterns.h>
#include <kaos/assetfoo/test/load_tc1014_image_test_expectations.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <fstream>


namespace hypertech::kaos::assetfoo::images::cm3::unittests
{

	namespace
	{
		using hypertech::kaos::assetfoo::images::cm3::cm3_image;
		using hypertech::kaos::assetfoo::unittests::load_tc1014_image_test_expectations;
		using namespace hypertech::kaos::assetfoo::images::cm3::unittests;

		static const cm3_image::cycle_colors_list_type default_cycle_colors1 =
		{ {
			{ 0xFF, 0xAA, 0x00 }, { 0x55, 0xAA, 0xAA }, { 0xFF, 0xFF, 0xAA }, { 0xAA, 0xAA, 0xFF },
			{ 0x00, 0xFF, 0x55 }, { 0x00, 0xFF, 0x00 }, { 0x00, 0x55, 0x55 }, { 0x00, 0x55, 0x00 }
		} };

		static const cm3_image::cycle_colors_list_type default_cycle_colors2 =
		{ {
			{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0xFF }, { 0x00, 0xAA, 0xFF }, { 0xAA, 0xFF, 0xFF },
			{ 0xFF, 0xFF, 0xFF }, { 0xAA, 0xFF, 0x55 }, { 0xFF, 0x55, 0x00 }, { 0x55, 0x55, 0x00 }
		} };

		template<size_t Height_ = 192>
		struct load_cm3_image_test_expectations : load_tc1014_image_test_expectations<320, Height_>
		{
			static const cm3_image::size_type animation_rate = 3;
			static const cm3_image::size_type cycle_rate = 4;
			static const inline auto cycle_colors = default_cycle_colors1;
			static const inline auto patterns = default_pattern_set;

			virtual bool should_print_diagnostics() const
			{
				return false;
			}

			virtual void print_diagnostics(
				const typename load_tc1014_image_test_expectations<320, Height_>::base_image_type& base_image,
				const cm3_image::pattern_list_type& expected_patterns) const
			{
				if (!this->should_print_diagnostics())
				{
					return;
				}

				load_tc1014_image_test_expectations<320, Height_>::print_diagnostics(base_image);
				const auto& image(dynamic_cast<const cm3_image&>(base_image));

				std::cout << "PATS =\n";
				for (const auto& color : image.cycle_colors())
				{
					std::cout
						<< "{ " << std::hex << std::uppercase << std::setfill('0') << std::setw(2)
						<< "0x" << std::setw(2) << unsigned(color.R)
						<< ", 0x" << std::setw(2) << unsigned(color.G)
						<< ", 0x" << std::setw(2) << unsigned(color.B)
						<< " },\n";
				}

				auto expected_pattern_ptr(expected_patterns.begin());
				int count = 1;
				for (const auto& pattern : image.patterns())
				{
					if (*expected_pattern_ptr == pattern)
					{
						++expected_pattern_ptr;
						continue;
					}
					std::cout << "Expected: { " << pattern.foreground_color() << ", " << pattern.background_color() << ", { ";
					
					const char* comma = "";
					for (const auto& pixelrow : pattern.pixelmap())
					{
						std::cout
							<< comma << "0x"
							<< std::hex << std::uppercase << std::setw(2) << std::setfill('0')
							<< unsigned(pixelrow) << std::dec;
						comma = ", ";
					}

					std::cout << " } },\n";

					++count;
					++expected_pattern_ptr;
				}
			}
		};
		

		struct default_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/default_rgb.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3f, 0x36, 0x2e, 0x26, 0x19, 0x10, 0x0f, 0x38,
				0x07, 0x22, 0x28, 0x20, 0x0a, 0x02, 0x09, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0x77428ab1, 0x68d9088d, 0x376eb646, 0x906a1e9b
			};

			static const inline auto cycle_colors = default_cycle_colors2;
		};

		struct default_composite_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/default_composite.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3f, 0x33, 0x28, 0x26, 0x2d, 0x21, 0x2b, 0x20,
				0x10, 0x14, 0x08, 0x06, 0x0d, 0x0e, 0x0b, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0x77428ab1, 0x68d9088d, 0x376eb646, 0x906a1e9b
			};

			static const inline auto cycle_colors = default_cycle_colors2;
		};

		struct title_page_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/title_page.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3F, 0x33, 0x28, 0x07, 0x2D, 0x21, 0x0B, 0x20,
				0x3E, 0x14, 0x00, 0x02, 0x3E, 0x33, 0x11, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0xDD7B1D9C, 0x6468BB76, 0x752B55B3, 0xFF5EBE5D
			};

			static const inline auto cycle_colors = default_cycle_colors2;
		};

		struct bluedrag_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/bluedrag.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3F, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x0E, 0x0E,
				0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0x9F08EC22, 0x6CD17DC2, 0xB85EF6CE, 0xF4DDBA7C
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 3;
			static const inline cm3_image::cycle_colors_list_type cycle_colors =
			{ {
				{ 0xFF, 0xFF, 0x00 },
				{ 0xFF, 0x00, 0x00 },
				{ 0xAA, 0x00, 0x55 },
				{ 0x00, 0x00, 0xFF },
				{ 0x55, 0x55, 0xFF },
				{ 0x00, 0xAA, 0xFF },
				{ 0x00, 0xFF, 0x00 },
				{ 0xAA, 0xFF, 0x00 }
			} };

			const default_pattern_list_type patterns =
			{ {
				{ 1, 0,   default_pattern_1_pixmap },
				{ 5, 13,  { 0x55, 0x00, 0x55, 0x00, 0x55, 0x00, 0x55, 0x00 } },
				{ 2, 9,   { 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55 } },
				{ 1, 15,  { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA } },
				{ 7, 5,   { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA } },
				{ 6, 14,  { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA } },
				{ 6, 15,  { 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55 } },
				default_pattern_8 ,
				{ 14, 15, { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA } },
				{ 4, 7,   { 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55 } },
				{ 4, 15,  { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA } },
				default_pattern_12,
				default_pattern_13,
				default_pattern_14,
				default_pattern_15,
				default_pattern_16,
				default_pattern_17,
				{ 3, 1,   default_pattern_18_pixmap },
				default_pattern_19,
				default_pattern_20,
				default_pattern_21,
				default_pattern_22,
				default_pattern_23,
				default_pattern_24,
			} };
		};

		struct bridge_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/bridge.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x04, 0x06, 0x3F, 0x38, 0x26, 0x28, 0x33, 0x15,
				0x00, 0x0F, 0x25, 0x06, 0x1C, 0x1B, 0x1F, 0x3B
			};

			const std::array<uint32_t, 4> hash
			{
				0x69807182, 0x733EAE14, 0xDBE80C2D, 0x5A167AAA
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct bugsbull_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/bugsbull.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3F, 0x00, 0x38, 0x39, 0x24, 0x20, 0x26, 0x22,
				0x34, 0x19, 0x3E, 0x3C, 0x3F, 0x22, 0x22, 0x09
			};

			const std::array<uint32_t, 4> hash
			{
				0x614D1205, 0x6B5B7097, 0x74373315, 0x677D0C0E
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct citidel_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/citidel.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3F, 0x3B, 0x1C, 0x34, 0x38, 0x0E, 0x0C, 0x28,
				0x05, 0x36, 0x08, 0x06, 0x0D, 0x0E, 0x01, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0x600706D1, 0x5AA4311F, 0x2363C0BE, 0x264615FC
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 3;

			static const inline cm3_image::cycle_colors_list_type cycle_colors =
			{ {
				{ 0xFF, 0xFF, 0x00 },
				{ 0xFF, 0x00, 0x00 },
				{ 0xAA, 0x00, 0x55 },
				{ 0x00, 0x00, 0xFF },
				{ 0x55, 0x55, 0xFF },
				{ 0x00, 0xAA, 0xFF },
				{ 0x00, 0xFF, 0x00 },
				{ 0xAA, 0xFF, 0x00 },
			} };

			const default_pattern_list_type patterns =
			{
				default_pattern_1,
				default_pattern_2,
				{ 1, 3, { 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55 } },
				default_pattern_4,
				default_pattern_5,
				default_pattern_6,
				default_pattern_7,
				{ 3, 10, { 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA } },
				default_pattern_9,
				default_pattern_10,
				default_pattern_11,
				default_pattern_12,
				default_pattern_13,
				default_pattern_14,
				default_pattern_15,
				default_pattern_16,
				default_pattern_17,
				{ 3, 1, default_pattern_18_pixmap },
				default_pattern_19,
				default_pattern_20,
				default_pattern_21,
				default_pattern_22,
				default_pattern_23,
				default_pattern_24
			};
		};

		struct girl_rgb_cm3_expectations : load_cm3_image_test_expectations<>	//	NO PATTERNS
		{
			static const inline auto filename = "TestData/images/cm3/girl.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x00, 0x29, 0x03, 0x22, 0x02, 0x01, 0x3F, 0x3E,
				0x35, 0x22, 0x20, 0x04, 0x04, 0x00, 0x00, 0x04
			};

			const std::array<uint32_t, 4> hash
			{
				0x83F17918, 0x95E94E32, 0xE9715DA2, 0xA4D20C47
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;

			const default_pattern_list_type patterns;
		};

		struct jets_rgb_cm3_expectations : load_cm3_image_test_expectations<>	//	NO PATTERNS
		{
			static const inline auto filename = "TestData/images/cm3/jets.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3F, 0x01, 0x26, 0x3E, 0x0A, 0x14, 0x08, 0x02,
				0x38, 0x07, 0x3F, 0x36, 0x24, 0x3E, 0x19, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0x0DAEB7A3, 0x21BFFCFB, 0xCF1C87AB, 0x2F6740BF
			};

			static const cm3_image::size_type animation_rate = 1;
			static const cm3_image::size_type cycle_rate = 2;

			static const inline cm3_image::cycle_colors_list_type cycle_colors =
			{ {
				{ 0xFF, 0xFF, 0xAA},
				{ 0xFF, 0xFF, 0xAA},
				{ 0xFF, 0xFF, 0x00},
				{ 0xFF, 0xAA, 0x55},
				{ 0xFF, 0xFF, 0x00},
				{ 0xFF, 0xFF, 0xAA},
				{ 0xFF, 0xFF, 0xFF},
				{ 0xFF, 0xFF, 0xAA},
			} };

			static const inline default_pattern_list_type patterns =
			{
				default_pattern_1,
				{ 1, 6, default_pattern_2_pixmap},
				default_pattern_3,
				default_pattern_4,
				default_pattern_5,
				default_pattern_6,
				default_pattern_7,
				default_pattern_8,
				default_pattern_9,
				default_pattern_10,
				default_pattern_11,
				default_pattern_12,
				default_pattern_13,
				default_pattern_14,
				default_pattern_15,
				default_pattern_16,
				default_pattern_17,
				{ 3, 1, default_pattern_18_pixmap },
				default_pattern_19,
				default_pattern_20,
				default_pattern_21,
				default_pattern_22,
				default_pattern_23,
				default_pattern_24
			};
		};

		struct kingtut_rgb_cm3_expectations : load_cm3_image_test_expectations<>	//	NO PATTERNS
		{
			static const inline auto filename = "TestData/images/cm3/kingtut.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x00, 0x22, 0x04, 0x26, 0x20, 0x04, 0x04, 0x26,
				0x34, 0x35, 0x26, 0x24, 0x37, 0x34, 0x33, 0x36
			};

			const std::array<uint32_t, 4> hash
			{
				0xC832D136, 0x6549AF2C, 0x299C2D7F, 0x2208DB45
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct match_composite_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/match.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x00, 0x20, 0x09, 0x26, 0x34, 0x36, 0x12, 0x07,
				0x02, 0x04, 0x0C, 0x24, 0x26, 0x34, 0x36, 0x3F
			};

			const std::array<uint32_t, 4> hash
			{
				0x7F674CEF, 0xDA5B3C79, 0x3B138337, 0xB6740EB4
			};

			static const cm3_image::size_type animation_rate = 5;
			static const cm3_image::size_type cycle_rate = 5;

			static const inline cm3_image::cycle_colors_list_type cycle_colors =
			{ {
				{ 0x00, 0x00, 0x55 },
				{ 0x00, 0x00, 0xAA },
				{ 0x00, 0x00, 0x55 },
				{ 0x55, 0x00, 0xAA },
				{ 0x00, 0x00, 0x55 },
				{ 0x00, 0x00, 0xAA },
				{ 0x00, 0x00, 0xFF },
				{ 0x00, 0x00, 0xFF },
			} };

			static const inline default_pattern_list_type patterns =
			{
				default_pattern_1,
				default_pattern_2,
				default_pattern_3,
				default_pattern_4,
				default_pattern_5,
				default_pattern_6,
				default_pattern_7,
				default_pattern_8,
				default_pattern_9,
				default_pattern_10,
				default_pattern_11,
				default_pattern_12,
				default_pattern_13,
				default_pattern_14,
				default_pattern_15,
				default_pattern_16,
				default_pattern_17,
				{ 3, 1, default_pattern_18_pixmap },
				default_pattern_19,
				default_pattern_20,
				default_pattern_21,
				default_pattern_22,
				default_pattern_23,
				default_pattern_24
			};
		};

		struct mazda_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/mazda.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x26, 0x35, 0x3E, 0x24, 0x20, 0x0A, 0x0B, 0x0D,
				0x08, 0x19, 0x1D, 0x01, 0x34, 0x22, 0x07, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0xB04D5983, 0xABA9249B, 0x8D42AB9A, 0xBDC41AD1
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct paincan_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/paincan.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x00, 0x12, 0x10, 0x0D, 0x0F, 0x20, 0x24, 0x33,
				0x30, 0x03, 0x03, 0x07, 0x07, 0x1C, 0x1C, 0x38
			};

			const std::array<uint32_t, 4> hash
			{
				0x92AA8AAB, 0xE2FCDA93, 0x94AE9B48, 0x5D931DD5
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct playboy_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/playboy.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x00, 0x3F, 0x00, 0x00, 0x04, 0x04, 0x07, 0x20,
				0x07, 0x23, 0x31, 0x38, 0x3C, 0x3A, 0x1F, 0x3F
			};

			const std::array<uint32_t, 4> hash
			{
				0x91CC3AAA, 0xF2EAFBDE, 0x16407CCB, 0x667A8FD5
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct spaceman_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/spaceman.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x3F, 0x3E, 0x3C, 0x31, 0x23, 0x1C, 0x0F, 0x38,
				0x07, 0x22, 0x28, 0x20, 0x0A, 0x02, 0x09, 0x00
			};

			const std::array<uint32_t, 4> hash
			{
				0xAC79223C, 0x118E1853, 0xA0BEBD44, 0x662E49A2
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct starflt_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/starflt.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x00, 0x01, 0x05, 0x29, 0x2C, 0x05, 0x28, 0x14,
				0x06, 0x38, 0x0B, 0x36, 0x26, 0x34, 0x12, 0x11
			};

			const std::array<uint32_t, 4> hash
			{
				0xCAA3FC45, 0x78D708A9, 0x6B9A599F, 0xC9EE2F5D
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct timextal_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/timextal.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x0D, 0x02, 0x1B, 0x3B, 0x1B, 0x1F, 0x3B, 0x3F,
				0x18, 0x07, 0x03, 0x24, 0x35, 0x27, 0x06, 0x04
			};

			const std::array<uint32_t, 4> hash
			{
				0xF3BD5BA6, 0xD9A66761, 0x57E3AEB2, 0xF29C42C3
			};

			static const cm3_image::size_type animation_rate = 7;
			static const cm3_image::size_type cycle_rate = 7;
		};

		struct vigil_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/vigil.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x02, 0x00, 0x10, 0x36, 0x16, 0x3B, 0x3F, 0x00,
				0x00, 0x26, 0x39, 0x3C, 0x22, 0x28, 0x04, 0x38
			};

			const std::array<uint32_t, 4> hash
			{
				0xC309D073, 0x0B82CA5D, 0x9F2650D1, 0xB8E856ED
			};

			static const cm3_image::size_type animation_rate = 120;
			static const cm3_image::size_type cycle_rate = 120;

			static const inline cm3_image::cycle_colors_list_type cycle_colors =
			{ {
				{ 0xAA, 0xAA, 0xFF },
				{ 0xAA, 0xAA, 0xFF },
				{ 0x55, 0xAA, 0xFF },
				{ 0x00, 0xAA, 0xFF },
				{ 0xFF, 0xAA, 0xFF },
				{ 0xFF, 0xAA, 0xFF },
				{ 0xAA, 0xAA, 0xFF },
				{ 0xAA, 0xAA, 0xFF },
			} };

			const default_pattern_list_type patterns =
			{
				default_pattern_1,
				default_pattern_2,
				default_pattern_3,
				default_pattern_4,
				default_pattern_5,
				default_pattern_6,
				default_pattern_7,
				default_pattern_8,
				default_pattern_9,
				default_pattern_10,
				default_pattern_11,
				default_pattern_12,
				default_pattern_13,
				default_pattern_14,
				default_pattern_15,
				default_pattern_16,
				default_pattern_17,
				{ 3, 1, default_pattern_18_pixmap },
				default_pattern_19,
				default_pattern_20,
				default_pattern_21,
				default_pattern_22,
				default_pattern_23,
				default_pattern_24
			};
		};

		struct waterfall_rgb_cm3_expectations : load_cm3_image_test_expectations<>
		{
			static const inline auto filename = "TestData/images/cm3/waterfall.cm3";

			const cm3_image::native_color_map_type native_colormap
			{
				0x01, 0x1C, 0x00, 0x18, 0x04, 0x02, 0x0E, 0x11,
				0x36, 0x33, 0x38, 0x38, 0x1C, 0x18, 0x1D, 0x03
			};

			const std::array<uint32_t, 4> hash
			{
				0x42BB41BC, 0x510BDE17, 0xBF211047, 0x95EB4B0E
			};

			static const cm3_image::size_type animation_rate = 10;
			static const cm3_image::size_type cycle_rate = 7;

			//virtual bool should_print_diagnostics() const
			//{
			//	return true;
			//}
		};


		template<class TestType_>
		class test_cm3_image_reader : public ::testing::Test {};

		using testing_types = testing::Types<
			default_rgb_cm3_expectations,
			default_composite_cm3_expectations,
			title_page_cm3_expectations,
			bluedrag_cm3_expectations,
			bridge_cm3_expectations,
			bugsbull_cm3_expectations,
			citidel_cm3_expectations,
			girl_rgb_cm3_expectations,
			jets_rgb_cm3_expectations,
			kingtut_rgb_cm3_expectations,
			match_composite_cm3_expectations,
			mazda_rgb_cm3_expectations,
			paincan_rgb_cm3_expectations,
			playboy_rgb_cm3_expectations,
			spaceman_rgb_cm3_expectations,
			starflt_rgb_cm3_expectations,
			timextal_rgb_cm3_expectations,
			vigil_rgb_cm3_expectations,
			waterfall_rgb_cm3_expectations
		>;

		const auto single_page_exclude_patterns_header_data =
			std::string("\x01")		//	image flags (single page, exclude patterns)
			+ std::string(16, 0x3f)	//	colormap
			+ std::string("\x01")	//	animation_rate
			+ std::string("\x01")	//	cycle_rate
			+ std::string(8, 0x3f)	//	cycle_colors
			+ std::string("\x01")	//	animation_flags
			+ std::string("\x01")	//	cycling_flags
			;
		const auto single_page_include_patterns_header_data =
			std::string("\x00", 1)	//	image flags (single page, include patterns)
			+ std::string(16, 0x3f)	//	colormap
			+ std::string("\x01")	//	animation_rate
			+ std::string("\x01")	//	cycle_rate
			+ std::string(8, 0x3f)	//	cycle_colors
			+ std::string("\x01")	//	animation_flags
			+ std::string("\x01")	//	cycling_flags
			;

	}

	TEST(test_cm3_image_reader, load_file_not_found)
	{
		const std::string filename("TestData/images/cm3/NOEXIST.cm3");
		EXPECT_THROWS_MESSAGE(
			cm3_image_reader().load(filename),
			core::exceptions::file_not_found_error,
			("Unable to open '" + filename + "'. File does not exist").c_str());
	}


	TEST(test_cm3_image_reader, load_past_end_of_header)
	{
		std::istringstream input("01234567890ABCDEF");
		EXPECT_THROWS_MESSAGE(
			cm3_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file `<TEST>`");
	}



	TEST(test_cm3_image_reader, load_past_end_of_patterns)
	{
		std::istringstream input(single_page_include_patterns_header_data);

		EXPECT_THROWS_MESSAGE(
			cm3_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while loading patterns from `<TEST>");
	}

	TEST(test_cm3_image_reader, load_invalid_page_row_count)
	{
		auto file_data =
			single_page_exclude_patterns_header_data
			+ std::string("\x01");

		std::istringstream input(file_data);

		EXPECT_THROWS_MESSAGE(
			cm3_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: invalid row count of 1 in image page 0 of `<TEST>`");
	}


	TEST(test_cm3_image_reader, load_past_end_of_page)
	{
		std::istringstream input(
			single_page_exclude_patterns_header_data
			+ std::string("\xc0"));

		EXPECT_THROWS_MESSAGE(
			cm3_image_reader().load(input, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing uncompressed image data in page 0 of `<TEST>`");
	}


	TYPED_TEST_CASE_P(test_cm3_image_reader);

	TYPED_TEST_P(test_cm3_image_reader, load)
	{
		TypeParam expectations;

		auto image(cm3_image_reader().load_as<cm3_image>(expectations.filename));
		//if (expectations.should_print_diagnostics())
		//{
		//	std::ofstream output(expectations.filename + std::string(".data"));
		//	output.write(reinterpret_cast<char*>(image->data()), image->get_sequence().size_bytes());
		//}
		
		expectations.print_diagnostics(*image, expectations.patterns);
		ASSERT_NE(image, nullptr);
		EXPECT_FALSE(image->empty());
		EXPECT_EQ(image->width(), expectations.width);
		EXPECT_EQ(image->height(), expectations.height);
		EXPECT_EQ(image->native_color_space(), expectations.colorspace);
		EXPECT_EQ(image->native_colormap().size(), expectations.native_colormap.size());
		EXPECT_EQ(image->native_colormap(), expectations.native_colormap);
		EXPECT_EQ(image->animation_rate(), expectations.animation_rate);
		EXPECT_EQ(image->cycle_rate(), expectations.cycle_rate);
		EXPECT_EQ(image->cycle_colors(), expectations.cycle_colors);
		EXPECT_EQ(image->patterns(), expectations.patterns);
		EXPECT_EQ(calculate_md5_hash(*image), expectations.hash);
	}

	REGISTER_TYPED_TEST_CASE_P(test_cm3_image_reader, load);
	INSTANTIATE_TYPED_TEST_CASE_P(test_cm3_image_reader, test_cm3_image_reader, testing_types);

}
