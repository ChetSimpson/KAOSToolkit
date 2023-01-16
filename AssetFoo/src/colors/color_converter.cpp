// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/color_converter.h>
#include <kaos/assetfoo/exceptions.h>
#include <stdexcept>
#include <algorithm>
#include <cmath>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors
{

	color_converter::color_converter(std::shared_ptr<const color_layout> color_format)
		: layout_(move(color_format))
	{
		if (layout_ == nullptr)
		{
			throw std::invalid_argument("Color format cannot be null");
		}
	}


	std::shared_ptr<const color_layout> color_converter::layout() const noexcept
	{
		return layout_;
	}


	color_converter::color_type color_converter::to_color(packed_color_type packed_color) const
	{
		if((packed_color & ~layout_->packed_color_bitmask()) != 0)
		{
			throw exceptions::packed_color_format_error("packed color value contains unsupported bits");
		}

		const auto unpacked_red_component(unpack_component_value(layout_->red_component_bitfield(), packed_color));
		const auto unpacked_green_component(unpack_component_value(layout_->green_component_bitfield(), packed_color));
		const auto unpacked_blue_component(unpack_component_value(layout_->blue_component_bitfield(), packed_color));
		const auto unpacked_alpha_component
			= layout_->alpha_component_size() != 0
			? unpack_component_value(layout_->alpha_component_bitfield(), packed_color)
			: color_type::max_component_value();

		return color_type(
			unpacked_red_component,
			unpacked_green_component,
			unpacked_blue_component,
			unpacked_alpha_component);
	}


	color_converter::packed_color_type color_converter::from_color(color_type color) const
	{
		return from_rgba_impl(color.R, color.G, color.B, color.A);
	}


	color_converter::packed_color_type color_converter::from_rgb(
		component_value_type r,
		component_value_type g,
		component_value_type b) const
	{
		return from_rgba_impl(r, g, b, color_type::max_component_value());
	}


	color_converter::packed_color_type color_converter::from_rgba(
		component_value_type r,
		component_value_type g,
		component_value_type b,
		component_value_type a) const
	{
		return from_rgba_impl(r, g, b, a);
	}



	color_converter::packed_color_type color_converter::from_rgba_impl(
		component_value_type red,
		component_value_type green,
		component_value_type blue,
		component_value_type alpha) const
	{
		const auto packed_red_component(pack_component_value(layout_->red_component_bitfield(), red));
		const auto packed_green_component(pack_component_value(layout_->green_component_bitfield(), green));
		const auto packed_blue_component(pack_component_value(layout_->blue_component_bitfield(), blue));
		const auto packed_alpha_component
			= layout_->alpha_component_size() != 0
			? pack_component_value(layout_->alpha_component_bitfield(), alpha)
			: 0;

		return packed_red_component
			| packed_green_component
			| packed_blue_component
			| packed_alpha_component;
	}




	color_converter::component_value_type color_converter::unpack_component_value(
		const bitfield_type& bitfield,
		packed_color_type packed_color) const
	{
		const auto component_digits(bitfield.size());

		if (component_digits == 0)
		{
			throw std::length_error(bitfield.name() + " unpacked component size cannot be zero");
		}

		if (component_digits > std::numeric_limits<component_value_type>::digits)
		{
			throw std::length_error(bitfield.name() + " unpacked component size is larger than target component type");
		}

		const auto unpacked_component(bitfield.get_from(packed_color));
		if (unpacked_component > max_component_value())
		{
			throw std::range_error(bitfield.name() + " unpacked component value exceeds the maximum allowed component value");
		}

		const auto scale_value = max_component_value_as<double>() / bitfield.max_value();
		const auto color_component(uintmax_t(unpacked_component * scale_value));
		if (color_component > max_component_value())
		{
			//	FIXME: Not sure if we should even be checking this here if the assumption is bitfield works properly.
			throw std::range_error(bitfield.name() + " unpacked component value exceeds maximum allowed value after scaling");
		}

		return static_cast<component_value_type>(color_component);
	}


	color_converter::packed_color_type color_converter::pack_component_value(
		const bitfield_type& bitfield,
		component_value_type component_value) const
	{
		if (bitfield.size() == 0)
		{
			throw std::length_error(bitfield.name() + " packed component size cannot be zero");
		}

		//	Calculate our scale value and check that the given component value 
		//	is a multiple of the scale.
		const auto scale_value = max_component_value_as<float>() / bitfield.max_value();
		if (std::fmod(component_value, scale_value) >= std::numeric_limits<double>::epsilon())
		{
			throw std::range_error("Conversion of " + bitfield.name() + " component value to packed component results in loss of color precision");
		}

		const auto scaled_component_value(uintmax_t(component_value / scale_value));

		//	FIXME: This does not appear to be possible at the moment. Need to explore use-cases
		//	where it can happen.
		//
		//	NOT COVERED BY UNIT TESTS
		if (scaled_component_value > bitfield.max_value())
		{
			throw std::range_error(bitfield.name() + " component value exceeds maximum value allowed for packed component");
		}

		return bitfield.set_in(0, scaled_component_value);
	}

}}}}
