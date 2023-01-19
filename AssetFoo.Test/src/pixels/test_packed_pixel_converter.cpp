// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/test/base_fixture.h>
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <array>


namespace hypertech::kaos::assetfoo::pixels::unittests
{

	class packed_pixel_converter_fixture : public assetfoo::unittests::base_fixture
	{
	protected:

		static inline const colors::color_map default_colormap_1bpp_{ {
			test_colors::black,
			test_colors::white,
		} };

		static inline const colors::color_map default_colormap_2bpp_{ {
			test_colors::black,
			test_colors::bright_red,
			test_colors::bright_blue,
			test_colors::white,
		} };

		static inline const colors::color_map default_colormap_4bpp_{ {
			test_colors::black,
			test_colors::dark_gray,
			test_colors::light_gray,
			test_colors::white,
			test_colors::dark_red,
			test_colors::medium_red,
			test_colors::bright_red,
			test_colors::dark_green,
			test_colors::medium_green,
			test_colors::bright_green,
			test_colors::dark_blue,
			test_colors::medium_blue,
			test_colors::bright_blue,
			test_colors::dark_yellow,
			test_colors::medium_yellow,
			test_colors::bright_yellow
		} };

		packed_pixel_converter default_converter_;
		using color_output_sequence_type = packed_pixel_converter::color_output_sequence_type;
		using packed_pixel_type = packed_pixel_converter::packed_pixel_type;
	};



#pragma region Convert single packed pixel byte to colors
	//
	//	Convert packed pixel byte to colors
	//
	TEST_F(packed_pixel_converter_fixture, unpack_bpp_not_power_of_two)
	{
		std::array<color_type, 3> buffer;

		EXPECT_THROWS_MESSAGE(
			default_converter_.unpack(3, default_colormap_2bpp_, packed_pixel_type(0b00011011), buffer),
			std::range_error,
			"Bits per pixel passed to unpack must be a power of two");
	}

	TEST_F(packed_pixel_converter_fixture, unpack_output_buffer_too_small)
	{
		std::array<color_type, 3> buffer;

		EXPECT_THROWS_MESSAGE(
			default_converter_.unpack(2, default_colormap_2bpp_, packed_pixel_type(0b00011011), buffer),
			std::length_error,
			"Output buffer is too small to contain all unpacked pixels");
	}

	TEST_F(packed_pixel_converter_fixture, unpack_8_pixels_from_uint8_at_1bpp)
	{
		std::array<color_type, 8> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(1, default_colormap_1bpp_, packed_pixel_type(0b01010101), buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_1bpp_[i % default_colormap_1bpp_.size()]);
		}

		outseq = default_converter_.unpack(1, default_colormap_1bpp_, packed_pixel_type(0b10101010), buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_1bpp_[(i + 1) % default_colormap_1bpp_.size()]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_4_pixels_from_uint8_at_2bpp)
	{
		std::array<color_type, 4> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(2, default_colormap_2bpp_, packed_pixel_type(0b00011011), buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_2bpp_[i % default_colormap_2bpp_.size()]);
		}

		outseq = default_converter_.unpack(2, default_colormap_2bpp_, packed_pixel_type(0b11100100), buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_2bpp_[buffer.size() - i - 1]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_2_pixels_from_uint8_at_4bpp)
	{
		std::array<color_type, 2> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x01), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[0]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[1]);

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x23), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[2]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[3]);

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x45), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[4]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[5]);

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x67), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[6]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[7]);

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x89), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[8]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[9]);

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xab), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[10]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[11]);

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xcd), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[12]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[13]);

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xef), buffer);
		EXPECT_TRUE(outseq.empty());
		EXPECT_EQ(buffer[0], default_colormap_4bpp_[14]);
		EXPECT_EQ(buffer[1], default_colormap_4bpp_[15]);
	}

	TEST_F(packed_pixel_converter_fixture, unpack_2_pixels_from_uint8_at_4bpp_chained)
	{
		std::array<color_type, 16> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x01), buffer);
		EXPECT_EQ(outseq.size(), 14);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x23), outseq);
		EXPECT_EQ(outseq.size(), 12);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x45), outseq);
		EXPECT_EQ(outseq.size(), 10);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x67), outseq);
		EXPECT_EQ(outseq.size(), 8);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0x89), outseq);
		EXPECT_EQ(outseq.size(), 6);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xab), outseq);
		EXPECT_EQ(outseq.size(), 4);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xcd), outseq);
		EXPECT_EQ(outseq.size(), 2);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xef), outseq);
		EXPECT_TRUE(outseq.empty());

		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_4bpp_[i % default_colormap_4bpp_.size()]);
		}
	}
#pragma endregion



#pragma region Convert single repeating packed pixel byte to colors
	//
	//	Convert repeating packed pixel byte to colors
	//
	TEST_F(packed_pixel_converter_fixture, unpack_repeating_packed_pixel_bpp_not_power_of_two)
	{
		std::array<color_type, 3> buffer;

		EXPECT_THROWS_MESSAGE(
			default_converter_.unpack(3, default_colormap_2bpp_, packed_pixel_type(0b00011011), 100, buffer),
			std::range_error,
			"Bits per pixel passed to unpack repeating packed pixels must be a power of two");
	}

	TEST_F(packed_pixel_converter_fixture, unpack_repeating_packed_pixel_unpack_output_buffer_too_small)
	{
		std::array<color_type, 8> buffer;

		EXPECT_THROWS_MESSAGE(
			default_converter_.unpack(2, default_colormap_2bpp_, packed_pixel_type(0b00011011), 100, buffer),
			std::length_error,
			"Output buffer is too small to contain all repeating unpacked pixels");
	}

	TEST_F(packed_pixel_converter_fixture, unpack_8_repeating_pixels_from_uint8_at_1bpp)
	{
		std::array<color_type, 32> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(1, default_colormap_1bpp_, packed_pixel_type(0b01010101), 4, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_1bpp_[i % default_colormap_1bpp_.size()]);
		}

		outseq = default_converter_.unpack(1, default_colormap_1bpp_, packed_pixel_type(0b10101010), 4, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_1bpp_[(i + 1) % default_colormap_1bpp_.size()]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_4_repeating_pixels_from_uint8_at_2bpp)
	{
		std::array<color_type, 16> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(2, default_colormap_2bpp_, packed_pixel_type(0b00011011), 4, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_2bpp_[i % default_colormap_2bpp_.size()]);
		}

		outseq = default_converter_.unpack(2, default_colormap_2bpp_, packed_pixel_type(0b11100100), 4, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_2bpp_[(buffer.size() - i - 1) % default_colormap_2bpp_.size()]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_2_repeating_pixels_from_uint8_at_4bpp)
	{
		std::array<color_type, 8> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xa5), 4, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_4bpp_[(i % 2) ? 0x05 : 0x0a]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_2_repeating_pixels_from_uint8_at_4bpp_chained)
	{
		std::array<color_type, 32> buffer;
		color_output_sequence_type outseq;

		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xa5), 4, buffer);
		EXPECT_EQ(outseq.size(), 24);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xa5), 4, outseq);
		EXPECT_EQ(outseq.size(), 16);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xa5), 4, outseq);
		EXPECT_EQ(outseq.size(), 8);
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, packed_pixel_type(0xa5), 4, outseq);
		EXPECT_TRUE(outseq.empty());

		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_4bpp_[(i % 2) ? 0x05 : 0x0a]);
		}
	}
#pragma endregion



#pragma region Convert sequence of packed pixel bytes to colors
	//
	//	Convert outseq of packed pixel bytes to colors
	//
	TEST_F(packed_pixel_converter_fixture, unpack_bpp_not_power_of_two_on_input_sequence)
	{
		std::array<color_type, 3> buffer;
		std::array<packed_pixel_type, 3> input;

		EXPECT_THROWS_MESSAGE(
			default_converter_.unpack(3, default_colormap_2bpp_, input, buffer),
			std::range_error,
			"Bits per pixel passed to unpack with input buffer must be a power of two");
	}

	TEST_F(packed_pixel_converter_fixture, unpack_output_buffer_too_small_on_input_sequence)
	{
		std::array<color_type, 3> buffer;
		std::array<packed_pixel_type, 3> input{ 0b01010101, 0b01010101, 0b01010101 };

		EXPECT_THROWS_MESSAGE(
			default_converter_.unpack(2, default_colormap_2bpp_, input, buffer),
			std::length_error,
			"Output buffer is too small to contain all unpacked pixels from input buffer");
	}

	TEST_F(packed_pixel_converter_fixture, unpack_24_pixels_from_uint8_sequence_at_1bpp)
	{
		std::array<color_type, 24> buffer;
		std::array<packed_pixel_type, 3> input;
		color_output_sequence_type outseq;

		//	Part 1
		input = { 0b01010101, 0b01010101, 0b01010101 };
		outseq = default_converter_.unpack(1, default_colormap_1bpp_, input, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_1bpp_[i % default_colormap_1bpp_.size()]);
		}

		//	Part 2
		input = { 0b10101010, 0b10101010, 0b10101010 };
		outseq = default_converter_.unpack(1, default_colormap_1bpp_, input, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_1bpp_[(i + 1) % default_colormap_1bpp_.size()]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_12_pixels_from_uint8_sequence_at_2bpp)
	{
		std::array<color_type, 12> buffer;
		std::array<packed_pixel_type, 3> input;
		color_output_sequence_type outseq;

		// Part 1
		input = { 0b00011011, 0b00011011, 0b00011011 };
		outseq = default_converter_.unpack(2, default_colormap_2bpp_, input, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_2bpp_[i % default_colormap_2bpp_.size()]);
		}

		//	Part 2
		input = { 0b11100100, 0b11100100, 0b11100100 };
		outseq = default_converter_.unpack(2, default_colormap_2bpp_, input, buffer);
		EXPECT_TRUE(outseq.empty());
		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_2bpp_[(buffer.size() - i - 1) % default_colormap_2bpp_.size()]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_16_pixels_from_uint8_sequence_at_4bpp)
	{
		std::array<color_type, 16> buffer;
		std::array<packed_pixel_type, 8> input;
		color_output_sequence_type outseq;

		input = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, input, buffer);
		EXPECT_TRUE(outseq.empty());

		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_4bpp_[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, unpack_16_pixels_from_uint8_at_4bpp_chained)
	{
		std::array<color_type, 16> buffer;
		std::array<packed_pixel_type, 3> input_3elements;
		std::array<packed_pixel_type, 2> input_2elements;
		color_output_sequence_type outseq;

		input_3elements = { 0x01, 0x23, 0x45 };
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, input_3elements, buffer);
		EXPECT_EQ(outseq.size(), 10);

		input_2elements = { 0x67, 0x89 };
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, input_2elements, outseq);
		EXPECT_EQ(outseq.size(), 6);

		input_3elements = { 0xab, 0xcd, 0xef };
		outseq = default_converter_.unpack(4, default_colormap_4bpp_, input_3elements, outseq);
		EXPECT_TRUE(outseq.empty());

		for (auto i(0U); i < buffer.size(); ++i)
		{
			ASSERT_EQ(buffer[i], default_colormap_4bpp_[i]);
		}
	}
#pragma endregion



#pragma region Convert multiple colors to packed pixels
	TEST_F(packed_pixel_converter_fixture, pack_bpp_not_power_of_two)
	{
		std::array<color_type, 3> buffer;
		packed_pixel_converter::packed_pixel_type packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(3, default_colormap_2bpp_, buffer, packed_pixels),
			std::range_error,
			"Bits per pixel passed to pack must be a power of two");
	}

	TEST_F(packed_pixel_converter_fixture, pack_color_not_found)
	{
		std::array<color_type, 8> buffer
		{
			default_colormap_2bpp_[2]
		};

		packed_pixel_converter::packed_pixel_type packed_pixels;
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels),
			std::runtime_error,
			"pixel index for color (0, 0, 255, 255) not found in target colormap");
	}

	TEST_F(packed_pixel_converter_fixture, pack_output_buffer_too_small_1bpp)
	{
		std::array<color_type, 7> buffer;
		packed_pixel_converter::packed_pixel_type packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels),
			std::length_error,
			"Input buffer is too small to fill a packed pixel type");
	}

	TEST_F(packed_pixel_converter_fixture, pack_output_buffer_too_small_2bpp)
	{
		std::array<color_type, 3> buffer;
		packed_pixel_converter::packed_pixel_type packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels),
			std::length_error,
			"Input buffer is too small to fill a packed pixel type");
	}

	TEST_F(packed_pixel_converter_fixture, pack_output_buffer_too_small_4bpp)
	{
		std::array<color_type, 1> buffer;
		packed_pixel_converter::packed_pixel_type packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(4, default_colormap_4bpp_, buffer, packed_pixels),
			std::length_error,
			"Input buffer is too small to fill a packed pixel type");
	}

	TEST_F(packed_pixel_converter_fixture, pack_color_index_exceeds_max_pixel_value_1bpp)
	{
		std::array<color_type, 8> buffer
		{
			default_colormap_2bpp_[2]
		};

		packed_pixel_converter::packed_pixel_type packed_pixels;
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(1, default_colormap_2bpp_, buffer, packed_pixels),
			std::runtime_error,
			"Pixel index 2 for color (0, 0, 255, 255) is out of range");
	}

	TEST_F(packed_pixel_converter_fixture, pack_color_index_exceeds_max_pixel_value_2bpp)
	{
		std::array<color_type, 4> buffer
		{
			default_colormap_4bpp_[4]
		};

		packed_pixel_converter::packed_pixel_type packed_pixels;
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(2, default_colormap_4bpp_, buffer, packed_pixels),
			std::runtime_error,
			"Pixel index 4 for color (85, 0, 0, 255) is out of range");
	}

	TEST_F(packed_pixel_converter_fixture, pack_color_index_exceeds_max_pixel_value_4bpp)
	{
		auto colormap(default_colormap_4bpp_);
		colormap.add(color_type(100, 100, 100));

		std::array<color_type, 2> buffer
		{
			colormap[16]
		};

		packed_pixel_converter::packed_pixel_type packed_pixels;
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(4, colormap, buffer, packed_pixels),
			std::runtime_error,
			"Pixel index 16 for color (100, 100, 100, 255) is out of range");
	}

	TEST_F(packed_pixel_converter_fixture, pack_8_colors_to_packed_pixel_1bpp)
	{
		std::array<color_type, 8> buffer
		{
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1]
		};
		packed_pixel_converter::packed_pixel_type packed_pixels;

		auto result(default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels));
		EXPECT_TRUE(result.empty());
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b01010101));

		buffer = 
		{
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
		};

		result = default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels);
		EXPECT_TRUE(result.empty());
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b10101010));
	}

	TEST_F(packed_pixel_converter_fixture, pack_8_colors_to_packed_pixel_1bpp_input_pending)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1]
		};
		packed_pixel_converter::packed_pixel_type packed_pixels;

		auto result(default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels));
		EXPECT_EQ(result.size(), 8);
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b01010101));

		buffer = 
		{
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
		};

		result = default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels);
		EXPECT_EQ(result.size(), 8);
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b10101010));
	}

	TEST_F(packed_pixel_converter_fixture, pack_4_colors_to_packed_pixel_2bpp)
	{
		std::array<color_type, 4> buffer
		{
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3]
		};
		packed_pixel_converter::packed_pixel_type packed_pixels;

		auto result(default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels));
		EXPECT_TRUE(result.empty());
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b00011011));

		buffer = 
		{
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
		};

		result = default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels);
		EXPECT_TRUE(result.empty());
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b11100100));
	}

	TEST_F(packed_pixel_converter_fixture, pack_4_colors_to_packed_pixel_2bpp_input_pending)
	{
		std::array<color_type, 8> buffer
		{
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3]
		};
		packed_pixel_converter::packed_pixel_type packed_pixels;

		auto result(default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels));
		EXPECT_EQ(result.size(), 4);
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b00011011));

		buffer = 
		{
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
		};

		result = default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels);
		EXPECT_EQ(result.size(), 4);
		EXPECT_EQ(packed_pixels, packed_pixel_type(0b11100100));
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_colors_to_packed_pixel_4bpp)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_4bpp_[0],
			default_colormap_4bpp_[1],
			default_colormap_4bpp_[2],
			default_colormap_4bpp_[3],
			default_colormap_4bpp_[4],
			default_colormap_4bpp_[5],
			default_colormap_4bpp_[6],
			default_colormap_4bpp_[7],
			default_colormap_4bpp_[8],
			default_colormap_4bpp_[9],
			default_colormap_4bpp_[10],
			default_colormap_4bpp_[11],
			default_colormap_4bpp_[12],
			default_colormap_4bpp_[13],
			default_colormap_4bpp_[14],
			default_colormap_4bpp_[15]
		};
		std::array<packed_pixel_type, 8> expected_packed_pixels
		{
			0b00000001,
			0b00100011,
			0b01000101,
			0b01100111,
			0b10001001,
			0b10101011,
			0b11001101,
			0b11101111,
		};

		packed_pixel_converter::color_input_sequence_type sequence(buffer);
		for (const auto& expected_pixel : expected_packed_pixels)
		{
			packed_pixel_converter::packed_pixel_type packed_pixels;
			sequence = default_converter_.pack(4, default_colormap_4bpp_, sequence, packed_pixels);
			ASSERT_EQ(packed_pixels, expected_pixel);
		}
		EXPECT_TRUE(sequence.empty());
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_colors_to_packed_pixel_4bpp_input_pending)
	{
		std::array<color_type, 32> buffer
		{
			default_colormap_4bpp_[0],
			default_colormap_4bpp_[1],
			default_colormap_4bpp_[2],
			default_colormap_4bpp_[3],
			default_colormap_4bpp_[4],
			default_colormap_4bpp_[5],
			default_colormap_4bpp_[6],
			default_colormap_4bpp_[7],
			default_colormap_4bpp_[8],
			default_colormap_4bpp_[9],
			default_colormap_4bpp_[10],
			default_colormap_4bpp_[11],
			default_colormap_4bpp_[12],
			default_colormap_4bpp_[13],
			default_colormap_4bpp_[14],
			default_colormap_4bpp_[15]
		};
		std::array<packed_pixel_type, 8> expected_packed_pixels
		{
			0b00000001,
			0b00100011,
			0b01000101,
			0b01100111,
			0b10001001,
			0b10101011,
			0b11001101,
			0b11101111,
		};

		packed_pixel_converter::color_input_sequence_type sequence(buffer);
		for (const auto& expected_pixel : expected_packed_pixels)
		{
			packed_pixel_converter::packed_pixel_type packed_pixels;
			sequence = default_converter_.pack(4, default_colormap_4bpp_, sequence, packed_pixels);
			ASSERT_EQ(packed_pixels, expected_pixel);
		}
		EXPECT_EQ(sequence.size(), 16);
	}
#pragma endregion



#pragma region Convert multiple colors to multiple packed pixels
	TEST_F(packed_pixel_converter_fixture, pack_bpp_not_power_of_two_on_sequences)
	{
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(3, default_colormap_2bpp_, {}, {}),
			std::range_error,
			"Bits per pixel passed to pack must be a power of two");
	}

	TEST_F(packed_pixel_converter_fixture, pack_output_buffer_empty)
	{
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(1, default_colormap_1bpp_, {}, {}),
			std::length_error,
			"packed pixel output buffer cannot be empty");
	}

	TEST_F(packed_pixel_converter_fixture, pack_input_sequence_cannot_fill_last_pixel_1bpp)
	{
		std::array<color_type, 15> input_colors;
		std::array<packed_pixel_converter::packed_pixel_type, 2> packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(1, default_colormap_1bpp_, input_colors, packed_pixels),
			std::length_error,
			"input buffer is too small to fill the last full packed pixel");
	}

	TEST_F(packed_pixel_converter_fixture, pack_input_sequence_cannot_fill_last_pixel_2bpp)
	{
		std::array<color_type, 7> input_colors;
		std::array<packed_pixel_converter::packed_pixel_type, 2> packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(2, default_colormap_2bpp_, input_colors, packed_pixels),
			std::length_error,
			"input buffer is too small to fill the last full packed pixel");
	}

	TEST_F(packed_pixel_converter_fixture, pack_input_sequence_cannot_fill_last_pixel_4bpp)
	{
		std::array<color_type, 3> input_colors;
		std::array<packed_pixel_converter::packed_pixel_type, 2> packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(4, default_colormap_4bpp_, input_colors, packed_pixels),
			std::length_error,
			"input buffer is too small to fill the last full packed pixel");
	}

	TEST_F(packed_pixel_converter_fixture, pack_sequence_color_not_found)
	{
		std::array<color_type, 8> buffer
		{
			default_colormap_2bpp_[2]
		};

		std::array<packed_pixel_type, 1> packed_pixels;
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels),
			std::runtime_error,
			"pixel index for color (0, 0, 255, 255) not found in target colormap");
	}

	TEST_F(packed_pixel_converter_fixture, pack_color_seqence_index_exceeds_max_pixel_value_1bpp)
	{
		std::array<color_type, 8> buffer
		{
			default_colormap_2bpp_[2]
		};

		std::array<packed_pixel_type, 1> packed_pixels;

		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(1, default_colormap_2bpp_, buffer, packed_pixels),
			std::runtime_error,
			"Pixel index 2 for color (0, 0, 255, 255) is out of range");
	}

	TEST_F(packed_pixel_converter_fixture, pack_color_seqence_index_exceeds_max_pixel_value_2bpp)
	{
		std::array<color_type, 4> buffer
		{
			default_colormap_4bpp_[4]
		};

		std::array<packed_pixel_type, 1> packed_pixels;
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(2, default_colormap_4bpp_, buffer, packed_pixels),
			std::runtime_error,
			"Pixel index 4 for color (85, 0, 0, 255) is out of range");
	}

	TEST_F(packed_pixel_converter_fixture, pack_color_seqence_index_exceeds_max_pixel_value_4bpp)
	{
		auto colormap(default_colormap_4bpp_);
		colormap.add(color_type(100, 100, 100));

		std::array<color_type, 2> buffer
		{
			colormap[16]
		};

		std::array<packed_pixel_type, 1> packed_pixels;
		EXPECT_THROWS_MESSAGE(
			default_converter_.pack(4, colormap, buffer, packed_pixels),
			std::runtime_error,
			"Pixel index 16 for color (100, 100, 100, 255) is out of range");
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_1bpp)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[1],

			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0]
		};
		std::array<packed_pixel_type, 2> expected_packed_pixels
		{
			0b00110011,
			0b10101010
		};

		std::array<packed_pixel_type, 2> packed_pixels;

		auto sequence = default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels);
		EXPECT_TRUE(sequence.first.empty());
		EXPECT_TRUE(sequence.second.empty());

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_1bpp_output_pending)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[1],

			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0]
		};
		std::array<packed_pixel_type, 2> expected_packed_pixels
		{
			0b00110011,
			0b10101010
		};

		std::array<packed_pixel_type, 4> packed_pixels;

		auto sequence = default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels);
		EXPECT_TRUE(sequence.first.empty());
		EXPECT_EQ(sequence.second.size(), 2);

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_1bpp_input_pending)
	{
		std::array<color_type, 32> buffer
		{
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[1],

			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0],
			default_colormap_1bpp_[1],
			default_colormap_1bpp_[0]
		};
		std::array<packed_pixel_type, 2> expected_packed_pixels
		{
			0b00110011,
			0b10101010
		};

		std::array<packed_pixel_type, 2> packed_pixels;

		auto sequence = default_converter_.pack(1, default_colormap_1bpp_, buffer, packed_pixels);
		EXPECT_EQ(sequence.first.size(), 16);
		EXPECT_TRUE(sequence.second.empty());

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_2bpp)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3],

			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],

			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],

			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
		};

		std::array<packed_pixel_type, 4> expected_packed_pixels
		{
			0b00011011,
			0b10110001,
			0b01001110,
			0b11100100
		};

		std::array<packed_pixel_type, 4> packed_pixels;

		auto result(default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels));
		EXPECT_TRUE(result.first.empty());
		EXPECT_TRUE(result.second.empty());

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_2bpp_output_pending)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3],

			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],

			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],

			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
		};

		std::array<packed_pixel_type, 4> expected_packed_pixels
		{
			0b00011011,
			0b10110001,
			0b01001110,
			0b11100100
		};

		std::array<packed_pixel_type, 8> packed_pixels;

		auto result(default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels));
		EXPECT_TRUE(result.first.empty());
		EXPECT_EQ(result.second.size(), 4);

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_2bpp_input_pending)
	{
		std::array<color_type, 32> buffer
		{
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3],

			default_colormap_2bpp_[2],
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[1],

			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],

			default_colormap_2bpp_[3],
			default_colormap_2bpp_[2],
			default_colormap_2bpp_[1],
			default_colormap_2bpp_[0],
		};

		std::array<packed_pixel_type, 4> expected_packed_pixels
		{
			0b00011011,
			0b10110001,
			0b01001110,
			0b11100100
		};

		std::array<packed_pixel_type, 4> packed_pixels;

		auto result(default_converter_.pack(2, default_colormap_2bpp_, buffer, packed_pixels));
		EXPECT_EQ(result.first.size(), 16);
		EXPECT_TRUE(result.second.empty());

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_4bpp)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_4bpp_[0],
			default_colormap_4bpp_[1],
			default_colormap_4bpp_[2],
			default_colormap_4bpp_[3],
			default_colormap_4bpp_[4],
			default_colormap_4bpp_[5],
			default_colormap_4bpp_[6],
			default_colormap_4bpp_[7],
			default_colormap_4bpp_[8],
			default_colormap_4bpp_[9],
			default_colormap_4bpp_[10],
			default_colormap_4bpp_[11],
			default_colormap_4bpp_[12],
			default_colormap_4bpp_[13],
			default_colormap_4bpp_[14],
			default_colormap_4bpp_[15]
		};
		std::array<packed_pixel_type, 8> expected_packed_pixels
		{
			0b00000001,
			0b00100011,
			0b01000101,
			0b01100111,
			0b10001001,
			0b10101011,
			0b11001101,
			0b11101111,
		};

		std::array<packed_pixel_type, 8> packed_pixels;

		auto result(default_converter_.pack(4, default_colormap_4bpp_, buffer, packed_pixels));
		EXPECT_TRUE(result.first.empty());
		EXPECT_TRUE(result.second.empty());

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_4bpp_output_pending)
	{
		std::array<color_type, 16> buffer
		{
			default_colormap_4bpp_[0],
			default_colormap_4bpp_[1],
			default_colormap_4bpp_[2],
			default_colormap_4bpp_[3],
			default_colormap_4bpp_[4],
			default_colormap_4bpp_[5],
			default_colormap_4bpp_[6],
			default_colormap_4bpp_[7],
			default_colormap_4bpp_[8],
			default_colormap_4bpp_[9],
			default_colormap_4bpp_[10],
			default_colormap_4bpp_[11],
			default_colormap_4bpp_[12],
			default_colormap_4bpp_[13],
			default_colormap_4bpp_[14],
			default_colormap_4bpp_[15]
		};
		std::array<packed_pixel_type, 8> expected_packed_pixels
		{
			0b00000001,
			0b00100011,
			0b01000101,
			0b01100111,
			0b10001001,
			0b10101011,
			0b11001101,
			0b11101111,
		};

		std::array<packed_pixel_type, 16> packed_pixels;

		auto result(default_converter_.pack(4, default_colormap_4bpp_, buffer, packed_pixels));
		EXPECT_TRUE(result.first.empty());
		EXPECT_EQ(result.second.size(), 8);

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}

	TEST_F(packed_pixel_converter_fixture, pack_16_color_sequence_to_packed_pixel_4bpp_input_pending)
	{
		std::array<color_type, 32> buffer
		{
			default_colormap_4bpp_[0],
			default_colormap_4bpp_[1],
			default_colormap_4bpp_[2],
			default_colormap_4bpp_[3],
			default_colormap_4bpp_[4],
			default_colormap_4bpp_[5],
			default_colormap_4bpp_[6],
			default_colormap_4bpp_[7],
			default_colormap_4bpp_[8],
			default_colormap_4bpp_[9],
			default_colormap_4bpp_[10],
			default_colormap_4bpp_[11],
			default_colormap_4bpp_[12],
			default_colormap_4bpp_[13],
			default_colormap_4bpp_[14],
			default_colormap_4bpp_[15]
		};
		std::array<packed_pixel_type, 8> expected_packed_pixels
		{
			0b00000001,
			0b00100011,
			0b01000101,
			0b01100111,
			0b10001001,
			0b10101011,
			0b11001101,
			0b11101111,
		};

		std::array<packed_pixel_type, 8> packed_pixels;

		auto result(default_converter_.pack(4, default_colormap_4bpp_, buffer, packed_pixels));
		EXPECT_EQ(result.first.size(), 16);
		EXPECT_TRUE(result.second.empty());

		for (auto i(0U); i < expected_packed_pixels.size(); ++i)
		{
			ASSERT_EQ(packed_pixels[i], expected_packed_pixels[i]);
		}
	}
#pragma endregion

}
