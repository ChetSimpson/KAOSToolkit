// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
///	\file
///	@brief Binary stream reader
#include <kaos/core/io/binary_ios.h>
#include <kaos/core/utility/bit.h>
#include <kaos/core/type_traits.h>
#include <istream>
#include <string>
#include <vector>
#include <span>


namespace hypertech::kaos::core::io
{

	/// @brief Endian aware binary stream reader
	/// 
	/// This class provides basic functionality for reading integral types and enumerations with
	/// support for reading into std::vector, std::array, and std::pair. It reads the data
	/// in binary form from input stream with automatic conversion between big and little
	/// endian ordering. It provides an extractor-based interface similar to istream.
	class binary_reader : public binary_ios
	{
	public:

		/// @brief The stream type
		using stream_type = std::istream;
		/// @brief Span type
		template<class Type_> using span_type = std::span<Type_>;
		/// @brief String type
		using string_type = std::string;


	public:

		/// @brief Creates a binary reader
		/// @param input The input stream
		/// @param ordering Byte ordering to use when extracting integral types from the stream.
		binary_reader(stream_type& input, ordering_type ordering = ordering_type::native);


		/// @brief Skip over bytes
		/// 
		/// Skips past \p length number of bytes in the input stream.
		/// 
		/// @param length Number of bytes to skip
		/// 
		/// @return *this
		binary_reader& skipg(size_t length);

		/// @brief returns the input position indicator
		/// 
		/// Returns input position indicator of the current associated streambuf object.
		/// 
		/// Behaves as UnformattedInputFunction, except that gcount() is not affected.
		/// After constructing and checking the sentry object.
		/// 
		/// @return The current position of the get pointer on success, pos_type(-1) on failure
		[[nodiscard]] pos_type tellg();

		/// @brief sets the input position indicator
		/// 
		/// Sets input position indicator of the current associated streambuf object.
		/// 
		/// @param pos absolute position to set the input position indicator to.
		/// @return *this
		binary_reader& seekg( pos_type pos );

		/// @brief sets the input position indicator
		/// 
		/// Sets input position indicator of the current associated streambuf object.
		/// 
		/// @param off relative position (positive or negative) to set the input
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
		binary_reader& seekg(off_type off, std::ios_base::seekdir dir);


		/// @brief extracts boolean value from the stream
		/// 
		/// Reads one boolean value and stores it to \p output if available.
		/// Otherwise, leaves \p output unmodified and sets failbit and eofbit.
		/// 
		/// @param output reference to the boolean value to write the result to
		/// 
		/// @return *this
		binary_reader& read(bool& output);

		/// @brief extracts a integral value from the stream
		/// 
		/// Reads one integral value and stores it to \p output if available.
		/// Otherwise, leaves \p output unmodified and sets failbit and eofbit.
		/// If the value is greater than 8 bits and the selected byte ordering of
		/// the reader is not the same as the native ordering the bytes in the
		/// value will be reversed from LSB to MSB.
		/// 
		/// @param output reference to the variable to write the result to
		/// 
		/// @return *this
		template<std::integral Type_>
		binary_reader& read(Type_& output);

		/// @brief extracts multiple integral values from the stream
		/// 
		/// Reads multiple integral values if available and stores them to the
		/// span referenced by \p output. Otherwise, leaves \p output unmodified
		/// and sets failbit and eofbit.
		/// If the value type is greater than 8 bits and the selected byte ordering of
		/// the reader is not the same as the native ordering the bytes in each value
		/// extracted will be reversed from LSB to MSB.
		/// 
		/// @param output reference to the variable to write the result to
		/// 
		/// @return *this
		template<std::integral Type_>
		binary_reader& read(const span_type<Type_>& output);


		/// @brief extracts a integral value from the stream
		/// 
		/// Reads one integral value and returns it otherwise it sets failbit and eofbit
		/// and throws an exception. If the value is greater than 8 bits and the
		/// selected byte ordering of the reader is not the same as the native ordering
		/// the bytes in the value will be reversed from LSB to MSB.
		/// 
		/// @tparam Type_ the value type to read.
		/// 
		/// @return the value extracted from the stream
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the value.
		template<std::integral Type_>
		[[nodiscard]] Type_ read();

		/// @brief extracts a integral value from the stream and converts it to an
		/// enumeration type.
		/// 
		/// Reads one integral value, converts it to an enumeration type and returns it.
		/// Otherwise it sets failbit and eofbit and throws an exception. If the value
		/// is greater than 8 bits and the selected byte ordering of the reader is not
		/// the same as the native ordering the bytes in the value will be reversed
		/// from LSB to MSB.
		/// 
		/// @tparam Type_ the value type to read.
		/// 
		/// @return the value extracted from the stream
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the value.
		template<std::integral Type_, class EnumType_>
		requires std::is_enum_v<EnumType_>
		[[nodiscard]] EnumType_ read_enum();

		/// @brief extracts a pair of integral values from the stream
		/// 
		/// Reads two scalars value returns them as a std::pair.Otherwise it sets failbit
		/// and eofbit and throws an exception. If the size of either value is greater
		/// than 8 bits and the selected byte ordering of the reader is not the same as the
		/// native ordering the bytes in the values will be reversed from LSB to MSB.
		/// 
		/// @tparam FirstType_ The type of the first value to read.
		/// @tparam SecondType_ The type of the second value to read.
		/// 
		/// @return the value extracted from the stream
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the values.
		template<std::integral FirstType_, std::integral SecondType_>
		[[nodiscard]] std::pair<FirstType_, SecondType_> read_pair();

		/// @brief extracts a multiple integral values from the stream and returns them in
		/// a std::array.
		/// 
		/// Reads multiple scalars value returns them in a std::array. Otherwise it sets
		/// failbit and eofbit and throws an exception. If the size of Value_ is greater
		/// than 8 bits and the selected byte ordering of the reader is not the same as the
		/// native ordering the bytes in each value will be reversed from LSB to MSB.
		/// 
		/// @tparam Type_ The value type contained in the array 
		/// @tparam Size_ The number of values in the array.
		/// 
		/// @return A std::array of type Type_ and a size of Size_.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the values.
		template<std::integral Type_, size_t Size_>
		[[nodiscard]] std::array<Type_, Size_> read_array();

		/// @brief extracts a multiple integral values from the stream and returns them in
		/// a std::vector.
		/// 
		/// Reads multiple scalars value returns them in a std::vector. Otherwise it sets
		/// failbit and eofbit and throws an exception. If the size of Value_ is greater
		/// than 8 bits and the selected byte ordering of the reader is not the same as the
		/// native ordering the bytes in each value will be reversed from LSB to MSB.
		/// 
		///	\todo Possibly add specialization for vector<bool>
		/// 
		/// @param length The number of bytes to extract from the stream.
		/// 
		/// @tparam Type_ The value type contained in the vector 
		/// 
		/// @return A std::vector of type Type_.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the values.
		template<integral_not_bool_v Type_>
		[[nodiscard]] std::vector<Type_> read_vector(size_type length);

		/// @brief extracts a multiple byte values from the stream and stores them in
		/// a std::string.
		/// 
		/// Reads multiple byte values and returns them in a std::string with optional
		/// truncation at the furst null terminator. Otherwise it sets failbit and eofbit
		/// and throws an exception. 
		/// 
		/// @param length The number of characters to extract from the stream.
		/// @param null_truncate if true truncates the string at the first null terminator otherwise
		/// the string is left unmodified.
		/// 
		/// @todo Add support for wstring
		/// @return A string
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the string.
		[[nodiscard]] string_type read_string(size_type length, bool null_truncate = true);


	private:

		void throw_on_error() const;


	private:

		stream_type& input_;
	};


	template<std::integral Type_>
	binary_reader& binary_reader::read(Type_& output)
	{
		if (input_.read(reinterpret_cast<char*>(&output), sizeof(output)) && swap_bytes_ && sizeof(Type_) > 1)
		{
			output = utility::byteswap(output);
		}

		return *this;
	}

	template<std::integral Type_>
	binary_reader& binary_reader::read(const span_type<Type_>& output)
	{
		if (input_.read(reinterpret_cast<char*>(output.data()), output.size_bytes()))
		{
			if (swap_bytes_)
			{
				if constexpr (sizeof(Type_) > 1)
				{
					std::transform(
						begin(output),
						end(output),
						begin(output),
						utility::byteswap<Type_>);
				}
			}

			if constexpr (std::is_same_v<Type_, bool>)
			{
				static_assert(sizeof(Type_) == 1, "Expected type bool to be 1 byte in size");

				std::transform(
					reinterpret_cast<char*>(output.data()),
					reinterpret_cast<char*>(output.data()) + output.size_bytes(),
					reinterpret_cast<char*>(output.data()),
					[](char value) -> bool { return value == 0 ? false : true; });
			}
		}

		return *this;
	}

	template<std::integral Type_>
	Type_ binary_reader::read()
	{
		Type_ value;
		if (!read(value))
		{
			throw_on_error();
		}

		return value;
	}

	template<std::integral Type_, class EnumType_>
	requires std::is_enum_v<EnumType_>
	EnumType_ binary_reader::read_enum()
	{
		return static_cast<EnumType_>(read<Type_>());
	}

	template<std::integral FirstType_, std::integral SecondType_>
	std::pair<FirstType_, SecondType_> binary_reader::read_pair()
	{
		auto first_value = read<FirstType_>();
		auto second_value = read<SecondType_>();

		return { first_value, second_value };
	}



	template<std::integral Type_, size_t Size_>
	std::array<Type_, Size_> binary_reader::read_array()
	{
		std::array<Type_, Size_> value;
		if (!read(span_type<Type_>(value)))
		{
			throw_on_error();
		}

		return value;
	}

	template<integral_not_bool_v Type_>
	std::vector<Type_> binary_reader::read_vector(size_type length)
	{
		std::vector<Type_> value(length, 0);
		if (!read(span_type<Type_>(value)))
		{
			throw_on_error();
		}

		return value;
	}


	/// @brief extracts a integral value from the stream
	/// 
	/// Reads one integral value and stores it to \p output if available.
	/// Otherwise, leaves \p output unmodified and sets failbit and eofbit.
	/// 
	/// If the value is greater than 8 bits and the selected byte ordering of
	/// the reader is not the same as the native ordering the bytes in the
	/// value will be reversed from LSB to MSB.
	/// 
	/// @param reader reference to the binary_reader to read data from.
	/// @param value reference to the variable to sture the value read to
	/// 
	/// @return The binary_reader on the left hand of the expression
	template<std::integral Type_>
	inline binary_reader& operator>>(binary_reader& reader, Type_& value)
	{
		return reader.read(value);
	}

	/// @brief extracts multiple integral values from the stream
	/// 
	/// Reads multiple integral values if available and stores them to the
	/// span referenced by \p output. Otherwise, leaves \p output unmodified
	/// and sets failbit and eofbit.
	/// 
	/// If the value type is greater than 8 bits and the selected byte ordering of
	/// the reader is not the same as the native ordering the bytes in each value
	/// extracted will be reversed from LSB to MSB.
	/// 
	/// @param reader reference to the binary_reader to read data from.
	/// @param value reference to the variable to sture the value read to
	/// 
	/// @return The binary_reader on the left hand of the expression
	template<std::integral Type_>
	inline binary_reader& operator>>(binary_reader& reader, const binary_reader::span_type<Type_>& value)
	{
		return reader.read(value);
	}

}
