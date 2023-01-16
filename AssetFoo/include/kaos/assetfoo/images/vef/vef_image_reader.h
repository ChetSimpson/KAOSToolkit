// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/vef/vef_image.h>
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <array>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace vef
{

	/// @brief Loads a VEF image
	///
	/// This class loads a Color Computer 3 OS-9 Level II VEF format image and
	/// converts it to an RGBA image.
	class vef_image_reader : public tc1014::tc1014_image_reader
	{
	protected:

		/// @brief Describes details of a VEF image type
		struct image_type_details
		{
			/// @brief The width and eight in pixels of the image
			const vef_image::dimensions_type dimensions;
			/// @brief The packed pixel layout of the image
			const pixels::packed_pixel_layout& layout;
		};

		/// @brief Specifies details of the image format
		struct format_details
		{
			/// @brief Mask to retrieve the flag indicating if the image is compressed or uncompressed.
			static const uint8_t compression_flag_mask = 0x80;
			/// @brief The default number of colors in the image.
			/// 
			/// The default number of colors used by the image. VEF files always store 16 colors
			/// in the image even if the image is not a 16 color image (monochrome or 4 colors).
			static const size_t colormap_length = 16;
			/// @brief Mask used to retrieve indicating if a scanline packet is compressed or
			/// uncompressed.
			static const size_t packet_compressed_flag_mask = 0x80;
			/// @brief Mask used to retrieve the length of the scanline packet data.
			static const size_t packet_length_mask = 0x7f;
		};

		/// @brief List of image types supported by the VEF format
		static const std::array<image_type_details, 5> image_type_descriptors;


	public:

		/// @brief Create a VEF image reader
		vef_image_reader() noexcept = default;

		/// @brief Create a copy of a VEF image reader
		/// 
		/// @param other The VEF image reader to make a copy of
		vef_image_reader(const vef_image_reader& other) noexcept = default;

		/// @brief Create a VEF image reader using move semantics
		/// 
		/// @param other The instance to initialize the new VEF image reader with.
		vef_image_reader(vef_image_reader&& other) noexcept = default;


		using tc1014_image_reader::load;

		/// @brief Loads a VEF format image from a stream.
		/// 
		/// Loads a VEF format image from the stream specified in \p input_stream.
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

		/// @brief Loads a compressed VEF image
		/// 
		/// @param image The RGBA image to load the converted VEF image data into
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
			vef_image& image,
			const pixels::packed_pixel_layout& layout,
			core::io::binary_reader& reader,
			const filename_type& source_name) const;
	};


	/// @brief Used to indicate that a VEF image reader object may be "moved".
	/// 
	/// Used to indicate that a VEF image reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of vef_image_reader
	inline vef_image_reader&& move(vef_image_reader& value)
	{
		return static_cast<vef_image_reader&&>(value);
	}

}}}}}
