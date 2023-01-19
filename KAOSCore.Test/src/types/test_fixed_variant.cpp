// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/fixed_variant.h>
#include <kaos/core/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <typeinfo>


namespace hypertech { namespace kaos { namespace core { namespace types { namespace unittests
{

	namespace
	{
		constexpr auto integer_type_max(std::numeric_limits<fixed_variant::integer_type>::max());
		constexpr auto integer_type_min(std::numeric_limits<fixed_variant::integer_type>::min());
		constexpr auto unsigned_type_max(std::numeric_limits<fixed_variant::unsigned_type>::max());
		constexpr auto float_type_max(std::numeric_limits<fixed_variant::float_type>::max());
		constexpr auto float_type_min(std::numeric_limits<fixed_variant::float_type>::min());
		constexpr auto double_type_max(std::numeric_limits<fixed_variant::double_type>::max());
		constexpr auto double_type_min(std::numeric_limits<fixed_variant::double_type>::min());

		const auto color1int(int32_t(0x0055AAFF));
		const auto color2int(int32_t(0xFFAA5500));

		const auto color1uint(uint32_t(0x0055AAFF));
		const auto color2uint(uint32_t(0xFFAA5500));

		const auto color1color(fixed_variant::color_type(0x00, 0x55, 0xAA, 0xFF));
		const auto color2color(fixed_variant::color_type(0xFF, 0xAA, 0x55, 0x00));

		const auto color1value{fixed_variant(color1color)};
		const auto color2value{fixed_variant(color2color)};
	}



#pragma region Empty value
	TEST(fixed_variant, create_empty)
	{
		EXPECT_EQ(fixed_variant().type(), fixed_variant::tag_type::Empty);
	}

	TEST(fixed_variant, convert_empty_to_boolean)
	{
		EXPECT_THROW(fixed_variant().as_boolean(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_boolean_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_boolean();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_empty_to_integer)
	{
		EXPECT_THROW(fixed_variant().as_integer(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_integer_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_integer();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_empty_to_unsigned)
	{
		EXPECT_THROW(fixed_variant().as_unsigned(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_unsigned_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_unsigned();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_empty_to_float)
	{
		EXPECT_THROW(fixed_variant().as_float(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_float_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_float();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::float_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_empty_to_double)
	{
		EXPECT_THROW(fixed_variant().as_double(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_double_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_double();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::double_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_empty_to_string)
	{
		EXPECT_THROW(fixed_variant().as_string(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_string_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_string();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::string_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_empty_to_path)
	{
		EXPECT_THROW(fixed_variant().as_path(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_path();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::path_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_empty_to_color)
	{
		EXPECT_THROW(fixed_variant().as_color(), exceptions::empty_cast_error);
	}

	TEST(fixed_variant, convert_empty_to_color_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant().as_color();
		}
		catch (exceptions::empty_cast_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(void));
			EXPECT_EQ(e.target(), typeid(fixed_variant::color_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, assign_empty)
	{
		fixed_variant v(fixed_variant::boolean_type(false));

		EXPECT_EQ(v.type(), fixed_variant::tag_type::Boolean);
		v = nullptr;
		EXPECT_EQ(v.type(), fixed_variant::tag_type::Empty);
	}
#pragma endregion


#pragma region Boolean value
	TEST(fixed_variant, create_boolean)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).type(), fixed_variant::tag_type::Boolean);
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).type(), fixed_variant::tag_type::Boolean);
	}

	TEST(fixed_variant, assign_boolean)
	{
		fixed_variant value;

		EXPECT_EQ(value.type(), fixed_variant::tag_type::Empty);
		value = true;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Boolean);
		EXPECT_TRUE(value.as_boolean());
		value = false;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Boolean);
		EXPECT_FALSE(value.as_boolean());
	}

	TEST(fixed_variant, convert_boolean_to_boolean)
	{
		//	bool -> bool
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).as_boolean(), false);
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).as_boolean(), true);
	}

	TEST(fixed_variant, convert_boolean_to_integer)
	{
		//	bool -> int
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).as_integer(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).as_integer(), 1);
	}

	TEST(fixed_variant, convert_boolean_to_unsigned)
	{
		//	bool -> unsigned
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).as_unsigned(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).as_unsigned(), 1);
	}

	TEST(fixed_variant, convert_boolean_to_float)
	{
		//	bool -> float
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).as_float(), 0.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).as_float(), 1.0f);
	}

	TEST(fixed_variant, convert_boolean_to_double)
	{
		//	bool -> double
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).as_double(), 0.0);
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).as_double(), 1.0);
	}

	TEST(fixed_variant, convert_boolean_to_string)
	{
		//	bool -> string
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).as_string(), "false");
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).as_string(), "true");
	}

	TEST(fixed_variant, convert_boolean_to_path)
	{
		//	bool -> path
		EXPECT_THROW(fixed_variant(fixed_variant::boolean_type(false)).as_path(), exceptions::incompatible_type_error);
		EXPECT_THROW(fixed_variant(fixed_variant::boolean_type(true)).as_path(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_boolean_to_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::boolean_type(true)).as_path();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::boolean_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::path_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_boolean_to_color)
	{
		//	bool -> color
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(false)).as_color(), fixed_variant::color_type());
		EXPECT_EQ(fixed_variant(fixed_variant::boolean_type(true)).as_color(), fixed_variant::color_type(255, 255, 255));
	}
#pragma endregion


#pragma region Integer value
	TEST(fixed_variant, create_integer)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(1)).type(), fixed_variant::tag_type::Integer);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-1)).type(), fixed_variant::tag_type::Integer);
	}

	TEST(fixed_variant, assign_integer)
	{
		fixed_variant value;

		EXPECT_EQ(value.type(), fixed_variant::tag_type::Empty);
		value = 5LL;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Integer);
		EXPECT_EQ(value.as_integer(), 5);
		value = 7LL;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Integer);
		EXPECT_EQ(value.as_integer(), 7);
	}

	TEST(fixed_variant, convert_integer_to_boolean)
	{
		//	int -> bool
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(0)).as_boolean(), false);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(1)).as_boolean(), true);
		EXPECT_THROW(fixed_variant(fixed_variant::integer_type(2)).as_boolean(), exceptions::positive_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::integer_type(-1)).as_boolean(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::integer_type(-2)).as_boolean(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_integer_to_boolean_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::integer_type(2)).as_boolean();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::integer_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(fixed_variant::integer_type(-2)).as_boolean();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::integer_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_integer_to_integer)
	{
		//	int -> int
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(0)).as_integer(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(1)).as_integer(), 1);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(2)).as_integer(), 2);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-1)).as_integer(), -1);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-2)).as_integer(), -2);
	}

	TEST(fixed_variant, convert_integer_to_unsigned)
	{
		//	int -> unsigned
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(0)).as_unsigned(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(1)).as_unsigned(), 1);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(2)).as_unsigned(), 2);
		EXPECT_THROW(fixed_variant(fixed_variant::integer_type(-1)).as_unsigned(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::integer_type(-2)).as_unsigned(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_integer_to_unsigned_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::integer_type(-1)).as_unsigned();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::integer_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_integer_to_float)
	{
		//	int -> float
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(0)).as_float(), 0.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(1)).as_float(), 1.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(2)).as_float(), 2.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-1)).as_float(), -1.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-2)).as_float(), -2.0f);
	}

	TEST(fixed_variant, convert_integer_to_double)
	{
		//	int -> double
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(0)).as_double(), 0.0);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(1)).as_double(), 1.0);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(2)).as_double(), 2.0);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-1)).as_double(), -1.0);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-2)).as_double(), -2.0);
	}

	TEST(fixed_variant, convert_integer_to_string)
	{
		//	int -> string
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(0)).as_string(), "0");
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(1)).as_string(), "1");
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(2)).as_string(), "2");
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-1)).as_string(), "-1");
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(-2)).as_string(), "-2");
	}

	TEST(fixed_variant, convert_integer_to_path)
	{
		//	int -> path
		EXPECT_THROW(fixed_variant(fixed_variant::integer_type(0)).as_path(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_integer_to_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::integer_type(0)).as_path();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::integer_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::path_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_integer_to_color)
	{
		//	int -> color
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(color1int)).as_color(), color1color);
		EXPECT_EQ(fixed_variant(fixed_variant::integer_type(color2int)).as_color(), color2color);
	}
#pragma endregion


#pragma region Unsigned value
	TEST(fixed_variant, create_unsigned)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(0)).type(), fixed_variant::tag_type::Unsigned);
	}

	TEST(fixed_variant, assign_unsigned)
	{
		fixed_variant value;

		EXPECT_EQ(value.type(), fixed_variant::tag_type::Empty);
		value = 5ULL;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Unsigned);
		EXPECT_EQ(value.as_unsigned(), 5);
		value = 7ULL;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Unsigned);
		EXPECT_EQ(value.as_unsigned(), 7);
	}

	TEST(fixed_variant, convert_unsigned_to_boolean)
	{
		//	unsigned -> bool
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(0)).as_boolean(), false);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(1)).as_boolean(), true);
		EXPECT_THROW(fixed_variant(fixed_variant::unsigned_type(2)).as_boolean(), exceptions::positive_overflow_error);
	}

	TEST(fixed_variant, convert_unsigned_to_boolean_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::unsigned_type(2)).as_boolean();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::unsigned_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_unsigned_to_integer)
	{
		//	unsigned -> int
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(0)).as_integer(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(1)).as_integer(), 1);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(2)).as_integer(), 2);
		EXPECT_THROW(fixed_variant(unsigned_type_max).as_integer(), exceptions::positive_overflow_error);
	}

	TEST(fixed_variant, convert_unsigned_to_integer_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(unsigned_type_max).as_integer();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::unsigned_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_unsigned_to_unsigned)
	{
		//	unsigned -> unsigned
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(0)).as_unsigned(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(1)).as_unsigned(), 1);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(2)).as_unsigned(), 2);
		EXPECT_EQ(fixed_variant(unsigned_type_max).as_unsigned(), unsigned_type_max);
	}

	TEST(fixed_variant, convert_unsigned_to_float)
	{
		//	unsigned -> float
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(0)).as_float(), 0.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(1)).as_float(), 1.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(2)).as_float(), 2.0f);
	}

	TEST(fixed_variant, convert_unsigned_to_double)
	{
		//	unsigned -> double
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(0)).as_double(), 0.0);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(1)).as_double(), 1.0);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(2)).as_double(), 2.0);
	}

	TEST(fixed_variant, convert_unsigned_to_string)
	{
		//	unsigned -> string
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(0)).as_string(), "0");
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(1)).as_string(), "1");
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(2)).as_string(), "2");
	}

	TEST(fixed_variant, convert_unsigned_to_path)
	{
		//	unsigned -> path
		EXPECT_THROW(fixed_variant(fixed_variant::unsigned_type(0)).as_path(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_unsigned_to_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::unsigned_type(0)).as_path();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::unsigned_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::path_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_unsigned_to_color)
	{
		//	unsigned -> color
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(color1uint)).as_color(), color1color);
		EXPECT_EQ(fixed_variant(fixed_variant::unsigned_type(color2uint)).as_color(), color2color);
	}
#pragma endregion


#pragma region Float value
	TEST(fixed_variant, create_float)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0)).type(), fixed_variant::tag_type::Float);
	}

	TEST(fixed_variant, assign_float)
	{
		fixed_variant value;

		EXPECT_EQ(value.type(), fixed_variant::tag_type::Empty);
		value = 5.f;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Float);
		EXPECT_EQ(value.as_float(), 5.f);
		value = 7.f;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Float);
		EXPECT_EQ(value.as_float(), 7.f);
	}

	TEST(fixed_variant, convert_float_to_boolean)
	{
		//	float -> bool
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.0f)).as_boolean(), false);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.5f)).as_boolean(), false);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(1.0f)).as_boolean(), true);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(2.0f)).as_boolean(), exceptions::positive_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(-0.5f)).as_boolean(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(-1.0f)).as_boolean(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(-2.0f)).as_boolean(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_float_to_boolean_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::float_type(2.0f)).as_boolean();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::float_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(fixed_variant::float_type(-2.0f)).as_boolean();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::float_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_float_to_integer)
	{
		//	float -> int
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.0f)).as_integer(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.5f)).as_integer(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(5.0f)).as_integer(), 5);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(-5.0f)).as_integer(), -5);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(float_type_max)).as_integer(), exceptions::positive_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(-float_type_max)).as_integer(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_float_to_integer_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::float_type(float_type_max)).as_integer();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::float_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(fixed_variant::float_type(-float_type_max)).as_integer();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::float_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_float_to_unsigned)
	{
		//	float -> unsigned
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.0f)).as_unsigned(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.5f)).as_unsigned(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(1.0f)).as_unsigned(), 1);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(2.0f)).as_unsigned(), 2);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(-0.5f)).as_unsigned(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(-1.0f)).as_unsigned(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(-2.0f)).as_unsigned(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_float_to_unsigned_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::float_type(-1.0f)).as_unsigned();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::float_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_float_to_float)
	{
		//	float -> float
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.0f)).as_float(), 0.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.5f)).as_float(), 0.5f);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(5.0f)).as_float(), 5.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(-5.0f)).as_float(), -5.0f);
	}

	TEST(fixed_variant, convert_float_to_double)
	{
		//	float -> double
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.0f)).as_double(), 0.0);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.5f)).as_double(), 0.5);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(5.0f)).as_double(), 5.0);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(-5.0f)).as_double(), -5.0);
	}

	TEST(fixed_variant, convert_float_to_string)
	{
		//	float -> string
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.0f)).as_string(), "0");
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(0.5f)).as_string(), "0.5");
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(5.0f)).as_string(), "5");
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(-5.0f)).as_string(), "-5");
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(-5.456f)).as_string(), "-5.456");
	}

	TEST(fixed_variant, convert_float_to_path)
	{
		//	float -> path
		EXPECT_THROW(fixed_variant(fixed_variant::float_type(0)).as_path(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_float_to_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::float_type(0)).as_path();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::float_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::path_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_float_to_color)
	{
		//	float -> color
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(color1int)).as_color(), color1color);
		EXPECT_EQ(fixed_variant(fixed_variant::float_type(color2int)).as_color(), color2color);
	}
#pragma endregion


#pragma region Double precision value
	TEST(fixed_variant, create_double)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0)).type(), fixed_variant::tag_type::Double);
	}

	TEST(fixed_variant, assign_double)
	{
		fixed_variant value;

		EXPECT_EQ(value.type(), fixed_variant::tag_type::Empty);
		value = 5.0;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Double);
		EXPECT_EQ(value.as_double(), 5.f);
		value = 7.0;
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Double);
		EXPECT_EQ(value.as_double(), 7.f);
	}

	TEST(fixed_variant, convert_double_to_boolean)
	{
		//	double -> bool
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.0)).as_boolean(), false);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.5)).as_boolean(), false);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(1.0)).as_boolean(), true);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(2.0)).as_boolean(), exceptions::positive_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-0.5)).as_boolean(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-1.0)).as_boolean(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-2.0)).as_boolean(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_double_to_boolean_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::double_type(2.0)).as_boolean();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(fixed_variant::double_type(-2.0)).as_boolean();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_double_to_integer)
	{
		//	double -> int
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.0)).as_integer(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.5)).as_integer(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(1.0)).as_integer(), 1);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(2.0)).as_integer(), 2);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(double_type_max)).as_integer(), exceptions::positive_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-double_type_max)).as_integer(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_double_to_integer_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::double_type(double_type_max)).as_integer();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(fixed_variant::double_type(-double_type_max)).as_integer();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_double_to_unsigned)
	{
		//	double -> unsigned
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.0)).as_unsigned(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.5)).as_unsigned(), 0);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(1.0)).as_unsigned(), 1);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(2.0)).as_unsigned(), 2);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-0.5)).as_unsigned(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-1.0)).as_unsigned(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-2.0)).as_unsigned(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(double_type_max)).as_unsigned(), exceptions::positive_overflow_error);
	}

	TEST(fixed_variant, convert_double_to_unsigned_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::double_type(-0.5)).as_unsigned();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(fixed_variant::double_type(double_type_max)).as_unsigned();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}
		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_double_to_float)
	{
		//	double -> float
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.0)).as_float(), 0.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.5)).as_float(), 0.5f);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(1.0)).as_float(), 1.0f);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(2.0)).as_float(), 2.0f);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(double_type_max)).as_float(), exceptions::positive_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(-double_type_max)).as_float(), exceptions::negative_overflow_error);
	}

	TEST(fixed_variant, convert_double_to_float_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::double_type(double_type_max)).as_float();
		}
		catch (exceptions::positive_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::float_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(fixed_variant::double_type(-double_type_max)).as_float();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::float_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_double_to_double)
	{
		//	double -> double
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.0)).as_double(), 0.0);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.5)).as_double(), 0.5);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(1.0)).as_double(), 1.0);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(2.0)).as_double(), 2.0);
	}

	TEST(fixed_variant, convert_double_to_string)
	{
		//	double -> string
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.0)).as_string(), "0");
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(0.5)).as_string(), "0.5");
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(5.0)).as_string(), "5");
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(-5.0)).as_string(), "-5");
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(-5.456)).as_string(), "-5.456");
	}

	TEST(fixed_variant, convert_double_to_path)
	{
		//	double -> path
		EXPECT_THROW(fixed_variant(fixed_variant::double_type(0)).as_path(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_double_to_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::double_type(0)).as_path();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::double_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::path_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_double_to_color)
	{
		//	double -> color
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(color1int)).as_color(), color1color);
		EXPECT_EQ(fixed_variant(fixed_variant::double_type(color2int)).as_color(), color2color);
	}
#pragma endregion


#pragma region String value
	TEST(fixed_variant, create_string)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::string_type()).type(), fixed_variant::tag_type::String);
		EXPECT_EQ(fixed_variant(fixed_variant::string_type("Hello World!")).type(), fixed_variant::tag_type::String);
		EXPECT_EQ(fixed_variant("Hello World!").type(), fixed_variant::tag_type::String);
	}

	TEST(fixed_variant, assign_string)
	{
		fixed_variant value;

		EXPECT_EQ(value.type(), fixed_variant::tag_type::Empty);
		value = "hello";
		EXPECT_EQ(value.type(), fixed_variant::tag_type::String);
		EXPECT_EQ(value.as_string(), "hello");
		value = "world";
		EXPECT_EQ(value.type(), fixed_variant::tag_type::String);
		EXPECT_EQ(value.as_string(), "world");
	}

	TEST(fixed_variant, convert_string_to_boolean)
	{
		//	string -> bool
		EXPECT_EQ(fixed_variant("0").as_boolean(), false);
		EXPECT_EQ(fixed_variant("false").as_boolean(), false);
		EXPECT_EQ(fixed_variant("FaLsE").as_boolean(), false);
		EXPECT_EQ(fixed_variant("1").as_boolean(), true);
		EXPECT_EQ(fixed_variant("true").as_boolean(), true);
		EXPECT_EQ(fixed_variant("TrUe").as_boolean(), true);
		EXPECT_THROW(fixed_variant("-1").as_boolean(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant(fixed_variant::string_type()).as_boolean(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("something").as_boolean(), exceptions::lexical_error);
	}

	TEST(fixed_variant, convert_string_to_boolean_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant("-1").as_boolean();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant("something").as_boolean();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_string_to_integer)
	{
		//	string -> int
		EXPECT_EQ(fixed_variant("0").as_integer(), 0);
		EXPECT_EQ(fixed_variant("1").as_integer(), 1);
		EXPECT_EQ(fixed_variant("2").as_integer(), 2);
		EXPECT_EQ(fixed_variant("-1").as_integer(), -1);
		EXPECT_THROW(fixed_variant(fixed_variant::string_type()).as_integer(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant(std::to_string(integer_type_max) + "1").as_integer(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant(std::to_string(integer_type_min) + "1").as_integer(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("false").as_integer(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("true").as_integer(), exceptions::lexical_error);
	}

	TEST(fixed_variant, convert_string_to_integer_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::string_type()).as_integer();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(std::to_string(integer_type_max) + "1").as_integer();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::integer_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_string_to_unsigned)
	{
		//	string -> unsigned
		EXPECT_EQ(fixed_variant("0").as_unsigned(), 0);
		EXPECT_EQ(fixed_variant("1").as_unsigned(), 1);
		EXPECT_EQ(fixed_variant("2").as_unsigned(), 2);
		EXPECT_THROW(fixed_variant(fixed_variant::string_type()).as_unsigned(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant(std::to_string(unsigned_type_max) + "1").as_unsigned(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("-1").as_unsigned(), exceptions::negative_overflow_error);
		EXPECT_THROW(fixed_variant("false").as_unsigned(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("true").as_unsigned(), exceptions::lexical_error);
	}

	TEST(fixed_variant, convert_string_to_unsigned_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::string_type()).as_unsigned();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant("-1").as_unsigned();
		}
		catch (exceptions::negative_overflow_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant("false").as_unsigned();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::unsigned_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_string_to_float)
	{
		//	string -> float
		EXPECT_EQ(fixed_variant("0").as_float(), 0.0f);
		EXPECT_EQ(fixed_variant("0.0").as_float(), 0.0f);
		EXPECT_EQ(fixed_variant("1").as_float(), 1.0f);
		EXPECT_EQ(fixed_variant("1.0").as_float(), 1.0f);
		EXPECT_EQ(fixed_variant("2").as_float(), 2.0f);
		EXPECT_EQ(fixed_variant("2.0").as_float(), 2.0f);
		EXPECT_EQ(fixed_variant("0.5").as_float(), 0.5f);
		EXPECT_EQ(fixed_variant("-1.5").as_float(), -1.5f);
		EXPECT_EQ(fixed_variant("-0.5").as_float(), -0.5f);
		EXPECT_THROW(fixed_variant(fixed_variant::string_type()).as_float(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant(std::to_string(unsigned_type_max) + "99999999999999999999").as_float(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("false").as_float(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("true").as_float(), exceptions::lexical_error);
	}

	TEST(fixed_variant, convert_string_to_float_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::string_type()).as_float();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::float_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant(std::to_string(unsigned_type_max) + "99999999999999999999").as_float();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::float_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant("true").as_float();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::float_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_string_to_double)
	{
		//	string -> double
		EXPECT_EQ(fixed_variant("0").as_double(), 0.0);
		EXPECT_EQ(fixed_variant("0.0").as_double(), 0.0);
		EXPECT_EQ(fixed_variant("1").as_double(), 1.0);
		EXPECT_EQ(fixed_variant("1.0").as_double(), 1.0);
		EXPECT_EQ(fixed_variant("2").as_double(), 2.0);
		EXPECT_EQ(fixed_variant("2.0").as_double(), 2.0);
		EXPECT_EQ(fixed_variant("0.5").as_double(), 0.5);
		EXPECT_EQ(fixed_variant("-1.5").as_double(), -1.5);
		EXPECT_EQ(fixed_variant("-0.5").as_double(), -0.5);
		EXPECT_THROW(fixed_variant(fixed_variant::string_type()).as_double(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("false").as_double(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("true").as_double(), exceptions::lexical_error);
	}

	TEST(fixed_variant, convert_string_to_double_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::string_type()).as_double();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::double_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant("false").as_double();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::double_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_string_to_string)
	{
		//	string -> string
		EXPECT_EQ(fixed_variant("0").as_string(), "0");
		EXPECT_EQ(fixed_variant("0.0").as_string(), "0.0");
		EXPECT_EQ(fixed_variant("Hello").as_string(), "Hello");
		EXPECT_EQ(fixed_variant("World").as_string(), "World");
	}

	TEST(fixed_variant, convert_string_to_path)
	{
		//	string -> path
		EXPECT_EQ(fixed_variant(fixed_variant::string_type("hello world")).as_path(), fixed_variant::path_type("hello world"));
		EXPECT_EQ(fixed_variant(fixed_variant::string_type("../Test.txt")).as_path(), fixed_variant::path_type("../Test.txt"));
	}

	TEST(fixed_variant, convert_string_to_color)
	{
		//	string -> color
		EXPECT_EQ(fixed_variant("#0055AAFF").as_color(), color1color);
		EXPECT_EQ(fixed_variant("#FFAA5500").as_color(), color2color);
		EXPECT_THROW(fixed_variant(fixed_variant::string_type()).as_color(), exceptions::lexical_error);
		EXPECT_THROW(fixed_variant("#xxx").as_color(), exceptions::lexical_error);
	}

	TEST(fixed_variant, convert_string_to_color_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::string_type()).as_color();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::color_type));
		}

		EXPECT_TRUE(exception_caught);

		exception_caught = false;

		try
		{
			fixed_variant("#xxx").as_color();
		}
		catch (exceptions::lexical_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::string_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::color_type));
		}

		EXPECT_TRUE(exception_caught);
	}
#pragma endregion


#pragma region Path value
	TEST(fixed_variant, create_path)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::path_type()).type(), fixed_variant::tag_type::Path);
	}

	TEST(fixed_variant, assign_path)
	{
		fixed_variant value;

		EXPECT_EQ(value.type(), fixed_variant::tag_type::Empty);
		value = fixed_variant::path_type("hello");
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Path);
		EXPECT_EQ(value.as_path(), "hello");
		value = fixed_variant::path_type("world");
		EXPECT_EQ(value.type(), fixed_variant::tag_type::Path);
		EXPECT_EQ(value.as_path(), "world");
	}

	TEST(fixed_variant, convert_path)
	{
		EXPECT_THROW(fixed_variant(fixed_variant::path_type()).as_boolean(), exceptions::incompatible_type_error);
		EXPECT_THROW(fixed_variant(fixed_variant::path_type()).as_integer(), exceptions::incompatible_type_error);
		EXPECT_THROW(fixed_variant(fixed_variant::path_type()).as_unsigned(), exceptions::incompatible_type_error);
		EXPECT_THROW(fixed_variant(fixed_variant::path_type()).as_float(), exceptions::incompatible_type_error);
		EXPECT_THROW(fixed_variant(fixed_variant::path_type()).as_double(), exceptions::incompatible_type_error);

		EXPECT_EQ(fixed_variant(fixed_variant::path_type("D:/file.txt")).as_string(), fixed_variant::string_type("D:/file.txt"));
		EXPECT_EQ(fixed_variant(fixed_variant::path_type("D:/file.txt")).as_path(), fixed_variant::path_type("D:/file.txt"));

		EXPECT_THROW(fixed_variant(fixed_variant::path_type()).as_color(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			fixed_variant(fixed_variant::path_type()).as_color();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::path_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::color_type));
		}

		EXPECT_TRUE(exception_caught);
	}
#pragma endregion


#pragma region Color value
	TEST(fixed_variant, create_color)
	{
		EXPECT_EQ(fixed_variant(fixed_variant::color_type()).type(), fixed_variant::tag_type::Color);
	}

	TEST(fixed_variant, assign_color)
	{
		fixed_variant v;

		v = color1color;
		EXPECT_EQ(v.type(), fixed_variant::tag_type::Color);
		EXPECT_EQ(v.as_color(), color1color);
	}

	TEST(fixed_variant, convert_color_to_boolean)
	{
		//	color -> bool
		EXPECT_THROW(color1value.as_boolean(), exceptions::incompatible_type_error);
		EXPECT_THROW(color2value.as_boolean(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_color_to_boolean_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			color1value.as_boolean();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::color_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::boolean_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_color_to_integer)
	{
		//	color -> int
		EXPECT_EQ(color1value.as_integer(), color1int);
		EXPECT_EQ(color2value.as_integer(), color2int);
	}

	TEST(fixed_variant, convert_color_to_unsigned)
	{
		//	color -> unsigned
		EXPECT_EQ(color1value.as_unsigned(), color1uint);
		EXPECT_EQ(color2value.as_unsigned(), color2uint);
	}

	TEST(fixed_variant, convert_color_to_float)
	{
		//	color -> float
		EXPECT_EQ(color1value.as_float(), color1int);
		EXPECT_EQ(color2value.as_float(), color2int);
	}

	TEST(fixed_variant, convert_color_to_double)
	{
		//	color -> double
		EXPECT_EQ(color1value.as_double(), color1int);
		EXPECT_EQ(color2value.as_double(), color2int);
	}

	TEST(fixed_variant, convert_color_to_string)
	{
		//	color -> string
		EXPECT_EQ(color1value.as_string(), "#0055AAFF");
		EXPECT_EQ(color2value.as_string(), "#FFAA5500");
	}

	TEST(fixed_variant, convert_color_to_path)
	{
		//	color -> path
		EXPECT_THROW(color1value.as_path(), exceptions::incompatible_type_error);
		EXPECT_THROW(color2value.as_path(), exceptions::incompatible_type_error);
	}

	TEST(fixed_variant, convert_color_to_path_exception_typeinfo)
	{
		bool exception_caught(false);

		try
		{
			color1value.as_path();
		}
		catch (exceptions::incompatible_type_error& e)
		{
			exception_caught = true;

			EXPECT_EQ(e.source(), typeid(fixed_variant::color_type));
			EXPECT_EQ(e.target(), typeid(fixed_variant::path_type));
		}

		EXPECT_TRUE(exception_caught);
	}

	TEST(fixed_variant, convert_color_to_color)
	{
		//	color -> color
		EXPECT_EQ(color1value.as_color(), color1color);
		EXPECT_EQ(color2value.as_color(), color2color);
	}
#pragma endregion

}}}}}
