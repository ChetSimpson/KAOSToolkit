// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/mge/mge_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <kaos/core/exceptions.h>
#include <algorithm>


namespace hypertech::kaos::assetfoo::images::tc1014
{

	const tc1014_image_reader::attribute_definition<tc1014_image_reader::color_space_type>
		tc1014_image_reader::attributes::native_color_space("native_color_space");
	const tc1014_image_reader::attribute_definition<tc1014_image_reader::native_color_map_type>
		tc1014_image_reader::attributes::native_color_map("native_color_map");


	void tc1014_image_reader::load_uncompressed_pixel_data(
		core::io::binary_reader& reader,
		image& image,
		const color_map_type& colormap,
		const pixels::packed_pixel_layout& layout,
		const filename_type& source_name) const
	try
	{
		const auto bpp(layout.bits_per_pixel());
		const pixels::packed_pixel_converter converter;

		for (auto sequence(image.get_sequence()); !sequence.empty(); )
		{
			sequence = converter.unpack(bpp, colormap, reader.read<uint8_t>(), sequence);
		}
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file while processing uncompressed image data of `"
			+ source_name + "`");
	}

}
