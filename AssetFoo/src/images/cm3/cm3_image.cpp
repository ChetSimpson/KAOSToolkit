// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/cm3/cm3_image.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace cm3
{

	cm3_image::cm3_image(
		dimensions_type dimensions,
		std::unique_ptr<colors::color_map> colormap,
		color_space_type native_color_space,
		native_color_map_type native_colormap,
		size_type animation_rate,
		size_type cycle_rate,
		cycle_colors_list_type cycle_colors,
		pattern_list_type patterns)
		:
		tc1014_image(dimensions, move(colormap), native_color_space, move(native_colormap)),
		animation_rate_(animation_rate),
		cycle_rate_(cycle_rate),
		cycle_colors_(move(cycle_colors)),
		patterns_(move(patterns))
	{
		if (this->native_colormap().size() != feature_details::max_colormap_size)
		{
			throw std::out_of_range("colormap must contain 16 colors");
		}

		if (animation_rate_ > feature_details::max_animation_rate)
		{
			throw std::out_of_range("animation rate is too large");
		}

		if (cycle_rate_ > feature_details::max_cycle_rate)
		{
			throw std::out_of_range("cycle rate is too large");
		}

		if (!cycle_colors_.empty() && cycle_colors_.size() != feature_details::fixed_cycle_color_count)
		{
			throw std::out_of_range("cycle color list must contain 0 or 8 colors");
		}
	}

	cm3_image::cm3_image(const cm3_image& other)
		:
		tc1014_image(other),
		animation_rate_(other.animation_rate_),
		cycle_rate_(other.cycle_rate_),
		cycle_colors_(other.cycle_colors_),
		patterns_(other.patterns_)
	{}

	cm3_image::cm3_image(cm3_image&& other) noexcept
		:
		tc1014_image(move(other)),
		animation_rate_(other.animation_rate_),
		cycle_rate_(other.cycle_rate_),
		cycle_colors_(move(other.cycle_colors_)),
		patterns_(move(other.patterns_))
	{
		other.animation_rate_ = decltype(other.animation_rate_)();
		other.cycle_rate_ = decltype(other.cycle_rate_)();
	}

	cm3_image::size_type cm3_image::animation_rate() const
	{
		return animation_rate_;
	}

	cm3_image::size_type cm3_image::cycle_rate() const
	{
		return cycle_rate_;
	}

	const cm3_image::cycle_colors_list_type& cm3_image::cycle_colors() const
	{
		return cycle_colors_;
	}

	const cm3_image::pattern_list_type& cm3_image::patterns() const
	{
		return patterns_;
	}

}}}}}
