// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/debug.h>
#include <kaos/core/types/box_iterator.h>
#include <span>
#include <stdexcept>


namespace hypertech::kaos::core::types
{

	/// @brief A simple 2 dimensional view of sequential data with dimensions and pitch/stride
	/// 
	/// This class provides a 2 dimensional view of sequential data with full iterator
	/// support, subviews, and attributs for width, height, and pitch/stride.
	/// 
	/// @tparam Type_ Element type to view.
	template<class Type_>
	class box_view
	{
	public:

		/// @brief The type of element in the sequence of rows
		using element_type		= std::span<Type_>;
		/// @brief The value type
		using value_type		= typename std::remove_cv<Type_>::type;
		/// @brief Type used to reference a size
		using size_type			= std::size_t;
		/// @brief Different type
		using difference_type	= std::ptrdiff_t;
		/// @brief Pointer type
		using pointer			= Type_*;
		/// @brief Constant pointer type
		using const_pointer		= const Type_*;
		/// @brief Reference an element_type
		using reference			= Type_&;
		/// @brief Reference a constant element_type
		using const_reference	= const Type_&;
		/// @brief Iterator whose value is element_type
		using iterator			= box_iterator<Type_>;
		//using reverse_iterator	= std::reverse_iterator<iterator>;

		/// @brief Creates an empty view.
		box_view() noexcept = default;


		/// @brief Creates a 2 dimensional view
		/// 
		/// Creates a 2 dimensional view with specified \p width, \p height, and a pitch
		/// equal to the \p width.
		/// 
		/// @param start_ptr The start of the data to view. This value cannot be null.
		/// @param width The number of elements visible on each row. This value must be greater than 0.
		/// @param height The number of rows to view. This value must be greater than 0.
		/// the value specified in \p width.
		box_view(pointer start_ptr, size_type width, size_type height) noexcept
			: box_view(start_ptr, width, height, width)
		{}

		/// @brief Creates a 2 dimensional box view
		/// 
		/// Creates a 2 dimensional box view with specified width, height, and pitch.
		/// 
		/// @param start_ptr The start of the data to view. This value cannot be null.
		/// @param width The number of elements visible on each row. This value must be greater than 0.
		/// @param height The number of rows to view. This value must be greater than 0.
		/// @param pitch The number of elements on each row. This value must be greater than or equal to
		/// the value specified in \p width.
		box_view(pointer start_ptr, size_type width, size_type height, size_type pitch) noexcept
			:
			start_pointer_(start_ptr),
			end_pointer_(start_ptr + (height * pitch)),
			width_(width),
			height_(height),
			pitch_(pitch)
		{
			KAOS_CONTAINER_VERIFY(start_pointer_, "start pointer passed to box view cannot be null");
			//KAOS_CONTAINER_VERIFY(end_ptr, "end pointer passed to box view cannot be null");
			//KAOS_CONTAINER_VERIFY(end_ptr >= start_pointer_, "end pointer passed to to box view must be greater than start pointer");
			KAOS_CONTAINER_VERIFY(width_ > 0, "width of box view must be greater than 0");
			KAOS_CONTAINER_VERIFY(height_ > 0, "height of box view must be greater than 0");
			KAOS_CONTAINER_VERIFY(pitch_ >= width_, "pitch of box view must be greater or equal to width");

			// Validate height and viewspace
			//const auto entire_view_space = (end_ptr - start_pointer_) + (pitch_ - width_);
			//KAOS_CONTAINER_VERIFY(entire_view_space % pitch_ == 0, "total elements in box view to match height and pitch");
			//KAOS_CONTAINER_VERIFY(entire_view_space / pitch_ == height_, "height of box view does not match the end pointer");
		}

		/// @brief Creates the box_view using copy semantics.
		/// 
		/// Creates the box_view with the contents of other using copy semantics.
		/// 
		/// @param other another container to be used as source to initialize the box_view with
		box_view(const box_view& other) noexcept = default;

		/// @brief Creates the box_view using copy semantics.
		/// 
		/// Creates a box_view of a const value type with the contents of a box_view of a
		/// non-const value type using copy semantics.
		/// 
		/// @param other another container to be used as source to initialize the box_view with
		box_view(const box_view<value_type>& other) noexcept requires std::is_const_v<Type_>
			:
			start_pointer_(other.start_pointer_),
			end_pointer_(other.end_pointer_),
			width_(other.width_),
			height_(other.height_),
			pitch_(other.pitch_)
		{}


		/// @brief Creates the box_view using move semantics.
		/// 
		/// Creates the box_view with the contents of other using move semantics. After
		/// the move, other is guaranteed to be empty().
		/// 
		/// @param other another container to be used as source to initialize the box_view with
		box_view(box_view&& other) noexcept
			:
			start_pointer_(other.start_pointer_),
			end_pointer_(other.end_pointer_),
			width_(other.width_),
			height_(other.height_),
			pitch_(other.pitch_)
		{
			other.start_pointer_ = nullptr;
			other.end_pointer_ = nullptr;
			other.width_ = 0;
			other.height_ = 0;
			other.pitch_ = 0;
		}


		/// @brief Replaces the contents with a copy of the contents of other.
		/// 
		/// @param other The  box_view to use as data source
		/// 
		/// @return *this
		box_view& operator=(const box_view& other) noexcept
		{
			if (this != &other)
			{
				start_pointer_ = other.start_pointer_;
				end_pointer_ = other.end_pointer_;
				width_ = other.width_;
				height_ = other.height_;
				pitch_ = other.pitch_;
			}

			return *this;
		}

		/// @brief  Replaces the contents using move semantics
		/// 
		/// Replaces the contents with those of other using move semantics (i.e. the data
		/// in other is moved from other into this container). After the move \p other
		/// other is guaranteed to be empty().
		/// 
		/// @param other The  box_view to use as data source
		/// 
		/// @return *this
		box_view& operator=(box_view&& other) noexcept
		{
			if (this != &other)
			{
				start_pointer_ = other.start_pointer_;
				end_pointer_ = other.end_pointer_;
				width_ = other.width_;
				height_ = other.height_;
				pitch_ = other.pitch_;

				other.start_pointer_ = nullptr;
				other.end_pointer_ = nullptr;
				other.width_ = 0;
				other.height_ = 0;
				other.pitch_ = 0;
			}

			return *this;
		}



		/// @brief checks if the view is empty
		/// 
		/// @return true is the view is empty; false if it is not
		[[nodiscard]] bool empty() const noexcept
		{
			return !start_pointer_;
		}

		/// @brief Returns the number of elements visible on each row.
		///
		/// The value returns by width() is guaranteed to be less than or equal to
		/// the value returned by pitch().
		/// 
		/// @return The number of elements visible on each row.
		[[nodiscard]] size_type width() const noexcept
		{
			return width_;
		}

		/// @brief Returns the number of rows in the sequence.
		/// 
		/// @return The number of row elements.
		[[nodiscard]] size_type height() const noexcept
		{
			return height_;
		}

		/// @brief Returns the number of elements on each row.
		/// 
		/// Returns the number of elements on each row. This value guaranteed to
		/// be at least the same as the value returned by width() but may be greater.
		/// 
		/// @return The number of elements on each row.
		[[nodiscard]] size_type pitch() const noexcept
		{
			return pitch_;
		}

		/// @brief Returns the total number of elements in the sequence.
		/// 
		/// @return The total number of elements in the sequence.
		[[nodiscard]] size_type count() const noexcept
		{
			return width_ * height_;
		}


		/// @brief Returns an iterator to the first row in the sequence.
		///
		/// @return Iterator to the first element.
		[[nodiscard]] iterator begin() const noexcept
		{
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			return start_pointer_
				? box_iterator<element_type::element_type>(start_pointer_, start_pointer_, end_pointer_, width_, pitch_)
				: box_iterator<element_type::element_type>();
#else
			return box_iterator<element_type::element_type>(start_pointer_, width_, pitch_);
#endif
		}

		/// @brief Returns an iterator to the end of the sequence of rows.
		///
		/// Returns an iterator to the end of the sequence of rows. If the view is
		/// empty the element referenced by the iterator is unspecified otherwise
		/// the iterator points to the last element row + 1.
		/// 
		/// @return Iterator to the element following the last element.
		[[nodiscard]] iterator end() const noexcept
		{
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			return start_pointer_
				? box_iterator<element_type::element_type>(end_pointer_, start_pointer_, end_pointer_, width_, pitch_)
				: box_iterator<element_type::element_type>();
#else
			return box_iterator<element_type::element_type>(end_pointer_, width_, pitch_);
#endif
		}


		//[[nodiscard]] reverse_iterator rbegin() const noexcept
		//{
		//	return reverse_iterator(end());
		//}

		//[[nodiscard]] reverse_iterator rend() const noexcept
		//{
		//	return reverse_iterator(begin());
		//}


		
		/// @brief Creates a subview
		/// 
		/// @param x The position of the left side within the current view used to clip the subview.
		/// @param y The position of the top side within the current view used to clip the subview.
		/// @param width The number of elements visible on each row of the subview.
		/// @param height The number of rows in the subview.
		/// 
		/// @return The new subview.
		/// 
		/// @exception std::range_error If \p width is 0
		/// @exception std::out_of_range If \p x is outside the bounds of the current view
		/// @exception std::out_of_range If the \p x position + \p width are outside the bounds of the current view
		/// @exception std::range_error If \p height is 0
		/// @exception std::out_of_range If the \p y position + \p height are outside the bounds of the current view
		/// @exception std::out_of_range If \p y is outside the bounds of the current view
		[[nodiscard]] box_view<typename element_type::element_type> subview(
			size_t x,
			size_t y,
			size_t width,
			size_t height) const
		{
			if (width == 0)
			{
				throw std::range_error("subview width cannot be 0");
			}

			if (x >= width_)
			{
				throw std::out_of_range("x position of requested subview exceeds bounds of current view");
			}

			if (x + width > width_)
			{
				throw std::out_of_range("horizontal size of requested subview exceeds bounds of current view");
			}


			if (height == 0)
			{
				throw std::range_error("subview height cannot be 0");
			}

			if (y >= height_)
			{
				throw std::out_of_range("y position of requested subview exceeds bounds of current view");
			}

			if (y + height > height_)
			{
				throw std::out_of_range("vertical size of requested subview exceeds bounds of current view");
			}

			return box_view(start_pointer_ + (y * pitch_) + x, width, height, pitch_);
		}



		/// @brief Returns the index-th row of the sequence.
		/// 
		/// The behavior is undefined if index is out of range (i.e., if it is greater than or equal to size()).
		/// 
		/// @param index the index of the row to access.
		/// 
		/// @return The index-th row of the sequence.
		[[nodiscard]] constexpr element_type operator[](const difference_type index) const noexcept
		{
			const auto address(start_pointer_ + (index * pitch_));

			KAOS_CONTAINER_VERIFY(address >= start_pointer_ && address < end_pointer_, "box view index out of range");

			return element_type(address, width_);
		}


	private:

		friend box_view<const Type_>;

		pointer		start_pointer_ = nullptr;
		pointer		end_pointer_ = nullptr;
		size_type	width_ = 0;
		size_type	height_ = 0;
		size_type	pitch_ = 0;
	};


	/// @brief Used to indicate that a box view may be "moved".
	/// 
	/// Used to indicate that a box view may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of box_view
	template<class Type_>
	box_view<Type_>&& move(box_view<Type_>& view)
	{
		return static_cast<box_view<Type_>&&>(view);
	}

}
