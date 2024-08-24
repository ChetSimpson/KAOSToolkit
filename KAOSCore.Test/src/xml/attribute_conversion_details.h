// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/xml/pugixml_extensions.h>
#include <map>

namespace hypertech::kaos::core::xml::unittests
{
	namespace
	{
		enum class test_enum
		{
			one,
			two,
			three
		};
	}
}

namespace pugi::details
{

	template<>
	struct attribute_conversion_details<hypertech::kaos::core::xml::unittests::test_enum>
	{
		using test_enum = hypertech::kaos::core::xml::unittests::test_enum;

		static inline const std::map<std::string, test_enum> string_to_enum_list
		{
			{"one", test_enum::one},
			{"two", test_enum::two},
			{"three", test_enum::three}
		};

		static inline const std::map<test_enum, std::string> enum_to_string_list
		{
			{test_enum::one, "one"},
			{test_enum::two, "two"},
			{test_enum::three, "three"},
		};
	};
}
