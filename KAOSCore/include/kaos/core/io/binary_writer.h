// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
///	\file
///	@brief Binary stream writer.
#include <kaos/core/io/binary_ios.h>
#include <kaos/core/utility/bit.h>
#include <kaos/core/type_traits.h>
#include <istream>
#include <string>
#include <vector>
#include <span>


namespace hypertech::kaos::core::io
{

	/// @brief Endian aware binary stream writer
	/// 
	/// This class provides basic functionality for writing integral types, enumerations,
	/// std::vector, std::array, std::pair, and std::basic_string to a endian aware binary
	/// stream. It writesthe data in binary form to an output stream with automatic
	/// conversion between big and little endian ordering.
	class binary_writer : public binary_ios
	{
	public:

		/// @brief The stream type
		using stream_type = std::ostream;
		/// @brief Span type
		template<class Type_> using span_type = std::span<Type_>;


	public:

		/// @brief Creates a binary writer
		/// 
		/// @param output The output stream
		/// @param ordering Byte ordering to use when extracting integral types to the stream.
		binary_writer(stream_type& output, ordering_type ordering = ordering_type::native);


		/// @brief Skip over bytes
		/// 
		/// Skips past \p length number of bytes in the output stream.
		/// 
		/// @param length Number of bytes to skip
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
		/// while skiping bytes in the file
		binary_writer& skipp(size_t length);

		/// @brief returns the output position indicator
		/// 
		/// Returns output position indicator of the current associated streambuf object.
		/// 
		/// Behaves as UnformattedOutputFunction (except without actually performing
		/// output). After constructing and checking the sentry object.
		/// 
		/// @return The current position of the get pointer on success, pos_type(-1) on failure
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
		/// while retrieving the put position.
		[[nodiscard]] pos_type tellp();

		/// @brief sets the output position indicator
		/// 
		/// Sets output position indicator of the current associated streambuf object.
		/// 
		/// @param pos absolute position to set the output position indicator to.
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
		/// while changing put position.
		binary_writer& seekp(pos_type pos);

		/// @brief sets the output position indicator
		/// 
		/// Sets output position indicator of the current associated streambuf object.
		/// 
		/// @param off relative position (positive or negative) to set the output
		/// position indicator to.
		/// @param dir defines base position to apply the relative offset to. It can
		/// be one of the following constants:
		/// 
		///		Constant | Explanation
		///		-------- | -----------
		///		beg		 | the beginning of a stream
		///		end		 | the ending of a stream
		///		cur		 | the current position of stream position indicator
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
		/// while changing put position.
		binary_writer& seekp(off_type off, std::ios_base::seekdir dir);


		/// @brief Writes an integral value to the stream
		/// 
		/// Writes an integral value to the stream and sets failbit and badbit
		/// if an error occurs.
		/// 
		/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
		/// of the writer is not the same as the native ordering, the bytes in the
		/// value will be reversed from LSB to MSB before writing.
		/// 
		/// @tparam Type_ The type of \p value to write.
		/// 
		/// @param value The integral value to write to the stream.
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
		/// while writing the value.
		template<std::integral Type_>
		binary_writer& write(Type_ value);

		/// @brief Writes an enumeration value to the stream.
		/// 
		/// Writes an enumeration value to the stream as the type specified by \p Type_
		/// and sets failbit and badbit if an error occurs.
		/// 
		/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
		/// of the writer is not the same as the native ordering, the bytes in the value
		/// will be reversed from LSB to MSB before writing.
		/// 
		/// @tparam Type_ the value type convert the enumeration to for the write.
		/// @tparam EnumType_ the enumeration value type.
		/// 
		/// @param value The enumeration value to write to the stream
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
		/// while writing the value.
		template<std::integral Type_, class EnumType_>
		requires std::is_enum_v<EnumType_>
		binary_writer& write(EnumType_ value);

		/// @brief Writes a pair of integral values to the stream
		/// 
		/// Writes two integral values contained in a `std::pair` to the stream and sets
		/// failbit and badbit if an error occurs.
		/// 
		/// If size of \p FirstType_ pr \p SecondType_ is greater than 8 bits and the
		/// selected byte ordering of the writer is not the same as the native ordering,
		/// the bytes in the corresponsing value will be reversed from LSB to MSB before
		/// writing.
		/// 
		/// @tparam FirstType_ The type of the first value to write.
		/// @tparam SecondType_ The type of the second value to write.
		/// 
		/// @param values the pair of values to write to the stream
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
		/// writing the values.
		template<std::integral FirstType_, std::integral SecondType_>
		binary_writer& write(std::pair<FirstType_, SecondType_> values);

		/// @brief Writes multiple integral values to the stream
		/// 
		/// Writes multiple integral values from a `std::span` to the stream and sets
		/// failbit and badbit if an error occurs.
		/// 
		/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
		/// of the writer is not the same as the native ordering, the bytes in the
		/// value will be reversed from LSB to MSB before writing.
		/// 
		/// @tparam Type_ The type of \p values in the span to write.
		/// 
		/// @param values The `std::span` referencing the range of values to write to the stream.
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
		/// writing the values.
		template<std::integral Type_>
		binary_writer& write(const span_type<Type_>& values);

		/// @brief Writes multiple integral values to the stream
		/// 
		/// Writes multiple integral values from a `std::array` to the stream and sets
		/// failbit and badbit if an error occurs.
		/// 
		/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
		/// of the writer is not the same as the native ordering, the bytes in the
		/// value will be reversed from LSB to MSB before writing.
		/// 
		/// @tparam Type_ The type of \p values in the span to write.
		/// 
		/// @param values The `std::array` containing the values to write to the stream.
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
		/// writing the values.
		template<std::integral Type_, size_t Size_>
		binary_writer& write(const std::array<Type_, Size_>& values);

		/// @brief Writes multiple integral values to the stream
		/// 
		/// Writes multiple integral values from a `std::vector` to the stream and sets
		/// failbit and badbit if an error occurs.
		/// 
		/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
		/// of the writer is not the same as the native ordering, the bytes in the
		/// value will be reversed from LSB to MSB before writing.
		/// 
		/// @tparam Type_ The type of \p values in the span to write.
		/// @tparam Args_ Extra template arguments of the `std::vector`
		/// 
		/// @param values The `std::vector` containing the values to write to the stream.
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
		/// writing the values.
		template<integral_not_bool_v Type_, class... Args_>
		binary_writer& write(const std::vector<Type_, Args_...>& values);

		/// @brief Writes multiple boolean values to the stream
		/// 
		/// Writes multiple boolean values from a `std::vector` to the stream and sets
		/// failbit and badbit if an error occurs.
		/// 
		/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
		/// of the writer is not the same as the native ordering, the bytes in the
		/// value will be reversed from LSB to MSB before writing.
		/// 
		/// @tparam Type_ The type of \p values in the span to write.
		/// @tparam Args_ Extra template arguments of the `std::vector`
		/// 
		/// @param values The `std::vector` containing the values to write to the stream.
		/// 
		/// @return *this
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
		/// writing the values.
		template<class Type_, class... Args_>
		requires std::is_same_v<Type_, bool>
		binary_writer& write(const std::vector<Type_, Args_...>& values);

		/// @brief Writes a string value to the stream.
		/// 
		/// Writes a string to the stream and sets ... if an error occurs.
		/// 
		/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
		/// of the writer is not the same as the native ordering, the bytes in the
		/// value will be reversed from LSB to MSB before writing.
		/// 
		/// @tparam Type_ The type of values in the string to write.
		/// @tparam Args_ Extra template arguments of the `std::basic_string`
		/// 
		/// @param value The string to write to the stream
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
		/// while writing the string.
		template<std::integral Type_, class... Args_>
		binary_writer& write(const std::basic_string<Type_, Args_...>& value)
		{
			return write(std::span(value.begin(), value.end()));
		}


	private:

		void throw_on_write_error() const;


	private:

		stream_type& output_;
	};


	template<std::integral Type_>
	binary_writer& binary_writer::write(Type_ value)
	{
		try
		{
			if (swap_bytes_ && sizeof(Type_) > 1)
			{
				value = utility::byteswap(value);
			}

			output_.write(reinterpret_cast<char*>(&value), sizeof(value));
		}
		catch (std::exception&)
		{
			throw_on_write_error();
		}

		return *this;
	}

	template<std::integral Type_>
	binary_writer& binary_writer::write(const span_type<Type_>& values)
	{
		try
		{
			if (!swap_bytes_ || sizeof(Type_) == 1)
			{
				output_.write(reinterpret_cast<const char*>(values.data()), values.size_bytes());

				return *this;
			}

			for (auto value : values)
			{
				if (!write(value))
				{
					return *this;
				}
			}
		}
		catch (std::exception&)
		{
			throw_on_write_error();
		}

		return *this;
	}

	template<std::integral Type_, class EnumType_>
	requires std::is_enum_v<EnumType_>
	binary_writer& binary_writer::write(EnumType_ value)
	{
		return write(static_cast<Type_>(value));
	}

	template<std::integral FirstType_, std::integral SecondType_>
	binary_writer& binary_writer::write(std::pair<FirstType_, SecondType_> values)
	{
		if (!write<FirstType_>(values.first))
		{
			return *this;
		}
		
		return write<SecondType_>(values.second);
	}

	template<std::integral Type_, size_t Size_>
	binary_writer& binary_writer::write(const std::array<Type_, Size_>& values)
	{
		return write(std::span(values.begin(), values.end()));
	}

	template<integral_not_bool_v Type_, class... Args_>
	binary_writer& binary_writer::write(const std::vector<Type_, Args_...>& values)
	{
		return write(std::span(values.begin(), values.end()));
	}

	template<class Type_, class... Args_>
	requires std::is_same_v<Type_, bool>
	binary_writer& binary_writer::write(const std::vector<Type_, Args_...>& values)
	{
		for (auto value : values)
		{
			if (!write(value))
			{
				return *this;
			}
		}

		return *this;
	}

	/// @brief Writes an integral value to the stream
	/// 
	/// Writes an integral value to the stream and sets failbit and badbit
	/// if an error occurs.
	/// 
	/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
	/// of the writer is not the same as the native ordering, the bytes in the
	/// value will be reversed from LSB to MSB before writing.
	/// 
	/// @tparam Type_ The type of \p value to write.
	/// 
	/// @param writer reference to the binary writer to write the value to
	/// @param value The integral value to write to the stream.
	/// 
	/// @return a reference to the binary writer on the left size of the expression.
	/// 
	/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
	/// while writing the value.
	template<std::integral Type_>
	inline binary_writer& operator<<(binary_writer& writer, Type_ value)
	{
		return writer.write(value);
	}

	/// @brief Writes a pair of integral values to the stream
	/// 
	/// Writes two integral values contained in a `std::pair` to the stream and sets
	/// failbit and badbit if an error occurs.
	/// 
	/// If size of \p FirstType_ pr \p SecondType_ is greater than 8 bits and the
	/// selected byte ordering of the writer is not the same as the native ordering,
	/// the bytes in the corresponsing value will be reversed from LSB to MSB before
	/// writing.
	/// 
	/// @tparam FirstType_ The type of the first value to write.
	/// @tparam SecondType_ The type of the second value to write.
	/// 
	/// @param writer reference to the binary writer to write the value to
	/// @param values the pair of values to write to the stream
	/// 
	/// @return a reference to the binary writer on the left size of the expression.
	/// 
	/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
	/// writing the values.
	template<std::integral FirstType_, std::integral SecondType_>
	inline binary_writer& operator<<(binary_writer& writer, std::pair<FirstType_, SecondType_> values)
	{
		return writer.write(values);
	}

	/// @brief Writes multiple integral values to the stream
	/// 
	/// Writes multiple integral values to the stream and sets failbit and badbit
	/// if an error occurs.
	/// 
	/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
	/// of the writer is not the same as the native ordering, the bytes in the
	/// value will be reversed from LSB to MSB before writing.
	/// 
	/// @tparam Type_ The type of \p values in the span to write.
	/// 
	/// @param writer reference to the binary writer to write the value to
	/// @param values The span referencing the range of values to write to the stream.
	/// 
	/// @return a reference to the binary writer on the left size of the expression.
	/// 
	/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
	/// writing the values.
	template<std::integral Type_>
	inline binary_writer& operator<<(binary_writer& writer, const binary_writer::span_type<Type_>& values)
	{
		return writer.write(values);
	}

	/// @brief Writes multiple integral values to the stream
	/// 
	/// Writes multiple integral values from a `std::array` to the stream and sets
	/// failbit and badbit if an error occurs.
	/// 
	/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
	/// of the writer is not the same as the native ordering, the bytes in the
	/// value will be reversed from LSB to MSB before writing.
	/// 
	/// @param writer reference to the binary writer to write the value to
	/// @tparam Type_ The type of \p values in the span to write.
	/// 
	/// @param values The `std::array` containing the values to write to the stream.
	/// 
	/// @return a reference to the binary writer on the left size of the expression.
	/// 
	/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
	/// writing the values.
	template<std::integral Type_, size_t Size_>
	inline binary_writer& operator<<(binary_writer& writer, const std::array<Type_, Size_>& values)
	{
		return writer.write(values);
	}

	/// @brief Writes multiple integral values to the stream
	/// 
	/// Writes multiple integral values from a `std::vector` to the stream and sets
	/// failbit and badbit if an error occurs.
	/// 
	/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
	/// of the writer is not the same as the native ordering, the bytes in the
	/// value will be reversed from LSB to MSB before writing.
	/// 
	/// @tparam Type_ The type of values in the vector to write.
	/// @tparam Args_ Extra template arguments of the `std::vector`
	/// 
	/// @param writer reference to the binary writer to write the value to
	/// @param values The `std::vector` containing the values to write to the stream.
	/// 
	/// @return a reference to the binary writer on the left size of the expression.
	/// 
	/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while
	/// writing the values.
	template<std::integral Type_, class... Args_>
	inline binary_writer& operator<<(binary_writer& writer, const std::vector<Type_, Args_...>& values)
	{
		return writer.write(values);
	}

	/// @brief Writes a string value to the stream.
	/// 
	/// Writes a string to the stream and sets ... if an error occurs.
	/// 
	/// If size of \p Type_ is greater than 8 bits and the selected byte ordering
	/// of the writer is not the same as the native ordering, the bytes in the
	/// value will be reversed from LSB to MSB before writing.
	/// 
	/// @tparam Type_ The type of values in the string to write.
	/// @tparam Args_ Extra template arguments of the `std::basic_string`
	/// 
	/// @param writer reference to the binary writer to write the value to
	/// @param value The string to write to the stream
	/// 
	/// @return a reference to the binary writer on the left size of the expression.
	/// 
	/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs
	/// while writing the string.
	template<std::integral Type_, class... Args_>
	inline binary_writer& operator<<(binary_writer& writer, const std::basic_string<Type_, Args_...>& value)
	{
		return writer.write(value);
	}

}
