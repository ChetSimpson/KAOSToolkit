// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
///	@file
///	@brief Provides element value conversion support to Pugi XML library
#include <pugixml/pugixml.hpp>
#include <kaos/core/exceptions.h>
#include <kaos/core/type_traits.h>
#include <boost/algorithm/string.hpp>
#include <charconv>
#include <string>
#include <optional>


namespace pugi
{

	namespace details
	{

		using ::hypertech::kaos::core::integral_not_bool_v;

		/// @brief Converts a string of characters to a string value type.
		/// 
		/// Converts a string of characters to am string  value type.
		/// 
		/// @tparam Type_ The string type to convert it to (always `std::string`)
		/// 
		/// @param string_value The characters to convert
		/// @param output The converted string value
		/// 
		/// @return An instance of `std::from_chars_result` contaning a pointer to
		/// 1 past the last character converted and the status of the conversion.
		template<class Type_>
		[[nodiscard]] std::from_chars_result convert_from_chars(
			const std::string& string_value,
			Type_& output) requires std::is_same_v<Type_, std::string>
		{
			output = string_value;

			return {string_value.data() + string_value.size(), std::errc()};
		}


		/// @brief Converts a string of characters to an integral or decimal value type.
		/// 
		/// Converts a string of characters to a non-boolean integral or decimal value type.
		/// 
		/// @tparam Type_ The value type to convert to
		/// 
		/// @param string_value The characters to convert
		/// @param output The converted value
		/// 
		/// @return An instance of `std::from_chars_result` contaning a pointer to
		/// 1 past the last character converted and the status of the conversion.
		template<class Type_>
		[[nodiscard]] std::from_chars_result convert_from_chars(
			const std::string& string_value,
			Type_& output) requires integral_not_bool_v<Type_> || std::is_floating_point_v<Type_>
		{
			return std::from_chars(string_value.data(), string_value.data() + string_value.size(), output);
		}


		/// @brief Converts a string of characters to a boolean value type.
		/// 
		/// Converts a string of characters to a boolean value type. If the
		/// string of characters start with `true` or `false` or starts with
		/// an integer value from -1 to 1 they are converted. Otherwise
		/// an error is returned.
		/// 
		/// @tparam Type_ The value type to convert to (always `bool`)
		/// 
		/// @param string_value The characters to convert
		/// @param output The converted boolean value
		/// 
		/// @return An instance of `std::from_chars_result` contaning a pointer to
		/// 1 past the last character converted and the status of the conversion.
		template<class Type_>
		[[nodiscard]] std::from_chars_result convert_from_chars(
			const std::string& string_value,
			Type_& output) requires std::is_same_v<Type_, bool>
		{
			static const std::string true_string_("true");
			static const std::string false_string_("false");

			if (::boost::istarts_with(string_value, true_string_))
			{
				output = true;

				return { string_value.data() + true_string_.size(), std::errc() };
			}

			if (::boost::istarts_with(string_value, false_string_))
			{
				output = false;

				return { string_value.data() + false_string_.size(), std::errc() };
			}

			int64_t int_value;
			auto result(std::from_chars(string_value.data(), string_value.data() + string_value.size(), int_value));
			if (result.ec != std::errc())
			{
				return result;
			}

			if (int_value > 1 || int_value < -1)
			{
				return { result.ptr, std::errc::result_out_of_range };
			}

			output = int_value != 0;

			return result;
		}



		/// @brief Gets an attribute value from a node and converts to a specific type
		/// 
		/// Attempts to retrieve an attribute from an XML node and convert it to a
		/// specific value type. If the attribute exists and can be converted it is
		/// returned in a `std::optional`. If the attribute does not exist an empty
		/// `std::optional` is returned. If the attribute exists but an error occurs
		/// converting it to the specified value type and \p throw_on_conversion_error 
		/// is set to `true` the function will throw an exception otherwise it will
		/// will return an empty `std::optional`.
		/// 
		/// @tparam Type_ The type to convert the attribute to.
		/// @tparam ThrowIfNotFound_ If true the function will throw an exception if
		/// the attribute does not exist; otherwise it returns an empty `std::optional`
		/// if the attribute does not exist.
		/// 
		/// @param node The XML node containing the attribute.
		/// @param name The name of the attribute to convert.
		/// @param throw_on_conversion_error If true the function will throw an exception
		/// if the attribute cannot be converted; if false the function will return an
		/// empty value if the attribute cannot be converted.
		/// 
		/// @return If the attribute is converted a `std::optional` containing the value
		/// otherwise an empty `std::optional`.
		/// 
		/// @throws hypertech::kaos::core::exceptions::attribute_not_found_error If the
		/// attribute does not exist and \p ThrowIfNotFound_ is true.
		/// @throws hypertech::kaos::core::exceptions::attribute_conversion_error If the
		/// value cannot be converted and \p throw_on_conversion_error is `true`.
		template<class Type_, bool ThrowIfNotFound_>
		[[nodiscard]] std::optional<Type_> get_attribute_as(
			const xml_node& node,
			const std::string& name,
			bool throw_on_conversion_error)
		{
			auto attribute(node.attribute(name.c_str()));
			if (!attribute)
			{
				if constexpr (ThrowIfNotFound_)
				{
					throw ::hypertech::kaos::core::exceptions::attribute_not_found_error(name);
				}
				else
				{
					return {};
				}
			}

			std::string string_value(attribute.value());
			::boost::algorithm::trim(string_value);

			const auto is_negative((!string_value.empty() && string_value[0] == '-'));

			// First we need to check for negative to unsigned conversion since it will not
			// be picked up by from_chars
			if constexpr (std::is_unsigned_v<Type_>)
			{
				if (is_negative)
				{
					if (throw_on_conversion_error)
					{
						throw ::hypertech::kaos::core::exceptions::attribute_conversion_error(
							"negative overflow",
							name,
							typeid(Type_));
					}

					return {};
				}
			}



			Type_ converted_value;
			auto result(convert_from_chars(string_value, converted_value));

			// First we need to check for input that couldn't be parsed.
			if (result.ec == std::errc::invalid_argument)
			{
				if (throw_on_conversion_error)
				{
					throw ::hypertech::kaos::core::exceptions::attribute_conversion_error(
						"invalid input" ,
						name,
						typeid(Type_));
				}

				return {};
			}

			// Then we need to check for valid input that's out of range for the target data type.
			if (result.ec == std::errc::result_out_of_range)
			{
				if (throw_on_conversion_error)
				{
					if (is_negative)
					{
						throw ::hypertech::kaos::core::exceptions::attribute_conversion_error(
							"negative overflow",
							name,
							typeid(Type_));
					}

					throw ::hypertech::kaos::core::exceptions::attribute_conversion_error(
						"positive overflow",
						name,
						typeid(Type_));
				}

				return {};
			}

			// Then we'll check for unexpected errors we don't account for.
			if (result.ec != std::errc())
			{
				if (throw_on_conversion_error)
				{
					throw ::hypertech::kaos::core::exceptions::attribute_conversion_error(
						"lexical",
						name,
						typeid(Type_));
				}

				return {};
			}

			// Then we check for valid conversions that didn't process the entire string
			if (result.ptr != string_value.data() + string_value.size())
			{
				if (throw_on_conversion_error)
				{
					throw ::hypertech::kaos::core::exceptions::attribute_conversion_error(
						"partial conversion",
						name,
						typeid(Type_));
				}

				return {};
			}

			return converted_value;
		}

	}

	/// @brief Gets an attribute value from a node and converts to a specific type
	/// 
	/// Attempts to retrieve an attribute from an XML node and convert it to a
	/// specific value type. If the attribute exists and can be converted it is
	/// returned in a `std::optional`. If the attribute does not exist an empty
	/// `std::optional` is returned. If the attribute exists but an error occurs
	/// converting it to the specified value type and \p throw_on_conversion_error 
	/// is set to `true` the function will throw an exception otherwise it will
	/// will return an empty `std::optional`.
	/// 
	/// @tparam Type_ The type to convert the attribute to.
	/// 
	/// @param node The XML node containing the attribute.
	/// @param name The name of the attribute to convert.
	/// @param throw_on_conversion_error If true the function will throw an exception
	/// if the attribute cannot be converted; if false the function will return an
	/// empty value if the attribute cannot be converted.
	/// 
	/// @return If the attribute is converted a `std::optional` containing the value
	/// otherwise an empty `std::optional`.
	/// 
	/// @throws hypertech::kaos::core::exceptions::attribute_conversion_error If the
	/// value cannot be converted.
	template<class Type_>
	[[nodiscard]] std::optional<Type_> try_get_attribute_as(
		const xml_node& node,
		const std::string& name,
		bool throw_on_conversion_error = true)
	{
		return details::get_attribute_as<Type_, false>(node, name, throw_on_conversion_error);
	}

	/// @brief Gets an attribute value from a node and converts to a specific type
	/// 
	/// Retrieve an attribute from an XML node and converts it to a specific value
	/// type. If the attribute does not exist or an error occurs converting the
	/// attribute to the specified value type an exception is thrown.
	/// 
	/// @tparam Type_ The type to convert the attribute to.
	/// 
	/// @param node The XML node containing the attribute.
	/// @param name The name of the attribute to convert.
	/// 
	/// @return The converted attribute value.
	/// 
	/// @throws hypertech::kaos::core::exceptions::attribute_not_found_error If the
	/// attribute does not exist.
	/// @throws hypertech::kaos::core::exceptions::attribute_conversion_error If the
	/// value cannot be converted.
	template<class Type_>
	[[nodiscard]] Type_ get_attribute_as(const xml_node& node, const std::string& name)
	{
		return details::get_attribute_as<Type_, true>(node, name, true).value();
	}

	/// @brief Gets an attribute value from a node and converts to a specific type
	/// 
	/// Retrieve an attribute from an XML node and converts it to a specific value
	/// type. If the attribute does not exist a default value is returned. If an
	/// error occurs converting the attribute to the specified value type an
	/// exception is thrown.
	/// 
	/// @tparam Type_ The type to convert the attribute to.
	/// 
	/// @param node The XML node containing the attribute.
	/// @param name The name of the attribute to convert.
	/// @param default_value The value to return if the attribute does not exist.
	/// 
	/// @return The converted attribute value.
	/// 
	/// @throws hypertech::kaos::core::exceptions::attribute_not_found_error If the
	/// attribute does not exist.
	/// @throws hypertech::kaos::core::exceptions::attribute_conversion_error If the
	/// value cannot be converted.
	template<class Type_>
	[[nodiscard]] Type_ get_attribute_as(const xml_node& node, const std::string& name, const Type_& default_value)
	{
		auto value(details::get_attribute_as<Type_, false>(node, name, true));
		if (value.has_value())
		{
			return value.value();
		}

		return default_value;
	}

}
