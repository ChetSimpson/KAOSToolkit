// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/mge/mge_image_attributes.h>


namespace hypertech::kaos::assetfoo::images::mge
{

	const asset::attribute_def<mge_image_attributes::string_type>
		mge_image_attributes::title("title");
	const asset::attribute_def<mge_image_attributes::size_type>
		mge_image_attributes::color_animation_rate("color_animation_rate");
	const asset::attribute_def<mge_image_attributes::size_type>
		mge_image_attributes::color_animation_start_index("color_animation_start_index");
	const asset::attribute_def<mge_image_attributes::size_type>
		mge_image_attributes::color_animation_end_index("color_animation_end_index");

}