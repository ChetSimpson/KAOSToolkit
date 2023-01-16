// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/png/png_image_reader.h>
#include <kaos/assetfoo/images/image.h>
#include <kaos/core/exceptions.h>
#include <lodepng/lodepng.h>
#include <istream>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace png
{

	std::unique_ptr<asset> png_image_reader::load(
		std::istream& input_stream,
		const filename_type& source_name)
	{
		auto start_position(input_stream.tellg());
		input_stream.seekg(0, std::ios::end);
		auto end_position(input_stream.tellg());
		input_stream.seekg(start_position);
		
		std::vector<uint8_t> input_buffer(boost::numeric_cast<size_t>(end_position - start_position), 0);
		if (!input_stream.read(reinterpret_cast<char*>(input_buffer.data()), input_buffer.size()))
		{
			throw core::exceptions::file_format_error("image file format error: unexpected error encountered while loading `" + source_name + "`");
		}


		uint8_t* pixel_buffer_ptr;

		unsigned width, height;
		if (lodepng_decode32(&pixel_buffer_ptr, &width, &height, input_buffer.data(), input_buffer.size()))
		{
			free(pixel_buffer_ptr);

			throw core::exceptions::file_format_error("image file format error: unexpected error encountered while decoding `" + source_name + "`");
		}

		std::vector<image::pixel_type> pixel_buffer;
		try
		{
			pixel_buffer = std::vector<image::pixel_type>(
				reinterpret_cast<image::pixel_type*>(pixel_buffer_ptr),
				reinterpret_cast<image::pixel_type*>(pixel_buffer_ptr) + size_t(width) * size_t(height));
		}
		catch (...)
		{
			free(pixel_buffer_ptr);
			throw;
		}

		free(pixel_buffer_ptr);

		return std::make_unique<image>(width, height, move(pixel_buffer));
	}

}}}}}
