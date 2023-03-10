// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/images/mge/mge_image.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace mge
{

	/// @brief Loads a ColorMax (Deluxe) MGE image
	///
	/// This class loads an MGE format image and converts it to an RGBA image.
	class mge_image_reader : public tc1014::tc1014_image_reader
	{
	protected:

		/// @brief Specifies details of the image format
		struct format_details
		{
			/// @brief List of image types supported by the MGE format
			enum class image_types
			{
				color_320x200_4bpp = 0	//!<	Specifies a 320x200 16 color (4bpp) image.
			};

			/// @brief The length of the title stored in the MGE file
			static const size_t title_length = mge_image::feature_details::max_title_length;
			/// @brief The number of colors supported.
			static const size_t colormap_length = 16;
			/// @brief The width and height of the image
			static inline const auto dimensions = mge_image::dimensions_type(320, 200);
			/// @brief Pixel layout of the image
			static const inline pixels::packed_pixel_layout& pixel_layout{ pixels::packed_pixel_layout::BPP4 };
		};

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

		/// @brief Loads a compressed MGE image
		/// 
		/// @param image The RGBA image to load the converted MGE image data into
		/// @param layout The pixel layout of the image data
		/// @param reader The binary reader the image file is attached to.
		/// @param source_name The name of the image file being loaded. This may be a filename or
		/// another name describing the source of the image such as a network stream or a memory
		/// buffer.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if invalid data
		/// is encountered while decoding the image or if the decoding attemps to read past
		/// the end of the input stream.
		void load_compressed_pixel_data(
			mge_image& image,
			const pixels::packed_pixel_layout& layout,
			core::io::binary_reader& reader,
			const filename_type& source_name) const;
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

}}}}}
