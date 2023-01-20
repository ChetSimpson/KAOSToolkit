// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/images/hash.h>
#include <iostream>
#include <iomanip>


namespace hypertech::kaos::assetfoo::unittests
{

	template<
		size_t Width_,
		size_t Height_,
		images::tc1014::tc1014_image_reader::color_space_type ColorSpace_ = images::tc1014::tc1014_image_reader::color_space_type::rgb>
		struct tc1014_image_reader_test_expectations
	{
		using size_type = size_t;
		using color_map_type = images::tc1014::tc1014_image_reader::color_map_type;
		using color_type = images::tc1014::tc1014_image_reader::color_type;
		using color_space_type = images::tc1014::tc1014_image_reader::color_space_type;
		using native_packed_color_type = images::tc1014::tc1014_image_reader::native_packed_color_type;
		using native_color_map_type = images::tc1014::tc1014_image_reader::native_color_map_type;

		static const size_type width = Width_;
		static const size_type height = Height_;
		static const images::tc1014::tc1014_image_reader::color_space_type colorspace = ColorSpace_;
	};

}
