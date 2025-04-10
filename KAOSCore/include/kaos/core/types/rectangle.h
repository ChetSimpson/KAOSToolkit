// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/vector2.h>
#include <kaos/core/types/dimension2.h>


namespace hypertech::kaos::core::types
{
	// FIXME: This should be renamed to something like basic_rectangle

	/// @brief A rectangle refined by left, right, top, and bottom edges.
	/// 
	/// @tparam ValueType_ The value type of the left, right, top, and
	/// bottom edges.
	template <typename ValueType_>
	class rectangle
	{
	public:

		/// @brief Type used to store the position and size values in.
		using value_type = ValueType_;
		/// @brief The type represneting the position of the rectangle.
		using position_type = ::hypertech::kaos::core::types::vector2<value_type>;
		/// @brief The type represneting the size of the rectangle.
		using size_type = ::hypertech::kaos::core::types::dimension2<value_type>;


	public:

		/// @brief Creates a rectangle at position {0,0} with a width and height of 0.
		constexpr rectangle() noexcept = default;

		/// @brief Creates a rectangle.
		/// 
		/// Creates a rectangle with an initial set of bounds.
		/// 
		/// @param left The position of the left edge of the rectangle.
		/// @param top The position of the top edge of the rectangle.
		/// @param right The position of the right edge of the rectangle.
		/// @param bottom The position of the bottom edge of the rectangle.
		constexpr rectangle(value_type left, value_type top, value_type right, value_type bottom) noexcept
			:
			left(left),
			top(top),
			right(right),
			bottom(bottom)
		{}

		/// @brief Creates a rectangle.
		/// 
		/// @param position The position (top and left edges) of the rectangle.
		/// @param size The size (width and height) of the rectangle.
		constexpr rectangle(const position_type& position, const size_type& size) noexcept
			:
			left(position.x),
			top(position.y),
			right(position.x + size.width - 1),
			bottom(position.y + size.height - 1)
		{}

		/// @brief Converts a rectangle using a different value type of its edges.
		/// 
		/// @tparam OtherValueType_ The rectangle to convert.
		/// 
		/// @param rectangle An instance of the other rectangle.
		template <typename OtherValueType_>
		constexpr explicit rectangle(const rectangle<OtherValueType_>& rectangle) noexcept
			:
			left(static_cast<value_type>(rectangle.left)),
			top(static_cast<value_type>(rectangle.top)),
			right(static_cast<value_type>(rectangle.right)),
			bottom(static_cast<value_type>(rectangle.bottom))
		{}

		/// @brief Check for equality of two rectangles.
		/// 
		/// @param other the rectangle to compare against.
		/// 
		/// @return `true` if the rectangles are the same; `false` otherwise.
		constexpr bool operator==(const rectangle& other) const noexcept = default;

		/// @brief Check for inequality of two rectangles.
		/// 
		/// @param other the rectangle to compare against.
		/// 
		/// @return `true` if the rectangles are not the same; `false` otherwise.
		constexpr bool operator!=(const rectangle& other) const noexcept = default;

		/// @brief Determines if a point is inside the rectangle.
		/// 
		/// @param x The x position of the point.
		/// @param y The y position of the point.
		/// 
		/// @return `true` is the point is inside the rectangle; `false` otherwise.
		constexpr bool contains(value_type x, value_type y) const noexcept
		{
			return x >= left && x <= right && y >= top && y <= bottom;
		}

		/// @brief Determines if a point is inside the rectangle.
		/// 
		/// @param point The position to check.
		/// 
		/// @return `true` is the point is inside the rectangle; `false` otherwise.
		constexpr bool contains(const position_type& point) const noexcept
		{
			return contains(point.x, point.y);
		}

		/// @brief Retrieves the position of the rectangle.
		/// 
		/// @return the position of the rectangle.
		constexpr position_type position() const noexcept
		{
			return position_type(left, top);
		}

		/// @brief Retrieves the size of the rectangle.
		/// 
		/// @return the size of the rectangle.
		constexpr size_type size() const noexcept
		{
			return size_type(right - left, bottom - top);
		}


	public:

		value_type left = value_type();   //!< Left coordinate of the rectangle
		value_type top = value_type();    //!< Top coordinate of the rectangle
		value_type right = value_type();  //!< Right coordinate of the rectangle
		value_type bottom = value_type(); //!< Bottom coordinate of the rectangle
	};

	using i64_rectangle = rectangle<int64_t>;
	using u64_rectangle = rectangle<uint64_t>;
	using f32_rectangle = rectangle<float>;
	using d64_rectangle = rectangle<double>;

}
