// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/colors/color_layout.h>
#include <limits>
#include <memory>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors
{

	/// @brief Provides facilities for color conversion
	/// 
	/// This class provides facilities for converting colors between RGBA and
	/// packed color formats.
	class color_converter
	{
	public:

		/// @brief The color value type used for conversions to RGB.
		using color_type = core::types::rgba_color;

		/// @brief The type representing values used in RGB color components.
		using component_value_type = color_type::component_value_type;

		/// @brief The type respresenting values containing packed pixels.
		using packed_color_type = uint64_t;

		/// @copydoc color_layout::bitfield_type
		using bitfield_type = color_layout::bitfield_type;


	public:

		/// @brief Creates a color converter
		/// 
		/// @param color_format The color format used for conversion between color_type and
		/// packed_color_type.
		/// 
		/// @exception invalid_argument If \p color_format is null.
		explicit color_converter(std::shared_ptr<const color_layout> color_format);

		/// @brief Create copy of a color converter
		/// 
		/// @param other The color converter to make a copy of
		color_converter(const color_converter& other) = default;

		/// @brief Deleted move constructor
		color_converter(color_converter&&) = delete;

		/// @brief Destructor
		virtual ~color_converter() = default;

		/// @brief Get the color layout used by the converter
		/// @return A shared pointer referencing the layout used by the converter.
		std::shared_ptr<const color_layout> layout() const noexcept;

		/// @brief Converts a packed color to a common color type representation.
		/// 
		/// @param packed_color An interger value containing a packed color.
		/// 
		/// @return A common RGB representation of the packed color.
		/// 
		/// @exception hypertech::kaos::core::exceptions::packed_color_format_error Thrown if the value in
		/// packed_color contains invalid bits.
		/// @exception std::length_error Thrown if a packed component size is 0
		/// @exception std::length_error Thrown if a packed component size is greater than the unpacked component type
		/// @exception std::range_error Thrown if a packed component size is greater than the unpacked component size
		/// @exception std::range_error Thrown if a packed component cannot be scaled to fit in the unpacked component type.
		virtual color_type to_color(packed_color_type packed_color) const;

		/// @brief Converts from a common color type to a packed color value.
		/// 
		/// @param color A reference to a common color instance to convert.
		/// 
		/// @return Returns an interger value containing a packed representation of the color
		/// 
		/// @exception std::range_error Thrown if the red, green, or blue component
		/// values are not supported.
		/// @exception std::length_error Thrown if a packed component size is 0
		/// @exception std::range_error Thrown if an unpacked component cannot be converted to a packed component
		/// without loss of precision.
		/// @exception std::range_error Thrown if an packed component value is larger than a packed component type.
		virtual packed_color_type from_color(color_type color) const;

		/// @brief Creates a packed color value from specified RGB values.
		/// 
		/// @param r Red color component value.
		/// @param g Green color component value.
		/// @param b Blue color component value.
		/// 
		/// @return Returns an interger value containing a packed representation of the color
		/// 
		/// @exception std::range_error Thrown if the red, green, or blue component values
		/// are not supported.
		/// @exception std::length_error Thrown if a packed component size is 0
		/// @exception std::range_error Thrown if an unpacked component cannot be converted to a packed component
		/// without loss of precision.
		/// @exception std::range_error Thrown if an packed component value is larger than a packed component type.
		virtual packed_color_type from_rgb(
			component_value_type r,
			component_value_type g,
			component_value_type b) const;

		/// @brief Creates a packed color value from specified RGBA values.
		/// 
		/// @param r Red color component value.
		/// @param g Green color component value.
		/// @param b Blue color component value.
		/// @param a Alpha color component value.
		/// 
		/// @return Returns an interger value containing a packed representation of the color
		/// 
		/// @exception std::range_error Thrown if the red, green, blue, or alpha component values
		/// are not supported.
		/// @exception std::length_error Thrown if a packed component size is 0
		/// @exception std::range_error Thrown if an unpacked component cannot be converted to a packed component
		/// without loss of precision.
		/// @exception std::range_error Thrown if an packed component value is larger than a packed component type.
		virtual packed_color_type from_rgba(
			component_value_type r,
			component_value_type g,
			component_value_type b,
			component_value_type a) const;


		/// @brief Returns the maximum value a color component can store.
		static constexpr size_t max_component_value() noexcept
		{
			return std::numeric_limits<component_value_type>::max();
		}

		/// @brief Returns the maximum value a color component can store as a floating point value.
		template<class ReturnType_>
		static constexpr ReturnType_ max_component_value_as() noexcept
		{
			return ReturnType_(std::numeric_limits<component_value_type>::max());
		}


	protected:

		/// @copydoc color_converter::from_rgba
		virtual packed_color_type from_rgba_impl(
			component_value_type r,
			component_value_type g,
			component_value_type b,
			component_value_type a) const;

		/// @brief Extracts component from a packed color value
		///
		/// Unpacks (extracts) a color component returns a color component value from 0 to N.
		/// 
		/// @param bitfield The bitfield used to extract the packed color component.
		/// @param packed_color The packed value containing the color component to extract
		/// 
		/// @return A color component value from 0 to N.
		virtual component_value_type unpack_component_value(
			const bitfield_type& bitfield,
			packed_color_type packed_color) const;

		/// @brief Convert a component value to a packed representation.
		///
		/// @param bitfield The bitfield used to set the packed color component.
		/// @param component_value The component value to pack.
		/// 
		/// @return A packed component value.
		virtual packed_color_type pack_component_value(
			const bitfield_type& bitfield,
			component_value_type component_value) const;


	private:

		/// @brief The color format used for conversion between color_type and
		/// packed_color_type.
		std::shared_ptr<const color_layout> layout_;
	};


	/// @brief Used to indicate that a color converter object may be "moved".
	/// 
	/// Used to indicate that a color converter object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of color_converter
	inline color_converter&& move(color_converter& value)
	{
		return static_cast<color_converter&&>(value);
	}

}}}}
