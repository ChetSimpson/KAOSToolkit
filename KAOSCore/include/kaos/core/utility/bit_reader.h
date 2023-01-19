// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/exceptions.h>
#include <limits>
#include <concepts>
#include <span>
#include <stdexcept>


namespace hypertech::kaos::core::utility
{

	/// @brief Bit stream reader
	///
	/// @tparam Type_ The underlying type used by the bit stream data.
	/// 
	/// This class allows a bit stream to be opened on a range of data and bits extracted
	/// from the input stream. Input starts at the most significant bit and progresses to
	/// the least significant bit. Once the LSB is read from the input stream the bit reader
	/// advances to the next data value in the stream.
	template<std::integral Type_>
	requires (std::is_unsigned_v<Type_> && !std::is_same_v<Type_, bool>)
	class bit_reader
	{
	public:

		/// @brief The underlying data type of the input data.
		using value_type = Type_;

		/// @brief Type managing the range of input data.
		using span_type = std::span<const value_type>;

		/// @brief The highest bit available in the underlying data type of \p value_type.
		static const value_type high_bit = value_type(1) << (std::numeric_limits<value_type>::digits - 1);


	public:

		/// @brief Create an empty bit reader
		bit_reader() = default;

		/// @brief Create a bit reader
		/// 
		/// Creates a bit reader and initializes it with the \p range as its input data.
		/// 
		/// @param range Range of data to read bits from
		/// 
		/// @exception std::invalid_argument Thrown if the \p range is empty.
		bit_reader(span_type range)
			:
			range_(range),
			current_ptr_(begin(range)),
			current_bit_(range.empty() ? 0 : high_bit)
		{
			if (range.empty())
			{
				throw std::invalid_argument("attempt to create bit reader with empty range");
			}
		}


		/// @brief Checks if the bit reader is currently open
		/// @return true if the bit reader is open; false if it is closed.
		bool is_open() const
		{
			return !range_.empty();
		}


		/// @brief Returns the empty state of the bit reader.
		/// 
		/// Indicates if the bit reader has no more data to return on a call to
		/// read().
		/// 
		/// @return true if the bit reader is closed or has reached the end of the input stream;
		/// false if there is bit data still pending.
		bool empty() const
		{
			return 
				range_.empty()
				|| (current_bit_ == 0 && current_ptr_ == end(range_))
				|| (current_bit_ == 0 && (current_ptr_ + 1 == end(range_)));
		}


		/// @brief Opens a bit reader with data
		/// 
		/// Opens a bit reader for reading and initializes it with
		/// the \p range as its input data.
		/// 
		/// @param range Range of data to read bits from
		/// 
		/// @exception std::runtime_error Thrown if the bit reader is already open.
		/// @exception std::invalid_argument Thrown if the \p range is empty.
		void open(span_type range)
		{
			if (!range_.empty())
			{
				throw std::runtime_error("attempt to open bit reader that's already open");
			}

			if (range.empty())
			{
				throw std::invalid_argument("attempt to open bit reader with empty range");
			}

			range_ = range;
			current_ptr_ = begin(range);
			current_bit_ = high_bit;
		}

		/// @brief Closes the bit reader
		/// 
		/// Closes the bit reader and resets it to a default empty state (empty() returns true).
		void close()
		{
			range_ = span_type();
			current_ptr_ = span_type::iterator();
			current_bit_ = 0;
		}

		/// @brief Reads the next bit from the input stream
		/// 
		/// @return The value of the bit as a boolean.
		/// 
		/// @exception std::runtime_error Thrown if the bit reader is not open.
		/// @exception hypertech::kaos::core::exceptions::end_of_file_error Thrown if the last bit has already been read and the
		/// bit reader is currently at the end of the input stream
		bool read()
		{
			if (!is_open())
			{
				throw std::runtime_error("attempt to read from closed bit reader");
			}

			if (current_bit_ == 0)
			{
				if (current_ptr_ == end(range_))
				{
					throw exceptions::end_of_file_error("file error: attempt to read past end of bit reader range");
				}

				++current_ptr_;

				if (current_ptr_ == end(range_))
				{
					throw exceptions::end_of_file_error("file error: attempt to read past end of bit reader range");
				}

				current_bit_ = high_bit;
			}

			auto value(*current_ptr_ & current_bit_);
			current_bit_ >>= 1;


			return value;
		}


	private:

		span_type range_;
		span_type::iterator current_ptr_;
		value_type current_bit_ = 0;
	};

}
