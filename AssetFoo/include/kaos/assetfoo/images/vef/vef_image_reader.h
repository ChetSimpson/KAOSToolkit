// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/vef/vef_image_format_details.h>
#include <kaos/assetfoo/images/tc1014/tc1014_image_reader.h>
#include <kaos/assetfoo/pixels/packed_pixel_layout.h>
#include <array>


namespace hypertech::kaos::assetfoo::images::vef
{

	/// @brief Loads a VEF image
	///
	/// This class loads a Color Computer 3 OS-9 Level II VEF format image and
	/// converts it to an RGBA image.
	class vef_image_reader : public tc1014::tc1014_image_reader
	{
	public:

		/// @brief Describes details of a VEF image type
		struct image_descriptor
		{
			/// @brief The width and eight in pixels of the image
			const image::dimensions_type dimensions;
			/// @brief The packed pixel layout of the image
			const pixels::packed_pixel_layout& layout;
		};

		/// @copydoc vef_image_format_details
		using format_details = vef_image_format_details;

		/// @brief The type of image created by the asset reader
		using image_type = images::image;

		/// @brief List of image types supported by the VEF format
		static const std::array<image_descriptor, 5> image_type_descriptors;


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
		/// 
		/// @return A pointer to the loaded image.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		std::unique_ptr<asset> load(std::istream& input_stream) override;


	protected:

		/// @brief Loads a compressed VEF image
		/// 
		/// @param reader The binary reader the image file is attached to.
		/// @param image The RGBA image to load the converted VEF image data into
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

}
