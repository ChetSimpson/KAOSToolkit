// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include "attribute_conversion_details.h"
#include <kaos/core/xml/pugixml_extensions.h>
#include <gtest/gtest.h>

namespace hypertech::kaos::core::xml::unittests
{

	using pugi::xml_document;
	using pugi::xml_node;
	using pugi::xml_attribute;

	TEST(test_append_attribute_as_enum, convert_valid_value)
	{
		xml_document document;
		xml_node node(document.append_child("node"));

		EXPECT_STREQ(pugi::append_attribute(node, "one", test_enum::one).value(), "one");
		EXPECT_STREQ(pugi::append_attribute(node, "two", test_enum::two).value(), "two");
		EXPECT_STREQ(pugi::append_attribute(node, "three", test_enum::three).value(), "three");
	}

}
