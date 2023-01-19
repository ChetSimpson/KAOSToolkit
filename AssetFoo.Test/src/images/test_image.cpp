// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/image.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>


namespace hypertech::kaos::assetfoo::images::unittests
{

	namespace
	{
		const image::sequence_type empty_sequence;
		const image::view_type empty_view;
		const image::const_sequence_type empty_const_sequence;

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

		const image::size_type default_width(256);
		const image::size_type default_halfwidth(default_width / 2);
		const image::size_type default_height(192);
		const image::size_type default_count(default_width * default_height);
		const image::size_type default_halfheight(default_height / 2);
		const image::size_type default_doubleheight(default_height * 2);
		const image::size_type default_length(default_width * default_height);
		const image::dimensions_type default_dimensions(default_width, default_height);
		const image::dimensions_type empty_dimensions(0, 0);

		image::collection_type create_faded_image_data(size_t width, size_t height)
		{
			image::collection_type data;

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

		image create_faded_image()
		{
			image img(default_width, default_height);

			auto colorptr = img.data();
			for (auto y(0U); y < img.height(); ++y)
			{
				for (auto x(0U); x < img.width(); ++x)
				{
					*(colorptr++) = image::pixel_type(y, y, y, x);
				}
			}

			return img;
		}

		template<class TestType_>
		class test_image : public ::testing::Test
		{
		};

		TYPED_TEST_CASE_P(test_image);
	}



#pragma region Construction
	TEST(test_image, default_constructor)
	{
		image img;

		EXPECT_TRUE(img.empty());
		EXPECT_EQ(img.dimensions(), empty_dimensions);
		EXPECT_EQ(img.width(), 0U);
		EXPECT_EQ(img.height(), 0U);
		EXPECT_EQ(img.length(), 0U);
		EXPECT_EQ(img.data(), nullptr);
	}

	TEST(test_image, value_constructor_width_and_height)
	{
		image img(default_width, default_height, image::pixel_type(1, 2, 3, 4));
		const image::collection_type data(default_width * default_height, image::pixel_type(1, 2, 3, 4));

		EXPECT_FALSE(img.empty());
		EXPECT_EQ(img.dimensions(), default_dimensions);
		EXPECT_EQ(img.width(), default_width);
		EXPECT_EQ(img.height(), default_height);
		EXPECT_EQ(img.length(), default_length);
		EXPECT_NE(img.data(), nullptr);
		EXPECT_TRUE(std::equal(img.get_sequence().begin(), img.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_image, value_constructor_width_and_height_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			image(0, default_height),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_image, value_constructor_width_and_height_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			image(default_width, 0),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_image, value_constructor_width_and_height_copy_data)
	{
		const auto data(create_faded_image_data(default_width, default_height));
		image img(default_width, default_height, data);

		EXPECT_FALSE(img.empty());
		EXPECT_EQ(img.dimensions(), default_dimensions);
		EXPECT_EQ(img.width(), default_width);
		EXPECT_EQ(img.height(), default_height);
		EXPECT_EQ(img.length(), default_length);
		EXPECT_NE(img.data(), nullptr);
		EXPECT_TRUE(std::equal(img.get_sequence().begin(), img.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_image, value_constructor_width_and_height_copy_data_zero_width)
	{
		const image::collection_type data;

		EXPECT_THROWS_MESSAGE(
			image(0, default_height, data),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_image, value_constructor_width_and_height_copy_data_zero_height)
	{
		const image::collection_type data;

		EXPECT_THROWS_MESSAGE(
			image(default_width, 0, data),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_image, value_constructor_width_and_height_copy_data_size_mismatch)
	{
		const auto data(create_faded_image_data(default_width, default_height));

		EXPECT_THROWS_MESSAGE(
			image(default_width + 1, default_height, data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");

		EXPECT_THROWS_MESSAGE(
			image(default_width, default_height + 1, data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");

		EXPECT_THROWS_MESSAGE(
			image(default_width + 1, default_height + 1, data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
	}

	TEST(test_image, value_constructor_width_and_height_move_data_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			image(0, default_height, image::collection_type()),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_image, value_constructor_width_and_height_move_data_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			image(default_width, 0, image::collection_type()),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_image, value_constructor_width_and_height_move_data_size_mismatch)
	{
		auto data(create_faded_image_data(default_width, default_height));
		EXPECT_THROWS_MESSAGE(
			image(default_width + 1, default_height, move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			image(default_width, default_height + 1, move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			image(default_width + 1, default_height + 1, move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());
	}

	TEST(test_image, value_constructor_dimensions)
	{
		image img(default_dimensions, image::pixel_type(1, 2, 3, 4));
		const image::collection_type data(default_width * default_height, image::pixel_type(1, 2, 3, 4));

		EXPECT_FALSE(img.empty());
		EXPECT_EQ(img.dimensions(), default_dimensions);
		EXPECT_EQ(img.width(), default_width);
		EXPECT_EQ(img.height(), default_height);
		EXPECT_EQ(img.length(), default_length);
		EXPECT_NE(img.data(), nullptr);
		EXPECT_TRUE(std::equal(img.get_sequence().begin(), img.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_image, value_constructor_dimensions_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(0, default_height)),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_image, value_constructor_dimensions_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width, 0)),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_image, value_constructor_dimensions_copy_data)
	{
		const auto data(create_faded_image_data(default_width, default_height));
		image img(default_dimensions, data);

		EXPECT_FALSE(img.empty());
		EXPECT_EQ(img.dimensions(), default_dimensions);
		EXPECT_EQ(img.width(), default_width);
		EXPECT_EQ(img.height(), default_height);
		EXPECT_EQ(img.length(), default_length);
		EXPECT_NE(img.data(), nullptr);
		EXPECT_TRUE(std::equal(img.get_sequence().begin(), img.get_sequence().end(), data.begin(), data.end()));
	}

	TEST(test_image, value_constructor_dimensions_copy_data_zero_width)
	{
		const image::collection_type data;

		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(0, default_height), data),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_image, value_constructor_dimensions_copy_data_zero_height)
	{
		const image::collection_type data;

		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width, 0), data),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_image, value_constructor_dimensions_copy_data_size_mismatch)
	{
		const auto data(create_faded_image_data(default_width, default_height));
		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width + 1, default_height), data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width, default_height + 1), data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width + 1, default_height + 1), data),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());
	}

	TEST(test_image, value_constructor_dimensions_move_data)
	{
		const auto expected_data(create_faded_image_data(default_width, default_height));
		auto data(create_faded_image_data(default_width, default_height));
		image img(default_dimensions, move(data));

		EXPECT_TRUE(data.empty());
		EXPECT_FALSE(img.empty());
		EXPECT_EQ(img.dimensions(), default_dimensions);
		EXPECT_EQ(img.width(), default_width);
		EXPECT_EQ(img.height(), default_height);
		EXPECT_EQ(img.length(), default_length);
		EXPECT_NE(img.data(), nullptr);
		EXPECT_TRUE(std::equal(img.get_sequence().begin(), img.get_sequence().end(), expected_data.begin(), expected_data.end()));
	}

	TEST(test_image, value_constructor_dimensions_move_data_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(0, default_height), image::collection_type()),
			std::invalid_argument,
			"image width cannot be 0");
	}

	TEST(test_image, value_constructor_dimensions_move_data_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width, 0), image::collection_type()),
			std::invalid_argument,
			"image height cannot be 0");
	}

	TEST(test_image, value_constructor_dimensions_move_data_size_mismatch)
	{
		auto data(create_faded_image_data(default_width, default_height));
		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width + 1, default_height), move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width, default_height + 1), move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());

		EXPECT_THROWS_MESSAGE(
			image(image::dimensions_type(default_width + 1, default_height + 1), move(data)),
			std::invalid_argument,
			"specified dimensions of image does not match buffer size");
		ASSERT_FALSE(data.empty());
	}

	TEST(test_image, value_constructor_empty_view)
	{
		EXPECT_THROWS_MESSAGE(
			image{ image::view_type() },
			std::invalid_argument,
			"cannot create image from empty view");
	}

	TEST(test_image, value_constructor_view)
	{
		auto base_image(create_faded_image());
		image img(base_image.create_view());

		EXPECT_FALSE(img.empty());
		EXPECT_EQ(img.dimensions(), default_dimensions);
		EXPECT_EQ(img.width(), default_width);
		EXPECT_EQ(img.height(), default_height);
		EXPECT_EQ(img.length(), default_length);
		EXPECT_NE(img.data(), nullptr);
		EXPECT_TRUE(std::equal(
			img.get_sequence().begin(),
			img.get_sequence().end(),
			base_image.get_sequence().begin(),
			base_image.get_sequence().end()));
	}

	TEST(test_image, value_constructor_empty_const_view)
	{
		EXPECT_THROWS_MESSAGE(
			image{ image::const_view_type() },
			std::invalid_argument,
			"cannot create image from empty view");
	}

	TEST(test_image, value_constructor_const_view)
	{
		const auto base_image(create_faded_image());
		image img(base_image.create_view());

		EXPECT_FALSE(img.empty());
		EXPECT_EQ(img.dimensions(), default_dimensions);
		EXPECT_EQ(img.width(), default_width);
		EXPECT_EQ(img.height(), default_height);
		EXPECT_EQ(img.length(), default_length);
		EXPECT_NE(img.data(), nullptr);
		EXPECT_TRUE(std::equal(
			img.get_sequence().begin(),
			img.get_sequence().end(),
			base_image.get_sequence().begin(),
			base_image.get_sequence().end()));
	}

	TEST(test_image, copy_constructor)
	{
		image original_img(default_width, default_height);
		image copied_img(original_img);

		EXPECT_FALSE(original_img.empty());
		EXPECT_EQ(original_img.dimensions(), default_dimensions);
		EXPECT_EQ(original_img.width(), default_width);
		EXPECT_EQ(original_img.height(), default_height);
		EXPECT_EQ(original_img.length(), default_length);
		EXPECT_NE(original_img.data(), nullptr);

		EXPECT_EQ(original_img.empty(), copied_img.empty());
		EXPECT_EQ(original_img.dimensions(), copied_img.dimensions());
		EXPECT_EQ(original_img.width(), copied_img.width());
		EXPECT_EQ(original_img.height(), copied_img.height());
		EXPECT_EQ(original_img.length(), copied_img.length());
		EXPECT_NE(original_img.data(), copied_img.data());
	}

	TEST(test_image, move_constructor)
	{
		image original_img(default_width, default_height);
		image copied_img(move(original_img));

		EXPECT_TRUE(original_img.empty());
		EXPECT_EQ(original_img.dimensions(), empty_dimensions);
		EXPECT_EQ(original_img.width(), 0U);
		EXPECT_EQ(original_img.height(), 0U);
		EXPECT_EQ(original_img.length(), 0);
		EXPECT_EQ(original_img.data(), nullptr);

		EXPECT_FALSE(copied_img.empty());
		EXPECT_EQ(copied_img.dimensions(), default_dimensions);
		EXPECT_EQ(copied_img.width(), default_width);
		EXPECT_EQ(copied_img.height(), default_height);
		EXPECT_EQ(copied_img.length(), default_length);
		EXPECT_NE(copied_img.data(), nullptr);
	}
#pragma endregion




#pragma region at and subscript
	TYPED_TEST_P(test_image, at_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().at(0)),
			std::runtime_error,
			"cannot access subscript on empty image");
	}


	TYPED_TEST_P(test_image, at_out_of_range)
	{
		TypeParam img(create_faded_image());

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(img.at(img.height() + 1)),
			std::out_of_range,
			"image subscript index out of range");
	}


	TYPED_TEST_P(test_image, at)
	{
		TypeParam img(create_faded_image());

		auto color_level(0U);
		for (auto y(0U); y < img.height(); ++y)
		{
			auto alpha_level(0U);
			for (const auto& pixel : img.at(y))
			{
				ASSERT_EQ(pixel, image::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}
			++color_level;
		}
	}

	TYPED_TEST_P(test_image, subscript_operator_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam()[0]),
			std::runtime_error,
			"cannot access subscript on empty image");
	}

	TYPED_TEST_P(test_image, subscript_operator_out_of_range)
	{
		TypeParam img(create_faded_image());

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(img[img.height() + 1]),
			std::out_of_range,
			"image subscript index out of range");
	}

	TYPED_TEST_P(test_image, subscript_operator)
	{
		TypeParam img(create_faded_image());

		auto color_level(0U);
		for (auto y(0U); y < img.height(); ++y)
		{
			auto alpha_level(0U);
			for (const auto& pixel : img[y])
			{
				ASSERT_EQ(pixel, image::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}
			++color_level;
		}
	}
#pragma endregion




#pragma region get sequence
	TYPED_TEST_P(test_image, get_sequence_on_empty_image)
	{
		TypeParam img;

		auto sequence(img.get_sequence());

		EXPECT_EQ(sequence.size(), 0);
		EXPECT_EQ(sequence.data(), nullptr);
	}

	TYPED_TEST_P(test_image, get_sequence)
	{
		TypeParam img(create_faded_image());

		auto sequence(img.get_sequence());

		EXPECT_EQ(sequence.size(), default_length);
		EXPECT_EQ(sequence.data(), img.data());

		auto color_level(0U);
		auto alpha_level(0U);
	
		for (const auto& pixel : sequence)
		{
			ASSERT_EQ(pixel, image::pixel_type(color_level, color_level, color_level, alpha_level));
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
	TYPED_TEST_P(test_image, get_view_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view()),
			std::runtime_error,
			"cannot create view on empty image");
	}

	TYPED_TEST_P(test_image, get_view)
	{
		TypeParam img(create_faded_image());

		auto view(img.create_view());

		EXPECT_EQ(view.width(), default_width);
		EXPECT_EQ(view.height(), default_height);
		EXPECT_EQ(view.pitch(), default_width);
		EXPECT_EQ(view.count(), default_count);
		EXPECT_EQ(view.begin()->data(), img.data());

		auto color_level(0U);
		for (const auto& row : view)
		{
			auto alpha_level(0U);
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, image::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}
			++color_level;
		}
	}
#pragma endregion




#pragma region get width based view
	TYPED_TEST_P(test_image, get_view_width_only_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view(default_halfwidth)),
			std::runtime_error,
			"cannot create width based view on empty image");
	}

	TYPED_TEST_P(test_image, get_view_width_only_with_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0)),
			std::out_of_range,
			"image view width cannot be 0");
	}

	TYPED_TEST_P(test_image, get_view_width_only_with_width_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(default_width + 1)),
			std::out_of_range,
			"image view width cannot be greater than the image width");
	}

	TYPED_TEST_P(test_image, get_view_width_only_not_multiple_of_image_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(default_width - 1)),
			std::out_of_range,
			"image view width must be a multiple of the image data size");
	}

	TYPED_TEST_P(test_image, get_view_width_only)
	{
		TypeParam img(create_faded_image());
		auto view(img.create_view(default_halfwidth));

		EXPECT_EQ(view.width(), default_halfwidth);
		EXPECT_EQ(view.height(), default_doubleheight);
		EXPECT_EQ(view.pitch(), default_halfwidth);
		EXPECT_EQ(view.count(), default_count);
		EXPECT_EQ(view.begin()->data(), img.data());

		auto color_level(0U);
		auto alpha_level(0U);
		for (const auto& row : view)
		{
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, image::pixel_type(color_level, color_level, color_level, alpha_level));
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
	TYPED_TEST_P(test_image, get_view_boxed_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view(0, 0, 0, 0)),
			std::runtime_error,
			"cannot create boxed view on empty image");
	}

	TYPED_TEST_P(test_image, get_view_boxed_with_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, 0, 0)),
			std::out_of_range,
			"image boxed view width cannot be 0");
	}

	TYPED_TEST_P(test_image, get_view_boxed_with_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, 1, 0)),
			std::out_of_range,
			"image boxed view height cannot be 0");
	}

	TYPED_TEST_P(test_image, get_view_boxed_with_width_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, default_width + 1, default_height)),
			std::out_of_range,
			"width of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_image, get_view_boxed_with_height_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view(0, 0, default_width, default_height + 1)),
			std::out_of_range,
			"height of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_image, get_view_boxed_at_16_16)
	{
		auto img = create_faded_image();
		auto view = img.create_view(16, 16, 16, 16);
		
		auto color_level(16U);
		for (const auto& row : view)
		{
			auto alpha_level(16U);
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, image::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}

			++color_level;
		}
	}
#pragma endregion




#pragma region get boxed view (position, size)
	TYPED_TEST_P(test_image, get_view_boxed_posandsize_on_empty_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam().create_view({ 0, 0 }, { 0, 0 })),
			std::runtime_error,
			"cannot create boxed view on empty image");
	}

	TYPED_TEST_P(test_image, get_view_boxed_posandsize_with_zero_width)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { 0, 0 })),
			std::out_of_range,
			"image boxed view width cannot be 0");
	}

	TYPED_TEST_P(test_image, get_view_boxed_posandsize_with_zero_height)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { 1, 0 })),
			std::out_of_range,
			"image boxed view height cannot be 0");
	}

	TYPED_TEST_P(test_image, get_view_boxed_posandsize_with_width_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { default_width + 1, default_height })),
			std::out_of_range,
			"width of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_image, get_view_boxed_posandsize_with_height_larger_than_image)
	{
		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(TypeParam(default_dimensions).create_view({ 0, 0 }, { default_width, default_height + 1 })),
			std::out_of_range,
			"height of requested image boxed view exceeds bounds of image");
	}

	TYPED_TEST_P(test_image, get_view_boxed_posandsize_at_16_16)
	{
		auto img = create_faded_image();
		auto view = img.create_view({ 16, 16 }, { 16, 16 });

		auto color_level(16U);
		for (const auto& row : view)
		{
			auto alpha_level(16U);
			for (const auto& pixel : row)
			{
				ASSERT_EQ(pixel, image::pixel_type(color_level, color_level, color_level, alpha_level));
				++alpha_level;
			}

			++color_level;
		}
	}
#pragma endregion



	REGISTER_TYPED_TEST_CASE_P(
		test_image,
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

	using const_image = const image;
	using testing_types = testing::Types<image, const image>;

	INSTANTIATE_TYPED_TEST_CASE_P(test_image, test_image, testing_types);

}
