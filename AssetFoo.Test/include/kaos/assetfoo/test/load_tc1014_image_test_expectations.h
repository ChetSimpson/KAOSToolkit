// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image.h>
#include <kaos/assetfoo/images/hash.h>
#include <iostream>
#include <iomanip>


namespace hypertech::kaos::assetfoo::unittests
{

	template<
		size_t Width_,
		size_t Height_,
		images::tc1014::tc1014_image::color_space_type ColorSpace_ = images::tc1014::tc1014_image::color_space_type::rgb>
		struct load_tc1014_image_test_expectations
	{
		using base_image_type = images::tc1014::tc1014_image;
		static const size_t width = Width_;
		static const size_t height = Height_;
		static const images::tc1014::tc1014_image::color_space_type colorspace = ColorSpace_;

		virtual bool should_print_diagnostics() const
		{
			return false;
		}

		virtual void print_diagnostics(const base_image_type& image) const
		{
			if (!should_print_diagnostics())
			{
				return;
			}

			const char* comma = "";
			std::cout << "Hash = { ";
			for (const auto& value : calculate_md5_hash(image))
			{
				std::cout
					<< comma << "0x"
					<< std::hex << std::setw(8) << std::setfill('0') << value;
				comma = ", ";
			}
			std::cout << " }\n";

			//	native colormap
			const auto native_colormap(image.native_colormap());

			std::cout << "CLUT = { ";
			comma = "";
			for (const auto& color : image.native_colormap())
			{
				std::cout
					<< comma << "0x"
					<< std::hex << std::uppercase << std::setw(2) << std::setfill('0')
					<< unsigned(color) << std::dec;
				comma = ", ";
			}
			std::cout << " }\n";
		}
	};

}
