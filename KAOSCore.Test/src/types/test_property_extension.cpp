// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/property_extension.h>
#include <kaos/core/types/rgba_color.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech::kaos::core::types::unittests
{

	namespace
	{
		const property_extension::property_def<nullptr_t> nullptr_property_def("property");
		const property_extension::property_def<double> double_property_def("property");
		const property_extension::property_def<unsigned> unsigned_property_def("property");
		const property_extension::property_def<int> integer_property_def("property");
		const property_extension::property_def<core::types::rgba_color> color_property_def("property");

	}
	TEST(test_property_extension, set_property)
	{
		property_extension subject;

		subject.set_property(nullptr_property_def, nullptr);
		EXPECT_TRUE(subject.has_property(nullptr_property_def));
	}

	TEST(test_property_extension, has_property)
	{
		property_extension subject;

		subject.set_property(nullptr_property_def, nullptr);
		EXPECT_TRUE(subject.has_property(nullptr_property_def));
	}

	TEST(test_property_extension, delete_property)
	{
		property_extension subject;

		subject.set_property(nullptr_property_def, {});
		EXPECT_TRUE(subject.has_property(nullptr_property_def));
		EXPECT_TRUE(subject.delete_property("property"));
		EXPECT_FALSE(subject.has_property(nullptr_property_def));
		EXPECT_FALSE(subject.delete_property("property"));
	}

	TEST(test_property_extension, get_property)
	{
		property_extension subject;

		subject.set_property(nullptr_property_def, nullptr);
		EXPECT_EQ(subject.get_property(nullptr_property_def), nullptr);
	}

	TEST(test_property_extension, get_property_no_exist)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(property_extension().get_property(nullptr_property_def)),
			core::exceptions::attribute_not_found_error,
			"attribute `property` not found");
	}

	TEST(test_property_extension, try_get_property)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));

		property_extension subject;

		subject.set_property(color_property_def, pixel_value);
		EXPECT_EQ(*subject.try_get_property(color_property_def).value(), pixel_value);
	}

	TEST(test_property_extension, try_get_property_no_exist)
	{
		EXPECT_FALSE(property_extension().try_get_property(color_property_def).has_value());
	}



	TEST(test_property_extension, get_property_type_mismatch)
	{
		property_extension subject;

		subject.set_property(unsigned_property_def, 100U);

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(subject.get_property(double_property_def)),
			core::exceptions::attribute_conversion_error,
			"bad any cast error encountered while converting attribute `property` to `double`");
	}

	TEST(test_property_extension, set_property_overrite)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));

		property_extension subject;

		subject.set_property(integer_property_def, 100);
		EXPECT_TRUE(subject.has_property(integer_property_def));
		EXPECT_EQ(subject.get_property(integer_property_def), 100);
		subject.set_property(color_property_def, pixel_value);
		EXPECT_EQ(subject.get_property(color_property_def), pixel_value);
	}

	TEST(test_property_extension, set_property_as_rvalue)
	{
		property_extension subject;

		subject.set_property(double_property_def, 100.);
		EXPECT_TRUE(subject.has_property(double_property_def));
		EXPECT_EQ(subject.get_property(double_property_def), 100);
	}

	TEST(test_property_extension, set_property_as_lvalue)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));
		property_extension subject;

		subject.set_property(color_property_def, pixel_value);
		EXPECT_TRUE(subject.has_property(color_property_def));
		EXPECT_EQ(subject.get_property(color_property_def), pixel_value);
	}

}
