// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_attributes.h>
#include <kaos/assetfoo/images/monochrome_pattern.h>


namespace hypertech::kaos::assetfoo::images::cm3
{

	/// @brief List of attributes supported by the image reader.
	struct cm3_image_attributes : tc1014::tc1014_image_attributes
	{
		///	@brief Common size type
		using size_type = size_t;
		/// @brief The monochroome pixelmap pattern type.
		using pattern_type = monochrome_pattern<uint8_t, size_t>;
		/// @brief The type use for maintaining a list of monochrome pixelmap patterns.
		using pattern_list_type = std::vector<pattern_type>;
		/// @copydoc colors::tc1014::tc1014_color_converter::color_type
		using color_type = colors::tc1014::tc1014_color_converter::color_type;
		/// @brief List of colors to cycle.
		using cycle_colors_list_type = std::vector<color_type>;

		/// @brief Attribute definition for color animation rate
		static const asset::attribute_def<size_type> color_animation_rate;
		/// @brief Attribute definition for first palette index for color animation
		static const asset::attribute_def<size_type> color_animation_start_index;
		/// @brief Attribute definition for last palette index for color animation
		static const asset::attribute_def<size_type> color_animation_end_index;
		/// @brief Attribute definition for the color cycling rate
		static const asset::attribute_def<size_type> color_cycle_rate;
		/// @brief Attribute definition for the color cycle index
		static const asset::attribute_def<size_type> color_cycle_index;
		///	@brief Attribute definition for color cycling color list
		static const asset::attribute_def<cycle_colors_list_type> color_cycle_colors;
		///	@brief Attribute definition for embedded monochrome bitmap patterns
		static const asset::attribute_def<pattern_list_type> patterns;
	};
}
