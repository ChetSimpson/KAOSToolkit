// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/mge/mge_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <kaos/core/exceptions.h>
#include <algorithm>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace tc1014
{

	void tc1014_image_reader::load_uncompressed_pixel_data(
		tc1014_image& image,
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
			sequence = converter.unpack(bpp, colormap, reader.read<uint8_t>(), sequence);
		}
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file while processing uncompressed image data of `"
			+ source_name + "`");
	}

}}}}}
