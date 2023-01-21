// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <ios>
#include <string>
#include <vector>
#include <span>


namespace hypertech::kaos::core::io
{

	/// @brief Base class for endian aware binary streams
	/// 
	/// This class provides base functionality for binary streams that read and write in
	/// binary form with automatic conversion between big and little endian ordering.
	class binary_ios
	{
	public:

		/// @brief The stream type
		using base_stream_type = std::ios;
		/// @brief Stream state type
		using iostate_type = base_stream_type::iostate;
		/// @brief Stream position type
		using pos_type = base_stream_type::pos_type;
		/// @brief Stream offset type
		using off_type = base_stream_type::off_type;
		/// @brief Stream state type
		using iostate_type = std::ios_base::iostate;
		/// @brief Indicates the endianness of the integral types extracted by the reader.
		using ordering_type = std::endian;
		/// @brief Size type
		using size_type = size_t;

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

		/// @brief Creates a binary stream
		/// 
		/// @param stream The IO stream
		/// @param ordering Byte ordering to use when extracting integral types from the stream.
		binary_ios(base_stream_type& stream, ordering_type ordering = ordering_type::native);

		binary_ios(const binary_ios&) = delete;
		binary_ios(binary_ios&&) = delete;

		virtual ~binary_ios() = default;

		binary_ios& operator=(const binary_ios&) = delete;
		binary_ios& operator=(binary_ios&&) = delete;

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
		void clear(iostate_type state = goodbit);


	protected:

		/// @brief A reference to the base stream attached to the binary_ios instance
		base_stream_type& base_stream_;
		/// @brief Specifies if bytes should be swapped before writing or after reading.
		const bool swap_bytes_;
	};

}
