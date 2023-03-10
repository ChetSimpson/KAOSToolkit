// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/rat/rat_image_reader.h>
#include <kaos/assetfoo/images/rat/rat_image.h>
#include <kaos/assetfoo/colors/color_converter.h>
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <kaos/core/exceptions.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace rat
{

	using core::io::binary_reader;

	std::unique_ptr<asset> rat_image_reader::load(
		std::istream& input_stream,
		const filename_type& source_name)
	try
	{
		binary_reader reader(input_stream, binary_reader::ordering_type::big);

		const auto escape_value(reader.read<uint8_t>());
		const auto is_compressed(reader.read<bool>());
		const auto native_background_color(reader.read<uint8_t>());
		const auto native_colormap(reader.read_vector<native_packed_color_type>(format_details::colormap_length));
		const auto color_space(color_space_type::rgb);

		auto image(std::make_unique<rat_image>(
			format_details::dimensions,
			color_converter().create_colormap(color_space, native_colormap),
			color_space,
			native_colormap,
			color_converter().to_color(native_background_color)));

		const auto& layout(format_details::pixel_layout);
		if (is_compressed)
		{
			load_compressed_pixel_data(*image, layout, escape_value, reader, source_name);
		}
		else
		{
			load_uncompressed_pixel_data(*image, layout, reader, source_name);
		}

		return image;
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file `" + source_name + "`");
	}


	void rat_image_reader::load_compressed_pixel_data(
		rat_image& image,
		const pixels::packed_pixel_layout& layout,
		uint8_t escape_value,
		core::io::binary_reader& reader,
		const filename_type& source_name) const
	try
	{
		const auto bpp(layout.bits_per_pixel());
		const auto& colormap(image.colormap());
		const pixels::packed_pixel_converter converter;

		for (auto sequence(image.get_sequence()); !sequence.empty(); )
		{
			const auto data_byte(reader.read<uint8_t>());
			if (data_byte != escape_value)
			{
				sequence = converter.unpack(bpp, colormap, data_byte, sequence);
			}
			else
			{
				auto rlepair(reader.read_pair<uint8_t, uint8_t>());
				sequence = converter.unpack(
					bpp,
					colormap,
					rlepair.second,	//	Packed pixels
					rlepair.first,	//	Repeat count
					sequence);
			}
		}
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file while processing compressed image data of `"
			+ source_name + "`");
	}

}}}}}
