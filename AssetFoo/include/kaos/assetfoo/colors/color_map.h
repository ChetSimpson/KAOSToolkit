// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset.h>
#include <kaos/core/types/rgba_color.h>
#include <vector>
#include <functional>
#include <optional>


namespace hypertech::kaos::assetfoo::colors
{

	/// @brief A collection of colors that can be accessed individually by index.
	///
	/// A general colormap containing a collection of RGBA colors with configurable
	/// max color limit, searching, adding, and iteration support.
	/// 
	/// \todo add insertion by position and erasure
	class color_map final : public asset
	{
	public:

		/// @brief Color value type.
		using color_type = core::types::rgba_color;
		/// @brief Collection type used for managing the list of colors.
		using collection_type = std::vector<color_type>;
		/// @brief Size type
		using size_type = collection_type::size_type;
		/// @brief Type of the value managed by collection_type (should be same as color_type)
		using value_type = collection_type::value_type;
		/// @brief Reference to the value type managed by collection_type.
		using reference = collection_type::reference;
		/// @brief Constant reference to the value type managed by collection_type.
		using const_reference = collection_type::const_reference;
		/// @brief Iterator type used to iterate the values managed in an instance of collection_type
		using iterator = collection_type::iterator;
		/// @brief Constant iterator type used to iterate the values managed in an instance of collection_type
		using const_iterator = collection_type::const_iterator;
		/// @brief Predicate function used for matching colors managed in the color_map.
		using predicate_type = std::function<bool(const_reference)>;


	public:

#pragma region Construction
		/// @brief Creats an empty colormap.
		///
		/// Creates an empty colormap with no limit on the number of colors it can contain.
		color_map();

		/// @brief Construct an empty colormap with a limit to the number of colors it can contain.
		/// 
		/// @param initial_color_count The initial number of colors allocated in the colormap. The colors are
		/// initialized with the value passed in \p default_color
		/// @param default_color The color used to initialize the initial colors of the colormap.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		explicit color_map(
			size_type initial_color_count,
			color_type default_color = color_type());

		/// @brief Construct an empty colormap with a limit to the number of colors it can contain.
		/// 
		/// @param initial_color_count The initial number of colors allocated in the colormap. The colors are
		/// initialized with the value passed in \p default_color
		/// @param max_color_count Specifies the maximum number of colors the colormap can contain.
		/// @param default_color The color used to initialize the initial colors of the colormap.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		explicit color_map(
			size_type initial_color_count,
			size_type max_color_count,
			color_type default_color = color_type());

		/// @brief Creates a colormap with a list of colors and no limit on the number of colors
		/// the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		explicit color_map(collection_type colors) noexcept;

		/// @brief Creates a colormap with a list of colors and a specific limit on the number of
		/// colors the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		/// @param max_color_count Specifies the maximum number of colors the colormap can contain.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		/// @exception std::length_error Thrown if the number of colors in \p colors is greater
		/// then the number of colors specified in \p max_color_count
		color_map(collection_type colors, size_type max_color_count);

		/// @brief Creates a colormap with a list of colors and no limit on the number of colors
		/// the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		explicit color_map(const std::initializer_list<color_type>& colors);

		/// @brief Creates a colormap with a list of colors and a specific limit on the number of
		/// colors the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		/// @param max_color_count Specifies the maximum number of colors the colormap can contain.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		/// @exception std::length_error Thrown if the number of colors in \p colors is greater
		/// then the number of colors specified in \p max_color_count
		color_map(const std::initializer_list<color_type>& colors, size_type max_color_count);

		/// @brief Creates a copy of an existing color_map
		/// 
		/// @param other The instance of color_map to copy to the newly created instance of color_map.
		color_map(const color_map& other) = default;

		/// @brief Create a color_map using move semantics.
		/// 
		/// Createa a color_map by moving the contents of another color_map specified
		/// in \p other using move semantics. After the new color_map has been created
		/// the color_map specified by \p other is left in a default empty state.
		/// 
		/// \todo We should probably reset other.max_colors_ to a default on a move
		/// 
		/// @param other The instance of color_map to move into the newly created instance of color_map.
		color_map(color_map&& other) noexcept = default;
#pragma endregion


#pragma region Assignment
		/// @brief Copy assignment operator.
		/// 
		/// \todo We should probably allow copy assignment on this type
		/// 
		/// @param other The instance of color_map to copy into this instance of color_map.
		/// 
		/// @return A reference to this instance of the colormap.
		color_map& operator=(const color_map& other) = delete;

		/// @brief Move assignment operator.
		/// 
		/// \todo We should probably allow move assignment on this type
		/// 
		/// @param other The instance of color_map to move into this instance of color_map.
		/// 
		/// @return A reference to this instance of the colormap.
		color_map& operator=(color_map&& other) noexcept = delete;
#pragma endregion


#pragma region Element Access
		///	Retrieves a reference to the color at the specified position with bounds
		///	checking.
		/// 
		///	@param	position	Position of the color to retrieve.
		///
		///	@return A reference to an instance of the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		reference at(size_type position);

		///	@brief	Retrieves a const reference to the color at the specified position
		/// 
		///	@param	position	Position of the color to retrieve.
		/// 
		///	@return A const reference to the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		const_reference at(size_type position) const;

		///	Retrieves a reference to the color at the specified position with bounds
		///	checking.
		/// 
		///	@param	position	Position of the color to retrieve.
		///
		///	@return A reference to an instance of the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		reference operator[](size_type position);

		///	@brief	Retrieves a const reference to the color at the specified position
		/// 
		///	@param	position	Position of the color to retrieve.
		/// 
		///	@return A const reference to the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		const_reference operator[](size_type position) const;
#pragma endregion


#pragma region Iterators
		/// @brief Returns an iterator that addresses the first color element in the color_map.
		/// 
		/// @return A random-access iterator that points at the first color element of the
		/// color_map, or the location just beyond the end of an empty color_map.
		iterator begin() noexcept;

		/// @brief Returns a const iterator that addresses the first color element in the color_map.
		/// 
		/// @return A const random-access iterator that points at the first color element of the
		/// color_map, or the location just beyond the end of an empty color_map.
		const_iterator begin() const noexcept;

		/// @brief Returns a const iterator that addresses the first color element in the color_map.
		/// 
		/// @return A const random-access iterator that points at the first color element of the
		/// color_map, or the location just beyond the end of an empty color_map.
		const_iterator cbegin() const noexcept;


		/// @brief Returns a past-the-end iterator that points to the color element following
		/// the last colorelement of the color_map.
		/// 
		/// @return A past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		iterator end() noexcept;

		/// @brief Returns a const past-the-end iterator that points to the color element following
		/// the last colorelement of the color_map.
		/// 
		/// @return A const past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		const_iterator end() const noexcept;

		/// @brief Returns a const past-the-end iterator that points to the color element following
		/// the last colorelement of the color_map.
		/// 
		/// @return A const past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		const_iterator cend() const noexcept;
#pragma endregion


#pragma region Capacity
		/// @brief Tests if the color_map is empty.
		/// 
		/// @return true if the color_map is empty; false if the color_map isn't empty.
		bool empty() const noexcept;

		///	@brief	Retrieves the number of elements in the colormap
		/// 
		///	@return	The number of color elements in the colormap</returns>
		size_type size() const noexcept;

		/// @brief Returns the number of elements that the colormap currently has
		/// allocated space for.
		/// 
		/// @return Capacity of the currently allocated storage.
		size_type capacity() const noexcept;

		///	@brief	Retrieves the maximum number of elements allowed in the color_map
		/// 
		///	@return	The maximum number of color elements allowed in the colormap
		size_type max_size() const noexcept;
#pragma endregion


#pragma region Modifiers and operations
		/// @brief Erases all elements from the colormap.
		/// 
		/// Erases all elements from the colormap. After this call, size() returns zero.
		/// 
		/// Invalidates any references, pointers, or iterators referring to contained elements.
		/// Any past-the-end iterators are also invalidated.  
		void clear() noexcept;

		///	@brief	Adds a color to the colormap.
		///
		///	Adds a color to the colormap and returns the position of the new entry. If
		/// the color already exists in the colormap the position of the existing color
		/// is returned.
		/// 
		/// If the new size() is greater than capacity() then all iterators and references
		/// (including the past-the-end iterator) are invalidated. Otherwise only the
		/// past-the-end iterator is invalidated.
		///
		///	@return	The position of the color
		///
		///	@exception std::length_error if adding the color would cause the colormap
		///	to exceed the maximum number of allowed colors.
		size_type add(const_reference color);

		///	@brief	Adds a color to the colormap only if the color does not already exist.
		///
		///	Adds a color to the colormap and returns the position of the new entry. If
		///	the color already exists in the colormap the position of the existing color
		///	is returned.
		///
		/// If the new size() is greater than capacity() then all iterators and references
		/// (including the past-the-end iterator) are invalidated. Otherwise only the
		/// past-the-end iterator is invalidated.
		///
		///	@return	The position of the color added.
		///
		///	@exception std::length_error if adding the color would cause the colormap
		///	to exceed the maximum number of allowed colors. This exception is only
		///	thrown if the color does not already exist in the colormap.
		size_type add_unique(const_reference color);

		///	Sets the color at the specified position.
		/// 
		///	@param	position	Position of the color to set.
		///	@param	color		A reference to the color to add.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		void set(size_type position, const_reference color);
#pragma endregion


#pragma region Search
		/// @brief Returns the position of a specified color.
		///
		/// @param color A reference to the color to retrieve the position of.
		/// 
		/// @return The position in the color_map of the specified color or no
		/// value if the color does not exist in the colormap.
		std::optional<size_type> index_of(const_reference color) const noexcept;

		/// @brief Returns the position of a specified color.
		///
		/// @param predicate A predicate function used to match the color value
		/// being searched for.
		/// 
		/// @return The position in the color_map of the specified color or no
		/// value if the color does not exist in the colormap.
		std::optional<size_type> index_of(const predicate_type& predicate) const noexcept;
#pragma endregion


	private:

		/// @brief Maximum number of colors the colormap can contain or 0 if the
		/// colormap can contain the maximum allowed by collection_type.
		/// 
		/// \todo make non-const to allow copy and move assignment!
		const size_type max_colors_;	
		/// @brief The colormap colors
		collection_type	colors_;
	};


	/// @brief Used to indicate that a color map object may be "moved".
	/// 
	/// Used to indicate that a color map object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of color_map
	inline color_map&& move(color_map& value)
	{
		return static_cast<color_map&&>(value);
	}

}
