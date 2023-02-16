// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/images/monochrome_pattern.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::cm3
{

	/// @brief Loads a CoCoMax III CM3 image
	///
	/// This class loads an CM3 format image and converts it to an RGBA image.
	class cm3_image_reader : public tc1014::tc1014_image_reader
	{
	public:

		/// @brief The size type
		using size_type = size_t;
		/// @brief The type of image created by the asset reader
		using image_type = images::image;
		/// @brief The monochroome pixelmap pattern type.
		using pattern_type = monochrome_pattern<uint8_t, size_t>;
		/// @brief The type use for maintaining a list of monochrome pixelmap patterns.
		using pattern_list_type = std::vector<pattern_type>;
		/// @brief List of colors to cycle.
		using cycle_colors_list_type = std::vector<color_type>;

		/// @brief The number of colors supported.
		struct format_details
		{
			/// @brief The number of colors in the color map
			static const size_type color_count = 16;
			/// @brief The number of colors used for color cycling
			static const size_type cycle_color_count = 8;
			/// @brief The width of the image
			static const size_type page_width = 320;
			/// @brief The height of each image page. 
			static const size_type page_height = 192;
			/// @brief Pixel layout of the image
			static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
			/// @brief The mask for accessing the flag determining if the image is one or two pages in length
			static const uint8_t double_page_flag_mask = 0x80;
			/// @brief The mask for accessing the flag determining if the image contains editor patterns.
			static const uint8_t exclude_patterns_flag_mask = 0x01;
			/// @brief Size of the pattern section header
			static const size_type pattern_section_header_length = 3;
			/// @brief The maximum number of patterns allowed in the image
			static const size_type pattern_count = 24;
			/// @brief Mask to isolate only the bits in pattern color index that are valid.
			static const uint8_t pattern_color_index_mask = 0x0f;
			/// @brief Size of the buffer used to decompress a single row/line of the image.
			static const size_type decompression_line_buffer_size = 160;
			/// @brief Size of the horizontal bitstream used to decompress a single row/line of the image.
			static const size_type horizontal_bitstream_size_in_bytes = 20;
			/// @brief The color cycle index
			static const size_type color_cycle_index = 10;
			/// @brief The color first color index for color animation 
			static const size_type color_animation_start_index = 11;
			/// @brief The color last color index for color animation 
			static const size_type color_animation_end_index = 14;
		};

		/// @brief List of attributes supported by the image reader.
		struct attributes : tc1014_image_reader::attributes
		{
			/// @brief Attribute definition for color animation rate
			static const attribute_definition<size_type> color_animation_rate;
			/// @brief Attribute definition for first palette index for color animation
			static const attribute_definition<size_type> color_animation_start_index;
			/// @brief Attribute definition for last palette index for color animation
			static const attribute_definition<size_type> color_animation_end_index;
			/// @brief Attribute definition for the color cycling rate
			static const attribute_definition<size_type> color_cycle_rate;
			/// @brief Attribute definition for the color cycle index
			static const attribute_definition<size_type> color_cycle_index;
			///	@brief Attribute definition for color cycling color list
			static const attribute_definition<cycle_colors_list_type> color_cycle_colors;
			///	@brief Attribute definition for embedded monochrome bitmap patterns
			static const attribute_definition<pattern_list_type> patterns;
		};

	public:

		/// @brief Create a CM3 image reader
		cm3_image_reader() noexcept = default;

		/// @brief Create a copy of a CM3 image reader
		/// 
		/// @param other The CM3 image reader to make a copy of
		cm3_image_reader(const cm3_image_reader& other) noexcept = default;

		/// @brief Create a CM3 image reader using move semantics
		/// 
		/// @param other The instance to initialize the new CM3 image reader with.
		cm3_image_reader(cm3_image_reader&& other) noexcept = default;


		using tc1014_image_reader::load;

		/// @brief Loads an CocoMax III CM3 format image from a stream.
		/// 
		/// Loads a CoCoMax III CM3 format image from the stream specified in \p input_stream.
		/// 
		/// @param input_stream The stream to load the image from.
		/// 
		/// @return A pointer to the loaded image.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		std::unique_ptr<asset> load(std::istream& input_stream) override;


	protected:

		/// @brief Loads patterns from the input stream
		/// 
		/// @param colormap Colormap containing the colors the image was create with.
		/// @param reader Binary reader to read the patterns from
		/// 
		/// @return A list of patterns.
		pattern_list_type load_patterns(color_map_type colormap, core::io::binary_reader& reader) const;

		/// @brief Loads a compressed CM3 image
		/// 
		/// @param reader The binary reader the image file is attached to.
		/// @param image The RGBA image to load the converted CM3 image data into
		/// @param colormap The colormap used to map color indexes to.
		/// @param layout The pixel layout of the image data
		/// @param page_count The number of pages to load.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if invalid data
		/// is encountered while decoding the image or if the decoding attemps to read past
		/// the end of the input stream.
		void load_compressed_pixel_data(
			core::io::binary_reader& reader,
			image_type& image,
			const color_map_type& colormap,
			const pixels::packed_pixel_layout& layout,
			size_type page_count) const;

		/// @brief Loads a single compressed CM3 image page.
		/// 
		/// @param reader The binary reader the image file is attached to.
		/// @param page_view The view of the image to load the page into
		/// @param colormap The colormap used to map color indexes to.
		/// @param layout The layout of the pixelmap data
		/// @param page_index The index of the paage being loaded
		void load_page_compressed_pixel_data(
			core::io::binary_reader& reader,
			image_type::view_type page_view,
			const color_map_type& colormap,
			const pixels::packed_pixel_layout& layout,
			size_type page_index) const;
	};


	/// @brief Used to indicate that a CM3 image reader object may be "moved".
	/// 
	/// Used to indicate that a CM3 image reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of cm3_image_reader
	inline cm3_image_reader&& move(cm3_image_reader& value)
	{
		return static_cast<cm3_image_reader&&>(value);
	}

}
