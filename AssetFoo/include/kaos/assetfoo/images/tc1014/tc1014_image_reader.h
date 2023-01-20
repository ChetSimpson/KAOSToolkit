// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset_reader.h>
#include <kaos/assetfoo/images/image.h>
#include <kaos/assetfoo/colors/tc1014/tc1014_color_converter.h>
#include <kaos/assetfoo/pixels/packed_pixel_converter.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <kaos/core/io/binary_reader.h>


namespace hypertech::kaos::assetfoo::images::tc1014
{

	/// @brief Image reader for TC1014 (Tandy Color Computer 3) based images
	class tc1014_image_reader : public binary_asset_reader
	{
	public:

		/// @copydoc colors::tc1014::tc1014_color_converter::color_map_type
		using color_map_type = colors::tc1014::tc1014_color_converter::color_map_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::color_type
		using color_type = colors::tc1014::tc1014_color_converter::color_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::color_space_type
		using color_space_type = colors::tc1014::tc1014_color_converter::color_space_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::native_packed_color_type
		using native_packed_color_type = colors::tc1014::tc1014_color_converter::native_packed_color_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::native_color_map_type
		using native_color_map_type = colors::tc1014::tc1014_color_converter::native_color_map_type;

		/// @brief List of properties supported by the image reader.
		struct properties
		{
			/// @brief Property definition for native color space of image
			static const asset::property_def<color_space_type> native_color_space;
			/// @brief Property definition for native color map of image
			static const asset::property_def<native_color_map_type> native_color_map;
		};


	public:

		/// @brief Create a TC1014 based image reader
		tc1014_image_reader() noexcept = default;

		/// @brief Create a copy of a TC1014 based image reader
		/// 
		/// @param other The TC1014 based image reader to make a copy of
		tc1014_image_reader(const tc1014_image_reader& other) noexcept = default;

		/// @brief Create a TC1014 based image reader using move semantics
		/// 
		/// @param other The instance to initialize the new TC1014 based image reader with.
		tc1014_image_reader(tc1014_image_reader&& other) noexcept = default;


		using asset_reader::load;


	protected:

		/// @brief Loads a uncompressed TC1014 based image
		/// 
		/// @param reader The binary reader the image file is attached to.
		/// @param image The RGBA image to load the converted image data into
		/// @param colormap The colormap used to map color indexes to.
		/// @param layout The pixel layout of the image data
		/// @param source_name The name of the image file being loaded. This may be a filename or
		/// another name describing the source of the image such as a network stream or a memory
		/// buffer.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if invalid data
		/// is encountered while decoding the image or if the decoding attemps to read past
		/// the end of the input stream.
		virtual void load_uncompressed_pixel_data(
			core::io::binary_reader& reader,
			image& image,
			const color_map_type& colormap,
			const pixels::packed_pixel_layout& layout,
			const filename_type& source_name) const;

		/// @brief Get a reference to the color converter
		/// 
		/// Provides access to the color converter used by TC1014 based image readers.
		/// 
		/// @return A reference to the color converter..
		const colors::tc1014::tc1014_color_converter& color_converter() const
		{
			return color_converter_;
		}


	private:

		/// @brief Converter used to convert TC1014 packed colors to RGBA colors
		colors::tc1014::tc1014_color_converter color_converter_;
	};


	/// @brief Used to indicate that a TC1014 image reader object may be "moved".
	/// 
	/// Used to indicate that a TC1014 image reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of tc1014_image_reader
	inline tc1014_image_reader&& move(tc1014_image_reader& value)
	{
		return static_cast<tc1014_image_reader&&>(value);
	}

}
