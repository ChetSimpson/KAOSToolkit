// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/image.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::rat
{

	/// @brief Specifies details of the image format
	struct rat_image_format_details
	{
		/// @brief The number of colors supported.
		static const size_t colormap_length = 16;
		/// @brief The width and height of the image
		static inline const auto dimensions = image::dimensions_type(320, 199);
		/// @brief Pixel layout of the image
		static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
	};

}