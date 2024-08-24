// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once

namespace hypertech::kaos::core::types
{

	/// @brief A string literal accessible by constexpr expressions
	template<size_t Size_>
	struct string_literal_argument
	{
		/// @brief Create a constexpr string literal
		/// @param str Reference to a string literal as an array of type `char`
		constexpr string_literal_argument(const char(&str)[Size_])
		{
			std::copy_n(str, Size_, value);
		}

		/// @brief The string literal
		char value[Size_];
	};

}
