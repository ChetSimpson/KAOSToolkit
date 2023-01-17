// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once

#define EXPECT_THROWS_MESSAGE(expr, except, message)	\
	EXPECT_THROW(										\
	{													\
		try { expr; }									\
		catch( const except& e )						\
		{												\
			EXPECT_STREQ( message, e.what() );			\
			throw;										\
		}												\
	}, except );


#define ASSERT_THROWS_MESSAGE(expr, except, message)	\
	ASSERT_THROW(										\
	{													\
		try { expr; }									\
		catch( const except& e )						\
		{												\
			ASSERT_STREQ( message, e.what() );			\
			throw;										\
		}												\
	}, except );

//	FIXME: Rename to TEST_DiscardResult
#define DEBUG_DiscardResult(x) ((void)(x))

#define KAOS_DEATH_TEST(test_case_name, test_name)						\
	class GTEST_TEST_CLASS_NAME_(test_case_name, test_name) {			\
		void GTEST_TEST_CLASS_NAME_(test_case_name##notrun, test_name)();	\
	};																	\
	void GTEST_TEST_CLASS_NAME_(test_case_name##notrun, test_name)()
