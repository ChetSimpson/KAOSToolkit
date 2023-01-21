// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::rat
{

	/// @brief Loads a Rat Graphics Package RAT image
	class rat_image_reader : public tc1014::tc1014_image_reader
	{
	public:

		/// @brief The type of image created by the asset reader
		using image_type = images::image;

		/// @brief Specifies details of the image format
		struct format_details
		{
			/// @brief The number of colors supported.
			static const size_t colormap_length = 16;
			/// @brief The width and height of the image
			static inline const auto dimensions = image::dimensions_type(320, 199);
			/// @brief Pixel layout of the image
			static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
		};

		/// @brief List of attributes supported by the image reader.
		struct attributes : tc1014_image_reader::attributes
		{
			/// @brief Attribute definition for image title
			static const attribute_definition<color_type> background_color;
		};
		

	public:

		/// @brief Create a RAT image reader
		rat_image_reader() noexcept = default;

		/// @brief Create a copy of a RAT image reader
		/// 
		/// @param other The RAT image reader to make a copy of
		rat_image_reader(const rat_image_reader& other) noexcept = default;

		/// @brief Create a RAT image reader using move semantics
		/// 
		/// @param other The instance to initialize the new RAT image reader with.
		rat_image_reader(rat_image_reader&& other) noexcept = default;


		using tc1014_image_reader::load;

		/// @brief Loads an Rat Graphics Package RAT format image from a stream.
		/// 
		/// Loads a Rat Graphics Package RAT format image from the stream specified in \p input_stream.
		/// 
		/// @param input_stream The stream to load the image from.
		/// @param source_name The name of the image file being loaded. This may be a filename or
		/// another name describing the source of the image such as a network stream or a memory
		/// buffer.
		/// 
		/// @return A pointer to the loaded image.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		std::unique_ptr<asset> load(
			std::istream& input_stream,
			const filename_type& source_name) override;


	protected:

		/// @brief Loads a compressed RAT image
		/// 
		/// @param reader The binary reader the image file is attached to.
		/// @param image The RGBA image to load the converted RAT image data into
		/// @param colormap The colormap used to map color indexes to.
		/// @param layout The pixel layout of the image data
		/// @param escape_value The compression escape value used to detect compressed RLE pairs
		/// @param source_name The name of the image file being loaded. This may be a filename or
		/// another name describing the source of the image such as a network stream or a memory
		/// buffer.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if invalid data
		/// is encountered while decoding the image or if the decoding attemps to read past
		/// the end of the input stream.
		void load_compressed_pixel_data(
			core::io::binary_reader& reader,
			image_type& image,
			const color_map_type& colormap,
			const pixels::packed_pixel_layout& layout,
			uint8_t escape_value,
			const filename_type& source_name) const;
	};


	/// @brief Used to indicate that a RAT image reader object may be "moved".
	/// 
	/// Used to indicate that a RAT image reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of rat_image_reader
	inline rat_image_reader&& move(rat_image_reader& value)
	{
		return static_cast<rat_image_reader&&>(value);
	}

}
