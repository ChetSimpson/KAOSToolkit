// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/single_bitfield.h>
#include <vector>


namespace hypertech::kaos::assetfoo
{

	/// @brief Provides the base interface for packed pixel formats.
	/// 
	/// Ths class provides the base interface and information about packed
	/// pixel formats needed for conversion between pixel storage formats.
	class abstract_packed_pixel_layout
	{
	public:

		/// @brief Size type.
		using size_type = size_t;
		/// @brief Packed pixel value type.
		using packedpixelvalue_type = uint8_t;
		/// @brief Bitfield descripting a single pixel in a packed value.
		using bitfield_type = core::types::single_bitfield<packedpixelvalue_type>;
		/// @brief Container type for pixel bitfields
		using bitfieldlist_type = std::vector<bitfield_type>;


	public:

		/// @brief Create a packed pixel layout
		abstract_packed_pixel_layout() noexcept = default;

		/// @brief Create a copy of a packed pixel layout
		/// 
		/// @param other The packed pixel layout to make a copy of
		abstract_packed_pixel_layout(const abstract_packed_pixel_layout& other) noexcept = default;

		/// @brief Create a packed pixel layout using move semantics
		/// 
		/// @param other The instance to initialize the new packed pixel layout with.
		abstract_packed_pixel_layout(abstract_packed_pixel_layout&& other) noexcept = default;

		/// @brief Destructor.
		virtual ~abstract_packed_pixel_layout() noexcept = default;


		/// @brief Returns the maximum number of colors pixels per
		virtual size_type max_colors_in_pixel() const noexcept = 0;

		/// @brief Returns the number of pixels packed in a single value.
		virtual size_type pixels_per_packed_value() const noexcept = 0;

		/// @brief Returns the number of bits per pixel.
		virtual size_type bits_per_pixel() const noexcept = 0;

		/// @brief Returns a list of pixel bitfields used to shift a pixel from or to
		/// its home position.
		/// 
		/// Returns a list of pixel bitfields used to shift a pixel right from its home
		/// position to create a value of 0 to N with N being the value-1 returned from
		/// max_colors_in_pixel(). The first element in the list is the bitfield for
		/// the most significant pixel in the packed value while the last element in the
		/// list is the bitfield for the least significant pixel in the packed value.
		/// Likewise the bitfields can be used to move (shift left) a pixel value of 0
		/// to N to its home position in a packed pixel value.
		/// 
		/// @return A list of pixel bitfields.
		virtual const bitfieldlist_type& pixel_bitfields() const noexcept = 0;

		/// @brief Calculates the number of bytes required to store row of packed pixels.
		/// 
		/// @param width_in_pixels The number of pixels to store in a row of packed pixel values.
		/// @param alignment_in_bytes The number of bytes the pitch should be aligned to. Value
		/// must be a power of two.
		/// 
		/// @return The number of bytes required to store a row of packed pixels.
		/// 
		/// @exception std::invalid_argument Thrown if \p width_in_pixels is 0 or if \p alignment
		/// is 0 or not a power of two.
		virtual size_type calculate_pitch(size_type width_in_pixels, size_type alignment_in_bytes) const = 0;
	};

}
