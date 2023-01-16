// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/tc1014/tc1014_color_converter.h>
#include <algorithm>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors { namespace tc1014
{

	/// This table was extracted from the ColorMax Deluxe source code
	/// at https://github.com/milliluk/colormax/blob/master/RGBCMP.TXT
	const tc1014_color_converter::native_color_map_type tc1014_color_converter::composite_to_rgb_table_
	{
		0, 2, 2, 6, 0, 4, 33, 32, 32, 45, 5, 9, 13, 8, 1, 0,
		7, 16, 18, 21, 20, 34, 38, 36, 37, 44, 40, 42, 11, 15, 10, 27,
		56, 23, 19, 49, 48, 55, 38, 39, 37, 46, 47, 41, 11, 25, 24, 26,
		63, 58, 50, 51, 62, 52, 53, 60, 60, 46, 61, 61, 57, 59, 58, 63,
	};


	tc1014_color_converter::tc1014_color_converter()
		: color_converter(std::make_shared<tc1014_color_layout>())
	{}


	tc1014_color_converter::tc1014_color_converter(std::shared_ptr<const color_layout> color_format)
		: color_converter(color_format)
	{}


	const tc1014_color_converter::native_color_map_type& tc1014_color_converter::composite_to_rgb_table() const noexcept
	{
		return composite_to_rgb_table_;
	}

	void tc1014_color_converter::convert_color_to_colorspace(
		color_space_type from_color_space,
		color_space_type to_color_space,
		native_color_map_type& native_colormap) const
	{
		//	We do nothing if the from and to colorspaces are the same
		if (from_color_space == to_color_space)
		{
			return;
		}

		//	FIXME: Not covered in unit tests because there are no other colorspaces!
		if (from_color_space != color_space_type::composite && from_color_space != color_space_type::rgb)
		{
			throw std::runtime_error("converting from colorspace other than composite is not supported");

		}

		if (to_color_space != color_space_type::rgb)
		{
			throw std::runtime_error("converting to colorspace other than RGB is not supported");
		}

		for (auto& packed_color : native_colormap)
		{
			packed_color &= tc1014_color_layout::native_packed_color_mask;
		}

		if(from_color_space == color_space_type::composite)
		{
			for (auto& packed_color : native_colormap)
			{
				packed_color = composite_to_rgb_table_[packed_color & tc1014_color_layout::native_packed_color_mask];
			}
		}
	}


	std::vector<tc1014_color_converter::color_type> tc1014_color_converter::convert_colors(
		color_space_type color_space,
		native_color_map_type native_colormap) const
	{
		convert_color_to_colorspace(color_space, color_space_type::rgb, native_colormap);

		std::vector<color_type> colors(native_colormap.size());

		std::transform(
			native_colormap.begin(),
			native_colormap.end(),
			colors.begin(),
			[=](const auto& color) -> auto { return to_color(color & tc1014_color_layout::native_packed_color_mask); });

		return colors;
	}


	std::unique_ptr<colors::color_map> tc1014_color_converter::create_colormap(
		color_space_type color_space,
		native_color_map_type native_colormap) const
	{
		convert_color_to_colorspace(color_space, color_space_type::rgb, native_colormap);

		auto colormap(std::make_unique<colors::color_map>(
			native_colormap.size(),
			native_colormap.size()));

		std::transform(
			native_colormap.begin(),
			native_colormap.end(),
			colormap->begin(),
			[=](const auto& color) -> auto { return to_color(color); });

		return colormap;
	}

}}}}}
