// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/image.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::mge
{

	/// @brief Specifies details of the image format
	struct mge_image_format_details
	{
		/// @brief List of image types supported by the MGE format
		enum class image_types
		{
			color_320x200_4bpp = 0	//!<	Specifies a 320x200 16 color (4bpp) image.
		};

		/// @copydoc image::size_type
		using size_type = image::size_type;
		/// @brief Number of colors expected in the colormap
		static const size_type colormap_size = 16;
		/// @brief Maximum length of the title attribute
		static const size_type title_length = 30;
		/// @brief The number of colors supported.
		static const size_t colormap_length = 16;
		/// @brief The width and height of the image
		static inline const auto dimensions = image::dimensions_type(320, 200);
		/// @brief Pixel layout of the image
		static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
	};

}
