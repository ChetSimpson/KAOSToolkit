// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/debug.h>
#include <span>


namespace hypertech { namespace kaos { namespace core { namespace types
{

	/// @brief Sequential iterator with width and stride/pitch 
	/// 
	/// This class allows iteration over rows of sequential data and is primarily
	/// intended for use with \ref box_view
	/// 
	/// @tparam Type_ Element type to iterate over
	template<class Type_>
	class box_iterator
	{
	public:

		//using iterator_concept  = std::contiguous_iterator_tag;
		//	TODO: Needs operator[]
		//using iterator_category = std::random_access_iterator_tag;

		/// @brief The sequence type
		using element_type = std::span<Type_>;
		/// @brief The type of value
		using value_type = element_type::value_type;
		/// @brief Size type
		using size_type = std::size_t;
		/// @brief Difference type
		using difference_type = std::ptrdiff_t;
		/// @brief Reference to the element_type
		using reference = element_type const&;
		/// @brief Pointer to the element type
		using pointer = element_type const*;


		/// @brief Create a default value initialized box_iterator
		box_iterator() = default;

		/// @brief Create a box_iterator.
		/// 
		/// @param current_ptr Pointer to the current/starting row of data.
		/// @param width The width of each row sequence.
		/// @param pitch The pitch of each row.
		box_iterator(
			element_type::pointer current_ptr,
	#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			element_type::pointer begin_ptr,
			element_type::pointer end_ptr,
	#endif
			size_type width,
			size_type pitch) noexcept
			:
	#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			begin_ptr_(begin_ptr),
			end_ptr_(end_ptr),
	#endif
			pitch_(pitch),
			span_(current_ptr, width)
		{
			KAOS_ITERATOR_VERIFY(
				current_ptr != nullptr,
				"starting current pointer for box iterator cannot be null");
			KAOS_ITERATOR_VERIFY(
				begin_ptr != nullptr,
				"begin pointer for box iterator cannot be null");
			KAOS_ITERATOR_VERIFY(
				end_ptr > begin_ptr,
				"end pointer is less than or equal to begin pointer for box iterator");
			KAOS_ITERATOR_VERIFY(
				width > 0,
				"width of box iterator must be greater than 0");
			KAOS_ITERATOR_VERIFY(
				pitch >= width,
				"pitch of box iterator must be greater or equal to width");
			KAOS_ITERATOR_VERIFY(
				current_ptr >= begin_ptr && current_ptr <= end_ptr,
				"current pointer is not inside the bounds of the current and end pointers");
			KAOS_ITERATOR_VERIFY(
				(current_ptr - begin_ptr) % pitch == 0,
				"current pointer is not on a row boundary");
			KAOS_ITERATOR_VERIFY(
				(end_ptr - begin_ptr) % pitch == 0,
				"size of data from beginptr to endptr must be a multiple of the pitch");
		}


		/// @brief Create a cope of a box_iterator.
		/// 
		/// @param other The box_iterator to copy from.
		box_iterator(const box_iterator& other) = default;


		/// @brief Moves the iterator forward one element.
		/// 
		/// @return *this pointing to the next element.
		constexpr box_iterator& operator++() noexcept
		{
			KAOS_ITERATOR_VERIFY(
				begin_ptr_,
				"cannot increment value-initialized box iterator");
			KAOS_ITERATOR_VERIFY(
				span_.data() < end_ptr_,
				"cannot increment box iterator past end");

			span_ = element_type(span_.data() + pitch_, span_.size());

			return *this;
		}

		/// @brief Moves the iterator forward one element.
		/// 
		/// @return An iterator pointing to the element before moving forward.
		constexpr box_iterator operator++(int) noexcept
		{
			box_iterator tmp{ *this };
			++*this;

			return tmp;
		}

		/// @brief Moves the iterator backwards one element
		/// 
		/// @return *this pointing to the next element (one backwards from original position)
		constexpr box_iterator& operator--() noexcept
		{
			KAOS_ITERATOR_VERIFY(
				begin_ptr_,
				"cannot decrement value-initialized box iterator");
			KAOS_ITERATOR_VERIFY(
				begin_ptr_ < span_.data(),
				"cannot decrement box iterator at begin");

			span_ = element_type(span_.data() - pitch_, span_.size());

			return *this;
		}

		/// @brief Moves the iterator backwards one element
		/// 
		/// @return An iterator pointing to the element before moving backwards.
		constexpr box_iterator operator--(int) noexcept
		{
			box_iterator tmp{ *this };
			--*this;

			return tmp;
		}

		/// @brief Moves the iterator forward \p offset elements.
		/// 
		/// @param offset The number of elements to move forward
		/// 
		/// @return *this pointing to the \p offet'th element.
		constexpr box_iterator& operator+=(const difference_type offset) noexcept
		{
			verify_offset(offset);

			span_ = element_type(span_.data() + (pitch_ * offset), span_.size());

			return *this;
		}

		/// @brief Returns an iterator which is advanced by \p offset or -\p offset positions respectively.
		/// 
		/// @param offset The number of positions to offset the iterator
		/// 
		/// @return A box_iterator(*this + \p offset) or box_iterator(*this - \p offset) respectively.
		[[nodiscard]] constexpr box_iterator operator+(const difference_type offset) const noexcept
		{
			return box_iterator{ *this } += offset;
		}

		/// @brief Returns an iterator which is advanced by \p offset or -\p offset positions respectively.
		/// 
		/// @param offset The number of positions to offset the iterator
		/// @param rhv The iterator to offset.
		/// 
		/// @return A box_iterator(*rhv + \p offset) or box_iterator(*rhv - \p offset) respectively.
		[[nodiscard]] friend constexpr box_iterator operator+(
			const difference_type offset,
			box_iterator rhv) noexcept	//	UNCHECKED
		{
			return rhv += offset;
		}

		/// @brief Returns an iterator which is advanced by -\p offset or \p offset positions respectively.
		/// 
		/// @param offset The number of positions to offset the iterator
		/// 
		/// @return *this
		constexpr box_iterator& operator-=(const difference_type offset) noexcept
		{
			verify_offset(-offset);

			span_ = element_type(span_.data() - (pitch_ * offset), span_.size());

			return *this;
		}

		/// @brief Returns an iterator which is advanced by -\p offset or \p offset positions respectively.
		/// 
		/// @param offset The number of positions to offset the iterator
		/// 
		/// @return An box_iterator(*this - \p offset) or box_iterator(*this + \p offset) respectively.
		[[nodiscard]] constexpr box_iterator operator-(const difference_type offset) const noexcept
		{
			return box_iterator{ *this } -= offset;
		}

		/// @brief Returns the number of rows between two iterators.
		/// 
		/// @param right The iterator on the right side of the expression.
		/// 
		/// @return The difference in the number of rows between \p right and *this.
		[[nodiscard]] constexpr difference_type operator-(const box_iterator& right) const noexcept
		{
			KAOS_ITERATOR_VERIFY(
				begin_ptr_ == right.begin_ptr_ && end_ptr_ == right.end_ptr_,
				"cannot subtract incompatible box iterators");
			KAOS_ITERATOR_VERIFY(
				span_.size() == right.span_.size() && pitch_ == right.pitch_,
				"cannot subtract incompatible box iterators");

			return (span_.data() - right.span_.data()) / pitch_;
		}


		/// @brief Compares if the position of two iterators are equal.
		/// 
		/// @param right The iterator to compare to.
		/// 
		/// @return true if the iterators are equal; false if they are not.
		[[nodiscard]] constexpr bool operator==(const box_iterator& right) const noexcept
		{
			KAOS_ITERATOR_VERIFY(
				begin_ptr_ == right.begin_ptr_ && end_ptr_ == right.end_ptr_,
				"cannot compare incompatible box iterators for equality");
			return span_.data() == right.span_.data();
		}

		/// @brief Compares if the position of two iterators are not equal.
		/// 
		/// @param right The iterator to compare to.
		/// 
		/// @return true if the iterators are not equal; false if they are equal.
		[[nodiscard]] constexpr std::strong_ordering operator<=>(const box_iterator& right) const noexcept
		{
			KAOS_ITERATOR_VERIFY(
				begin_ptr_ == right.begin_ptr_ && end_ptr_ == right.end_ptr_,
				"cannot compare incompatible box iterators");
			return span_ <=> right.span_;
		}

	
	
		/// @brief Returns a reference to the current element
		/// 
		/// @return Returns a reference to the current element
		[[nodiscard]] constexpr reference operator*() const noexcept
		{
			KAOS_ITERATOR_VERIFY(
				begin_ptr_,
				"cannot (*) dereference value-initialized box iterator");
			KAOS_ITERATOR_VERIFY(
				span_.data() < end_ptr_,
				"cannot (*) dereference ended box iterator");

			return span_;
		}

		/// @brief Returns a pointer to the current element
		/// 
		/// @return Returns a pointer to the current element
		[[nodiscard]] constexpr pointer operator->() const noexcept
		{
			KAOS_ITERATOR_VERIFY(
				begin_ptr_,
				"cannot (->) dereference value-initialized box iterator");
			KAOS_ITERATOR_VERIFY(
				span_.data() < end_ptr_,
				"cannot (->) dereference ended box iterator");

			return &span_;
		}


	private:

		constexpr void verify_offset([[maybe_unused]] const difference_type offset) const noexcept
		{
	#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			if (offset != 0)
			{
				KAOS_ITERATOR_VERIFY(
					begin_ptr_,
					"cannot seek value-initialized box iterator");
			}

			if (offset > 0)
			{
				KAOS_ITERATOR_VERIFY(
					(end_ptr_ - span_.data()) / pitch_ >= offset,
					"cannot seek box iterator after end");
			}

			if (offset < 0)
			{
				KAOS_ITERATOR_VERIFY(
					(span_.data() - begin_ptr_) / pitch_ >= -offset,
					"cannot seek box iterator before begin");
			}
	#endif
		}


	private:

		difference_type	pitch_ = 0;
		element_type	span_ = element_type();
	#ifdef KAOS_ENABLE_ITERATOR_VERIFY
		element_type::pointer	begin_ptr_ = nullptr;
		element_type::pointer	end_ptr_ = nullptr;
	#endif
	};

}}}}
