// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <array>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace hrs
{

	using hrs_image = tc1014::tc1014_image;


	/// @brief Loads a HRS image
	///
	/// This class loads an uncompressed 16 color HRS format image and converts it
	/// to an RGBA image.
	class hrs_image_reader : public tc1014::tc1014_image_reader
	{
	protected:

		/// @brief Specifies details of the image format
		struct format_details
		{
			/// @brief The default number of colors in the image.
			/// 
			/// The default number of colors used by the image. HRS files always store 16 colors
			/// in the image even if the image is not a 16 color image (monochrome or 4 colors).
			static const size_t colormap_length = 16;

			/// @brief The width and height of the image
			static inline const auto dimensions = hrs_image::dimensions_type(320, 192);

			/// @brief Pixel layout of the image
			static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
		};


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

}}}}}
