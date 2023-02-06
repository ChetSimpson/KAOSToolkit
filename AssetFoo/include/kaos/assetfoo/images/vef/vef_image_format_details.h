// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <cstdint>


namespace hypertech::kaos::assetfoo::images::vef
{

	/// @brief Specifies details of the image format
	struct vef_image_format_details
	{
		/// @brief Mask to retrieve the flag indicating if the image is compressed or uncompressed.
		static const uint8_t compression_flag_mask = 0x80;
		/// @brief The default number of colors in the image.
		/// 
		/// The default number of colors used by the image. VEF files always store 16 colors
		/// in the image even if the image is not a 16 color image (monochrome or 4 colors).
		static const size_t colormap_length = 16;
		/// @brief Mask used to retrieve indicating if a scanline packet is compressed or
		/// uncompressed.
		static const size_t packet_compressed_flag_mask = 0x80;
		/// @brief Mask used to retrieve the length of the scanline packet data.
		static const size_t packet_length_mask = 0x7f;
	};

}