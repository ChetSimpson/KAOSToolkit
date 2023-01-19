// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <array>
#include <algorithm>
#include <string>
#include <stdexcept>


namespace hypertech::kaos::assetfoo::pixels
{
	
	const packed_pixel_layout packed_pixel_layout::BPP8(bitfieldlist_type({ {8, 0} }));

	const packed_pixel_layout packed_pixel_layout::BPP4(bitfieldlist_type({ {4, 4}, {4, 0} }));

	const packed_pixel_layout packed_pixel_layout::BPP2(
		bitfieldlist_type({ {2, 6}, {2, 4}, {2, 2}, {2, 0} }));

	const packed_pixel_layout packed_pixel_layout::BPP1(
		bitfieldlist_type({ {1, 7}, {1, 6}, {1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0} }));


	packed_pixel_layout::packed_pixel_layout(bitfieldlist_type pixel_bitfields)
		: pixel_bitfields_(move(pixel_bitfields))
	{
		if (pixel_bitfields_.size() == 0)
		{
			throw std::invalid_argument("Pixel bitfields list cannot contain 0 elements");
		}

		auto first_non_mathing_bitfield = std::find_if(
			pixel_bitfields_.begin(),
			pixel_bitfields_.end(),
			[this](const auto& bitfield)
			{
				return bitfield.size() != pixel_bitfields_.begin()->size();
			});

		if (first_non_mathing_bitfield != pixel_bitfields_.end())
		{
			throw std::invalid_argument("Packed pixel bitfield definitions must be uniform");
		}
	}


	packed_pixel_layout::packed_pixel_layout(size_type bits_per_pixel)
		: pixel_bitfields_(make_bitfields(bits_per_pixel))
	{}


	packed_pixel_layout::bitfieldlist_type packed_pixel_layout::make_bitfields(size_type bits_per_pixel)
	{
		if (bits_per_pixel == 0)
		{
			throw std::range_error("Bits per pixel passed to packed_pixel_layout cannot be 0");
		}

		const auto total_digits(std::numeric_limits<packedpixelvalue_type>::digits);
		if (bits_per_pixel > total_digits)
		{
			throw std::overflow_error("Bits per pixel passed to packed_pixel_layout must be less than or equal to " + std::to_string(total_digits));
		}

		if ((bits_per_pixel & (bits_per_pixel - 1)) != 0)
		{
			throw std::range_error("Bits per pixel passed to packed_pixel_layout must be a power of two");
		}

		//if ((total_digits % bits_per_pixel) != 0)
		//{
		//	throw std::range_error("Bits per pixel passed to packed_pixel_layout must be a a multiple of " + std::to_string(total_digits));
		//}

		bitfieldlist_type bitfields;
		for(auto pixel_position(total_digits - bits_per_pixel), total_pixels(total_digits / bits_per_pixel);
			total_pixels > 0;
			--total_pixels, pixel_position -= bits_per_pixel)
		{
			bitfields.emplace_back(bits_per_pixel, pixel_position);
		}

		return bitfields;
	}




	packed_pixel_layout::size_type packed_pixel_layout::max_colors_in_pixel() const noexcept
	{
		return pixel_bitfields_.front().max_value() + 1;
	}

	packed_pixel_layout::size_type packed_pixel_layout::pixels_per_packed_value() const noexcept
	{
		return pixel_bitfields_.size();
	}

	packed_pixel_layout::size_type packed_pixel_layout::bits_per_pixel() const noexcept
	{
		return pixel_bitfields_.front().size();
	}

	const packed_pixel_layout::bitfieldlist_type& packed_pixel_layout::pixel_bitfields() const noexcept
	{
		return pixel_bitfields_;
	}

	packed_pixel_layout::size_type packed_pixel_layout::calculate_pitch(
		size_type width_in_pixels,
		size_type alignment_in_bytes) const
	{
		if (width_in_pixels == 0)
		{
			throw std::invalid_argument("Width in pixels cannot be 0");
		}

		if (alignment_in_bytes == 0)
		{
			throw std::invalid_argument("Alignment cannot be 0");
		}

		if ((alignment_in_bytes & (alignment_in_bytes - 1)) != 0)
		{
			throw std::invalid_argument("Alignment must be a power of two");
		}

		auto pitch = (width_in_pixels + pixels_per_packed_value() - 1) / pixels_per_packed_value();

		return (pitch + alignment_in_bytes - 1) & ~(alignment_in_bytes - 1);
	}

}
