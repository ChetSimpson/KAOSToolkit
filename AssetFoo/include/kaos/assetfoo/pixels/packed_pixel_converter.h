// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/colors/color_map.h>
#include <kaos/core/types/rgba_color.h>
#include <span>


namespace hypertech::kaos::assetfoo::pixels
{

	/// @brief Packed pixel converter.
	/// 
	/// This class provides the base facilities for converting between symetrically
	/// packed pixels and RGB/RGBA pixel and color formats.
	/// 
	/// \todo Add flag to all pack and unpack functions to allow partial packing and unpacking.
	///	\todo Update to pass instance of packed_pixel_layout to pack and unpack functions (should have done this in the first place!)
	class packed_pixel_converter
	{
	public:

		/// @brief Sequence type
		/// @tparam T Value the sequence is a view of.
		template<class T> using sequence_type = std::span<T>;

		/// @brief Size type
		using size_type = std::size_t;
		/// @copydoc colors::color_map
		using color_map_type = colors::color_map;
		/// @copydoc color_map_type::color_type
		using color_type = color_map_type::color_type;
		/// @brief Packed pixel type
		using packed_pixel_type = uint8_t;
		/// @brief Sequence type for packed pixel input.
		using packed_pixel_input_sequence_type = sequence_type<const packed_pixel_type>;
		/// @brief Sequence type for packed pixel output.
		using packed_pixel_output_sequence_type = sequence_type<packed_pixel_type>;
		/// @brief Sequence type for color input.
		using color_input_sequence_type = sequence_type<const color_type>;
		/// @brief Sequence type for color output.
		using color_output_sequence_type = sequence_type<color_type>;


	public:

		/// @brief Create a packed pixel converter
		packed_pixel_converter() noexcept = default;

		/// @brief Create a copy of a packed pixel converter
		/// 
		/// @param other The packed pixel converter to make a copy of
		packed_pixel_converter(const packed_pixel_converter& other) noexcept = default;

		/// @brief Create a packed pixel converter using move semantics
		/// 
		/// @param other The instance to initialize the new packed pixel converter with.
		packed_pixel_converter(packed_pixel_converter&& other) noexcept = default;


		/// @brief Convert a sequence of RGBA colors into a packed pixel
		/// 
		/// Convert a sequence of RGBA colors into a single value containing packed pixels.
		/// The result of the packing is returned in \p packed_pixels_output. The input
		/// sequence specified in \p input must have enough colors to fill the packed pixels
		/// value.
		/// 
		/// @param bits_per_pixel Number of bits per pixel
		/// @param colormap THe colormap used to translate RGBA colors to a pixel index
		/// @param input The sequence of RGBA colors to pack
		/// @param packed_pixels_output The resulting packed pixels
		/// 
		/// @return Returns a new input sequence with its beginning pointing to immediately
		/// after the last converted color element of the input seqeuence.
		color_input_sequence_type pack(
			size_type bits_per_pixel,
			const color_map_type& colormap,
			color_input_sequence_type input,
			packed_pixel_type& packed_pixels_output) const;


		/// @brief Convert a sequence of RGBA colors into a sequence of packed pixels
		/// 
		/// Converts a sequence of RGBA colors into a sequence containing packed pixels.
		/// The input sequence specified in \p input must have enough colors to fill 
		/// the packed pixels value.
		/// 
		/// @param bits_per_pixel Number of bits per pixel.
		/// @param colormap THe colormap used to translate RGBA colors to a pixel index.
		/// @param input The sequence of RGBA colors to pack.
		/// @param output The output sequence where packed pixels are stored.
		/// 
		/// @return Returns a pair of new sequences. The \p first element of the pair
		/// is a new input sequence with its beginning pointing to immediately after
		/// the last converted color element of the input seqeuence or the end of the
		/// sequence. The \p second element of the pair is a new output sequence with
		/// its beginning pointing to immediately after the last packed set of pixels
		/// or the end of the sequence.
		std::pair<color_input_sequence_type, packed_pixel_output_sequence_type>
		pack(
			size_type bits_per_pixel,
			const color_map_type& colormap,
			color_input_sequence_type input,
			packed_pixel_output_sequence_type output) const;

		/// @brief Unpack a packed pixel value to a buffer of unpacked pixel colors.
		/// 
		/// @param bits_per_pixel Number of bits per pixel.
		/// @param colormap The colormap containing a list of colors to convert the pixels to.
		/// @param packed_pixels An unsigned byte containing the packed pixels.
		/// @param output The span to write the unpacked pixels to.
		/// 
		/// @return Returns a new sequence with its beginning pointing to immediately
		/// after the last converted color element output to the seqeuence.
		color_output_sequence_type unpack(
			size_type bits_per_pixel,
			const color_map_type& colormap,
			packed_pixel_type packed_pixels,
			color_output_sequence_type output) const;

		/// @brief Unpack a packed pixel value multiple times to a buffer of unpacked pixel colors.
		/// 
		/// @param bits_per_pixel Number of bits per pixel.
		/// @param colormap The colormap containing a list of colors to convert the pixels to.
		/// @param packed_pixels An unsigned byte containing the packed pixels.
		/// @param repeat_count Number of times to unpack the pixels.
		/// @param output The span to write the unpacked pixels to.
		/// 
		/// @return Returns a new output sequence with its beginning pointing to immediately
		/// after the last converted color element output to the seqeuence.
		color_output_sequence_type unpack(
			size_type bits_per_pixel,
			const color_map_type& colormap,
			packed_pixel_type packed_pixels,
			size_type repeat_count,
			color_output_sequence_type output) const;

		/// @brief Unpack multiple packed pixel values to a buffer of unpacked pixel colors.
		/// 
		/// @param bits_per_pixel Number of bits per pixel.
		/// @param colormap The colormap containing a list of colors to convert the pixels to.
		/// @param packed_pixels A series of unsigned bytes containing the packed pixels.
		/// @param output The span to write the unpacked pixels to.
		/// 
		/// @return Returns a new output sequence with its beginning pointing to immediately
		/// after the last converted color element output to the seqeuence.
		/// 
		/// \todo This should allow returning with either the input or output reaching its
		///	end as long as there are enough output elements to consume a full packed pixel.
		color_output_sequence_type unpack(
			size_type bits_per_pixel,
			const color_map_type& colormap,
			packed_pixel_input_sequence_type packed_pixels,
			color_output_sequence_type output) const;


	protected:

		/// @brief Create a mask for the most significant pixel in a packed pixel value.
		/// 
		/// @tparam PackedPixelType_ The value type of the packed pixels.
		/// 
		/// @param bits_per_pixel Number of bits per pixel.
		/// 
		/// @return The mask of the most significant pixel in a packed pixel value.
		static packed_pixel_type make_packed_pixel_mask(size_type bits_per_pixel) noexcept;

		
	private:

		/// @brief Number of bits in a packed pixel value.
		static constexpr size_type packed_pixels_digits_ = std::numeric_limits<packed_pixel_type>::digits;
		/// @brief Maximum value a packed pixel type can hold.
		static constexpr packed_pixel_type packed_pixels_max_value_ = std::numeric_limits<packed_pixel_type>::max();
	};


	/// @brief Used to indicate that a packed pixel converter object may be "moved".
	/// 
	/// Used to indicate that a packed pixel converter object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of packed_pixel_converter
	inline packed_pixel_converter&& move(packed_pixel_converter& value)
	{
		return static_cast<packed_pixel_converter&&>(value);
	}

}
