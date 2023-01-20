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

		const auto native_color_space(color_space_type::composite);
		const auto native_color_map(reader.read_vector<native_packed_color_type>(format_details::colormap_length));
		const auto colormap(color_converter().create_colormap(native_color_space, native_color_map));

		auto image(std::make_unique<image_type>(format_details::dimensions));

		load_uncompressed_pixel_data(reader, *image, *colormap, format_details::pixel_layout, source_name);

		image->set_property(properties::native_color_space, native_color_space);
		image->set_property(properties::native_color_map, native_color_map);

		return image;
	}
	catch (core::exceptions::end_of_file_error&)
	{
		throw core::exceptions::file_format_error(
			"image file format error: attempt to read past end of file `" + source_name + "`");
	}

}
