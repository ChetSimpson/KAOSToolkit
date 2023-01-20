// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/asset.h>
#include <kaos/core/types/rgba_color.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>

namespace hypertech::kaos::assetfoo::unittests
{

#pragma region Properties
	TEST(test_asset, set_property)
	{
		asset subject;

		subject.set_property("property", {});
		EXPECT_TRUE(subject.has_property("property"));
	}

	TEST(test_asset, has_property)
	{
		asset subject;

		subject.set_property("property", nullptr);
		EXPECT_TRUE(subject.has_property("property"));
	}

	TEST(test_asset, delete_property)
	{
		asset subject;

		subject.set_property("property", {});
		EXPECT_TRUE(subject.has_property("property"));
		subject.delete_property("property");
		EXPECT_FALSE(subject.has_property("property"));
	}

	TEST(test_asset, get_property)
	{
		asset subject;

		subject.set_property("property", nullptr);
		EXPECT_EQ(any_cast<nullptr_t>(subject.get_property("property")), nullptr);
	}

	TEST(test_asset, get_property_no_exist)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(asset().get_property("property")),
			core::exceptions::attribute_not_found_error,
			"attribute `property` not found");
	}

	TEST(test_asset, try_get_property)
	{
		asset subject;

		subject.set_property("property", nullptr);
		EXPECT_EQ(any_cast<nullptr_t>(subject.try_get_property("property")), nullptr);
	}

	TEST(test_asset, try_get_property_no_exist)
	{
		EXPECT_FALSE(asset().try_get_property("property").has_value());
	}

	TEST(test_asset, get_property_as)
	{
		asset subject;

		subject.set_property("property", 100U);
		EXPECT_EQ(subject.get_property_as<unsigned>("property"), 100U);
	}

	TEST(test_asset, get_property_as_no_exist)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(asset().get_property_as<int>("property")),
			core::exceptions::attribute_not_found_error,
			"attribute `property` not found");
	}

	TEST(test_asset, get_property_as_type_mismatch)
	{
		asset subject;

		subject.set_property("property", 100U);

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(subject.get_property_as<float>("property")),
			core::exceptions::attribute_conversion_error,
			"bad any cast error encountered while converting attribute `property` to `float`");
	}

	TEST(test_asset, set_property_overrite)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));

		asset subject;

		subject.set_property("property", 100);
		EXPECT_TRUE(subject.has_property("property"));
		EXPECT_EQ(subject.get_property_as<int>("property"), 100);
		subject.set_property("property", pixel_value);
		EXPECT_EQ(subject.get_property_as<core::types::rgba_color>("property"), pixel_value);
	}

	TEST(test_asset, set_property_as_rvalue)
	{
		asset subject;

		subject.set_property_as<double>("property", 100);
		EXPECT_TRUE(subject.has_property("property"));
		EXPECT_EQ(subject.get_property_as<double>("property"), 100);
	}

	TEST(test_asset, set_property_as_lvalue)
	{
		const auto pixel_value(core::types::rgba_color(1, 2, 3, 4));
		asset subject;

		subject.set_property_as<core::types::rgba_color>("property", pixel_value);
		EXPECT_TRUE(subject.has_property("property"));
		EXPECT_EQ(subject.get_property_as<core::types::rgba_color>("property"), pixel_value);
	}
#pragma endregion

}
