// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/color_converter.h>
#include <kaos/assetfoo/colors/color_layout.h>
#include <kaos/assetfoo/exceptions.h>
#include <kaos/core/types/split_bitfield.h>
#include <kaos/core/types/empty_bitfield.h>
#include <kaos/assetfoo/test/base_fixture.h>
#include <kaos/test/gtest-extensions.h>
#include <kaos/test/mocked_bitfield.h>
#include <gtest/gtest.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors { namespace unittests
{


	class color_converter_common_test : public assetfoo::unittests::base_fixture
	{
	protected:
		
		using bitfield_type = core::types::single_bitfield<color_converter::bitfield_type::value_type>;
		using mockedbitfield_type = core::types::unittests::mocks::mocked_bitfield<uint64_t>;


		static const inline bitfield_type alpha_component_bitfield_{ "alpha", 1, 3 };
		static const inline bitfield_type red_component_bitfield_{ "red", 1, 2 };
		static const inline bitfield_type green_component_bitfield_{ "green", 1, 1 };
		static const inline bitfield_type blue_component_bitfield_{ "blue", 1, 0 };
		static const inline mockedbitfield_type empty_bitfield_{ 0, 0, 0, 0 };

		static const inline auto onebit_layout_ = std::make_shared<color_layout>(
			red_component_bitfield_,
			green_component_bitfield_,
			blue_component_bitfield_,
			alpha_component_bitfield_);

		static const inline color_converter onebit_rgba_converter_{ onebit_layout_};

		static const inline color_converter zero_bit_rgba_converter_{ std::make_shared<color_layout>(
			empty_bitfield_,
			empty_bitfield_,
			empty_bitfield_,
			empty_bitfield_) };
	};




	TEST(color_converter_common, value_constructor_no_format)
	{
		EXPECT_THROWS_MESSAGE(color_converter(nullptr), std::invalid_argument, "Color format cannot be null");
	}

	TEST_F(color_converter_common_test, copy_constructor)
	{
		color_converter original_converter(onebit_rgba_converter_);

		auto converter(original_converter);
		EXPECT_EQ(original_converter.layout(), onebit_layout_);
		EXPECT_EQ(converter.layout(), onebit_layout_);
	}



	TEST_F(color_converter_common_test, to_color_zero_component_bits)
	{
		ASSERT_THROWS_MESSAGE(
			zero_bit_rgba_converter_.to_color(0),
			std::length_error,
			"<anonymous> unpacked component size cannot be zero");
	}

	TEST_F(color_converter_common_test, to_color_unpacked_component_too_large_for_rgb_component)
	{
		mockedbitfield_type bitfield(std::numeric_limits<mockedbitfield_type::value_type>::digits, 0, 0, 0);
		color_converter converter(std::make_shared<color_layout>(bitfield, bitfield, bitfield, bitfield));

		ASSERT_THROWS_MESSAGE(
			converter.to_color(0),
			std::length_error,
			"<anonymous> unpacked component size is larger than target component type");
	}

	TEST_F(color_converter_common_test, to_color_unpacked_component_exceeds_max_component_value)
	{
		mockedbitfield_type bitfield(3, 0, 0, 0);
		bitfield.get_from_value_ = 256;
		color_converter converter(std::make_shared<color_layout>(bitfield, bitfield, bitfield, bitfield));

		ASSERT_THROWS_MESSAGE(
			converter.to_color(0),
			std::range_error,
			"<anonymous> unpacked component value exceeds the maximum allowed component value");
	}

	TEST_F(color_converter_common_test, to_color_unpacked_component_exceeds_max_component_value_after_scaling)
	{
		mockedbitfield_type bitfield(3, 0, 0, 0);

		bitfield.get_from_value_ = 255;

		auto format(std::make_shared<color_layout>(bitfield, bitfield, bitfield, bitfield));
		color_converter converter(format);

		ASSERT_THROWS_MESSAGE(
			converter.to_color(0),
			std::range_error,
			"<anonymous> unpacked component value exceeds maximum allowed value after scaling");
	}


	TEST_F(color_converter_common_test, from_color_packed_component_size)
	{
		ASSERT_THROWS_MESSAGE(
			zero_bit_rgba_converter_.from_color({}),
			std::length_error,
			"<anonymous> packed component size cannot be zero");
	}


	TEST_F(color_converter_common_test, to_color_invalid_packed_color_bits)
	{
		EXPECT_THROWS_MESSAGE(
			onebit_rgba_converter_.to_color(std::numeric_limits<color_converter::packed_color_type>::max()),
			exceptions::packed_color_format_error,
			"packed color value contains unsupported bits");
	}

	TEST_F(color_converter_common_test, from_color_loss_of_red_precision)
	{
		//	Test invalid red component values
		for (auto i = 1U; i < onebit_rgba_converter_.max_component_value(); ++i)
		{
			ASSERT_THROWS_MESSAGE(
				onebit_rgba_converter_.from_color(color_type(i, 0, 0)),
				std::range_error,
				"Conversion of red component value to packed component results in loss of color precision");
		}
	}


	TEST_F(color_converter_common_test, from_color_loss_of_green_precision)
	{
		//	Test invalid green component values
		for (auto i = 1U; i < onebit_rgba_converter_.max_component_value(); ++i)
		{
			ASSERT_THROWS_MESSAGE(
				onebit_rgba_converter_.from_color(color_type(0, i, 0)),
				std::range_error,
				"Conversion of green component value to packed component results in loss of color precision");
		}
	}


	TEST_F(color_converter_common_test, from_color_loss_of_blue_precision)
	{
		//	Test invalid blue component values
		for (auto i = 1U; i < onebit_rgba_converter_.max_component_value(); ++i)
		{
			ASSERT_THROWS_MESSAGE(
				onebit_rgba_converter_.from_color(color_type(0, 0, i)),
				std::range_error,
				"Conversion of blue component value to packed component results in loss of color precision");
		}
	}

}}}}}
