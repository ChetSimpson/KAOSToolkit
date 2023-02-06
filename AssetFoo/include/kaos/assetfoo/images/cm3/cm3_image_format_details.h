// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::cm3
{

	/// @brief Details of the CM3 image file format.
	struct cm3_image_format_details
	{
		///	@brief Common size type
		using size_type = size_t;

		/// @brief The number of colors in the color map
		static const size_type color_count = 16;
		/// @brief The number of colors used for color cycling
		static const size_type cycle_color_count = 8;
		/// @brief The width of the image
		static const size_type page_width = 320;
		/// @brief The height of each image page. 
		static const size_type page_height = 192;
		/// @brief Pixel layout of the image
		static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
		/// @brief The mask for accessing the flag determining if the image is one or two pages in length
		static const uint8_t double_page_flag_mask = 0x80;
		/// @brief The mask for accessing the flag determining if the image contains editor patterns.
		static const uint8_t exclude_patterns_flag_mask = 0x01;
		/// @brief Size of the pattern section header
		static const size_type pattern_section_header_length = 3;
		/// @brief The maximum number of patterns allowed in the image
		static const size_type pattern_count = 24;
		/// @brief Mask to isolate only the bits in pattern color index that are valid.
		static const uint8_t pattern_color_index_mask = 0x0f;
		/// @brief Size of the buffer used to decompress a single row/line of the image.
		static const size_type decompression_line_buffer_size = 160;
		/// @brief Size of the horizontal bitstream used to decompress a single row/line of the image.
		static const size_type horizontal_bitstream_size_in_bytes = 20;
		/// @brief The color cycle index
		static const size_type color_cycle_index = 10;
		/// @brief The color first color index for color animation 
		static const size_type color_animation_start_index = 11;
		/// @brief The color last color index for color animation 
		static const size_type color_animation_end_index = 14;
	};

}