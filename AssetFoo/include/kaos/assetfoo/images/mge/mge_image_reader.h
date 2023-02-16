// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/mge/mge_image_attributes.h>
#include <kaos/assetfoo/images/mge/mge_image_format_details.h>
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech::kaos::assetfoo::images::mge
{

	/// @brief Loads a ColorMax (Deluxe) MGE image
	///
	/// This class loads an MGE format image and converts it to an RGBA image.
	class mge_image_reader : public tc1014::tc1014_image_reader
	{
	public:

		/// @brief The type of image created by the asset reader
		using image_type = images::image;

		/// @brief String type used for storing the name
		using string_type = std::string;
		/// @brief Size type.
		using size_type = size_t;
		/// @brief List of attributes supported by the image reader.
		using attributes = mge_image_attributes;
		/// @brief Specifies details of the image format
		using format_details = mge_image_format_details;


	public:

		/// @brief Create a MGE image reader
		mge_image_reader() noexcept = default;

		/// @brief Create a copy of a MGE image reader
		/// 
		/// @param other The MGE image reader to make a copy of
		mge_image_reader(const mge_image_reader& other) noexcept = default;

		/// @brief Create a MGE image reader using move semantics
		/// 
		/// @param other The instance to initialize the new MGE image reader with.
		mge_image_reader(mge_image_reader&& other) noexcept = default;


		using tc1014_image_reader::load;

		/// @brief Loads an ColorMax MGE format image from a stream.
		/// 
		/// Loads a ColorMax MGE format image from the stream specified in \p input_stream.
		/// 
		/// @param input_stream The stream to load the image from.
		/// 
		/// @return A pointer to the loaded image.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		std::unique_ptr<asset> load(std::istream& input_stream) override;


	protected:

		/// @brief Loads a compressed MGE image
		/// 
		/// @param reader The binary reader the image file is attached to.
		/// @param image The RGBA image to load the converted MGE image data into
		/// @param colormap The colormap used to map color indexes to.
		/// @param layout The pixel layout of the image data
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if invalid data
		/// is encountered while decoding the image or if the decoding attemps to read past
		/// the end of the input stream.
		void load_compressed_pixel_data(
			core::io::binary_reader& reader,
			image_type& image,
			const color_map_type& colormap,
			const pixels::packed_pixel_layout& layout) const;
	};


	/// @brief Used to indicate that a MGE image reader object may be "moved".
	/// 
	/// Used to indicate that a MGE image reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of mge_image_reader
	inline mge_image_reader&& move(mge_image_reader& value)
	{
		return static_cast<mge_image_reader&&>(value);
	}

}
