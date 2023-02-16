// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/core/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech::kaos::assetfoo::images::tc1014::unittests	
{

	namespace
	{
		/// @brief Image reader for TC1014 (Tandy Color Computer 3) based images
		class prot_tc1014_image_reader : public tc1014_image_reader
		{
		private:

			// NOT TESTED
			std::unique_ptr<asset> load(std::istream& input_stream) override
			{
				return {};
			}


		public:

			virtual void load_uncompressed_pixel_data(
				core::io::binary_reader& reader,
				image& image,
				const color_map_type& colormap,
				const pixels::packed_pixel_layout& layout,
				const filename_type& source_name)
			{
				source_name_ = source_name;
				return tc1014_image_reader::load_uncompressed_pixel_data(reader, image, colormap, layout);
			}
		};

		using native_color_map_type = tc1014_image_reader::native_color_map_type;
		using color_space_type = tc1014_image_reader::color_space_type;


		const tc1014_image_reader::native_color_map_type default_native_colormap_colors =
		{
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
		};


		const std::vector<tc1014_image_reader::color_type> default_colormap_colors = {
			tc1014_image_reader::color_type(0x00, 0x00, 0x00),
			tc1014_image_reader::color_type(0x00, 0x00, 0x55),
			tc1014_image_reader::color_type(0x00, 0x55, 0x00),
			tc1014_image_reader::color_type(0x00, 0x55, 0x55),
			tc1014_image_reader::color_type(0x55, 0x00, 0x00),
			tc1014_image_reader::color_type(0x55, 0x00, 0x55),
			tc1014_image_reader::color_type(0x55, 0x55, 0x00),
			tc1014_image_reader::color_type(0x55, 0x55, 0x55),
			tc1014_image_reader::color_type(0x00, 0x00, 0xAA),
			tc1014_image_reader::color_type(0x00, 0x00, 0xFF),
			tc1014_image_reader::color_type(0x00, 0x55, 0xAA),
			tc1014_image_reader::color_type(0x00, 0x55, 0xFF),
			tc1014_image_reader::color_type(0x55, 0x00, 0xAA),
			tc1014_image_reader::color_type(0x55, 0x00, 0xFF),
			tc1014_image_reader::color_type(0x55, 0x55, 0xAA),
			tc1014_image_reader::color_type(0x55, 0x55, 0xFF)
		};
	}


	TEST(test_tc1014_image_reader, load_uncompressed_pixel_data_read_past_end_of_file)
	{
		const auto colormap(std::make_unique<tc1014_image_reader::color_map_type>(default_colormap_colors));
		prot_tc1014_image_reader image_reader;
		images::image image(images::image::dimensions_type(4, 4));

		std::istringstream input;
		core::io::binary_reader reader(input);
		const auto& layout(pixels::packed_pixel_layout::BPP4);
		EXPECT_THROWS_MESSAGE(
			image_reader.load_uncompressed_pixel_data(reader, image, *colormap, layout, "<TEST>"),
			core::exceptions::file_format_error,
			"image file format error: attempt to read past end of file while processing uncompressed image data of `<TEST>`");
	}

	TEST(test_tc1014_image_reader, load_uncompressed_pixel_data)
	{
		const auto colormap(std::make_unique<tc1014_image_reader::color_map_type>(default_colormap_colors));

		prot_tc1014_image_reader image_reader;
		images::image image(images::image::dimensions_type(4, 4));

		std::istringstream input("\x01\x23\x45\x67\x89\xab\xcd\xef");
		core::io::binary_reader reader(input);

		image_reader.load_uncompressed_pixel_data(
			reader,
			image,
			*colormap,
			pixels::packed_pixel_layout::BPP4,
			"<TEST>");

		auto image_color_ptr(image.get_sequence().begin());
		for (auto i(0U); i < image.length(); ++i, ++image_color_ptr)
		{
			ASSERT_EQ(*image_color_ptr, default_colormap_colors[i]);
		}
	}

}
