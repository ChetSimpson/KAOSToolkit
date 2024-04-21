// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/resource_locator.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech::kaos::core::unittests
{

	namespace
	{

		class test_resource_locator : public ::testing::Test
		{
		protected:

			static inline const auto resource1_path = resource_locator::string_type("/mnt/d/sub/directory");
			static inline const auto resource2_path = resource_locator::string_type("/mnt/d/sub/sub/directory");
			static inline const auto resource3_path = resource_locator::string_type("/mnt/d/sub/sub/sub/directory");

			static inline const auto resource1 = resource_locator (resource1_path);
			static inline const auto resource2 = resource_locator (resource2_path);
			static inline const auto resource3 = resource_locator (resource3_path);
		};

	}

	TEST_F(test_resource_locator, default_ctor)
	{
		resource_locator locator;

		ASSERT_TRUE(locator.text().empty());
	}

	TEST_F(test_resource_locator, copy_ctor)
	{
		resource_locator resource(resource1);

		ASSERT_EQ(resource, resource1);
	}

	TEST_F(test_resource_locator, ctor_empty_filename)
	{
		resource_locator locator("");

		ASSERT_TRUE(locator.text().empty());
		ASSERT_EQ(locator.text(), "");
	}

	TEST_F(test_resource_locator, ctor_valid_path)
	{
		resource_locator locator(resource1_path);

		ASSERT_FALSE(locator.text().empty());
		ASSERT_EQ(locator.text(), resource1_path);
	}

	TEST_F(test_resource_locator, check_equal)
	{
		resource_locator local_resource1(resource1_path);
		resource_locator local_resource2(resource1_path);

		ASSERT_EQ(local_resource1, local_resource2);
		ASSERT_EQ(resource1, local_resource1);
		ASSERT_EQ(resource1, resource1);
	}

	TEST_F(test_resource_locator, check_not_equal)
	{
		ASSERT_NE(resource1, resource2);
		ASSERT_NE(resource1, resource3);
		ASSERT_NE(resource2, resource3);
	}

	TEST_F(test_resource_locator, assignment)
	{
		resource_locator locator1;

		ASSERT_NE(locator1, resource1);
		locator1 = resource1;
		ASSERT_EQ(locator1, resource1);
		locator1 = resource2;
		ASSERT_EQ(locator1, resource2);
		locator1 = resource3;
		ASSERT_EQ(locator1, resource3);
	}

}
