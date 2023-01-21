// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/attribute_extension.h>
#include <kaos/core/types/rgba_color.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech::kaos::core::types::unittests
{

	namespace
	{
		const attribute_extension::attribute_definition<nullptr_t> nullptr_attribute_def("attribute");
		const attribute_extension::attribute_definition<double> double_attribute_def("attribute");
		const attribute_extension::attribute_definition<unsigned> unsigned_attribute_def("attribute");
		const attribute_extension::attribute_definition<int> integer_attribute_def("attribute");
		const attribute_extension::attribute_definition<core::types::rgba_color> color_attribute_def("attribute");

	}
	TEST(test_attribute_extension, set_attribute)
	{
		attribute_extension subject;

		subject.set_attribute(nullptr_attribute_def, nullptr);
		EXPECT_TRUE(subject.has_attribute(nullptr_attribute_def));
	}

	TEST(test_attribute_extension, has_attribute)
	{
		attribute_extension subject;

		subject.set_attribute(nullptr_attribute_def, nullptr);
		EXPECT_TRUE(subject.has_attribute(nullptr_attribute_def));
	}

	TEST(test_attribute_extension, delete_attribute)
	{
		attribute_extension subject;

		subject.set_attribute(nullptr_attribute_def, {});
		EXPECT_TRUE(subject.has_attribute(nullptr_attribute_def));
		EXPECT_TRUE(subject.delete_attribute("attribute"));
		EXPECT_FALSE(subject.has_attribute(nullptr_attribute_def));
		EXPECT_FALSE(subject.delete_attribute("attribute"));
	}

	TEST(test_attribute_extension, get_attribute)
	{
		attribute_extension subject;

		subject.set_attribute(nullptr_attribute_def, nullptr);
		EXPECT_EQ(subject.get_attribute(nullptr_attribute_def), nullptr);
	}

	TEST(test_attribute_extension, get_attribute_no_exist)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(attribute_extension().get_attribute(nullptr_attribute_def)),
			core::exceptions::attribute_not_found_error,
			"attribute `attribute` not found");
	}

	TEST(test_attribute_extension, try_get_attribute)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));

		attribute_extension subject;

		subject.set_attribute(color_attribute_def, pixel_value);
		EXPECT_EQ(*subject.try_get_attribute(color_attribute_def).value(), pixel_value);
	}

	TEST(test_attribute_extension, try_get_attribute_no_exist)
	{
		EXPECT_FALSE(attribute_extension().try_get_attribute(color_attribute_def).has_value());
	}



	TEST(test_attribute_extension, get_attribute_type_mismatch)
	{
		attribute_extension subject;

		subject.set_attribute(unsigned_attribute_def, 100U);

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(subject.get_attribute(double_attribute_def)),
			core::exceptions::attribute_conversion_error,
			"bad any cast error encountered while converting attribute `attribute` to `double`");
	}

	TEST(test_attribute_extension, set_attribute_overrite)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));

		attribute_extension subject;

		subject.set_attribute(integer_attribute_def, 100);
		EXPECT_TRUE(subject.has_attribute(integer_attribute_def));
		EXPECT_EQ(subject.get_attribute(integer_attribute_def), 100);
		subject.set_attribute(color_attribute_def, pixel_value);
		EXPECT_EQ(subject.get_attribute(color_attribute_def), pixel_value);
	}

	TEST(test_attribute_extension, set_attribute_as_rvalue)
	{
		attribute_extension subject;

		subject.set_attribute(double_attribute_def, 100.);
		EXPECT_TRUE(subject.has_attribute(double_attribute_def));
		EXPECT_EQ(subject.get_attribute(double_attribute_def), 100);
	}

	TEST(test_attribute_extension, set_attribute_as_lvalue)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));
		attribute_extension subject;

		subject.set_attribute(color_attribute_def, pixel_value);
		EXPECT_TRUE(subject.has_attribute(color_attribute_def));
		EXPECT_EQ(subject.get_attribute(color_attribute_def), pixel_value);
	}

}
