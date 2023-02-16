// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/mge/mge_image_attributes.h>


namespace hypertech::kaos::assetfoo::images::mge
{

	const mge_image_attributes::attribute_definition<mge_image_attributes::string_type>
		mge_image_attributes::title("title");
	const mge_image_attributes::attribute_definition<mge_image_attributes::size_type>
		mge_image_attributes::color_animation_rate("color_animation_rate");
	const mge_image_attributes::attribute_definition<mge_image_attributes::size_type>
		mge_image_attributes::color_animation_start_index("color_animation_start_index");
	const mge_image_attributes::attribute_definition<mge_image_attributes::size_type>
		mge_image_attributes::color_animation_end_index("color_animation_end_index");

}