// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/rgba_color.h>
#include <boost/uuid/uuid.hpp>
#include <variant>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <filesystem>


namespace hypertech::kaos::core::types
{

	/// @brief A fixed type-safe variant with conversion between most supported
	///	types it can hold.
	class fixed_variant final
	{
	public:

		/// @brief Type storage tag values
		enum class tag_type
		{
			Empty,		//!<	Empty value
			Boolean,	//!<	Boolean value
			Integer,	//!<	Signed integer value
			Unsigned,	//!<	Unsigned integer value
			Float,		//!<	Floating point value
			Double,		//!<	Double precision floating point value
			String,		//!<	String value
			Path,		//!<	Path value
			Color,		//!<	RGBA color value.
			Uuid,		//!<	UUID value
		};

		
		using string_type = std::string;		//!< @brief String type held by fixed_variant.
		using boolean_type = bool;				//!< @brief Boolean type held by fixed_variant.
		using integer_type = std::int64_t;		//!< @brief Signed integer type held by fixed_variant.
		using unsigned_type = std::uint64_t;	//!< @brief Unsigned integer type held by fixed_variant.
		using float_type = float;				//!< @brief Decimal number type held by fixed_variant.
		using double_type = double;				//!< @brief Double precision decimal number type held by fixed_variant.
		using color_type = rgba_color;			//!< @brief Color type held by fixed_variant.
		using path_type = std::filesystem::path;	//!< @brief Path type held by value.
		using uuid_type = boost::uuids::uuid;	//!< UUID type

		/// @brief Storage type used to hold values
		using storge_type = std::variant<
			std::monostate,
			boolean_type,
			integer_type,
			unsigned_type,
			float_type,
			double_type,
			string_type,
			path_type,
			color_type,
			uuid_type>;


	public:

		/// @brief Create an empty value.
		fixed_variant() noexcept;

		/// @brief Create a boolean value.
		/// @param value The value.
		explicit fixed_variant(const boolean_type& value) noexcept;

		/// @brief Create a signed integer value.
		/// @param value The value.
		explicit fixed_variant(const integer_type& value) noexcept;

		/// @brief Create an unsigned integer value.
		/// @param value The value.
		explicit fixed_variant(const unsigned_type& value) noexcept;

		/// @brief Create a floating point value.
		/// @param value The value.
		explicit fixed_variant(const float_type& value) noexcept;

		/// @brief Create a double precision floating point value.
		/// @param value The value.
		explicit fixed_variant(const double_type& value) noexcept;

		/// @brief Create a string value.
		/// @param value The value.
		explicit fixed_variant(string_type value) noexcept;

		/// @brief Create a string value from a literal.
		/// 
		/// Createa s tring value from a literal to prevent conflicts with the
		/// boolean_type conversion constructor.
		/// 
		/// @param value The value.
		explicit fixed_variant(const char* value) throw();

		/// @brief Create a path value
		/// @param path The value
		explicit fixed_variant(path_type path) noexcept;

		/// @brief Create a color value.
		/// @param value The value.
		explicit fixed_variant(color_type value) noexcept;
		
		/// @brief Create a UUID value
		/// @param value The uuid value
		explicit fixed_variant(const uuid_type& value) noexcept;


		/// @brief Create a copy of another fixed_variant.
		/// 
		/// Creates the fixed_variant with a copy of contents of \p other.
		/// 
		/// @param other The value to copy from.
		fixed_variant(const fixed_variant& other) = default;

		/// @brief Creates a fixed_variant using move semantics.
		/// 
		/// Creates the fixed_variant by moving the contents of \p other using move
		/// semantics. \p other is in a valid but empty state afterward.
		/// 
		/// @param other The fixed_variant to move.
		fixed_variant(fixed_variant&& other) = default;

		fixed_variant& operator==(const fixed_variant&) const = delete;
		fixed_variant& operator!=(const fixed_variant&) const = delete;

		/// @brief Copy assignment operator
		/// 
		/// Replaces the contents with a copy of \p other.
		/// 
		/// @param other The fixed_variant to copy from.
		/// 
		/// @return *this
		fixed_variant& operator=(const fixed_variant& other) = default;

		/// @brief Move assignment operator
		/// 
		/// Replaces the contents with those of \p other using move semantics. \p other
		/// is in a valid but empty state afterward.
		/// 
		/// @param other The fixed_variant to move
		/// 
		/// @return *this
		fixed_variant& operator=(fixed_variant&& other) = default;


		/// @brief Reset to empty value
		/// @param value The value.
		fixed_variant& operator=(const nullptr_t& value) noexcept;

		/// @brief Assign a boolean value.
		/// @param value The value.
		fixed_variant& operator=(const boolean_type& value) noexcept;

		/// @brief Assign a signed integer value.
		/// @param value The value.
		fixed_variant& operator=(const integer_type& value) noexcept;

		/// @brief Assign an unsigned integer value.
		/// @param value The value.
		fixed_variant& operator=(const unsigned_type& value) noexcept;

		/// @brief Assign a floating point value.
		/// @param value The value.
		fixed_variant& operator=(const float_type& value) noexcept;

		/// @brief Assign a double precision floating point value.
		/// @param value The value.
		fixed_variant& operator=(const double_type& value) noexcept;

		/// @brief Assign a string value.
		/// @param value The value.
		fixed_variant& operator=(string_type value) noexcept;

		/// @brief Assign a string value.
		/// @param value The value.
		fixed_variant& operator=(const char* value) noexcept;

		/// @brief Assign a path value.
		/// @param value The value.
		fixed_variant& operator=(path_type value) noexcept;

		/// @brief Assign a color value.
		/// @param value The value.
		fixed_variant& operator=(color_type value) noexcept;

		/// @brief Assign a UUID value
		/// @param value The value
		/// @return *this
		fixed_variant& operator=(const uuid_type& value) noexcept;

		/// @brief Get the tag type of the value
		/// @return The tag indicating the value type currently held by the value instance.
		tag_type type() const noexcept
		{
			return type_;
		}


		/// @brief Gets the value as a boolean.
		/// 
		/// Attempts to convert the current value to a boolean value, if the current value
		/// cannot be converted an exception is thrown. If the current value is a string
		/// type the conversion will check for "true" and "false" in addition to "0" and
		/// "1" integer values. If the current value is a color type a incompatible_type_error
		/// exception is thrown regardless of the color value.
		/// 
		/// @return The boolean version of the value
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception positive_overflow_error The value is a convertible type but is greater than 1.
		/// @exception negative_overflow_error The value is a convertible type but is less than 0.
		/// @exception incompatible_type_error The value is not convertible.
		/// @exception lexical_error The current string value cannot be converted.
		boolean_type as_boolean() const;

		/// @brief Gets the value as a signed integer.
		/// 
		/// Attempts to convert the current value to a signed integer and returns
		/// the result. If the value cannot be converted an exception is thrown.
		/// 
		/// @return The value as a signed integer.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception positive_overflow_error The converted value is greater than 0 and does not fit in the signed value type.
		/// @exception negative_overflow_error The converted value is less than 0 and does not fit in the signed value type.
		/// @exception lexical_error The current string value cannot be converted.
		integer_type as_integer() const;

		/// @brief Gets the value as an unsigned integer.
		/// 
		/// Attempts to convert the current value to an unsigned integer and returns
		/// the result. If the value cannot be converted an exception is thrown.
		/// 
		/// @return The value as an unsigned integer.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception positive_overflow_error The converted value is greater than 0 and does not fit in the unsigned value type.
		/// @exception negative_overflow_error The value being converted is less than 0.
		/// @exception lexical_error The current string value cannot be converted.
		unsigned_type as_unsigned() const;

		/// @brief Gets the value as a floating point decimal value.
		/// 
		/// Attempts to convert the current value to a floating point decimal value
		/// and returns the result. If the value cannot be converted an exception is
		/// thrown.
		/// 
		/// @return The value as a floating point decimal value.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception positive_overflow_error The converted value is greater than 0 and does not fit in the signed value type.
		/// @exception negative_overflow_error The converted value is less than 0 and does not fit in the signed value type.
		/// @exception lexical_error The current string value cannot be converted.
		float_type as_float() const;

		/// @brief Gets the value as a double precision floating point decimal value.
		/// 
		/// Attempts to convert the current value to a double precision floating point
		/// decimal value and returns the result. If the value cannot be converted an
		/// exception is thrown.
		/// 
		/// @return The value as a double precision floating point decimal value.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception positive_overflow_error The converted value is greater than 0 and does not fit in the signed value type.
		/// @exception negative_overflow_error The converted value is less than 0 and does not fit in the signed value type.
		/// @exception lexical_error The current string value cannot be converted.
		double_type as_double() const;

		/// @brief Gets the value as a string.
		/// 
		/// Attempts to convert the current value to a string value and returns the result.
		/// If the value cannot be converted an exception is thrown.
		/// 
		/// @return The value as a string.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		string_type as_string() const;

		/// @brief Gets the value as a path
		/// 
		/// Attempts to convert the current value to a path and returns the result. If
		/// the current value is not a path or a string an exception is thrown.
		/// 
		/// @return The value as a path.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception lexical_error The current string value cannot be converted.
		path_type as_path() const;

		/// @brief Gets the value as a RGBA color value.
		/// 
		/// Attempts to convert the current value to a RGBA color value and returns the
		/// result. If the value cannot be converted an exception is thrown. If the
		/// source value is a boolean it will be converted to black with alpha set to
		/// fully opaque or if the source value is true it will be converted to white with
		/// alpha set to fully opaque. If the source value is a string is must be in an HTML
		/// like format prefixed with a hash symbol followed by 8 hexdecimal digits
		/// (i.e. "#RRGGBBAA"). 
		/// 
		/// @return The value as a RGBA color.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception positive_overflow_error The converted value is greater than 0 and
		/// does not fit in the signed value type representing an RGBA color value.
		/// @exception negative_overflow_error The converted value is less than 0 and does
		/// not fit in the signed value type representing an RGBA color value..
		/// @exception lexical_error The current string value is not the correct format
		/// and cannot be converted.
		color_type as_color() const;

		/// @brief Gets the value as a RGBA color value.
		/// 
		/// Attempts to convert the current value to a UUID value and returns the
		/// result. If the value cannot be converted an exception is thrown.
		/// 
		/// @return The value as a UUID.
		/// 
		/// @exception empty_cast_error The value is currently empty.
		/// @exception lexical_error The current string value is not the correct format
		/// and cannot be converted.
		uuid_type as_uuid() const;


	private:

		template<class OutputType_>
		OutputType_ convert_value_to_primitive() const;


	private:

		static const string_type false_string_;
		static const string_type true_string_;

		/// @brief The tag indicating the type of value currently held in value_.
		tag_type type_ = tag_type::Empty;

		/// @brief The value.
		storge_type	value_;
	};

}
