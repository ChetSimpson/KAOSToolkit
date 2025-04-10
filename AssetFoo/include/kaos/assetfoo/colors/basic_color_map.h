// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/colors/basic_color_map.h>
#include <kaos/assetfoo/asset.h>
#include <array>
#include <vector>
#include <functional>
#include <optional>
#include <stdexcept>


namespace hypertech::kaos::assetfoo::colors
{

	//	FIXME: The docs need to be reviewed

	template<class ColorType_, size_t FixedSize_ = 0>
	class basic_color_map;

	/// @brief A collection of colors that can be accessed individually by index.
	///
	/// A general colormap containing a collection of RGBA colors with configurable
	/// max color limit, searching, adding, and iteration support.
	/// 
	/// \todo add insertion by position and erasure
	template<class ColorType_, size_t FixedSize_>
	class basic_color_map final : public asset
	{
	public:

		/// @brief Color value type.
		using color_type = ColorType_;
		/// @brief Collection type used for managing the list of colors.
		using collection_type = std::array<color_type, FixedSize_>;
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
		/// @brief Predicate function used for matching colors managed in the basic_color_map.
		using predicate_type = std::function<bool(const_reference)>;


	public:

#pragma region Construction
		/// @brief Creats an empty colormap.
		///
		/// Creates an empty colormap with no limit on the number of colors it can contain.
		basic_color_map() = default;


		/// @brief Construct an empty colormap.
		/// 
		/// @param default_color The color used to initialize the initial colors of the colormap.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		explicit basic_color_map(color_type default_color)
		{
			colors_.fill(default_color);
		}


		/// @brief Creates a colormap with a list of colors and no limit on the number of colors
		/// the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		explicit basic_color_map(collection_type colors) noexcept
			: colors_(move(colors))
		{}


		/// @brief Creates a colormap with a list of colors and no limit on the number of colors
		/// the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		explicit basic_color_map(const std::initializer_list<color_type>& colors)
			: colors_(colors.begin(), colors.end())
		{}


		/// @brief Creates a copy of an existing basic_color_map
		/// 
		/// @param other The instance of basic_color_map to copy to the newly created instance of basic_color_map.
		basic_color_map(const basic_color_map& other) = default;

		/// @brief Create a basic_color_map using move semantics.
		/// 
		/// Createa a basic_color_map by moving the contents of another basic_color_map specified
		/// in \p other using move semantics. After the new basic_color_map has been created
		/// the basic_color_map specified by \p other is left in a default empty state.
		/// 
		/// \todo We should probably reset other.max_colors_ to a default on a move
		/// 
		/// @param other The instance of basic_color_map to move into the newly created instance of basic_color_map.
		basic_color_map(basic_color_map&& other) noexcept = default;
#pragma endregion


#pragma region Equality
		/// @brief Check for equality of two color maps.
		/// 
		/// @param other the color map to compare against.
		/// 
		/// @return `true` if the color maps are the same; `false` otherwise.
		bool operator==(const basic_color_map& other) const noexcept = default;

		/// @brief Check for inequality of two color maps.
		/// 
		/// @param other the color map to compare against.
		/// 
		/// @return `true` if the color maps are not the same; `false` otherwise.
		bool operator!=(const basic_color_map& other) const noexcept = default;
#pragma endregion


#pragma region Assignment
		/// @brief Copy assignment operator.
		/// 
		/// \todo We should probably allow copy assignment on this type
		/// 
		/// @param other The instance of basic_color_map to copy into this instance of basic_color_map.
		/// 
		/// @return A reference to this instance of the colormap.
		basic_color_map& operator=(const basic_color_map& other) = default;

		/// @brief Move assignment operator.
		/// 
		/// \todo We should probably allow move assignment on this type
		/// 
		/// @param other The instance of basic_color_map to move into this instance of basic_color_map.
		/// 
		/// @return A reference to this instance of the colormap.
		basic_color_map& operator=(basic_color_map&& other) noexcept = delete;
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
		reference at(size_type position)
		{
			return colors_.at(position);
		}

		///	@brief	Retrieves a const reference to the color at the specified position
		/// 
		///	@param	position	Position of the color to retrieve.
		/// 
		///	@return A const reference to the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		const_reference at(size_type position) const
		{
			return colors_.at(position);
		}

		///	Retrieves a reference to the color at the specified position with bounds
		///	checking.
		/// 
		///	@param	position	Position of the color to retrieve.
		///
		///	@return A reference to an instance of the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		reference operator[](size_type position)
		{
			if (position >= colors_.size())
			{
				throw std::out_of_range("Specified position is greater than the number of available colors");
			}

			return colors_[position];
		}

		///	@brief	Retrieves a const reference to the color at the specified position
		/// 
		///	@param	position	Position of the color to retrieve.
		/// 
		///	@return A const reference to the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		const_reference operator[](size_type position) const
		{
			if (position >= colors_.size())
			{
				throw std::out_of_range("Specified position is greater than the number of available colors");
			}

			return colors_[position];
		}
#pragma endregion


#pragma region Iterators
		/// @brief Returns an iterator that addresses the first color element in the basic_color_map.
		/// 
		/// @return A random-access iterator that points at the first color element of the
		/// basic_color_map, or the location just beyond the end of an empty basic_color_map.
		iterator begin() noexcept
		{
			return colors_.begin();
		}

		/// @brief Returns a const iterator that addresses the first color element in the basic_color_map.
		/// 
		/// @return A const random-access iterator that points at the first color element of the
		/// basic_color_map, or the location just beyond the end of an empty basic_color_map.
		const_iterator begin() const noexcept
		{
			return colors_.begin();
		}

		/// @brief Returns a const iterator that addresses the first color element in the basic_color_map.
		/// 
		/// @return A const random-access iterator that points at the first color element of the
		/// basic_color_map, or the location just beyond the end of an empty basic_color_map.
		const_iterator cbegin() const noexcept
		{
			return colors_.cbegin();
		}


		/// @brief Returns a past-the-end iterator that points to the color element following
		/// the last colorelement of the basic_color_map.
		/// 
		/// @return A past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		iterator end() noexcept
		{
			return colors_.end();
		}

		/// @brief Returns a const past-the-end iterator that points to the color element following
		/// the last colorelement of the basic_color_map.
		/// 
		/// @return A const past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		const_iterator end() const noexcept
		{
			return colors_.end();
		}

		/// @brief Returns a const past-the-end iterator that points to the color element following
		/// the last colorelement of the basic_color_map.
		/// 
		/// @return A const past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		const_iterator cend() const noexcept
		{
			return colors_.cend();
		}
#pragma endregion


#pragma region Capacity
		/// @brief Tests if the basic_color_map is empty.
		/// 
		/// @return true if the basic_color_map is empty; false if the basic_color_map isn't empty.
		bool empty() const noexcept
		{
			return colors_.empty();
		}

		///	@brief	Retrieves the number of elements in the colormap
		/// 
		///	@return	The number of color elements in the colormap</returns>
		size_type size() const noexcept
		{
			return colors_.size();
		}

		/// @brief Returns the number of elements that the colormap currently has
		/// allocated space for.
		/// 
		/// @return Capacity of the currently allocated storage.
		size_type capacity() const noexcept
		{
			return colors_.capacity();
		}

		///	@brief	Retrieves the maximum number of elements allowed in the basic_color_map
		/// 
		///	@return	The maximum number of color elements allowed in the colormap
		size_type max_size() const noexcept
		{
			return colors_.size();
		}
#pragma endregion


#pragma region Modifiers and operations
		///	Sets the color at the specified position.
		/// 
		///	@param	position	Position of the color to set.
		///	@param	color		A reference to the color to add.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		void set(size_type position, const_reference color)
		{
			if (position >= colors_.size())
			{
				throw std::out_of_range("Specified position is greater than the number of available colors");
			}

			colors_[position] = color;
		}
#pragma endregion


#pragma region Search
		/// @brief Returns the position of a specified color.
		///
		/// @param color A reference to the color to retrieve the position of.
		/// 
		/// @return The position in the basic_color_map of the specified color or no
		/// value if the color does not exist in the colormap.
		std::optional<size_type> index_of(const_reference color) const noexcept
		{
			const auto current_color(find(colors_.begin(), colors_.end(), color));
			if (current_color != colors_.end())
			{
				return distance(colors_.begin(), current_color);
			}

			return {};
		}

		/// @brief Returns the position of a specified color.
		///
		/// @param predicate A predicate function used to match the color value
		/// being searched for.
		/// 
		/// @return The position in the basic_color_map of the specified color or no
		/// value if the color does not exist in the colormap.
		std::optional<size_type> index_of(const predicate_type& predicate) const noexcept
		{
			const auto current_color(find_if(colors_.begin(), colors_.end(), predicate));
			if (current_color != colors_.end())
			{
				return distance(colors_.begin(), current_color);
			}

			return {};
		}
#pragma endregion


	private:

		/// @brief The colormap colors
		collection_type	colors_;
	};


	/// @brief A collection of colors that can be accessed individually by index.
	///
	/// A general colormap containing a collection of RGBA colors with configurable
	/// max color limit, searching, adding, and iteration support.
	/// 
	/// \todo add insertion by position and erasure
	template<class ColorType_>
	class basic_color_map<ColorType_, 0> final : public asset
	{
	public:

		/// @brief Color value type.
		using color_type = ColorType_;
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
		/// @brief Predicate function used for matching colors managed in the basic_color_map.
		using predicate_type = std::function<bool(const_reference)>;


	public:

#pragma region Construction
		/// @brief Creats an empty colormap.
		///
		/// Creates an empty colormap with no limit on the number of colors it can contain.
		basic_color_map()
			: max_colors_(0)
		{}


		/// @brief Construct an empty colormap with a limit to the number of colors it can contain.
		/// 
		/// @param initial_color_count The initial number of colors allocated in the colormap. The colors are
		/// initialized with the value passed in \p default_color
		/// @param default_color The color used to initialize the initial colors of the colormap.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		explicit basic_color_map(
			size_type initial_color_count,
			color_type default_color = color_type())
			:
			max_colors_(),
			colors_(initial_color_count, default_color)
		{}

		/// @brief Construct an empty colormap with a limit to the number of colors it can contain.
		/// 
		/// @param initial_color_count The initial number of colors allocated in the colormap. The colors are
		/// initialized with the value passed in \p default_color
		/// @param max_color_count Specifies the maximum number of colors the colormap can contain.
		/// @param default_color The color used to initialize the initial colors of the colormap.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		explicit basic_color_map(
			size_type initial_color_count,
			size_type max_color_count,
			color_type default_color = color_type())
			:
			max_colors_(max_color_count),
			colors_(initial_color_count > max_color_count ? 0 : initial_color_count, default_color)
		{
			if (max_colors_ == 0)
			{
				throw std::invalid_argument("Maximum number of colors passed to basic_color_map cannot be 0");
			}

			if (initial_color_count > max_color_count)
			{
				throw std::out_of_range("Initial color count in colormap cannot be greater than maximum number of colors");
			}
		}

		/// @brief Creates a colormap with a list of colors and no limit on the number of colors
		/// the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		explicit basic_color_map(collection_type colors) noexcept
			:
			max_colors_(),
			colors_(move(colors))
		{}

		/// @brief Creates a colormap with a list of colors and a specific limit on the number of
		/// colors the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		/// @param max_color_count Specifies the maximum number of colors the colormap can contain.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		/// @exception std::length_error Thrown if the number of colors in \p colors is greater
		/// then the number of colors specified in \p max_color_count
		basic_color_map(collection_type colors, size_type max_color_count)
			:
			max_colors_(max_color_count),
			colors_(move(colors))
		{
			if (max_colors_ == 0)
			{
				throw std::invalid_argument("Maximum number of colors passed to basic_color_map cannot be 0");
			}

			if (colors_.size() > max_colors_)
			{
				throw std::length_error("Number of colors in list passed to basic_color_map exceeds maximum number of colors specified");
			}
		}

		/// @brief Creates a colormap with a list of colors and no limit on the number of colors
		/// the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		explicit basic_color_map(const std::initializer_list<color_type>& colors)
			:
			max_colors_(),
			colors_(colors.begin(), colors.end())
		{}

		/// @brief Creates a colormap with a list of colors and a specific limit on the number of
		/// colors the colormap can contain.
		/// 
		/// @param colors List of initial colors for the colormap.
		/// @param max_color_count Specifies the maximum number of colors the colormap can contain.
		/// 
		/// @exception std::invalid_argument Thrown if max_color_count is zero.
		/// @exception std::length_error Thrown if the number of colors in \p colors is greater
		/// then the number of colors specified in \p max_color_count
		basic_color_map(const std::initializer_list<color_type>& colors, size_type max_color_count)
			:
			max_colors_(max_color_count),
			colors_(colors.begin(), colors.end())
		{
			if (max_colors_ == 0)
			{
				throw std::invalid_argument("Maximum number of colors passed to basic_color_map cannot be 0");
			}

			if (colors_.size() > max_colors_)
			{
				throw std::length_error("Number of colors in list passed to basic_color_map exceeds maximum number of colors specified");
			}
		}

		/// @brief Creates a copy of an existing basic_color_map
		/// 
		/// @param other The instance of basic_color_map to copy to the newly created instance of basic_color_map.
		basic_color_map(const basic_color_map& other) = default;

		/// @brief Create a basic_color_map using move semantics.
		/// 
		/// Createa a basic_color_map by moving the contents of another basic_color_map specified
		/// in \p other using move semantics. After the new basic_color_map has been created
		/// the basic_color_map specified by \p other is left in a default empty state.
		/// 
		/// \todo We should probably reset other.max_colors_ to a default on a move
		/// 
		/// @param other The instance of basic_color_map to move into the newly created instance of basic_color_map.
		basic_color_map(basic_color_map&& other) noexcept = default;
#pragma endregion


#pragma region Equality
		/// @brief Check for equality of two color maps.
		/// 
		/// @param other the colormaps to compare against.
		/// 
		/// @return `true` if the colormaps are the same; `false` otherwise.
		bool operator==(const basic_color_map& other) const noexcept
		{
			return max_colors_ == other.max_colors_ && colors_ == other.colors_;
		}

		/// @brief Check for inequality of two color maps.
		/// 
		/// @param other the colormaps to compare against.
		/// 
		/// @return `true` if the colormaps are not the same; `false` otherwise.
		bool operator!=(const basic_color_map& other) const noexcept
		{
			return max_colors_ != other.max_colors_ || colors_ != other.colors_;

		}
#pragma endregion


#pragma region Assignment
		/// @brief Copy assignment operator.
		/// 
		/// \todo We should probably allow copy assignment on this type
		/// 
		/// @param other The instance of basic_color_map to copy into this instance of basic_color_map.
		/// 
		/// @return A reference to this instance of the colormap.
		basic_color_map& operator=(const basic_color_map& other)
		{
			if (other.max_colors_ > max_colors_)
			{
				throw std::runtime_error("Cannot assign colormap. The maximum size of the destination colormap is smaller than the source.");
			}

			colors_ = other.colors_;

			return *this;
		}

		/// @brief Move assignment operator.
		/// 
		/// \todo We should probably allow move assignment on this type
		/// 
		/// @param other The instance of basic_color_map to move into this instance of basic_color_map.
		/// 
		/// @return A reference to this instance of the colormap.
		basic_color_map& operator=(basic_color_map&& other) noexcept = delete;
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
		reference at(size_type position)
		{
			return colors_.at(position);
		}

		///	@brief	Retrieves a const reference to the color at the specified position
		/// 
		///	@param	position	Position of the color to retrieve.
		/// 
		///	@return A const reference to the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		const_reference at(size_type position) const
		{
			return colors_.at(position);
		}

		///	Retrieves a reference to the color at the specified position with bounds
		///	checking.
		/// 
		///	@param	position	Position of the color to retrieve.
		///
		///	@return A reference to an instance of the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		reference operator[](size_type position)
		{
			if (position >= colors_.size())
			{
				throw std::out_of_range("Specified position is greater than the number of available colors");
			}

			return colors_[position];
		}

		///	@brief	Retrieves a const reference to the color at the specified position
		/// 
		///	@param	position	Position of the color to retrieve.
		/// 
		///	@return A const reference to the color at the specified position.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		const_reference operator[](size_type position) const
		{
			if (position >= colors_.size())
			{
				throw std::out_of_range("Specified position is greater than the number of available colors");
			}

			return colors_[position];
		}
#pragma endregion


#pragma region Iterators
		/// @brief Returns an iterator that addresses the first color element in the basic_color_map.
		/// 
		/// @return A random-access iterator that points at the first color element of the
		/// basic_color_map, or the location just beyond the end of an empty basic_color_map.
		iterator begin() noexcept
		{
			return colors_.begin();
		}

		/// @brief Returns a const iterator that addresses the first color element in the basic_color_map.
		/// 
		/// @return A const random-access iterator that points at the first color element of the
		/// basic_color_map, or the location just beyond the end of an empty basic_color_map.
		const_iterator begin() const noexcept
		{
			return colors_.begin();
		}

		/// @brief Returns a const iterator that addresses the first color element in the basic_color_map.
		/// 
		/// @return A const random-access iterator that points at the first color element of the
		/// basic_color_map, or the location just beyond the end of an empty basic_color_map.
		const_iterator cbegin() const noexcept
		{
			return colors_.cbegin();
		}


		/// @brief Returns a past-the-end iterator that points to the color element following
		/// the last colorelement of the basic_color_map.
		/// 
		/// @return A past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		iterator end() noexcept
		{
			return colors_.end();
		}

		/// @brief Returns a const past-the-end iterator that points to the color element following
		/// the last colorelement of the basic_color_map.
		/// 
		/// @return A const past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		const_iterator end() const noexcept
		{
			return colors_.end();
		}

		/// @brief Returns a const past-the-end iterator that points to the color element following
		/// the last colorelement of the basic_color_map.
		/// 
		/// @return A const past-the-end iterator for the vector. It points to the element following
		/// the last element of the vector. That element is a placeholder and shouldn't be
		/// dereferenced. Only use it for comparisons.
		const_iterator cend() const noexcept
		{
			return colors_.cend();
		}
#pragma endregion


#pragma region Capacity
		/// @brief Tests if the basic_color_map is empty.
		/// 
		/// @return true if the basic_color_map is empty; false if the basic_color_map isn't empty.
		bool empty() const noexcept
		{
			return colors_.empty();
		}

		///	@brief	Retrieves the number of elements in the colormap
		/// 
		///	@return	The number of color elements in the colormap</returns>
		size_type size() const noexcept
		{
			return colors_.size();
		}

		/// @brief Returns the number of elements that the colormap currently has
		/// allocated space for.
		/// 
		/// @return Capacity of the currently allocated storage.
		size_type capacity() const noexcept
		{
			return colors_.capacity();
		}

		///	@brief	Retrieves the maximum number of elements allowed in the basic_color_map
		/// 
		///	@return	The maximum number of color elements allowed in the colormap
		size_type max_size() const noexcept
		{
			return max_colors_ != 0 ? max_colors_ : colors_.max_size();
		}
#pragma endregion


#pragma region Modifiers and operations
		/// @brief Erases all elements from the colormap.
		/// 
		/// Erases all elements from the colormap. After this call, size() returns zero.
		/// 
		/// Invalidates any references, pointers, or iterators referring to contained elements.
		/// Any past-the-end iterators are also invalidated.  
		void clear() noexcept
		{
			return colors_.clear();
		}

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
		size_type add(const_reference color)
		{
			if (max_colors_ != 0 && colors_.size() == max_colors_)
			{
				throw std::length_error("Cannnot add color to colormap. Max colormap size reached");
			}

			colors_.emplace_back(color);

			return colors_.size() - 1;
		}

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
		size_type add_unique(const_reference color)
		{
			const auto found_color_iterator(find(colors_.begin(), colors_.end(), color));
			if (found_color_iterator != colors_.end())
			{
				return distance(colors_.begin(), found_color_iterator);
			}

			if (max_colors_ != 0 && colors_.size() == max_colors_)
			{
				throw std::length_error("Cannnot add color to colormap. Max colormap size reached");
			}

			colors_.emplace_back(color);

			return colors_.size() - 1;
		}

		///	Sets the color at the specified position.
		/// 
		///	@param	position	Position of the color to set.
		///	@param	color		A reference to the color to add.
		///
		///	@exception std::out_of_range if the specified position is not within range
		///	of the number of available colors in the colormap.
		void set(size_type position, const_reference color)
		{
			if (position >= colors_.size())
			{
				throw std::out_of_range("Specified position is greater than the number of available colors");
			}

			colors_[position] = color;
		}
#pragma endregion


#pragma region Search
		/// @brief Returns the position of a specified color.
		///
		/// @param color A reference to the color to retrieve the position of.
		/// 
		/// @return The position in the basic_color_map of the specified color or no
		/// value if the color does not exist in the colormap.
		std::optional<size_type> index_of(const_reference color) const noexcept
		{
			const auto current_color(find(colors_.begin(), colors_.end(), color));
			if (current_color != colors_.end())
			{
				return distance(colors_.begin(), current_color);
			}

			return {};
		}

		/// @brief Returns the position of a specified color.
		///
		/// @param predicate A predicate function used to match the color value
		/// being searched for.
		/// 
		/// @return The position in the basic_color_map of the specified color or no
		/// value if the color does not exist in the colormap.
		std::optional<size_type> index_of(const predicate_type& predicate) const noexcept
		{
			const auto current_color(find_if(colors_.begin(), colors_.end(), predicate));
			if (current_color != colors_.end())
			{
				return distance(colors_.begin(), current_color);
			}

			return {};
		}
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


	// FIXME: Except where there are differences this should reference
	// common docs via @copydoc

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
	template<class ColorType_, size_t Size_>
	inline basic_color_map<ColorType_, Size_>&& move(basic_color_map<ColorType_, Size_>& value)
	{
		return static_cast<basic_color_map<ColorType_, Size_>&&>(value);
	}

}
