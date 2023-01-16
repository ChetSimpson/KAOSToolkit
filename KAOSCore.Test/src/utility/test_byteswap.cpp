// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/utility/bit.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>


namespace hypertech { namespace kaos { namespace core { namespace utility { namespace unittests
{

	TEST(test_byteswap, wchar_t)
	{
		EXPECT_EQ(byteswap(wchar_t(0x0102)), 0x0201);
	}

	TEST(test_byteswap, char16_t)
	{
		EXPECT_TRUE(byteswap(char16_t(0x0102)) == 0x0201);
	}

	TEST(test_byteswap, char32_t)
	{
		EXPECT_TRUE(byteswap(char32_t(0x01020304)) == 0x04030201);
	}

	TEST(test_byteswap, int8_t)
	{
		EXPECT_EQ(byteswap(int8_t(0x01)), 0x01);
	}

	TEST(test_byteswap, uint8_t)
	{
		EXPECT_EQ(byteswap(uint8_t(0x01)), 0x01);
	}

	TEST(test_byteswap, int16_t)
	{
		EXPECT_EQ(byteswap(int16_t(0x0102)), 0x0201);
	}

	TEST(test_byteswap, uint16_t)
	{
		EXPECT_EQ(byteswap(uint16_t(0x0102)), 0x0201);
	}

	TEST(test_byteswap, int32_t)
	{
		EXPECT_EQ(byteswap(int32_t(0x01020304)), 0x04030201);
	}

	TEST(test_byteswap, uint32_t)
	{
		EXPECT_EQ(byteswap(uint32_t(0x01020304)), 0x04030201U);
	}

	TEST(test_byteswap, int64_t)
	{
		EXPECT_EQ(byteswap(int64_t(0x0102030405060708)), 0x0807060504030201);
	}

	TEST(test_byteswap, uint64_t)
	{
		EXPECT_EQ(byteswap(uint64_t(0x0102030405060708)), 0x0807060504030201U);
	}

}}}}}
