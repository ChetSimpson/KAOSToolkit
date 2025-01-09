// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/basic_bitmap.h>
#include <kaos/core/types/rgba_color.h>
#include <kaos/core/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech::kaos::assetfoo::images::unittests
{

	namespace
	{
		using bitmap_type = basic_bitmap<core::types::rgba_color>;

		const bitmap_type::sequence_type empty_sequence;
		const bitmap_type::view_type empty_view;
		const bitmap_type::const_sequence_type empty_const_sequence;

		template<class Type_>
		bool compare_spans(const std::span<Type_>& left, const std::span<Type_>& right)
		{
			return left.data() == right.data()
				&& left.size() == right.size();
		}

		template<class Type_>
		bool compare_views(const core::types::box_view<Type_>& left,
			const core::types::box_view<Type_>& right)
		{
			return left.empty() == right.empty()
				&& left.width() == right.width()
				&& left.height() == right.height()
				&& left.pitch() == right.pitch();
		}

		const bitmap_type::size_type default_width(256);
		const bitmap_type::size_type default_halfwidth(default_width / 2);
		const bitmap_type::size_type default_height(192);
		const bitmap_type::size_type default_count(default_width * default_height);
		const bitmap_type::size_type default_halfheight(default_height / 2);
		const bitmap_type::size_type default_doubleheight(default_height * 2);
		const bitmap_type::size_type default_length(default_width * default_height);
		const bitmap_type::dimensions_type default_dimensions(default_width, default_height);
		const bitmap_type::dimensions_type empty_dimensions(0, 0);

		bitmap_type::collection_type create_faded_image_data(size_t width, size_t height)
		{
			bitmap_type::collection_type data;

			data.reserve(width * height);
			for (auto y(0U); y < height; ++y)
			{
				for (auto x(0U); x < width; ++x)
				{
					data.emplace_back(y, y, y, x);
				}
			}

			return data;
		}

		bitmap_type create_faded_image()
		{
			bitmap_type bitmap(default_width, default_height);

			auto colorptr = bitmap.data();
			for (auto y(0U); y < bitmap.height(); ++y)
			{
				for (auto x(0U); x < bitmap.width(); ++x)
				{
					*(colorptr++) = bitmap_type::pixel_type(y, y, y, x);
				}
			}

			return bitmap;
		}

		template<class TestType_>
		class test_basic_bitmap : public ::testing::Test
		{};

		TYPED_TEST_CASE_P(test_basic_bitmap);
	}



#pragma region Construction
	TEST(test_basic_bitmap, default_constructor)
	{
		bitmap_type bitmap;

		EXPECT_TRUE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), empty_dimensions);
		EXPECT_EQ(bitmap.width(), 0U);
		EXPECT_EQ(bitmap.height(), 0U);
		EXPECT_EQ(bitmap.length(), 0U);
		EXPECT_EQ(bitmap.data(), nullptr);
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height)
	{
		bitmap_type bitmap(default_width, default_height, bitmap_type::pixel_type(1, 2, 3, 4));
		const bitmap_type::collection_type data(default_width * default_height, bitmap_type::pixel_type(1, 2, 3, 4));

		EXPECT_FALSE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(bitmap.width(), default_width);
		EXPECT_EQ(bitmap.height(), default_height);
		EXPECT_EQ(bitmap.length(), default_length);
		EXPECT_NE(bitmap.data(), nullptr);
		EXPECT_TRUE(std::equal(bitmap.get_sequence().begin(), bitmap.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(0, default_height),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width, 0),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_copy_data)
	{
		const auto data(create_faded_image_data(default_width, default_height));
		bitmap_type bitmap(default_width, default_height, data);

		EXPECT_FALSE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(bitmap.width(), default_width);
		EXPECT_EQ(bitmap.height(), default_height);
		EXPECT_EQ(bitmap.length(), default_length);
		EXPECT_NE(bitmap.data(), nullptr);
		EXPECT_TRUE(std::equal(bitmap.get_sequence().begin(), bitmap.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_copy_data_zero_width)
	{
		const bitmap_type::collection_type data;

		EXPECT_THROWS_MESSAGE(
			bitmap_type(0, default_height, data),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_copy_data_zero_height)
	{
		const bitmap_type::collection_type data;

		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width, 0, data),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_copy_data_size_mismatch)
	{
		const auto data(create_faded_image_data(default_width, default_height));

		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width + 1, default_height, data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");

		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width, default_height + 1, data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");

		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width + 1, default_height + 1, data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_move_data_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(0, default_height, bitmap_type::collection_type()),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_move_data_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width, 0, bitmap_type::collection_type()),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_width_and_height_move_data_size_mismatch)
	{
		auto data(create_faded_image_data(default_width, default_height));
		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width + 1, default_height, move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width, default_height + 1, move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			bitmap_type(default_width + 1, default_height + 1, move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());
	}

	TEST(test_basic_bitmap, value_constructor_dimensions)
	{
		bitmap_type bitmap(default_dimensions, bitmap_type::pixel_type(1, 2, 3, 4));
		const bitmap_type::collection_type data(default_width * default_height, bitmap_type::pixel_type(1, 2, 3, 4));

		EXPECT_FALSE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(bitmap.width(), default_width);
		EXPECT_EQ(bitmap.height(), default_height);
		EXPECT_EQ(bitmap.length(), default_length);
		EXPECT_NE(bitmap.data(), nullptr);
		EXPECT_TRUE(std::equal(bitmap.get_sequence().begin(), bitmap.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(0, default_height)),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width, 0)),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_copy_data)
	{
		const auto data(create_faded_image_data(default_width, default_height));
		bitmap_type bitmap(default_dimensions, data);

		EXPECT_FALSE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(bitmap.width(), default_width);
		EXPECT_EQ(bitmap.height(), default_height);
		EXPECT_EQ(bitmap.length(), default_length);
		EXPECT_NE(bitmap.data(), nullptr);
		EXPECT_TRUE(std::equal(bitmap.get_sequence().begin(), bitmap.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_copy_data_zero_width)
	{
		const bitmap_type::collection_type data;

		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(0, default_height), data),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_copy_data_zero_height)
	{
		const bitmap_type::collection_type data;

		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width, 0), data),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_copy_data_size_mismatch)
	{
		const auto data(create_faded_image_data(default_width, default_height));
		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width + 1, default_height), data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width, default_height + 1), data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width + 1, default_height + 1), data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_move_data)
	{
		const auto expected_data(create_faded_image_data(default_width, default_height));
		auto data(create_faded_image_data(default_width, default_height));
		bitmap_type bitmap(default_dimensions, move(data));

		EXPECT_TRUE(data.empty());
		EXPECT_FALSE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(bitmap.width(), default_width);
		EXPECT_EQ(bitmap.height(), default_height);
		EXPECT_EQ(bitmap.length(), default_length);
		EXPECT_NE(bitmap.data(), nullptr);
		EXPECT_TRUE(std::equal(bitmap.get_sequence().begin(), bitmap.get_sequence().end(), expected_data.begin(), expected_data.end()));
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_move_data_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(0, default_height), bitmap_type::collection_type()),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_move_data_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width, 0), bitmap_type::collection_type()),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_basic_bitmap, value_constructor_dimensions_move_data_size_mismatch)
	{
		auto data(create_faded_image_data(default_width, default_height));
		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width + 1, default_height), move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width, default_height + 1), move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			bitmap_type(bitmap_type::dimensions_type(default_width + 1, default_height + 1), move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());
	}

	TEST(test_basic_bitmap, value_constructor_empty_view)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type{ bitmap_type::view_type() },
			std::invalid_argument,
			"cannot create image from empty view");
	}

	TEST(test_basic_bitmap, value_constructor_view)
	{
		auto base_bitmap(create_faded_image());
		bitmap_type bitmap(base_bitmap.create_view());

		EXPECT_FALSE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(bitmap.width(), default_width);
		EXPECT_EQ(bitmap.height(), default_height);
		EXPECT_EQ(bitmap.length(), default_length);
		EXPECT_NE(bitmap.data(), nullptr);
		EXPECT_TRUE(std::equal(
			bitmap.get_sequence().begin(),
			bitmap.get_sequence().end(),
			base_bitmap.get_sequence().begin(),
			base_bitmap.get_sequence().end()));
	}

	TEST(test_basic_bitmap, value_constructor_empty_const_view)
	{
		EXPECT_THROWS_MESSAGE(
			bitmap_type{ bitmap_type::const_view_type() },
			std::invalid_argument,
			"cannot create image from empty view");
	}

	TEST(test_basic_bitmap, value_constructor_const_view)
	{
		const auto base_bitmap(create_faded_image());
		bitmap_type bitmap(base_bitmap.create_view());

		EXPECT_FALSE(bitmap.empty());
		EXPECT_EQ(bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(bitmap.width(), default_width);
		EXPECT_EQ(bitmap.height(), default_height);
		EXPECT_EQ(bitmap.length(), default_length);
		EXPECT_NE(bitmap.data(), nullptr);
		EXPECT_TRUE(std::equal(
			bitmap.get_sequence().begin(),
			bitmap.get_sequence().end(),
			base_bitmap.get_sequence().begin(),
			base_bitmap.get_sequence().end()));
	}

	TEST(test_basic_bitmap, copy_constructor)
	{
		bitmap_type original_bitmap(default_width, default_height);
		bitmap_type duplicate_bitmap(original_bitmap);

		EXPECT_FALSE(original_bitmap.empty());
		EXPECT_EQ(original_bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(original_bitmap.width(), default_width);
		EXPECT_EQ(original_bitmap.height(), default_height);
		EXPECT_EQ(original_bitmap.length(), default_length);
		EXPECT_NE(original_bitmap.data(), nullptr);

		EXPECT_EQ(original_bitmap.empty(), duplicate_bitmap.empty());
		EXPECT_EQ(original_bitmap.dimensions(), duplicate_bitmap.dimensions());
		EXPECT_EQ(original_bitmap.width(), duplicate_bitmap.width());
		EXPECT_EQ(original_bitmap.height(), duplicate_bitmap.height());
		EXPECT_EQ(original_bitmap.length(), duplicate_bitmap.length());
		EXPECT_NE(original_bitmap.data(), duplicate_bitmap.data());
	}

	TEST(test_basic_bitmap, move_constructor)
	{
		bitmap_type original_bitmap(default_width, default_height);
		bitmap_type duplicate_bitmap(move(original_bitmap));

		EXPECT_TRUE(original_bitmap.empty());
		EXPECT_EQ(original_bitmap.dimensions(), empty_dimensions);
		EXPECT_EQ(original_bitmap.width(), 0U);
		EXPECT_EQ(original_bitmap.height(), 0U);
		EXPECT_EQ(original_bitmap.length(), 0);
		EXPECT_EQ(original_bitmap.data(), nullptr);

		EXPECT_FALSE(duplicate_bitmap.empty());
		EXPECT_EQ(duplicate_bitmap.dimensions(), default_dimensions);
		EXPECT_EQ(duplicate_bitmap.width(), default_width);
		EXPECT_EQ(duplicate_bitmap.height(), default_height);
		EXPECT_EQ(duplicate_bitmap.length(), default_length);
		EXPECT_NE(duplicate_bitmap.data(), nullptr);
	}
#pragma endregion




#pragma region at and subscript
	TYPED_TEST_P(test_basic_bitmap, at_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().at(0)),
			std::runtime_error,
			"cannot access subscript on empty image");
	}


	TYPED_TEST_P(test_basic_bitmap, at_out_of_range)
	{
		TypeParam bitmap(create_faded_image());

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(bitmap.at(bitmap.height() + 1)),
			std::out_of_range,
			"image subscript index out of range");
	}


	TYPED_TEST_P(test_basic_bitmap, at)
	{
		TypeParam bitmap(create_faded_image());

		auto color_level(0U);
		for (auto y(0U); y < bitmap.height(); ++y)
		{
			auto alpha_level(0U);
			for (const auto& pixel : bitmap.at(y))
			{
				ASSERT_EQ(pixel, bitmap_type::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}
			++color_level;
		}
	}

	TYPED_TEST_P(test_basic_bitmap, subscript_operator_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam()[0]),
			std::runtime_error,
			"cannot access subscript on empty image");
	}

	TYPED_TEST_P(test_basic_bitmap, subscript_operator_out_of_range)
	{
		TypeParam bitmap(create_faded_image());

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(bitmap[bitmap.height() + 1]),
			std::out_of_range,
			"image subscript index out of range");
	}

	TYPED_TEST_P(test_basic_bitmap, subscript_operator)
	{
		TypeParam bitmap(create_faded_image());

		auto color_level(0U);
		for (auto y(0U); y < bitmap.height(); ++y)
		{
			auto alpha_level(0U);
			for (const auto& pixel : bitmap[y])
			{
				ASSERT_EQ(pixel, bitmap_type::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}
			++color_level;
		}
	}
#pragma endregion




#pragma region get sequence
	TYPED_TEST_P(test_basic_bitmap, get_sequence_on_empty_image)
	{
		TypeParam bitmap;

		auto sequence(bitmap.get_sequence());

		EXPECT_EQ(sequence.size(), 0);
		EXPECT_EQ(sequence.data(), nullptr);
	}

	TYPED_TEST_P(test_basic_bitmap, get_sequence)
	{
		TypeParam bitmap(create_faded_image());

		auto sequence(bitmap.get_sequence());

		EXPECT_EQ(sequence.size(), default_length);
		EXPECT_EQ(sequence.data(), bitmap.data());

		auto color_level(0U);
		auto alpha_level(0U);
	
		for (const auto& pixel : sequence)
		{
			ASSERT_EQ(pixel, bitmap_type::pixel_type(color_level, color_level, color_level, alpha_level));
			++alpha_level;
			if (alpha_level == 256)
			{
				alpha_level = 0;
				++color_level;
			}
		}
	}
#pragma endregion




#pragma region get full view
	TYPED_TEST_P(test_basic_bitmap, get_view_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view()),
			std::runtime_error,
			"cannot create view on empty image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view)
	{
		TypeParam bitmap(create_faded_image());

		auto view(bitmap.create_view());

		EXPECT_EQ(view.width(), default_width);
		EXPECT_EQ(view.height(), default_height);
		EXPECT_EQ(view.pitch(), default_width);
		EXPECT_EQ(view.count(), default_count);
		EXPECT_EQ(view.begin()->data(), bitmap.data());

		auto color_level(0U);
		for (const auto& row : view)
		{
			auto alpha_level(0U);
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, bitmap_type::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}
			++color_level;
		}
	}
#pragma endregion




#pragma region get width based view
	TYPED_TEST_P(test_basic_bitmap, get_view_width_only_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view(default_halfwidth)),
			std::runtime_error,
			"cannot create width based view on empty image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_width_only_with_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0)),
			std::out_of_range,
			"image view width cannot be 0");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_width_only_with_width_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(default_width + 1)),
			std::out_of_range,
			"image view width cannot be greater than the image width");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_width_only_not_multiple_of_image_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(default_width - 1)),
			std::out_of_range,
			"image view width must be a multiple of the image data size");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_width_only)
	{
		TypeParam bitmap(create_faded_image());
		auto view(bitmap.create_view(default_halfwidth));

		EXPECT_EQ(view.width(), default_halfwidth);
		EXPECT_EQ(view.height(), default_doubleheight);
		EXPECT_EQ(view.pitch(), default_halfwidth);
		EXPECT_EQ(view.count(), default_count);
		EXPECT_EQ(view.begin()->data(), bitmap.data());

		auto color_level(0U);
		auto alpha_level(0U);
		for (const auto& row : view)
		{
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, bitmap_type::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
				if (alpha_level == 256)
				{
					alpha_level = 0;
					++color_level;
				}
			}
		}
	}
#pragma endregion




#pragma region get boxed view (x, y, width, height)
	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view(0, 0, 0, 0)),
			std::runtime_error,
			"cannot create boxed view on empty image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_with_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, 0, 0)),
			std::out_of_range,
			"image boxed view width cannot be 0");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_with_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, 1, 0)),
			std::out_of_range,
			"image boxed view height cannot be 0");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_with_width_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, default_width + 1, default_height)),
			std::out_of_range,
			"width of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_with_height_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, default_width, default_height + 1)),
			std::out_of_range,
			"height of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_at_16_16)
	{
		auto bitmap = create_faded_image();
		auto view = bitmap.create_view(16, 16, 16, 16);
		
		auto color_level(16U);
		for (const auto& row : view)
		{
			auto alpha_level(16U);
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, bitmap_type::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}

			++color_level;
		}
	}
#pragma endregion




#pragma region get boxed view (position, size)
	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_posandsize_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view({ 0, 0 }, { 0, 0 })),
			std::runtime_error,
			"cannot create boxed view on empty image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_posandsize_with_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { 0, 0 })),
			std::out_of_range,
			"image boxed view width cannot be 0");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_posandsize_with_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { 1, 0 })),
			std::out_of_range,
			"image boxed view height cannot be 0");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_posandsize_with_width_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { default_width + 1, default_height })),
			std::out_of_range,
			"width of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_posandsize_with_height_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { default_width, default_height + 1 })),
			std::out_of_range,
			"height of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_basic_bitmap, get_view_boxed_posandsize_at_16_16)
	{
		auto bitmap = create_faded_image();
		auto view = bitmap.create_view({ 16, 16 }, { 16, 16 });

		auto color_level(16U);
		for (const auto& row : view)
		{
			auto alpha_level(16U);
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, bitmap_type::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}

			++color_level;
		}
	}
#pragma endregion



	REGISTER_TYPED_TEST_CASE_P(
		test_basic_bitmap,
		at_on_empty_image,
		at_out_of_range,
		at,
		subscript_operator_on_empty_image,
		subscript_operator_out_of_range,
		subscript_operator,
		get_sequence_on_empty_image,
		get_sequence,
		get_view_on_empty_image,
		get_view,
		get_view_width_only_on_empty_image,
		get_view_width_only_with_zero_width,
		get_view_width_only_with_width_larger_than_image,
		get_view_width_only_not_multiple_of_image_width,
		get_view_width_only,
		get_view_boxed_on_empty_image,
		get_view_boxed_with_zero_width,
		get_view_boxed_with_zero_height,
		get_view_boxed_with_width_larger_than_image,
		get_view_boxed_with_height_larger_than_image,
		get_view_boxed_at_16_16,
		get_view_boxed_posandsize_on_empty_image,
		get_view_boxed_posandsize_with_zero_width,
		get_view_boxed_posandsize_with_zero_height,
		get_view_boxed_posandsize_with_width_larger_than_image,
		get_view_boxed_posandsize_with_height_larger_than_image,
		get_view_boxed_posandsize_at_16_16
	);

	using const_image = const bitmap_type;
	using testing_types = testing::Types<bitmap_type, const bitmap_type>;

	INSTANTIATE_TYPED_TEST_CASE_P(test_basic_bitmap, test_basic_bitmap, testing_types);

}
