// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/abstract_packed_pixel_layout.h>
#include <initializer_list>


namespace hypertech { namespace kaos { namespace assetfoo { namespace pixels
{

	/// @brief Base implementation of the packed pixel format interface
	///
	/// This class provides an implementation of the \ref abstract_packed_pixel_layout
	/// to provide information about packed pixel formats.
	class packed_pixel_layout final : public abstract_packed_pixel_layout
	{
	public:

		/// @brief Create a packed pixel layout.
		/// 
		/// @param pixel_bitfields List of bitfields used to get and set color components in a packed pixel
		/// 
		/// @exception std::invalid_argument Thrown \p pixel_bitfields is empty.
		explicit packed_pixel_layout(bitfieldlist_type pixel_bitfields);

		/// @brief Create a copy of a packed pixel layout
		/// 
		/// @param other The packed pixel layout to make a copy of
		packed_pixel_layout(const packed_pixel_layout& other) = default;

		packed_pixel_layout(packed_pixel_layout&& other) noexcept = delete;


		/// @brief Create a packed pixel format
		/// 
		/// @param bits_per_pixel The number of bits per pixel.
		/// 
		/// @exception std::range_error If \p bits_per_pixel is zero.
		/// @exception std::overflow_error If the number of bits specified in \p bits_per_pixel is larger than
		/// the total number of bits available in a packed pixel value.
		/// @exception std::range_error If the value in \p bits_per_pixel is not a power of two.
		explicit packed_pixel_layout(size_type bits_per_pixel);

		size_type max_colors_in_pixel() const noexcept override;
		size_type pixels_per_packed_value() const noexcept override;
		size_type bits_per_pixel() const noexcept override;

		const bitfieldlist_type& pixel_bitfields() const noexcept override;

		size_type calculate_pitch(size_type width_in_pixels, size_type alignment_in_bytes) const override;


	private:

		static bitfieldlist_type make_bitfields(size_type bits_per_pixel);

	public:

		/// @brief Default representation of an 8 bits per pixel packed pixel stored in a single byte
		static const packed_pixel_layout BPP8;
		/// @brief Default representation of an 4 bits per pixel packed pixel stored in a single byte
		static const packed_pixel_layout BPP4;
		/// @brief Default representation of an 2 bits per pixel packed pixel stored in a single byte
		static const packed_pixel_layout BPP2;
		/// @brief Default representation of an 1 bit per pixel packed pixel stored in a single byte
		static const packed_pixel_layout BPP1;

	private:

		const bitfieldlist_type pixel_bitfields_;	//!<	List of pixel bitfields
	};

}}}}
