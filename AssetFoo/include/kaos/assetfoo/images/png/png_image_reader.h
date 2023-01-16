// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset_reader.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace png
{

	/// @brief Loads a PNG image
	///
	/// This class loads an PNG format image and converts it to an RGBA image.
	class png_image_reader : public binary_asset_reader
	{
	public:

		/// @brief Create a PNG image reader
		png_image_reader() noexcept = default;

		/// @brief Create a copy of a PNG image reader
		/// 
		/// @param other The PNG image reader to make a copy of
		png_image_reader(const png_image_reader& other) noexcept = default;

		/// @brief Create a PNG image reader using move semantics
		/// 
		/// @param other The instance to initialize the new PNG image reader with.
		png_image_reader(png_image_reader&& other) noexcept = default;


		using binary_asset_reader::load;


		/// @brief Loads a PNG format image from a stream.
		/// 
		/// Loads a PNG format image from the stream specified in \p input_stream.
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
	};


	/// @brief Used to indicate that a PNG image reader object may be "moved".
	/// 
	/// Used to indicate that a PNG image reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of png_image_reader
	inline png_image_reader&& move(png_image_reader& value)
	{
		return static_cast<png_image_reader&&>(value);
	}

}}}}}
