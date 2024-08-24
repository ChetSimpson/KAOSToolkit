// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/composites/objects/ellipse.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech::kaos::assetfoo::composites::objects::unit_tests
{

	TEST(test_ellipse, default_ctor)
	{
		ellipse obj;

		EXPECT_FALSE(obj.has_name());
		EXPECT_THROW(DEBUG_DiscardResult(obj.name()), std::bad_optional_access);

		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);

		EXPECT_EQ(obj.position(), ellipse::position_type());
		EXPECT_EQ(obj.dimensions(), ellipse::dimensions_type());
	}

	TEST(test_ellipse, ctor_name_classtype_position_dimensions_defaults)
	{
		ellipse obj({}, {}, {}, {});

		EXPECT_FALSE(obj.has_name());
		EXPECT_THROW(DEBUG_DiscardResult(obj.name()), std::bad_optional_access);

		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);

		EXPECT_EQ(obj.position(), ellipse::position_type());
		EXPECT_EQ(obj.dimensions(), ellipse::dimensions_type());
	}

	TEST(test_ellipse, ctor_empty_name)
	{
		EXPECT_THROWS_MESSAGE(
			ellipse("", {}, {}, {}),
			std::invalid_argument,
			"object name cannot be empty");
	}

	TEST(test_ellipse, ctor_empty_class_type)
	{
		EXPECT_THROWS_MESSAGE(
			ellipse({}, "", {}, {}),
			std::invalid_argument,
			"object class type cannot be empty");
	}

	TEST(test_ellipse, ctor_position)
	{
		ellipse obj({}, {}, { 100.0f, 200.0f }, {});

		EXPECT_EQ(obj.position(), ellipse::position_type(100.0f, 200.0f));
	}

	TEST(test_ellipse, ctor_dimensions_only)
	{
		ellipse obj({}, {}, {}, {100, 200});

		EXPECT_EQ(obj.dimensions(), ellipse::dimensions_type(100, 200));
	}

	TEST(test_ellipse, set_dimensions)
	{
		ellipse obj;

		obj.set_dimensions({ 100.0f, 200.0f });
		EXPECT_EQ(obj.dimensions(), ellipse::dimensions_type(100.0f, 200.0f));
	}

}
