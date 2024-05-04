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

			static inline const auto absolute_path_prefix = resource_locator::string_type("D:");
			//static inline const auto absolute_path_prefix = resource_locator::string_type("/mnt/d");

			static inline const auto resource_base_path = absolute_path_prefix + "/unit/test/project";
			static inline const auto resource_base = resource_locator(resource_base_path);

			static inline const auto resource1_absolute_path = resource_base_path + "/sub-a/directory";
			static inline const auto resource2_absolute_path = resource_base_path + "/sub-b/sub-c/directory";
			static inline const auto resource3_absolute_path = resource_base_path + "/sub-c/sub-d/sub-e/directory";

			static inline const auto resource1_abs = resource_locator(resource1_absolute_path);
			static inline const auto resource2_abs = resource_locator(resource2_absolute_path);
			static inline const auto resource3_abs = resource_locator(resource3_absolute_path);

			static inline const auto resource1_relative_path = resource_locator::string_type("../other_project");
			static inline const auto resource2_relative_path = resource_locator::string_type("../../other_test/project");
			static inline const auto resource3_relative_path = resource_locator::string_type("../../../other_unit/test/project");

			static inline const auto resource1_rel = resource_locator(resource1_relative_path);
			static inline const auto resource2_rel = resource_locator(resource2_relative_path);
			static inline const auto resource3_rel = resource_locator(resource3_relative_path);
		};

	}

	TEST_F(test_resource_locator, default_ctor)
	{
		resource_locator locator;

		ASSERT_TRUE(locator.text().empty());
	}

	TEST_F(test_resource_locator, copy_ctor)
	{
		resource_locator resource(resource1_abs);

		ASSERT_EQ(resource, resource1_abs);
	}

	TEST_F(test_resource_locator, ctor_empty_filename)
	{
		resource_locator locator("");

		ASSERT_TRUE(locator.text().empty());
		ASSERT_EQ(locator.text(), "");
	}

	TEST_F(test_resource_locator, ctor_valid_path)
	{
		resource_locator locator(resource1_absolute_path);

		ASSERT_FALSE(locator.text().empty());
		ASSERT_EQ(locator.text(), resource1_absolute_path);
	}

	TEST_F(test_resource_locator, check_equal)
	{
		resource_locator local_resource1(resource1_absolute_path);
		resource_locator local_resource2(resource1_absolute_path);

		ASSERT_EQ(local_resource1, local_resource2);
		ASSERT_EQ(resource1_abs, local_resource1);
		ASSERT_EQ(resource1_abs, resource1_abs);
	}

	TEST_F(test_resource_locator, check_not_equal)
	{
		ASSERT_NE(resource1_abs, resource2_abs);
		ASSERT_NE(resource1_abs, resource3_abs);
		ASSERT_NE(resource2_abs, resource3_abs);
	}

	TEST_F(test_resource_locator, assignment)
	{
		resource_locator locator1;

		ASSERT_NE(locator1, resource1_abs);
		locator1 = resource1_abs;
		ASSERT_EQ(locator1, resource1_abs);
		locator1 = resource2_abs;
		ASSERT_EQ(locator1, resource2_abs);
		locator1 = resource3_abs;
		ASSERT_EQ(locator1, resource3_abs);
	}

	TEST_F(test_resource_locator, make_relative_of_absolute)
	{
		const auto result(resource2_abs.make_relative_of(resource1_abs));

		ASSERT_EQ(result.text(), "/mnt/d/sub-b/directory");

	}

}
