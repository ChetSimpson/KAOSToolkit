// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <limits>
#include <cstdint>


namespace hypertech { namespace kaos { namespace core { namespace types
{

	/// @brief Represents a RGBA (red, green, blue, alpha) color.
	struct rgba_color final
	{
	public:

		/// @brief The type representing values used in RGBA color components.
		using component_value_type = uint8_t;
		/// @brief Unsigned integer used to represent a packed RGBA color.
		using unsigned_packed_color_type = uint32_t;
		/// @brief Signed integer used to represent a packed RGBA color.
		using signed_packed_color_type = int32_t;

		/// @brief Returns the maximum value of a color component.
		/// 
		/// @return The maximum value of a color component.
		static constexpr component_value_type max_component_value() noexcept
		{
			return std::numeric_limits<component_value_type>::max();
		}

		/// @brief Returns the maximum value of a color component.
		/// 
		/// @tparam Type_ The type to return the value as.
		/// 
		/// @return The maximum value of a color component.
		template<class Type_>
		static constexpr Type_ max_component_value_as() noexcept
		{
			return Type_(std::numeric_limits<component_value_type>::max());
		}


	public:

		/// @brief Creates a color.
		///
		/// Creates an instance of rgba_color with the red, green, and blue color components set 
		/// to 0 and the alpha component to fully opague.
		rgba_color() noexcept
			: rgba_color(0, 0, 0)
		{}

		/// @brief Creates a rgba_color from the three RGB component (red, green, and blue) values.
		/// 
		/// Creates an instance of rgba_color with the specified red, green, blue color component
		/// values and the alpha component set to fully opague.
		/// 
		/// @param red Specifies the red component value of the color.
		/// @param green Specifies the green component value of the color.
		/// @param blue Specifies the blue component value of the color.
		rgba_color(
			component_value_type red,
			component_value_type green,
			component_value_type blue) noexcept
			: rgba_color(red, green, blue, max_component_value())
		{}


		/// @brief Creates a rgba_color from the three RGBA component (red, green, blue, and alpha) values.
		/// 
		/// Creates an instance of rgba_color with the specified red, green, blue, and alpha color
		/// component values.
		/// 
		/// @param red Specifies the red component value of the color.
		/// @param green Specifies the green component value of the color.
		/// @param blue Specifies the blue component value of the color.
		/// @param alpha Specifies the alpha component value of the color.
		rgba_color(
			component_value_type red,
			component_value_type green,
			component_value_type blue,
			component_value_type alpha) noexcept
			: R(red), G(green), B(blue), A(alpha)
		{}

		
		/// @brief Create a color from a packed RGBA value
		/// 
		/// Creates an instance of rgba_color with red, green, blue, and alpha color
		/// component values packed in an unsigned integer.
		/// 
		/// @param packedvalue The unsigned integer value containing the packed
		/// R, G, B, and A component values.
		explicit rgba_color(const unsigned_packed_color_type& packedvalue) noexcept
			:
			R((packedvalue >> 24) & 0xff),
			G((packedvalue >> 16) & 0xff),
			B((packedvalue >> 8) & 0xff),
			A((packedvalue >> 0) & 0xff)
		{}

		
		/// @brief Create a color from a packed RGBA value
		/// 
		/// Creates an instance of rgba_color with red, green, blue, and alpha color
		/// component values packed in a signed integer.
		/// 
		/// @param packedvalue The signed integer value containing the packed
		/// R, G, B, and A component values.
		explicit rgba_color(const signed_packed_color_type& packedvalue) noexcept
			:
			R((packedvalue >> 24) & 0xff),
			G((packedvalue >> 16) & 0xff),
			B((packedvalue >> 8) & 0xff),
			A((packedvalue >> 0) & 0xff)
		{}

		/// @brief Copy constructor
		/// 
		/// @param other The instance of rgba_color to copy the contents of into this
		/// instance of rgba_color.
		rgba_color(const rgba_color& other) noexcept = default;

		/// @brief Move constructor
		/// 
		/// @param other The instance of rgba_color to move the conents of into this
		/// instance of rgba_color.
		rgba_color(rgba_color&& other) noexcept = default;

		/// @brief Replaces the color components of the rgba_color with a copy of
		/// another rgba_color.
		/// 
		/// @param other The rgba_color being copied into this rgba_color.
		/// 
		/// @return A reference to the rgba_color being copied to.
		rgba_color& operator=(const rgba_color& other) noexcept = default;

		/// @brief Replaces the color components of the rgba_color with a copy of
		/// another rgba_color.
		/// 
		/// @param other The rgba_color being moveid into this rgba_color.
		/// 
		/// @return A reference to the rgba_color being moved to.
		rgba_color& operator=(rgba_color&& other) noexcept = default;

		/// @brief Tests if this rgba_color object is equal to the rgba_color on the
		/// right side an expression.
		/// 
		/// @param other The other instance of rgba_color to compare to.
		/// @return true if the colors are equal; false if the colors are not equal.
		bool operator==(const rgba_color& other) const noexcept
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}

		/// @brief Tests if this rgba_color object is not equal to the rgba_color on the
		/// right side an expression.
		/// 
		/// @param other The other instance of rgba_color to compare to.
		/// @return true if the colors are not equal; false if the colors are equal.
		bool operator!=(const rgba_color& other) const noexcept
		{
			return R != other.R || G != other.G || B != other.B || A != other.A;
		}

		/// @brief Converts the color to packed unsigned integer value.
		/// @return The packed color value
		unsigned_packed_color_type to_unsigned() const noexcept
		{
			return (R << 24) | (G << 16) | (B << 8) | A;
		}

		/// @brief Converts the color to packed signed integer value.
		/// @return The packed color value
		signed_packed_color_type to_signed() const noexcept
		{
			return (R << 24) | (G << 16) | (B << 8) | A;
		}

		/// @brief Returns the Hue-Saturation-Lightness (HSL) lightness for this rgba_color.
		/// 
		/// @return A value from 0.0 to 1.0 indicating the brightness of the color.
		/// 
		/// @exception std::range_error If the brightness is below 0 or greater than 1
		float brightness() const;


	public:

		component_value_type R;	//!<	The red component value of the color
		component_value_type G;	//!<	The green component value of the color
		component_value_type B;	//!<	The blue component value of the color
		component_value_type A;	//!<	The alpha component value of the color
	};

}}}}
