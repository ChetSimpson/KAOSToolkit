// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/color_layout.h>
#include <boost/numeric/conversion/cast.hpp>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors
{

	color_layout::color_layout(
		const bitfield_type& red_component_bitfield,
		const bitfield_type& green_component_bitfield,
		const bitfield_type& blue_component_bitfield,
		const bitfield_type& alpha_component_bitfield)
		:
		red_component_bitfield_(red_component_bitfield),
		green_component_bitfield_(green_component_bitfield),
		blue_component_bitfield_(blue_component_bitfield),
		alpha_component_bitfield_(alpha_component_bitfield)
	{
		if (red_component_bitfield_.max_value() > std::numeric_limits<component_value_type>::max())
		{
			throw std::range_error("Maximum possible value of red component exceeds maximum value of component type");
		}

		if (green_component_bitfield_.max_value() > std::numeric_limits<component_value_type>::max())
		{
			throw std::range_error("Maximum possible value of green component exceeds maximum value of component type");
		}

		if (blue_component_bitfield_.max_value() > std::numeric_limits<component_value_type>::max())
		{
			throw std::range_error("Maximum possible value of blue component exceeds maximum value of component type");
		}

		if (alpha_component_bitfield_.max_value() > std::numeric_limits<component_value_type>::max())
		{
			throw std::range_error("Maximum possible value of alpha component exceeds maximum value of component type");
		}
	}


	color_layout::packed_color_type color_layout::packed_color_bitmask() const noexcept
	{
		return
			red_component_bitfield_.mask()
			| green_component_bitfield_.mask()
			| blue_component_bitfield_.mask()
			| alpha_component_bitfield_.mask();
	}


	color_layout::size_type color_layout::red_component_size() const noexcept
	{
		return red_component_bitfield_.size();
	}

	color_layout::size_type color_layout::green_component_size() const noexcept
	{
		return green_component_bitfield_.size();
	}

	color_layout::size_type color_layout::blue_component_size() const noexcept
	{
		return blue_component_bitfield_.size();
	}

	color_layout::size_type color_layout::alpha_component_size() const noexcept
	{
		return alpha_component_bitfield_.size();
	}


	color_layout::component_value_type color_layout::red_component_max_value() const noexcept
	{
		return boost::numeric_cast<component_value_type>(red_component_bitfield_.max_value());
	}

	color_layout::component_value_type color_layout::green_component_max_value() const noexcept
	{
		return boost::numeric_cast<component_value_type>(green_component_bitfield_.max_value());
	}

	color_layout::component_value_type color_layout::blue_component_max_value() const noexcept
	{
		return boost::numeric_cast<component_value_type>(blue_component_bitfield_.max_value());
	}

	color_layout::component_value_type color_layout::alpha_component_max_value() const noexcept
	{
		return boost::numeric_cast<component_value_type>(alpha_component_bitfield_.max_value());
	}


	const color_layout::bitfield_type& color_layout::red_component_bitfield() const noexcept
	{
		return red_component_bitfield_;
	}

	const color_layout::bitfield_type& color_layout::green_component_bitfield() const noexcept
	{
		return green_component_bitfield_;
	}

	const color_layout::bitfield_type& color_layout::blue_component_bitfield() const noexcept
	{
		return blue_component_bitfield_;
	}

	const color_layout::bitfield_type& color_layout::alpha_component_bitfield() const noexcept
	{
		return alpha_component_bitfield_;
	}

}}}}
