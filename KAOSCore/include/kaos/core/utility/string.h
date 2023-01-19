// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <string>


//	TODO: This is currently not used. Delete and switch to using boost::algorithm::trim* functions


namespace hypertech::kaos::core::utility::strings
{

	/// @brief Trim spaces from the beginning of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A reference to \p value after spaces have been trimmed.
	template<class Type_>
	inline std::basic_string<Type_>& trim_left(std::basic_string<Type_>& value)
	{
		value.erase(value.begin(), find_if(value.begin(), value.end(), [](unsigned char ch) { return !std::isspace(ch); }));

		return value;
	}

	/// @brief Trim spaces from the beginning of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A reference to \p value after spaces have been trimmed.
	template<class Type_>
	inline std::basic_string<Type_>&& trim_left(std::basic_string<Type_>&& value)
	{
		return move(trim_left(value));
	}


	/// @brief Trim spaces from the end of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A reference to \p value after spaces have been trimmed.
	template<class Type_>
	inline std::basic_string<Type_>& trim_right(std::basic_string<Type_> &value)
	{
		value.erase(find_if(value.rbegin(), value.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), value.end());

		return value;
	}

	/// @brief Trim spaces from the end of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A reference to \p value after spaces have been trimmed.
	template<class Type_>
	inline std::basic_string<Type_>&& trim_right(std::basic_string<Type_>&& value)
	{
		return move(trim_right(value));
	}


	/// @brief Trim spaces from the beginning and end of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A reference to \p value after spaces have been trimmed.
	template<class Type_>
	inline std::basic_string<Type_>& trim(std::basic_string<Type_>& value)
	{
		return trim_right(trim_left(value));
	}

	/// @brief Trim spaces from the beginning and end of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A reference to \p value after spaces have been trimmed.
	template<class Type_>
	inline std::basic_string<Type_>&& trim(std::basic_string<Type_>&& value)
	{
		return move(trim(value));
	}

	/// @brief Trim spaces from the beginning of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A copy of \p value with spaces removed from the beginning and end
	template<class Type_>
	inline std::basic_string<Type_> trim_left_copy(std::basic_string<Type_> value)
	{
		return trim_left(value);
	}

	/// @brief Trim spaces from the end of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A copy of \p value with spaces removed from the beginning and end
	template<class Type_>
	inline std::basic_string<Type_> trim_right_copy(std::basic_string<Type_> value)
	{
		return trim_right(value);
	}

	/// @brief Trim spaces from the beginning and end of a string
	/// 
	/// @tparam Type_ Character type of the string
	/// 
	/// @param value string value
	/// 
	/// @return A copy of \p value with spaces removed from the beginning and end
	template<class Type_>
	inline std::basic_string<Type_> trim_copy(std::basic_string<Type_> value)
	{
		return trim(value);
	}

}
