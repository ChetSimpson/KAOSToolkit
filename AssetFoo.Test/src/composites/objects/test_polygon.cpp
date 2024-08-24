// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/composites/objects/polygon.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech::kaos::assetfoo::composites::objects::unit_tests
{

	TEST(test_polygon, default_ctor)
	{
		polygon obj;

		EXPECT_FALSE(obj.has_name());
		EXPECT_THROW(DEBUG_DiscardResult(obj.name()), std::bad_optional_access);

		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);

		EXPECT_EQ(obj.position(), polygon::position_type());
		EXPECT_EQ(obj.count(), 0);
	}

	TEST(test_polygon, ctor_name_classtype_position_dimensions_defaults)
	{
		polygon obj({}, {}, {}, {});

		EXPECT_FALSE(obj.has_name());
		EXPECT_THROW(DEBUG_DiscardResult(obj.name()), std::bad_optional_access);

		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);

		EXPECT_EQ(obj.position(), polygon::position_type());
		EXPECT_EQ(obj.count(), 0);
	}

	TEST(test_polygon, ctor_empty_name)
	{
		EXPECT_THROWS_MESSAGE(
			polygon("", {}, {}, {}),
			std::invalid_argument,
			"object name cannot be empty");
	}

	TEST(test_polygon, ctor_empty_class_type)
	{
		EXPECT_THROWS_MESSAGE(
			polygon({}, "", {}, {}),
			std::invalid_argument,
			"object class type cannot be empty");
	}

	TEST(test_polygon, ctor_position)
	{
		polygon obj({}, {}, { 100.0f, 200.0f }, {});

		EXPECT_EQ(obj.position(), polygon::position_type(100.0f, 200.0f));
	}

	static const polygon::point_list_type test_points
	{
		{100, 100},
		{150, 100},
		{150, 150},
		{100, 150}
	};

	TEST(test_polygon, ctor_points)
	{
		polygon obj({}, {}, {}, test_points);

		EXPECT_EQ(obj.count(), test_points.size());
		EXPECT_TRUE(std::equal(obj.begin(), obj.end(), test_points.begin(), test_points.end()));
	}
}
