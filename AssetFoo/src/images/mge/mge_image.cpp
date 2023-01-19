// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/mge/mge_image.h>


namespace hypertech::kaos::assetfoo::images::mge
{

	mge_image::mge_image(
		dimensions_type dimensions,
		std::unique_ptr<colors::color_map> colormap,
		color_space_type native_color_space,
		native_color_map_type native_colormap,
		string_type title)
		: 
		tc1014_image(dimensions, move(colormap), native_color_space, native_colormap),
		title_(move(title))
	{}


	const mge_image::string_type& mge_image::title() const
	{
		return title_;
	}

}
