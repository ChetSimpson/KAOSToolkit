// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/tc1014/tc1014_image.h>


namespace hypertech::kaos::assetfoo::images::tc1014
{

	tc1014_image::tc1014_image(
		dimensions_type dimensions,
		std::unique_ptr<colors::color_map> colormap,
		color_space_type native_color_space,
		native_color_map_type native_colormap)
		: 
		image(dimensions, pixel_type(255, 255, 255)),
		colormap_(move(colormap)),
		native_color_space_(native_color_space),
		native_colormap_(move(native_colormap))
	{
		if (colormap_ == nullptr)
		{
			throw std::invalid_argument("colormap passed to tc1014 based image cannot be null");
		}

		if (native_colormap_.size() != colormap_->size())
		{
			throw std::invalid_argument("Number of colors in native colormap do not match RGBA colormap");
		}
	}


	tc1014_image::tc1014_image(const tc1014_image& other)
		:
		image(other),
		colormap_(other.colormap_ != nullptr ? std::make_unique<color_map_type>(*other.colormap_) : nullptr),
		native_color_space_(other.native_color_space_),
		native_colormap_(other.native_colormap_)
	{}


	tc1014_image::tc1014_image(tc1014_image&& other) noexcept
		:
		image(move(other)),
		colormap_(move(other.colormap_)),
		native_color_space_(other.native_color_space_),
		native_colormap_(move(other.native_colormap_))
	{
		other.native_color_space_ = decltype(other.native_color_space_)();
		other.native_colormap_ = decltype(other.native_colormap_)();
	}


	const tc1014_image::color_map_type& tc1014_image::colormap() const
	{
		if (colormap_ == nullptr)
		{
			throw std::runtime_error("colormap is null");
		}

		return *colormap_;
	}

	tc1014_image::color_space_type tc1014_image::native_color_space() const
	{
		return native_color_space_;
	}

	const tc1014_image::native_color_map_type& tc1014_image::native_colormap() const
	{
		return native_colormap_;
	}

}
