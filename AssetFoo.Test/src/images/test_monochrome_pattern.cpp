// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/monochrome_pattern.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace unittests
{

	namespace
	{
		template<class Type_>
		struct expectations;

		template<class Type_>
		struct expectations_base
		{
			static const inline monochrome_pattern<Type_>::pixelmap_type empty_pattern_pixmap{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

			static const size_t width = std::numeric_limits<Type_>::digits;
			static const size_t height = width;
			static const size_t pixmap_length = height;
		};

		template<>
		struct expectations<uint8_t> : expectations_base<uint8_t>
		{
			static const inline std::vector<monochrome_pattern<uint8_t>::pixelmap_type> pattern_pixmaps
			{
				{0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA},
				{0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55},
				{0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00},
				{0xDD, 0xBB, 0x77, 0xEE, 0xDD, 0xBB, 0x77, 0xEE},
			};

		};

		template<>
		struct expectations<uint16_t> : expectations_base<uint16_t>
		{
			static const inline std::vector<monochrome_pattern<uint16_t>::pixelmap_type> pattern_pixmaps
			{
				{0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA, 0x5555, 0xAAAA},
				{0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555},
				{0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000},
				{0xDDDD, 0xBBBB, 0x7777, 0xEEEE, 0xDDDD, 0xBBBB, 0x7777, 0xEEEE},
			};

		};

		template<>
		struct expectations<uint32_t> : expectations_base<uint32_t>
		{
			static const inline std::vector<monochrome_pattern<uint32_t>::pixelmap_type> pattern_pixmaps
			{
				{0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA},
				{0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555},
				{0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000},
				{0xDDDDDDDD, 0xBBBBBBBB, 0x77777777, 0xEEEEEEEE, 0xDDDDDDDD, 0xBBBBBBBB, 0x77777777, 0xEEEEEEEE},
			};

		};

		template<>
		struct expectations<uint64_t> : expectations_base<uint64_t>
		{
			static const inline std::vector<monochrome_pattern<uint64_t>::pixelmap_type> pattern_pixmaps
			{
				{0x5555555555555555, 0xAAAAAAAAAAAAAAAA, 0x5555555555555555, 0xAAAAAAAAAAAAAAAA, 0x5555555555555555, 0xAAAAAAAAAAAAAAAA, 0x5555555555555555, 0xAAAAAAAAAAAAAAAA},
				{0x5555555555555555, 0x5555555555555555, 0x5555555555555555, 0x5555555555555555, 0x5555555555555555, 0x5555555555555555, 0x5555555555555555, 0x5555555555555555},
				{0xFFFFFFFFFFFFFFFF, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000},
				{0xDDDDDDDDDDDDDDDD, 0xBBBBBBBBBBBBBBBB, 0x7777777777777777, 0xEEEEEEEEEEEEEEEE, 0xDDDDDDDDDDDDDDDD, 0xBBBBBBBBBBBBBBBB, 0x7777777777777777, 0xEEEEEEEEEEEEEEEE},
			};

		};

		using color_type = core::types::rgba_color;


		template<class TestType_>
		class test_monochrome_pattern : public ::testing::Test
		{
		};

		TYPED_TEST_CASE_P(test_monochrome_pattern);
	}



	TYPED_TEST_P(test_monochrome_pattern, default_constructor)
	{
		expectations<TypeParam> expectations;

		monochrome_pattern<TypeParam> pattern;

		EXPECT_EQ(pattern.width, expectations.width);
		EXPECT_EQ(pattern.height, expectations.height);
		EXPECT_EQ(pattern.pixmap_length, expectations.pixmap_length);
		EXPECT_EQ(pattern.background_color(), color_type());
		EXPECT_EQ(pattern.foreground_color(), color_type());
		EXPECT_EQ(pattern.pixelmap(), expectations.empty_pattern_pixmap);
	}

	TYPED_TEST_P(test_monochrome_pattern, value_constructor)
	{
		expectations<TypeParam> expectations;

		const auto color1(color_type(1, 2, 3));
		const auto color2(color_type(4, 5, 6));

		for (const auto& pixmap : expectations.pattern_pixmaps)
		{
			monochrome_pattern<TypeParam> pattern(color1, color2, pixmap);

			ASSERT_EQ(pattern.width, expectations.width);
			ASSERT_EQ(pattern.height, expectations.height);
			ASSERT_EQ(pattern.pixmap_length, expectations.pixmap_length);
			ASSERT_EQ(pattern.background_color(), color1);
			ASSERT_EQ(pattern.foreground_color(), color2);
			ASSERT_EQ(pattern.pixelmap(), pixmap);
		}
	}

	TYPED_TEST_P(test_monochrome_pattern, copy_constructor)
	{
		expectations<TypeParam> expectations;

		const auto color1(color_type(1, 2, 3));
		const auto color2(color_type(4, 5, 6));

		for (const auto& pixmap : expectations.pattern_pixmaps)
		{
			monochrome_pattern<TypeParam> pattern(color1, color2, pixmap);
			monochrome_pattern<TypeParam> copy_pattern(pattern);

			EXPECT_EQ(pattern.width, expectations.width);
			EXPECT_EQ(pattern.height, expectations.height);
			EXPECT_EQ(pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(pattern.background_color(), color1);
			EXPECT_EQ(pattern.foreground_color(), color2);
			EXPECT_EQ(pattern.pixelmap(), pixmap);

			EXPECT_EQ(copy_pattern.width, expectations.width);
			EXPECT_EQ(copy_pattern.height, expectations.height);
			EXPECT_EQ(copy_pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(copy_pattern.background_color(), color1);
			EXPECT_EQ(copy_pattern.foreground_color(), color2);
			EXPECT_EQ(copy_pattern.pixelmap(), pixmap);
		}
	}

	TYPED_TEST_P(test_monochrome_pattern, move_constructor)
	{
		expectations<TypeParam> expectations;

		const auto color1(color_type(1, 2, 3));
		const auto color2(color_type(4, 5, 6));

		for (const auto& pixmap : expectations.pattern_pixmaps)
		{
			monochrome_pattern<TypeParam> pattern(color1, color2, pixmap);
			monochrome_pattern<TypeParam> copy_pattern(move(pattern));

			EXPECT_EQ(pattern.width, expectations.width);
			EXPECT_EQ(pattern.height, expectations.height);
			EXPECT_EQ(pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(pattern.background_color(), color_type());
			EXPECT_EQ(pattern.foreground_color(), color_type());
			EXPECT_EQ(pattern.pixelmap(), expectations.empty_pattern_pixmap);

			EXPECT_EQ(copy_pattern.width, expectations.width);
			EXPECT_EQ(copy_pattern.height, expectations.height);
			EXPECT_EQ(copy_pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(copy_pattern.background_color(), color1);
			EXPECT_EQ(copy_pattern.foreground_color(), color2);
			EXPECT_EQ(copy_pattern.pixelmap(), pixmap);
		}
	}

	TYPED_TEST_P(test_monochrome_pattern, copy_assignment)
	{
		expectations<TypeParam> expectations;

		const auto color1(color_type(1, 2, 3));
		const auto color2(color_type(4, 5, 6));

		for (const auto& pixmap : expectations.pattern_pixmaps)
		{
			monochrome_pattern<TypeParam> pattern(color1, color2, pixmap);
			monochrome_pattern<TypeParam> copy_pattern;

			copy_pattern = pattern;

			EXPECT_EQ(pattern.width, expectations.width);
			EXPECT_EQ(pattern.height, expectations.height);
			EXPECT_EQ(pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(pattern.background_color(), color1);
			EXPECT_EQ(pattern.foreground_color(), color2);
			EXPECT_EQ(pattern.pixelmap(), pixmap);

			EXPECT_EQ(copy_pattern.width, expectations.width);
			EXPECT_EQ(copy_pattern.height, expectations.height);
			EXPECT_EQ(copy_pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(copy_pattern.background_color(), color1);
			EXPECT_EQ(copy_pattern.foreground_color(), color2);
			EXPECT_EQ(copy_pattern.pixelmap(), pixmap);
		}
	}

	TYPED_TEST_P(test_monochrome_pattern, move_assignment)
	{
		expectations<TypeParam> expectations;

		const auto color1(color_type(1, 2, 3));
		const auto color2(color_type(4, 5, 6));

		for (const auto& pixmap : expectations.pattern_pixmaps)
		{
			monochrome_pattern<TypeParam> pattern(color1, color2, pixmap);
			monochrome_pattern<TypeParam> copy_pattern;

			copy_pattern = move(pattern);

			EXPECT_EQ(pattern.width, expectations.width);
			EXPECT_EQ(pattern.height, expectations.height);
			EXPECT_EQ(pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(pattern.background_color(), color_type());
			EXPECT_EQ(pattern.foreground_color(), color_type());
			EXPECT_EQ(pattern.pixelmap(), expectations.empty_pattern_pixmap);

			EXPECT_EQ(copy_pattern.width, expectations.width);
			EXPECT_EQ(copy_pattern.height, expectations.height);
			EXPECT_EQ(copy_pattern.pixmap_length, expectations.pixmap_length);
			EXPECT_EQ(copy_pattern.background_color(), color1);
			EXPECT_EQ(copy_pattern.foreground_color(), color2);
			EXPECT_EQ(copy_pattern.pixelmap(), pixmap);
		}
	}



	REGISTER_TYPED_TEST_CASE_P(
		test_monochrome_pattern,
		default_constructor,
		value_constructor,
		copy_constructor,
		move_constructor,
		copy_assignment,
		move_assignment);

	using testing_types = testing::Types<uint8_t, uint16_t, uint32_t, uint64_t>;

	INSTANTIATE_TYPED_TEST_CASE_P(test_monochrome_pattern, test_monochrome_pattern, testing_types);

}}}}}
