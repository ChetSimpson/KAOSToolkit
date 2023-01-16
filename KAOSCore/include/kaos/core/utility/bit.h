// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <bit>
#include <algorithm>
#include <array>


namespace hypertech { namespace kaos { namespace core { namespace utility
{

	//	NOTE: Swap to std implementation when switched to C++23 (this was taken from cppreference.com)
	
	/// @brief Reverses the bytes in the given integer \p value.
	/// 
	/// byteswap participates in overload resolution only if Type_ satisfies
	/// integral, i.e., Type_ is an integer type. The program is ill-formed
	/// if Type_ has padding bits.
	/// 
	/// @param value interger value
	/// 
	/// @return An integer value of type Type_ whose object representation
	/// comprises the bytes of that of \p value in reversed order.
	template<std::integral Type_>
	requires std::is_integral_v<Type_>
	constexpr Type_ byteswap(Type_ value) noexcept
	{
		static_assert(
			std::has_unique_object_representations_v<Type_>, 
			"Type_ may not have padding bits");

		auto value_representation = std::bit_cast<std::array<std::byte, sizeof(Type_)>>(value);
		std::ranges::reverse(value_representation);
		return std::bit_cast<Type_>(value_representation);
	}

}}}}
