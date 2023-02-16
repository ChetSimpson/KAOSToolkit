// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/colors/tc1014/tc1014_color_converter.h>
#include <kaos/core/types/attribute_extension.h>


namespace hypertech::kaos::assetfoo::images::tc1014
{

	/// @brief List of attributes supported by the image reader.
	struct tc1014_image_attributes
	{

		template<class Type_>
		using attribute_definition = hypertech::kaos::core::types::attribute_extension::attribute_definition<Type_>;

		/// @copydoc colors::tc1014::tc1014_color_converter::color_space_type
		using color_space_type = colors::tc1014::tc1014_color_converter::color_space_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::native_color_map_type
		using native_color_map_type = colors::tc1014::tc1014_color_converter::native_color_map_type;

		/// @brief Attribute definition for native color space of image
		static const attribute_definition<color_space_type> native_color_space;
		/// @brief Attribute definition for native color map of image
		static const attribute_definition<native_color_map_type> native_color_map;
	};

}
