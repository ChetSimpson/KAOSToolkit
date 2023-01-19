// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/mge/mge_image_reader.h>
#include <kaos/assetfoo/images/mge/mge_image.h>
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <kaos/core/exceptions.h>


namespace hypertech::kaos::assetfoo::images::mge
{

	using core::io::binary_reader;

	std::unique_ptr<asset> mge_image_reader::load(
		std::istream& input_stream,
		const filename_type& source_name)
	try
	{
		binary_reader reader(input_stream, binary_reader::ordering_type::big);

		if (reader.read_enum<uint8_t, format_details::image_types>() != format_details::image_types::color_320x200_4bpp)
		{
			throw core::exceptions::file_format_error("unknown image type specified in " + source_name);
		}

		const auto native_colormap(reader.read_vector<native_packed_color_type>(format_details::colormap_length));
		const auto color_space(reader.read<bool>() ? color_space_type::composite : color_space_type::rgb);
		const auto is_compressed(!reader.read<bool>());
		const auto title(reader.read_string(format_details::title_length, true));
		const auto cycle_rate(reader.read<uint8_t>());		//	TODO: Not used
		const auto cycle_indexes(reader.read<uint8_t>());	//	TODO: Not used

		auto image(std::make_unique<mge_image>(
			format_details::dimensions,
			color_converter().create_colormap(color_space, native_colormap),
			color_space,
			native_colormap,
			title));

		const auto& layout(pixels::packed_pixel_layout::BPP4);
		if (is_compressed)
		{
			load_compressed_pixel_data(*image, layout, reader, source_name);
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


	void mge_image_reader::load_compressed_pixel_data(
		mge_image& image,
		const pixels::packed_pixel_layout& layout,
		core::io::binary_reader& reader,
		const filename_type& source_name) const
	try
	{
		const auto bpp(layout.bits_per_pixel());
		const auto& colormap(image.colormap());
		const pixels::packed_pixel_converter converter;

		for (auto sequence(image.get_sequence()); !sequence.empty(); )
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
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file while processing compressed image data of `"
			+ source_name + "`");
	}

}
