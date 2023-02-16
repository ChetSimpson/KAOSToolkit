// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/rat/rat_image_format_details.h>
#include <kaos/assetfoo/images/tc1014/tc1014_image_attributes.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::rat
{

	/// @brief List of attributes supported by the image reader.
	struct rat_image_attributes : tc1014::tc1014_image_attributes
	{
		/// @copydoc colors::tc1014::tc1014_color_converter::color_type
		using color_type = colors::tc1014::tc1014_color_converter::color_type;

		/// @brief Attribute definition for image title
		static const attribute_definition<color_type> background_color;
	};

}