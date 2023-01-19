// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <type_traits>


namespace hypertech::kaos::core
{

	template<class Type_>
	concept integral_not_bool_v = std::is_integral_v<Type_> && !std::is_same_v<Type_, bool>;

	template <class Type_>
	struct integral_not_bool : std::bool_constant<integral_not_bool_v<Type_>> {};

}
