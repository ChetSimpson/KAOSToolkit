// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/composites/object.h>
#include <kaos/core/types/dimension2.h>
#include <vector>


namespace hypertech::kaos::assetfoo::composites::objects
{

	/// @brief An polygon object with a position and list of points
	class polygon : public object
	{
	public:

		/// @brief Type container for managing the list of points
		using point_list_type = std::vector<position_type>;
		/// @brief Type represneting an unsigned size
		using size_type = point_list_type::size_type;
		/// @brief Iterator referencing a mutable point in the polygon
		using iterator = point_list_type::iterator;
		/// @brief Iterator referencing an immutable point in the polygon
		using const_iterator = point_list_type::const_iterator;


	public:

		/// @brief Create a polygon with default values for position and size.
		polygon() = default;

		/// @brief Creates a polygon
		/// 
		/// Creates a polygon with position and size with an optional name and
		/// class type.
		/// 
		/// @param name An optional name to assign to the polygon
		/// @param class_type An optional class type to assign to the polygon
		/// @param position The position of the polygon
		/// @param points A list of points relative to the \p position of the polygon
		/// 
		/// @exception std::invalid_argument If \p name contains an empty string
		/// @exception std::invalid_argument If \p class_type contains an empty string
		polygon(
			std::optional<string_type> name,
			std::optional<string_type> class_type,
			position_type position,
			point_list_type points);


		[[nodiscard]] bool operator==(const object& other) const noexcept;


		/// @brief Retrieves an iterator to the first element in the list of points
		/// 
		/// @return An iterator to the first point of the polygon
		[[nodiscard]] iterator begin() noexcept;

		/// @brief Returns a past-the-end iterator referencing a point element immediately
		/// following the last point of the polygon.
		/// 
		/// @return A past-the-end iterator for the list of points in the polygon.
		[[nodiscard]] iterator end() noexcept;


		/// @brief Retrieves an iterator to the first element in the list of points
		/// 
		/// @return An iterator to the first point of the polygon
		[[nodiscard]] const_iterator begin() const noexcept;

		/// @brief Returns a past-the-end iterator referencing a point element immediately
		/// following the last point of the polygon.
		/// 
		/// @return A past-the-end iterator for the list of points in the polygon.
		[[nodiscard]] const_iterator end() const noexcept;


		/// @brief Retrieves an iterator to the first element in the list of points
		/// 
		/// @return An iterator to the first point of the polygon
		[[nodiscard]] const_iterator cbegin() const noexcept;

		/// @brief Returns a past-the-end iterator referencing a point element immediately
		/// following the last point of the polygon.
		/// 
		/// @return A past-the-end iterator for the list of points in the polygon.
		[[nodiscard]] const_iterator cend() const noexcept;

		/// @brief Retrieves the number of points defining the polygon
		/// 
		/// @return The number of points defining the polygon
		[[nodiscard]] size_type count() const noexcept;


	private:

		point_list_type points_;
	};
}
