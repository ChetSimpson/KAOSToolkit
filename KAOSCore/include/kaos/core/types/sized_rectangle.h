// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/vector2.h>
#include <kaos/core/types/dimension2.h>


namespace hypertech::kaos::core::types
{

	// FIXME: This should be consolidated with `rectangle`. Maybe provide
	// helper functions for the conversion betwen two schemes.

	/// @brief A rectangle defined by a position and size.
	/// 
	/// @tparam ValueType_ The value type of the left, right, top, and
	/// bottom edges.
	template <typename ValueType_>
	class sized_rectangle
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
		constexpr sized_rectangle() noexcept = default;

		/// @brief Creates a rectangle.
		/// 
		/// Creates a rectangle at a specific position and with a specified size.
		/// 
		/// @param left The position of the left edge of the rectangle.
		/// @param top The position of the top edge of the rectangle.
		/// @param width The width of the rectangle.
		/// @param height The height of the rectangle.
		constexpr sized_rectangle(value_type left, value_type top, value_type width, value_type height) noexcept
			:
			left(left),
			top(top),
			width(width),
			height(height)
		{}

		/// @brief Creates a rectangle.
		/// 
		/// @param position The position (top and left edges) of the rectangle.
		/// @param size The size (width and height) of the rectangle.
		constexpr sized_rectangle(const position_type& position, const size_type& size) noexcept
			:
			left(position.x),
			top(position.y),
			width(size.w),
			height(size.h)
		{}

		/// @brief Converts a rectangle using a different value type of its position and size.
		/// 
		/// @tparam OtherValueType_ The rectangle to convert.
		/// 
		/// @param rectangle An instance of the other rectangle.
		template <typename OtherValueType_>
		constexpr explicit sized_rectangle(const sized_rectangle<OtherValueType_>& rectangle) noexcept
			:
			left(static_cast<value_type>(rectangle.left)),
			top(static_cast<value_type>(rectangle.top)),
			width(static_cast<value_type>(rectangle.width)),
			height(static_cast<value_type>(rectangle.height))
		{}

		/// @brief Check for equality of two rectangles.
		/// 
		/// @param other the rectangle to compare against.
		/// 
		/// @return `true` if the rectangles are the same; `false` otherwise.
		constexpr bool operator==(const sized_rectangle& other) const noexcept = default;

		/// @brief Check for inequality of two rectangles.
		/// 
		/// @param other the rectangle to compare against.
		/// 
		/// @return `true` if the rectangles are not the same; `false` otherwise.
		constexpr bool operator!=(const sized_rectangle& other) const noexcept = default;

		/// @brief Determines if a point is inside the rectangle.
		/// 
		/// @param x The x position of the point.
		/// @param y The y position of the point.
		/// 
		/// @return `true` is the point is inside the rectangle; `false` otherwise.
		constexpr bool contains(value_type x, value_type y) const noexcept
		{
			// Rectangles with negative dimensions are allowed, so we must handle them correctly

			// Compute the real min and max of the rectangle on both axes
			const auto minX(std::min(left, static_cast<value_type>(left + width)));
			const auto maxX(std::max(left, static_cast<value_type>(left + width)));
			const auto minY(std::min(top, static_cast<value_type>(top + height)));
			const auto maxY(std::max(top, static_cast<value_type>(top + height)));

			return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
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

		/// @brief Determines if two rectangles intersect.
		/// 
		/// @param rectangle The rectangle to intersect against.
		/// 
		/// @return `true` if this rectangle intersects with `rectangle`; `false` otherwise.
		constexpr bool intersects(const sized_rectangle<value_type>& rectangle) const noexcept
		{
			sized_rectangle<value_type> intersection;

			return intersects(rectangle, intersection);
		}

		/// @brief Determines if two rectangles intersect.
		/// 
		/// @param rectangle The rectangle to intersect against.
		/// @param intersection If the function returns `true` this is set to the area
		/// the two tectangles intersect.
		/// 
		/// @return `true` if this rectangle intersects with `rectangle`; `false` otherwise.
		constexpr bool intersects(
			const sized_rectangle<value_type>& rectangle,
			sized_rectangle<value_type>& intersection) const noexcept
		{
			// Rectangles with negative dimensions are allowed, so we must handle them correctly

			// Compute the min and max of the first rectangle on both axes
			const auto r1MinX(std::min(left, static_cast<value_type>(left + width)));
			const auto r1MaxX(std::max(left, static_cast<value_type>(left + width)));
			const auto r1MinY(std::min(top, static_cast<value_type>(top + height)));
			const auto r1MaxY(std::max(top, static_cast<value_type>(top + height)));

			// Compute the min and max of the second rectangle on both axes
			const auto r2MinX(std::min(rectangle.left, static_cast<value_type>(rectangle.left + rectangle.width)));
			const auto r2MaxX(std::max(rectangle.left, static_cast<value_type>(rectangle.left + rectangle.width)));
			const auto r2MinY(std::min(rectangle.top, static_cast<value_type>(rectangle.top + rectangle.height)));
			const auto r2MaxY(std::max(rectangle.top, static_cast<value_type>(rectangle.top + rectangle.height)));

			// Compute the intersection boundaries
			const auto interLeft(std::max(r1MinX, r2MinX));
			const auto interTop(std::max(r1MinY, r2MinY));
			const auto interRight(std::min(r1MaxX, r2MaxX));
			const auto interBottom(std::min(r1MaxY, r2MaxY));

			// If the intersection is valid (positive non zero area), then there is an intersection
			if ((interLeft < interRight) && (interTop < interBottom))
			{
				intersection = sized_rectangle<value_type>(interLeft, interTop, interRight - interLeft, interBottom - interTop);

				return true;
			}

			intersection = sized_rectangle<value_type>();

			return false;
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
			return size_type(width, height);
		}


	public:

		value_type left = value_type();   //!< Left coordinate of the rectangle
		value_type top = value_type();    //!< Top coordinate of the rectangle
		value_type width = value_type();  //!< Width of the rectangle
		value_type height = value_type(); //!< Height of the rectangle
	};

	using i64_sized_rectangle = sized_rectangle<int64_t>;
	using u64_sized_rectangle = sized_rectangle<uint64_t>;
	using f32_sized_rectangle = sized_rectangle<float>;
	using d64_sized_rectangle = sized_rectangle<double>;

}
