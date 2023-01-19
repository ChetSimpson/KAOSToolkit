// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <string>
#include <stdexcept>


namespace hypertech::kaos::assetfoo::pixels
{

	packed_pixel_converter::color_input_sequence_type packed_pixel_converter::pack(
		size_type bits_per_pixel,
		const color_map_type& colormap,
		color_input_sequence_type input,
		packed_pixel_type& packed_pixels_output) const
	{
		if ((bits_per_pixel & (bits_per_pixel - 1)) != 0)
		{
			throw std::range_error("Bits per pixel passed to pack must be a power of two");
		}

		auto pixels_to_pack(packed_pixels_digits_ / bits_per_pixel);
		if (input.size() < pixels_to_pack)
		{
			throw std::length_error("Input buffer is too small to fill a packed pixel type");
		}

		auto pixel_shift(packed_pixels_digits_ - bits_per_pixel);
		auto pixel_mask(make_packed_pixel_mask(bits_per_pixel));
		auto max_pixel_value((1U << bits_per_pixel) - 1);
		auto input_ptr(input.begin());
		auto input_end(input.end());
		packed_pixel_type packed_pixels(0);

		while (pixels_to_pack > 0 && pixel_mask != 0 && input_ptr != input_end)
		{
			const auto pixel_index(colormap.index_of(*input_ptr));
			if (!pixel_index.has_value())
			{
				throw std::runtime_error(
					"pixel index for color ("
					+ std::to_string(input_ptr->R) + ", "
					+ std::to_string(input_ptr->G) + ", "
					+ std::to_string(input_ptr->B) + ", "
					+ std::to_string(input_ptr->A)
					+ ") not found in target colormap");
			}

			if (pixel_index.value() > max_pixel_value)
			{
				throw std::runtime_error(
					"Pixel index "
					+ std::to_string(pixel_index.value())
					+ " for color ("
					+ std::to_string(input_ptr->R) + ", "
					+ std::to_string(input_ptr->G) + ", "
					+ std::to_string(input_ptr->B) + ", "
					+ std::to_string(input_ptr->A)
					+ ") is out of range");
			}

			packed_pixels |= pixel_index.value() << pixel_shift;

			pixel_mask >>= bits_per_pixel;
			pixel_shift -= bits_per_pixel;
			++input_ptr;
			--pixels_to_pack;
		}

		packed_pixels_output = packed_pixels;

		return { input_ptr, input_end };
	}


	std::pair<
		packed_pixel_converter::color_input_sequence_type,
		packed_pixel_converter::packed_pixel_output_sequence_type>
	packed_pixel_converter::pack(
		size_type bits_per_pixel,
		const color_map_type& colormap,
		color_input_sequence_type input,
		packed_pixel_output_sequence_type output) const
	{
		if ((bits_per_pixel & (bits_per_pixel - 1)) != 0)
		{
			throw std::range_error("Bits per pixel passed to pack must be a power of two");
		}

		if (output.empty())
		{
			throw std::length_error("packed pixel output buffer cannot be empty");
		}

		const auto pixels_per_packed_value(packed_pixels_digits_ / bits_per_pixel);
		if ((input.size() % pixels_per_packed_value) != 0)
		{
			throw std::length_error("input buffer is too small to fill the last full packed pixel");
		}

		const auto starting_pixel_shift(packed_pixels_digits_ - bits_per_pixel);
		const auto starting_pixel_mask(make_packed_pixel_mask(bits_per_pixel));

		auto input_ptr(input.begin());
		auto input_end(input.end());
		auto output_ptr(output.begin());
		auto output_end(output.end());

		while (output_ptr != output_end && input_ptr != input_end)
		{
			auto pixel_shift(starting_pixel_shift);
			auto pixel_mask(starting_pixel_mask);
			auto max_pixel_value((1U << bits_per_pixel) - 1);

			packed_pixel_type packed_pixels(0);
			auto pixels_to_pack(pixels_per_packed_value);
			while (pixels_to_pack > 0 && pixel_mask != 0)
			{
				const auto pixel_index(colormap.index_of(*input_ptr));
				if (!pixel_index.has_value())
				{
					throw std::runtime_error(
						"pixel index for color ("
						+ std::to_string(input_ptr->R) + ", "
						+ std::to_string(input_ptr->G) + ", "
						+ std::to_string(input_ptr->B) + ", "
						+ std::to_string(input_ptr->A)
						+ ") not found in target colormap");
				}

				if (pixel_index.value() > max_pixel_value)
				{
					throw std::runtime_error(
						"Pixel index "
						+ std::to_string(pixel_index.value())
						+ " for color ("
						+ std::to_string(input_ptr->R) + ", "
						+ std::to_string(input_ptr->G) + ", "
						+ std::to_string(input_ptr->B) + ", "
						+ std::to_string(input_ptr->A)
						+ ") is out of range");
				}

				packed_pixels |= pixel_index.value() << pixel_shift;

				pixel_mask >>= bits_per_pixel;
				pixel_shift -= bits_per_pixel;
				++input_ptr;
				--pixels_to_pack;
			}

			*output_ptr = packed_pixels;
			++output_ptr;
		}

		return { { input_ptr, input_end }, { output_ptr, output_end } };
	}



	packed_pixel_converter::color_output_sequence_type packed_pixel_converter::unpack(
		size_type bits_per_pixel,
		const color_map_type& colormap,
		const packed_pixel_type packed_pixels,
		color_output_sequence_type output) const
	{
		if ((bits_per_pixel & (bits_per_pixel - 1)) != 0)
		{
			throw std::range_error("Bits per pixel passed to unpack must be a power of two");
		}

		auto pixels_to_unpack(packed_pixels_digits_ / bits_per_pixel);
		if (output.size() < pixels_to_unpack)
		{
			throw std::length_error("Output buffer is too small to contain all unpacked pixels");
		}

		auto pixel_shift(packed_pixels_digits_ - bits_per_pixel);
		auto pixel_mask(make_packed_pixel_mask(bits_per_pixel));
		auto output_ptr(output.begin());
		auto output_end(output.end());

		while (pixels_to_unpack > 0 && pixel_mask != 0 && output_ptr != output_end)
		{
			const auto pixel_index((packed_pixels & pixel_mask) >> pixel_shift);
			*output_ptr = colormap.at(pixel_index);

			pixel_mask >>= bits_per_pixel;
			pixel_shift -= bits_per_pixel;
			++output_ptr;
			--pixels_to_unpack;
		}

		return { output_ptr, output_end };
	}

	packed_pixel_converter::color_output_sequence_type packed_pixel_converter::unpack(
		size_type bits_per_pixel,
		const color_map_type& colormap,
		packed_pixel_type packed_pixels,
		size_type repeat_count,
		color_output_sequence_type output) const
	{
		if ((bits_per_pixel & (bits_per_pixel - 1)) != 0)
		{
			throw std::range_error("Bits per pixel passed to unpack repeating packed pixels must be a power of two");
		}

		auto pixels_to_unpack(packed_pixels_digits_ / bits_per_pixel * repeat_count);
		if (output.size() < pixels_to_unpack)
		{
			throw std::length_error("Output buffer is too small to contain all repeating unpacked pixels");
		}

		const auto starting_pixel_shift(packed_pixels_digits_ - bits_per_pixel);
		const auto starting_pixel_mask(make_packed_pixel_mask(bits_per_pixel));

		auto output_ptr(output.begin());
		auto output_end(output.end());

		while (pixels_to_unpack > 0 && output_ptr != output_end)
		{
			auto pixel_shift(starting_pixel_shift);
			auto pixel_mask(starting_pixel_mask);

			while (pixels_to_unpack > 0 && pixel_mask != 0 && output_ptr != output_end)
			{
				const auto pixel_index((packed_pixels & pixel_mask) >> pixel_shift);
				*output_ptr = colormap.at(pixel_index);

				pixel_mask >>= bits_per_pixel;
				pixel_shift -= bits_per_pixel;
				++output_ptr;
				--pixels_to_unpack;
			}

			--repeat_count;
		}

		return { output_ptr, output_end };
	}

	packed_pixel_converter::color_output_sequence_type packed_pixel_converter::unpack(
		size_type bits_per_pixel,
		const color_map_type& colormap,
		packed_pixel_input_sequence_type input,
		color_output_sequence_type output) const
	{
		if ((bits_per_pixel & (bits_per_pixel - 1)) != 0)
		{
			throw std::range_error("Bits per pixel passed to unpack with input buffer must be a power of two");
		}

		auto pixels_to_unpack(packed_pixels_digits_ / bits_per_pixel * input.size());
		if (output.size() < pixels_to_unpack)
		{
			throw std::length_error("Output buffer is too small to contain all unpacked pixels from input buffer");
		}

		const auto starting_pixel_shift(packed_pixels_digits_ - bits_per_pixel);
		const auto starting_pixel_mask(make_packed_pixel_mask(bits_per_pixel));

		auto output_ptr(output.begin());
		auto output_end(output.end());
		auto input_ptr(input.begin());
		auto input_end(input.end());

		while (pixels_to_unpack > 0 && output_ptr != output_end && input_ptr != input_end)
		{
			auto pixel_shift(starting_pixel_shift);
			auto pixel_mask(starting_pixel_mask);
			auto packed_pixels(*input_ptr);

			++input_ptr;

			while (pixels_to_unpack > 0 && pixel_mask != 0 && output_ptr != output_end)
			{
				const auto pixel_index((packed_pixels & pixel_mask) >> pixel_shift);
				*output_ptr = colormap.at(pixel_index);

				pixel_mask >>= bits_per_pixel;
				pixel_shift -= bits_per_pixel;
				++output_ptr;
				--pixels_to_unpack;
			}
		}

		return { output_ptr, output_end };
	}

	packed_pixel_converter::packed_pixel_type packed_pixel_converter::make_packed_pixel_mask(size_type bits_per_pixel) noexcept
	{
		return packed_pixel_type((~(packed_pixels_max_value_ >> bits_per_pixel)));
	}

}
