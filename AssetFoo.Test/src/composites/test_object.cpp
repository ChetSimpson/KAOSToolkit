// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/composites/object.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech::kaos::assetfoo::composites::unit_tests
{

	TEST(test_object, default_ctor)
	{
		object obj;

		EXPECT_FALSE(obj.has_name());
		EXPECT_THROW(DEBUG_DiscardResult(obj.name()), std::bad_optional_access);

		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);

		EXPECT_EQ(obj.position(), object::position_type());
	}

	TEST(test_object, ctor_name_classtype_position_defaults)
	{
		object obj({}, {}, {});

		EXPECT_FALSE(obj.has_name());
		EXPECT_THROW(DEBUG_DiscardResult(obj.name()), std::bad_optional_access);

		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);

		EXPECT_EQ(obj.position(), object::position_type());
	}

	TEST(test_object, ctor_empty_name)
	{
		EXPECT_THROWS_MESSAGE(
			object("", {}, {}),
			std::invalid_argument,
			"object name cannot be empty");
	}

	TEST(test_object, ctor_empty_class_type)
	{
		EXPECT_THROWS_MESSAGE(
			object({}, "", {}),
			std::invalid_argument,
			"object class type cannot be empty");
	}

	TEST(test_object, ctor_name)
	{
		object obj("object name", {}, {});

		EXPECT_TRUE(obj.has_name());
		EXPECT_EQ(obj.name(), "object name");
	}

	TEST(test_object, ctor_class_type)
	{
		object obj({}, "class type", {});

		EXPECT_TRUE(obj.has_class_type());
		EXPECT_EQ(obj.class_type(), "class type");
	}

	TEST(test_object, ctor_position)
	{
		object obj({}, {}, {100.0f, 200.0f});

		EXPECT_EQ(obj.position(), object::position_type(100.0f, 200.0f));
	}


	TEST(test_object, set_name)
	{
		object obj;

		obj.set_name("object name");
		EXPECT_TRUE(obj.has_name());
		EXPECT_EQ(obj.name(), "object name");
	}

	TEST(test_object, remove_name)
	{
		object obj("object name", {}, {});

		EXPECT_TRUE(obj.has_name());
		EXPECT_EQ(obj.name(), "object name");
		obj.remove_name();
		EXPECT_FALSE(obj.has_name());
		EXPECT_THROW(DEBUG_DiscardResult(obj.name()), std::bad_optional_access);
	}

	TEST(test_object, set_class_type)
	{
		object obj;

		obj.set_class_type("class type");
		EXPECT_TRUE(obj.has_class_type());
		EXPECT_EQ(obj.class_type(), "class type");
		obj.remove_class_type();
		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);
	}

	TEST(test_object, remove_class_type)
	{
		object obj({}, "class type", {});

		EXPECT_TRUE(obj.has_class_type());
		EXPECT_EQ(obj.class_type(), "class type");
		obj.remove_class_type();
		EXPECT_FALSE(obj.has_class_type());
		EXPECT_THROW(DEBUG_DiscardResult(obj.class_type()), std::bad_optional_access);
	}

	TEST(test_object, set_position)
	{
		object obj;

		obj.set_position({ 100.0f, 200.0f });
		EXPECT_EQ(obj.position(), object::position_type(100.0f, 200.0f));
	}

}
