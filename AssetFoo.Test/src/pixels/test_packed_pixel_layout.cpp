// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <algorithm>


namespace hypertech::kaos::assetfoo::pixels::unittests
{

	class packed_pixel_layout_fixture : public ::testing::Test
	{
	protected:

		using bitfieldlist_type = packed_pixel_layout::bitfieldlist_type;

		static const bitfieldlist_type bitfields_1bpp_;
		static const bitfieldlist_type bitfields_2bpp_;
		static const bitfieldlist_type bitfields_4bpp_;
		static const bitfieldlist_type bitfields_8bpp_;

		static const packed_pixel_layout test_format_;
		static const size_t default_pitch_alignment_ = 1;
	};


	const packed_pixel_layout_fixture::bitfieldlist_type packed_pixel_layout_fixture::bitfields_1bpp_(
		packed_pixel_layout_fixture::bitfieldlist_type({ {1, 7}, {1, 6}, {1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0} }));

	const packed_pixel_layout_fixture::bitfieldlist_type packed_pixel_layout_fixture::bitfields_2bpp_(
		packed_pixel_layout_fixture::bitfieldlist_type({ {2, 6}, {2, 4}, {2, 2}, {2, 0} }));

	const packed_pixel_layout_fixture::bitfieldlist_type packed_pixel_layout_fixture::bitfields_4bpp_(
		packed_pixel_layout_fixture::bitfieldlist_type({ {4, 4}, {4, 0} }));

	const packed_pixel_layout_fixture::bitfieldlist_type packed_pixel_layout_fixture::bitfields_8bpp_ = 
		packed_pixel_layout_fixture::bitfieldlist_type({ {8, 0} });

	const packed_pixel_layout packed_pixel_layout_fixture::test_format_(bitfields_8bpp_);


	TEST_F(packed_pixel_layout_fixture, ctor_empty_bitfield_list)
	{
		EXPECT_THROWS_MESSAGE(
			packed_pixel_layout(bitfieldlist_type{}),
			std::invalid_argument,
			"Pixel bitfields list cannot contain 0 elements");
	}

	TEST_F(packed_pixel_layout_fixture, ctor_non_uniform_pixels)
	{
		EXPECT_THROWS_MESSAGE(
			packed_pixel_layout({ {1,7}, {2, 5} }),
			std::invalid_argument,
			"Packed pixel bitfield definitions must be uniform");
	}

	TEST_F(packed_pixel_layout_fixture, ctor_zero_bits_per_pixel)
	{
		EXPECT_THROWS_MESSAGE(
			packed_pixel_layout(0),
			std::range_error,
			"Bits per pixel passed to packed_pixel_layout cannot be 0");
	}

	TEST_F(packed_pixel_layout_fixture, ctor_bits_per_pixel_larger_than_underlying_value_type)
	{
		EXPECT_THROWS_MESSAGE(
			packed_pixel_layout(64),
			std::overflow_error,
			"Bits per pixel passed to packed_pixel_layout must be less than or equal to 8");
	}

	TEST_F(packed_pixel_layout_fixture, ctor_non_power_of_two_bits_per_pixel)
	{
		EXPECT_THROWS_MESSAGE(
			packed_pixel_layout(3),
			std::range_error,
			"Bits per pixel passed to packed_pixel_layout must be a power of two");
	}


	TEST_F(packed_pixel_layout_fixture, copy_constructor)
	{
		packed_pixel_layout layout(bitfields_1bpp_);

		auto layout_copy(layout);

		EXPECT_EQ(layout_copy.pixel_bitfields(), layout.pixel_bitfields());
		EXPECT_EQ(layout_copy.max_colors_in_pixel(), layout.max_colors_in_pixel());
		EXPECT_EQ(layout_copy.pixels_per_packed_value(), layout.pixels_per_packed_value());
		EXPECT_EQ(layout_copy.bits_per_pixel(), layout.bits_per_pixel());
	}








	TEST_F(packed_pixel_layout_fixture, calculate_pitch_fail_on_zero_pixel_width)
	{
		EXPECT_THROWS_MESSAGE(
			test_format_.calculate_pitch(0, default_pitch_alignment_),
			std::invalid_argument,
			"Width in pixels cannot be 0");
	}


	TEST_F(packed_pixel_layout_fixture, calculate_pitch_fail_on_zero_alignment)
	{
		EXPECT_THROWS_MESSAGE(
			test_format_.calculate_pitch(8, 0),
			std::invalid_argument,
			"Alignment cannot be 0");
	}


	TEST_F(packed_pixel_layout_fixture, calculate_pitch_valid_alignment)
	{
		EXPECT_EQ(test_format_.calculate_pitch(1, 1), 1);
		EXPECT_EQ(test_format_.calculate_pitch(2, 1), 2);
		EXPECT_EQ(test_format_.calculate_pitch(3, 1), 3);
		EXPECT_EQ(test_format_.calculate_pitch(4, 1), 4);

		EXPECT_EQ(test_format_.calculate_pitch(1, 2), 2);
		EXPECT_EQ(test_format_.calculate_pitch(2, 2), 2);
		EXPECT_EQ(test_format_.calculate_pitch(3, 2), 4);

		EXPECT_EQ(test_format_.calculate_pitch(3, 4), 4);
		EXPECT_EQ(test_format_.calculate_pitch(4, 4), 4);
		EXPECT_EQ(test_format_.calculate_pitch(5, 4), 8);

		EXPECT_EQ(test_format_.calculate_pitch(7, 8), 8);
		EXPECT_EQ(test_format_.calculate_pitch(8, 8), 8);
		EXPECT_EQ(test_format_.calculate_pitch(9, 8), 16);

		EXPECT_EQ(test_format_.calculate_pitch(15, 16), 16);
		EXPECT_EQ(test_format_.calculate_pitch(16, 16), 16);
		EXPECT_EQ(test_format_.calculate_pitch(17, 16), 32);

		EXPECT_EQ(test_format_.calculate_pitch(31, 32), 32);
		EXPECT_EQ(test_format_.calculate_pitch(32, 32), 32);
		EXPECT_EQ(test_format_.calculate_pitch(33, 32), 64);

		EXPECT_EQ(test_format_.calculate_pitch(63, 64), 64);
		EXPECT_EQ(test_format_.calculate_pitch(64, 64), 64);
		EXPECT_EQ(test_format_.calculate_pitch(65, 64), 128);

		EXPECT_EQ(test_format_.calculate_pitch(127, 128), 128);
		EXPECT_EQ(test_format_.calculate_pitch(128, 128), 128);
		EXPECT_EQ(test_format_.calculate_pitch(129, 128), 256);

		EXPECT_EQ(test_format_.calculate_pitch(255, 256), 256);
		EXPECT_EQ(test_format_.calculate_pitch(256, 256), 256);
		EXPECT_EQ(test_format_.calculate_pitch(267, 256), 512);

	}


	TEST_F(packed_pixel_layout_fixture, calculate_pitch_fail_on_alignment_not_power_of_two)
	{
		EXPECT_THROWS_MESSAGE(
			test_format_.calculate_pitch(8, 3),
			std::invalid_argument,
			"Alignment must be a power of two");

		EXPECT_THROWS_MESSAGE(
			test_format_.calculate_pitch(8, 7),
			std::invalid_argument,
			"Alignment must be a power of two");

		EXPECT_THROWS_MESSAGE(
			test_format_.calculate_pitch(8, 15),
			std::invalid_argument,
			"Alignment must be a power of two");

		EXPECT_THROWS_MESSAGE(
			test_format_.calculate_pitch(8, 31),
			std::invalid_argument,
			"Alignment must be a power of two");

		EXPECT_THROWS_MESSAGE(
			test_format_.calculate_pitch(8, 63),
			std::invalid_argument,
			"Alignment must be a power of two");
	}




	TEST_F(packed_pixel_layout_fixture, attributes_1bpp)
	{
		auto tester = [](const auto& format, const auto& bitfields)
		{
			EXPECT_EQ(format.max_colors_in_pixel(), 2);
			EXPECT_EQ(format.pixels_per_packed_value(), 8);
			EXPECT_EQ(format.bits_per_pixel(), 1);
			EXPECT_TRUE(std::equal(format.pixel_bitfields().begin(), format.pixel_bitfields().end(), bitfields.begin(), bitfields.end()));
		};

		tester(packed_pixel_layout(1), bitfields_1bpp_);
		tester(packed_pixel_layout::BPP1, bitfields_1bpp_);
	}


	TEST_F(packed_pixel_layout_fixture, calculate_pitch_1bpp)
	{
		const auto& format = packed_pixel_layout::BPP1;

		EXPECT_EQ(format.calculate_pitch(1, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(2, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(3, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(4, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(5, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(6, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(7, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(8, default_pitch_alignment_), 1);

		EXPECT_EQ(format.calculate_pitch(9, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(10, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(11, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(12, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(13, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(14, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(15, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(16, default_pitch_alignment_), 2);

		EXPECT_EQ(format.calculate_pitch(17, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(18, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(19, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(20, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(21, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(22, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(23, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(24, default_pitch_alignment_), 3);
	}




	TEST_F(packed_pixel_layout_fixture, attributes_2bpp)
	{
		auto tester = [](const auto& format, const auto& bitfields)
		{
			EXPECT_EQ(format.max_colors_in_pixel(), 4);
			EXPECT_EQ(format.pixels_per_packed_value(), 4);
			EXPECT_EQ(format.bits_per_pixel(), 2);
			EXPECT_TRUE(std::equal(format.pixel_bitfields().begin(), format.pixel_bitfields().end(), bitfields.begin(), bitfields.end()));
		};

		tester(packed_pixel_layout(2), bitfields_2bpp_);
		tester(packed_pixel_layout::BPP2, bitfields_2bpp_);
	}


	TEST_F(packed_pixel_layout_fixture, calculate_pitch_2bpp)
	{
		const auto& format = packed_pixel_layout::BPP2;

		EXPECT_EQ(format.calculate_pitch(1, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(2, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(3, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(4, default_pitch_alignment_), 1);

		EXPECT_EQ(format.calculate_pitch(5, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(6, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(7, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(8, default_pitch_alignment_), 2);

		EXPECT_EQ(format.calculate_pitch(9, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(10, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(11, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(12, default_pitch_alignment_), 3);

		EXPECT_EQ(format.calculate_pitch(13, default_pitch_alignment_), 4);
		EXPECT_EQ(format.calculate_pitch(14, default_pitch_alignment_), 4);
		EXPECT_EQ(format.calculate_pitch(15, default_pitch_alignment_), 4);
		EXPECT_EQ(format.calculate_pitch(16, default_pitch_alignment_), 4);
	}




	TEST_F(packed_pixel_layout_fixture, attributes_4bpp)
	{
		auto tester = [](const auto& format, const auto& bitfields)
		{
			EXPECT_EQ(format.max_colors_in_pixel(), 16);
			EXPECT_EQ(format.pixels_per_packed_value(), 2);
			EXPECT_EQ(format.bits_per_pixel(), 4);
			EXPECT_TRUE(std::equal(format.pixel_bitfields().begin(), format.pixel_bitfields().end(), bitfields.begin(), bitfields.end()));
		};

		tester(packed_pixel_layout(4), bitfields_4bpp_);
		tester(packed_pixel_layout::BPP4, bitfields_4bpp_);
	}


	TEST_F(packed_pixel_layout_fixture, calculate_pitch_4bpp)
	{
		const auto& format = packed_pixel_layout::BPP4;

		EXPECT_EQ(format.calculate_pitch(1, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(2, default_pitch_alignment_), 1);

		EXPECT_EQ(format.calculate_pitch(3, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(4, default_pitch_alignment_), 2);

		EXPECT_EQ(format.calculate_pitch(5, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(6, default_pitch_alignment_), 3);

		EXPECT_EQ(format.calculate_pitch(7, default_pitch_alignment_), 4);
		EXPECT_EQ(format.calculate_pitch(8, default_pitch_alignment_), 4);

		EXPECT_EQ(format.calculate_pitch(9, default_pitch_alignment_), 5);
		EXPECT_EQ(format.calculate_pitch(10, default_pitch_alignment_), 5);

		EXPECT_EQ(format.calculate_pitch(11, default_pitch_alignment_), 6);
		EXPECT_EQ(format.calculate_pitch(12, default_pitch_alignment_), 6);

		EXPECT_EQ(format.calculate_pitch(13, default_pitch_alignment_), 7);
		EXPECT_EQ(format.calculate_pitch(14, default_pitch_alignment_), 7);

		EXPECT_EQ(format.calculate_pitch(15, default_pitch_alignment_), 8);
		EXPECT_EQ(format.calculate_pitch(16, default_pitch_alignment_), 8);
	}




	TEST_F(packed_pixel_layout_fixture, attributes_8bpp)
	{
		auto tester = [](const auto& format, const auto& bitfields)
		{
			EXPECT_EQ(format.max_colors_in_pixel(), 256);
			EXPECT_EQ(format.pixels_per_packed_value(), 1);
			EXPECT_EQ(format.bits_per_pixel(), 8);
			EXPECT_TRUE(std::equal(format.pixel_bitfields().begin(), format.pixel_bitfields().end(), bitfields.begin(), bitfields.end()));
		};

		tester(packed_pixel_layout(8), bitfields_8bpp_);
		tester(packed_pixel_layout::BPP8, bitfields_8bpp_);

	}


	TEST_F(packed_pixel_layout_fixture, calculate_pitch_8bpp)
	{
		const auto& format = packed_pixel_layout::BPP8;

		EXPECT_EQ(format.calculate_pitch(1, default_pitch_alignment_), 1);
		EXPECT_EQ(format.calculate_pitch(2, default_pitch_alignment_), 2);
		EXPECT_EQ(format.calculate_pitch(3, default_pitch_alignment_), 3);
		EXPECT_EQ(format.calculate_pitch(4, default_pitch_alignment_), 4);
		EXPECT_EQ(format.calculate_pitch(5, default_pitch_alignment_), 5);
		EXPECT_EQ(format.calculate_pitch(6, default_pitch_alignment_), 6);
		EXPECT_EQ(format.calculate_pitch(7, default_pitch_alignment_), 7);
		EXPECT_EQ(format.calculate_pitch(8, default_pitch_alignment_), 8);
		EXPECT_EQ(format.calculate_pitch(9, default_pitch_alignment_), 9);
		EXPECT_EQ(format.calculate_pitch(10, default_pitch_alignment_), 10);
		EXPECT_EQ(format.calculate_pitch(11, default_pitch_alignment_), 11);
		EXPECT_EQ(format.calculate_pitch(12, default_pitch_alignment_), 12);
		EXPECT_EQ(format.calculate_pitch(13, default_pitch_alignment_), 13);
		EXPECT_EQ(format.calculate_pitch(14, default_pitch_alignment_), 14);
		EXPECT_EQ(format.calculate_pitch(15, default_pitch_alignment_), 15);
		EXPECT_EQ(format.calculate_pitch(16, default_pitch_alignment_), 16);
	}

}
