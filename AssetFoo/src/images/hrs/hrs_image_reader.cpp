// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/hrs/hrs_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <kaos/core/exceptions.h>
#include <utility>


namespace hypertech::kaos::assetfoo::images::hrs
{

	using core::io::binary_reader;

	std::unique_ptr<asset> hrs_image_reader::load(
		std::istream& input_stream,
		const filename_type& source_name)
	try
	{
		binary_reader reader(input_stream, binary_reader::ordering_type::big);

		const auto color_space(color_space_type::composite);
		auto native_colormap(reader.read_vector<native_packed_color_type>(format_details::colormap_length));

		auto image(std::make_unique<hrs_image>(
			format_details::dimensions,
			color_converter().create_colormap(color_space, native_colormap),
			color_space,
			native_colormap));

		load_uncompressed_pixel_data(*image, format_details::pixel_layout, reader, source_name);

		return image;
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file `" + source_name + "`");
	}

}
