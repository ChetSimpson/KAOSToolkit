// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/rat/rat_image.h>


namespace hypertech::kaos::assetfoo::images::rat
{

	rat_image::rat_image(
		dimensions_type dimensions,
		std::unique_ptr<colors::color_map> colormap,
		color_space_type native_color_space,
		native_color_map_type native_colormap,
		color_type background_color)
		: 
		tc1014_image(dimensions, move(colormap), native_color_space, native_colormap),
		background_color_(background_color)
	{}


	rat_image::rat_image(rat_image&& other) noexcept
		:
		tc1014_image(move(other)),
		background_color_(other.background_color_)
	{
		other.background_color_ = decltype(other.background_color_)();
	}

	rat_image::color_type rat_image::background_color() const
	{
		return background_color_;
	}

}
