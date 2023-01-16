// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/utility/bit.h>
#include <istream>
#include <string>
#include <vector>
#include <span>


namespace hypertech { namespace kaos { namespace core { namespace io
{

	namespace details
	{
		template<class Type_>
		concept integral_not_bool = std::is_integral_v<Type_> && !std::is_same_v<Type_, bool>;
	}


	/// @brief Endian aware binary stream reader
	/// 
	/// This class provides basic functionality for reading integral types and enumerations with
	/// support for reading into std::vector, std::array, and std::pair. It reads the data
	/// in binary form from input stream with automatic conversion between big and little
	/// endian ordering. It provides an extractor-based interface similar to istream.
	class binary_reader
	{
	public:

		/// @brief The stream type
		using stream_type = std::istream;
		/// @brief Size type
		using size_type = size_t;
		/// @brief Stream position type
		using pos_type = stream_type::pos_type;
		/// @brief Stream offset type
		using off_type = stream_type::off_type;
		/// @brief Stream state type
		using iostate_type = std::ios_base::iostate;
		/// @brief Span type
		template<class Type_> using span_type = std::span<Type_>;
		/// @brief Indicates the endianness of the integral types extracted by the reader.
		using ordering_type = std::endian;
		/// @brief String type
		using string_type = std::string;

		///	brief IO state bit indicating no error
		static constexpr iostate_type goodbit = std::ios_base::goodbit;
		///	brief IO state bit indicating associated input sequence has reached end-of-file
		static constexpr iostate_type eofbit = std::ios_base::eofbit;
		///	brief IO state bit indicating input/output operation failed (formatting or extraction error)
		static constexpr iostate_type failbit = std::ios_base::failbit;
		///	brief IO state bit indicating irrecoverable stream error
		static constexpr iostate_type badbit = std::ios_base::badbit;
		///	brief All state bits indicating stream errors
		static constexpr iostate_type allbits = eofbit | failbit | badbit;


	public:

		/// @brief Creates a binary reader
		/// @param input The input stream
		/// @param ordering Byte ordering to use when extracting integral types from the stream.
		binary_reader(stream_type& input, ordering_type ordering = ordering_type::native);


		/// @brief Checks whether the stream has no errors.
		///
		/// @return Returns true if the stream has no errors and is
		/// ready for I/O operations. Specifically, returns !fail().
		[[nodiscard]] explicit operator bool() const;

		/// @brief Checks whether the stream has no errors.
		///
		/// @return Returns a null pointer if fail() returns true, otherwise returns a
		/// non-null pointer. This pointer is implicitly convertible to bool and may
		/// be used in boolean contexts.
		[[nodiscard]] bool operator!() const;

		/// @brief Gets the exception mask
		/// 
		/// Gets the exception mask of the stream. The exception mask determines
		/// which error states trigger exceptions of type failure.
		/// 
		/// @return The current exception mask
		[[nodiscard]] iostate_type exceptions() const;

		/// @brief Sets the exception mask
		/// 
		/// Sets the exception mask of the stream. The exception mask determines
		/// which error states trigger exceptions of type failure.
		/// 
		/// @param except exception mask
		void exceptions(iostate_type except);

		/// @brief Skip over bytes
		/// 
		/// Skips past \p length number of bytes in the input stream.
		/// 
		/// @param length Number of bytes to skip
		/// 
		/// @return *this
		binary_reader& skip(size_t length);

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
		/// @param size The number of bytes to extract from the stream.
		/// 
		/// @tparam Type_ The value type contained in the vector 
		/// 
		/// @return A std::vector of type Type_.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the values.
		template<details::integral_not_bool Type_>
		[[nodiscard]] std::vector<Type_> read_vector(size_type size);

		/// @brief extracts a multiple byte values from the stream and stores them in
		/// a std::string.
		/// 
		/// Reads multiple byte values and returns them in a std::string with optional
		/// truncation at the furst null terminator. Otherwise it sets failbit and eofbit
		/// and throws an exception. 
		/// 
		/// @param size The number of characters to extract from the stream.
		/// @param null_truncate if true truncates the string at the first null terminator otherwise
		/// the string is left unmodified.
		/// 
		/// @return A string
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_error If an error occurs while extracting the string.
		[[nodiscard]] string_type read_string(size_type size, bool null_truncate = true);


		/// @brief returns the input position indicator
		/// 
		/// Returns input position indicator of the current associated streambuf object.
		/// 
		/// Behaves as UnformattedInputFunction, except that gcount() is not affected.
		/// After constructing and checking the sentry object,
		/// if fail() == true, returns pos_type(-1).
		/// Otherwise, returns rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::in).
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

		
		/// @brief checks if no error has occurred i.e. I/O operations are available
		/// @return true if the stream error flags are all false, false otherwise.
		[[nodiscard]] bool good() const;
		/// @brief checks if end-of-file has been reached
		/// @return true if an end-of-file has occurred, false otherwise.
		[[nodiscard]] bool eof() const;
		/// @brief checks if an error has occurred
		/// @return true if an error has occurred, false otherwise.
		[[nodiscard]] bool fail() const;
		/// @brief checks if a non-recoverable error has occurred
		/// @return true if a non-recoverable error has occurred, false otherwise.
		[[nodiscard]] bool bad() const;

		/// @brief modifies state flags
		/// 
		/// Sets the stream error state flags by assigning them the value of state.
		/// By default, assigns std::ios_base::goodbit which has the effect of clearing
		/// all error state flags.
		/// 
		/// @param state new error state flags setting. It can be a combination of the
		/// following constants:
		/// 
		///		goodbit	| no error
		///		badbit	| irrecoverable stream error
		///		failbit	| input/output operation failed (formatting or extraction error)
		///		eofbit	| associated input sequence has reached end-of-file
		void clear( iostate_type state = goodbit );


	private:

		void throw_on_error() const;


	private:

		stream_type& input_;
		bool swap_bytes_;
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
		if (input_.read(reinterpret_cast<char*>(output.data()), output.size_bytes()) && swap_bytes_)
		{
			if constexpr (std::is_same<Type_, bool>::value)
			{
				std::transform(
					begin(output),
					end(output),
					begin(output),
					[](auto value) { return value != 0; });
			}
			else if constexpr(sizeof(Type_) > 1)
			{
				std::transform(
					begin(output),
					end(output),
					begin(output),
					utility::byteswap<Type_>);
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

	//	TODO: Possibly add specialization for vector<bool>
	template<details::integral_not_bool Type_>
	std::vector<Type_> binary_reader::read_vector(size_type size)
	{
		std::vector<Type_> value(size, 0);
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
	/// If the value is greater than 8 bits and the selected byte ordering of
	/// the reader is not the same as the native ordering the bytes in the
	/// value will be reversed from LSB to MSB.
	/// 
	/// @param output reference to the variable to write the result to
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
	/// If the value type is greater than 8 bits and the selected byte ordering of
	/// the reader is not the same as the native ordering the bytes in each value
	/// extracted will be reversed from LSB to MSB.
	/// 
	/// @param output reference to the variable to write the result to
	/// 
	/// @return The binary_reader on the left hand of the expression
	template<std::integral Type_>
	inline binary_reader& operator>>(binary_reader& reader, const binary_reader::span_type<Type_>& value)
	{
		return reader.read(value);
	}

}}}}
