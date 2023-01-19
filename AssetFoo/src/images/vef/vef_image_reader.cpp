// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/vef/vef_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <kaos/core/exceptions.h>
#include <utility>


namespace hypertech::kaos::assetfoo::images::vef
{

	using core::io::binary_reader;

	const std::array<vef_image_reader::image_type_details, 5> vef_image_reader::image_type_descriptors
	{{
		{ { 320, 200 }, pixels::packed_pixel_layout::BPP4},
		{ { 640, 200 }, pixels::packed_pixel_layout::BPP2},
		{ { 160, 200 }, pixels::packed_pixel_layout::BPP4},
		{ { 320, 200 }, pixels::packed_pixel_layout::BPP2},
		{ { 640, 200 }, pixels::packed_pixel_layout::BPP1}
	}};

	std::unique_ptr<asset> vef_image_reader::load(
		std::istream& input_stream,
		const filename_type& source_name)
	try
	{
		binary_reader reader(input_stream, binary_reader::ordering_type::big);

		const auto image_flags(reader.read<uint8_t>());
		const auto image_type(reader.read<uint8_t>());
		if (image_type >= image_type_descriptors.size())
		{
			throw core::exceptions::file_format_error("invalid image type in `" + source_name + "`");
		}
		const auto& image_descriptor(image_type_descriptors[image_type]);
		const auto color_space(color_space_type::rgb);
		const auto is_compressed((image_flags & format_details::compression_flag_mask) != 0);

		auto native_colormap(reader.read_vector<native_packed_color_type>(format_details::colormap_length));
		native_colormap.resize(image_descriptor.layout.max_colors_in_pixel());

		auto image(std::make_unique<vef_image>(
			image_descriptor.dimensions,
			color_converter().create_colormap(color_space, native_colormap),
			color_space,
			native_colormap));

		if (is_compressed)
		{
			load_compressed_pixel_data(*image, image_descriptor.layout, reader, source_name);
		}
		else
		{
			load_uncompressed_pixel_data(*image, image_descriptor.layout, reader, source_name);
		}

		return image;
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file `" + source_name + "`");
	}


	void vef_image_reader::load_compressed_pixel_data(
		vef_image& image,
		const pixels::packed_pixel_layout& layout,
		core::io::binary_reader& reader,
		const filename_type& source_name) const
	try
	{
		const auto bpp(layout.bits_per_pixel());
		const auto pixels_per_byte(layout.pixels_per_packed_value());
		const auto& colormap(image.colormap());

		const pixels::packed_pixel_converter converter;
		for (auto row : image.create_view(image.width() / 2))
		{
			const auto block_size(reader.read<uint8_t>());
			const auto block_data(reader.read_vector<uint8_t>(block_size));

			for (auto data_ptr(block_data.begin()); !row.empty() && data_ptr != block_data.end(); )
			{
				const auto packet_header(*(data_ptr++));

				// We need to determine the number of bytes to process based on the remaining
				// number of colors in the row because some VEF files are encoded too many
				// bytes to fit in the half-row scheme.
				auto count(std::min(packet_header & format_details::packet_length_mask, row.size() / pixels_per_byte));
				if ((packet_header & format_details::packet_compressed_flag_mask) == 0)
				{
					//	Process uncompressed packet
					for (; count > 0 && data_ptr != block_data.end(); --count, ++data_ptr)
					{
						row = converter.unpack(bpp, colormap, *data_ptr, row);
					}
				}
				else
				{
					row = converter.unpack(bpp, colormap, *(data_ptr++), count, row);
				}
			}
		}
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file while processing compressed image data of `"
			+ source_name + "`");
	}

}
