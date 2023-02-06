// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_attributes.h>


namespace hypertech::kaos::assetfoo::images::mge
{

	/// @brief List of attributes supported by the image reader.
	struct mge_image_attributes : tc1014::tc1014_image_attributes
	{
		/// @brief String type used for storing the name
		using string_type = std::string;
		/// @brief Size type.
		using size_type = size_t;

		/// @brief Attribute definition for image title
		static const asset::attribute_def<string_type> title;
		/// @brief Attribute definition for color animation rate
		static const asset::attribute_def<size_type> color_animation_rate;
		/// @brief Attribute definition for first palette index for color animation
		static const asset::attribute_def<size_type> color_animation_start_index;
		/// @brief Attribute definition for last palette index for color animation
		static const asset::attribute_def<size_type> color_animation_end_index;
	};


}
