// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <stdexcept>
#include <typeinfo>


namespace hypertech { namespace kaos { namespace core { namespace exceptions
{

	/// @brief Exception thrown when an error occurs while reading from or
	///	writing to a file.
	class file_error : public std::runtime_error
	{
	public:

		using std::runtime_error::runtime_error;
	};


	/// @brief Exception thrown when a file is inaccessible for reading or writing.
	class file_access_error : public file_error
	{
	public:

		using file_error::file_error;
	};


	/// @brief Exception thrown when a file cannot be found.
	class file_not_found_error : public file_error
	{
	public:

		using file_error::file_error;
	};


	/// @brief Exception thrown when a problem with the format of a file
	///	occurs.
	class file_format_error : public file_error
	{
	public:

		using file_error::file_error;
	};


	/// @brief Exception thrown when a file is inaccessible for reading or writing.
	class end_of_file_error : public file_error
	{
	public:

		using file_error::file_error;
	};


	/// @brief Exception used to indicate runtime type conversion failure
	class bad_value_cast : public std::bad_cast
	{
	public:

		/// @brief Type information
		using typeinfo_type = ::std::type_info;

		/// @brief Create a bad value cast exception
		/// @param source_type_arg The type information of the source type involved in the failed conversion.
		/// @param target_type_arg The type information of the target type involved in the failed conversion.
		bad_value_cast(
			const typeinfo_type &source_type_arg,
			const typeinfo_type &target_type_arg) noexcept
			: source_(&source_type_arg), target_(&target_type_arg)
		{}

	public:

		/// @brief Returns a string containing an explanation of the exception.
		/// 
		/// @return Pointer to a null-terminated string with explanatory information.
		/// The pointer is guaranteed to be valid at least until the exception object
		/// from which it is obtained is destroyed, or until a non-const member
		/// function on the exception object is called.
		const char * what() const noexcept
		{  return "bad value cast"; }

		/// @brief Returns the type information of the source value type.
		/// 
		/// @return Returns the type information of the source value type
		/// involved in the failed conversion.
		const typeinfo_type &source() const noexcept {
			return *source_;
		}

		/// @brief Returns the type information of the target value type
		/// 
		/// @return Returns the type information of the target value type
		/// involved in the failed conversion.
		const typeinfo_type &target() const noexcept {
			return *target_;
		}

	private:
		const typeinfo_type *source_;
		const typeinfo_type *target_;
	};


	/// @brief Exception used to indicate an attempt to convert an empty value.
	class empty_cast_error : public bad_value_cast
	{
	public:

		/// @inheritdoc
		using bad_value_cast::bad_value_cast;

		/// @inheritdoc
		const char * what() const noexcept
		{  return "bad value cast: negative overflow"; }
	};


	/// @brief Exception used to indicate a negative overflow occurred when
	///	converting a value.
	class negative_overflow_error : public bad_value_cast
	{
	public:

		/// @inheritdoc
		using bad_value_cast::bad_value_cast;

		/// @inheritdoc
		const char * what() const noexcept
		{  return "bad value cast: negative overflow"; }
	};


	/// @brief Exception used to indicate an overflow occurred when
	///	converting a value.
	class positive_overflow_error : public bad_value_cast
	{
	public:

		/// @inheritdoc
		using bad_value_cast::bad_value_cast;

		/// @inheritdoc
		const char * what() const noexcept
		{ return "bad value cast: positive overflow"; }
	};


	/// @brief Exception used to indicate that a conversion cannot be performed
	/// because the source and target types are incompatible.
	class incompatible_type_error : public bad_value_cast
	{
	public:

		/// @inheritdoc
		using bad_value_cast::bad_value_cast;

		/// @inheritdoc
		const char * what() const noexcept
		{ return "bad value cast: incompatible types"; }
	};


	/// @brief Exception used to indicate lexical error occurred while
	///	converting the contents of a string to another type.
	class lexical_error : public bad_value_cast
	{
	public:

		/// @inheritdoc
		using bad_value_cast::bad_value_cast;

		/// @inheritdoc
		const char * what() const noexcept
		{ return "bad value cast: lexical conversion error"; }
	};


	/// @brief Exception used to indicate the an attribute cannot
	/// be found in a value container.
	class attribute_not_found_error : public std::runtime_error
	{
	public:

		/// @brief Create an attribute_not_found_error exception
		/// 
		/// @param attribute_name The name of the attribute that wasn't found
		attribute_not_found_error(const std::string& attribute_name)
			: std::runtime_error("attribute `" + attribute_name + "` not found")
		{}

	};

	/// @brief Exception used to indicate the an attribute cannot
	/// be converted from one value type to another.
	class attribute_conversion_error : public std::runtime_error
	{
	public:

		/// @brief Create an attribute_conversion_error exception
		/// 
		/// @param error_message A brief error message describing the conversion error
		/// @param attribute_name The name of the attribute that couldn't be converted
		/// @param target_type The type info of the target value type the attribute
		/// could not be converted to.
		attribute_conversion_error(
			const std::string& error_message,
			const std::string& attribute_name,
			const std::type_info& target_type)
			: std::runtime_error(
				error_message
				+ " error encountered while converting attribute `"
				+ attribute_name
				+ "` to `"
				+ target_type.name()
				+ "`")
		{}

	};

}}}}
