// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/hrs/hrs_image_format_details.h>
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <array>


namespace hypertech::kaos::assetfoo::images::hrs
{

	/// @brief Loads a HRS image
	///
	/// This class loads an uncompressed 16 color HRS format image and converts it
	/// to an RGBA image.
	class hrs_image_reader : public tc1014::tc1014_image_reader
	{
	public:

		/// @copydoc hrs_image_format_details
		using format_details = hrs_image_format_details;

		/// @brief The type of image created by the asset reader
		using image_type = images::image;


	public:

		/// @brief Create a HRS image reader
		hrs_image_reader() noexcept = default;

		/// @brief Create a copy of a HRS image reader
		/// 
		/// @param other The HRS image reader to make a copy of
		hrs_image_reader(const hrs_image_reader& other) noexcept = default;

		/// @brief Create a HRS image reader using move semantics
		/// 
		/// @param other The instance to initialize the new HRS image reader with.
		hrs_image_reader(hrs_image_reader&& other) noexcept = default;


		using tc1014_image_reader::load;

		/// @brief Loads a HRS format image from a stream.
		/// 
		/// Loads a HRS format image from the stream specified in \p input_stream.
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


	/// @brief Used to indicate that a HRS image reader object may be "moved".
	/// 
	/// Used to indicate that a HRS image reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of hrs_image_reader
	inline hrs_image_reader&& move(hrs_image_reader& value)
	{
		return static_cast<hrs_image_reader&&>(value);
	}

}
