// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <limits>
#include <cstdint>


namespace hypertech::kaos::core::types
{

	/// @brief Represents a RGB (red, green, blue) color.
	struct rgb_color final
	{
	public:

		/// @brief The type representing values used in RGB color components.
		using component_value_type = uint8_t;

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
		/// Creates an instance of rgb_color with the red, green, and blue color components set 
		/// to 0 and the alpha component to fully opague.
		rgb_color() noexcept
			: rgb_color(0, 0, 0)
		{}

		/// @brief Creates a rgb_color from the three RGB component (red, green, and blue) values.
		/// 
		/// Creates an instance of rgb_color with the specified red, green, blue color component
		/// values and the alpha component set to fully opague.
		/// 
		/// @param red Specifies the red component value of the color.
		/// @param green Specifies the green component value of the color.
		/// @param blue Specifies the blue component value of the color.
		rgb_color(
			component_value_type red,
			component_value_type green,
			component_value_type blue) noexcept
			: r(red), g(green), b(blue)
		{}


		/// @brief Copy constructor
		/// 
		/// @param other The instance of rgb_color to copy the contents of into this
		/// instance of rgb_color.
		rgb_color(const rgb_color& other) noexcept = default;

		/// @brief Move constructor
		/// 
		/// @param other The instance of rgb_color to move the conents of into this
		/// instance of rgb_color.
		rgb_color(rgb_color&& other) noexcept = default;

		/// @brief Replaces the color components of the rgb_color with a copy of
		/// another rgb_color.
		/// 
		/// @param other The rgb_color being copied into this rgb_color.
		/// 
		/// @return A reference to the rgb_color being copied to.
		rgb_color& operator=(const rgb_color& other) noexcept = default;

		/// @brief Replaces the color components of the rgb_color with a copy of
		/// another rgb_color.
		/// 
		/// @param other The rgb_color being moveid into this rgb_color.
		/// 
		/// @return A reference to the rgb_color being moved to.
		rgb_color& operator=(rgb_color&& other) noexcept = default;

		/// @brief Tests if this rgb_color object is equal to the rgb_color on the
		/// right side an expression.
		/// 
		/// @param other The other instance of rgb_color to compare to.
		/// @return true if the colors are equal; false if the colors are not equal.
		bool operator==(const rgb_color& other) const noexcept = default;

		/// @brief Tests if this rgb_color object is not equal to the rgb_color on the
		/// right side an expression.
		/// 
		/// @param other The other instance of rgb_color to compare to.
		/// @return true if the colors are not equal; false if the colors are equal.
		bool operator!=(const rgb_color& other) const noexcept = default;


	public:

		component_value_type r;	//!<	The red component value of the color
		component_value_type g;	//!<	The green component value of the color
		component_value_type b;	//!<	The blue component value of the color
	};

}
