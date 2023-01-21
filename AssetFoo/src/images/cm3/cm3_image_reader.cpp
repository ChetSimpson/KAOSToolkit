// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/cm3/cm3_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <kaos/core/utility/bit_reader.h>
#include <kaos/core/exceptions.h>


namespace hypertech::kaos::assetfoo::images::cm3
{

	using core::io::binary_reader;
	using core::utility::bit_reader;

	const cm3_image_reader::attribute_definition<cm3_image_reader::size_type>
		cm3_image_reader::attributes::color_animation_rate("color_animation_rate");
	const cm3_image_reader::attribute_definition<cm3_image_reader::size_type>
		cm3_image_reader::attributes::color_animation_start_index("color_animation_start_index");
	const cm3_image_reader::attribute_definition<cm3_image_reader::size_type>
		cm3_image_reader::attributes::color_animation_end_index("color_animation_end_index");
	const cm3_image_reader::attribute_definition<cm3_image_reader::size_type>
		cm3_image_reader::attributes::color_cycle_rate("color_cycle_rate");
	const cm3_image_reader::attribute_definition<cm3_image_reader::size_type>
		cm3_image_reader::attributes::color_cycle_index("color_cycle_index");
	const cm3_image_reader::attribute_definition<cm3_image_reader::cycle_colors_list_type>
		cm3_image_reader::attributes::color_cycle_colors("color_cycle_colors");
	const cm3_image_reader::attribute_definition<cm3_image_reader::pattern_list_type>
		cm3_image_reader::attributes::patterns("patterns");


	std::unique_ptr<asset> cm3_image_reader::load(
		std::istream& input_stream,
		const filename_type& source_name)
	try
	{
		binary_reader reader(input_stream, binary_reader::ordering_type::big);

		// First load the header
		const auto image_flags(reader.read<uint8_t>());
		const auto native_color_map(reader.read_vector<native_packed_color_type>(format_details::color_count));
		const auto animation_rate(reader.read<uint8_t>());
		const auto cycle_rate(reader.read<uint8_t>());
		const auto cycle_colors(reader.read_vector<native_packed_color_type>(format_details::cycle_color_count));
		const auto animation_flags(reader.read<uint8_t>());
		const auto cycling_flags(reader.read<uint8_t>());

		//	Extract the details we need and create the colormap
		const auto native_color_space(color_space_type::rgb);	//	Needs user supplied option
		const auto page_count((image_flags & format_details::double_page_flag_mask) == 0 ? 1 : 2);
		const auto include_patterns((image_flags & format_details::exclude_patterns_flag_mask) == 0);

		const auto dimensions(image_type::dimensions_type(format_details::page_width, format_details::page_height * page_count));

		auto colormap(color_converter().create_colormap(native_color_space, native_color_map));
		//	Load the patterns if they exist
		pattern_list_type patterns;
		if (include_patterns)
		{
			patterns = load_patterns(*colormap, reader, source_name);
		}

		auto image(std::make_unique<image_type>(dimensions, color_type(255, 255, 255)));
		load_compressed_pixel_data(
			reader,
			*image,
			*colormap,
			format_details::pixel_layout,
			page_count,
			source_name);

		image->set_attribute(attributes::native_color_space, native_color_space);
		image->set_attribute(attributes::native_color_map, native_color_map);
		image->set_attribute(attributes::color_animation_rate, animation_rate);
		image->set_attribute(attributes::color_animation_start_index, format_details::color_animation_start_index);
		image->set_attribute(attributes::color_animation_end_index, format_details::color_animation_end_index);
		image->set_attribute(attributes::color_cycle_rate, cycle_rate);
		image->set_attribute(attributes::color_cycle_index, format_details::color_cycle_index);
		image->set_attribute(attributes::color_cycle_colors, color_converter().convert_colors(native_color_space, cycle_colors));
		image->set_attribute(attributes::patterns, patterns);

		return image;
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file `" + source_name + "`");
	}

	cm3_image_reader::pattern_list_type cm3_image_reader::load_patterns(
		color_map_type colormap,
		binary_reader& reader,
		const filename_type& source_name) const
	try
	{
		reader.skip(format_details::pattern_section_header_length);

		pattern_list_type patterns;
		for(auto i(0U); i < format_details::pattern_count; ++i)
		{
			const auto background_color_index(reader.read<uint8_t>() & format_details::pattern_color_index_mask);
			const auto foreground_color_index(reader.read<uint8_t>() & format_details::pattern_color_index_mask);
			const auto pixmap(reader.read_array<pattern_type::pixelmap_pixel_type, pattern_type::pixmap_length>());

			patterns.emplace_back(background_color_index, foreground_color_index, pixmap);
		}

		return patterns;
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file while loading patterns from `"
			+ source_name);
	}

	void cm3_image_reader::load_compressed_pixel_data(
		core::io::binary_reader& reader,
		image_type& image,
		const color_map_type& colormap,
		const pixels::packed_pixel_layout& layout,
		size_type page_count,
		const filename_type& source_name) const
	{
		auto page_size(image.height() / page_count);

		for (auto page(0U); page < page_count; ++page)
		{
			auto y_position(page_size * page);
			load_page_compressed_pixel_data(
				reader,
				image.create_view(0, y_position, image.width(), page_size),
				colormap,
				layout,
				page,
				source_name);
		}
	}


	void cm3_image_reader::load_page_compressed_pixel_data(
		core::io::binary_reader& reader,
		image_type::view_type page_view,
		const color_map_type& colormap,
		const pixels::packed_pixel_layout& layout,
		size_type page_index,
		const filename_type& source_name) const
	try
	{
		const auto row_count(reader.read<uint8_t>());
		if (row_count != page_view.height())
		{
			throw core::exceptions::file_format_error(
				"image file format error: invalid row count of "
				+ std::to_string(row_count)
				+ " in image page "
				+ std::to_string(page_index)
				+ " of `" + source_name + "`");
		}

		const auto bpp(layout.bits_per_pixel());
		const pixels::packed_pixel_converter converter;

		std::array<uint8_t, format_details::decompression_line_buffer_size> line_buffer = { 0 };
		std::array<uint8_t, format_details::horizontal_bitstream_size_in_bytes> horizontal_dictionary_buffer = { 0 };
		std::vector<uint8_t> vertical_dictionary_buffer;
		uint8_t last_byte = 0;

		for (auto row : page_view)
		{
			auto control_byte(reader.read<uint8_t>());
			if ((control_byte & 0x80) != 0)
			{
				line_buffer = reader.read_array<uint8_t, line_buffer.size()>();

				//	We need to track the last byte read for the case where the horizontal
				//	bit is not set.
				last_byte = line_buffer.back();
			}
			else
			{
				horizontal_dictionary_buffer = reader.read_array<uint8_t, horizontal_dictionary_buffer.size()>();
				vertical_dictionary_buffer = reader.read_vector<uint8_t>(control_byte & 0x7f);

				bit_reader<uint8_t> horizontal_dictionary(horizontal_dictionary_buffer);
				auto vertical_dictionary(
					(control_byte & 0x7F) == 0
					? bit_reader<uint8_t>()
					: bit_reader<uint8_t>(vertical_dictionary_buffer));

				for (auto line_ptr(line_buffer.begin()); line_ptr != line_buffer.end(); ++line_ptr)
				{

					//	If the next bit in the horizontal dictionary is not set we use the previous
					//	byte
					if (!horizontal_dictionary.read())
					{
						*line_ptr = last_byte;
					}
					//	Otherwise if the next bit in the vertical_dictionary is set we get the next
					//	byte in the input stream
					else if (vertical_dictionary.read())
					{
						*line_ptr = reader.read<uint8_t>();
					}

					// NOTE: In the case where neither the next bit in the horizontal dictionary is set 
					// and the next bit in the vertical dictionary is not set we need to use the byte
					// immediately above the current position in the image. Since the line buffer is
					// recycled that is the byte at the current line_ptr position.


					//	We need to track the last byte read for the case where the horizontal
					//	bit is not set.
					last_byte = *line_ptr;
				}

				converter.unpack(bpp, colormap, line_buffer, row);
			}
		}
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file while processing uncompressed image data in page "
			+ std::to_string(page_index)
			+ " of `" + source_name + "`");
	}

}
