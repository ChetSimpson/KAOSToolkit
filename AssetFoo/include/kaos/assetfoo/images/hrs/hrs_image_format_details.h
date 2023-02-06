// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/image.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::hrs
{

	/// @brief Details of the HRS image format
	struct hrs_image_format_details
	{
		/// @brief The default number of colors in the image.
		/// 
		/// The default number of colors used by the image. HRS files always store 16 colors
		/// in the image even if the image is not a 16 color image (monochrome or 4 colors).
		static const size_t colormap_length = 16;

		/// @brief The width and height of the image
		static inline const auto dimensions = image::dimensions_type(320, 192);

		/// @brief Pixel layout of the image
		static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
	};

}