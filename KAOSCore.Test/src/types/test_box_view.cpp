// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/box_view.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <numeric>


namespace hypertech { namespace kaos { namespace core { namespace types { namespace unittests
{

#ifdef KAOS_ENABLE_CONTAINER_VERIFY
#define KAOS_CONTAINER_DEATH_TEST(test_case_name, test_name) TEST(test_case_name, test_name)
#else
#define KAOS_CONTAINER_DEATH_TEST(test_case_name, test_name)	KAOS_DEATH_TEST(test_case_name, test_name)
#undef EXPECT_DEATH
#define EXPECT_DEATH(x, y)
#endif

	namespace { namespace defaults
	{
		const size_t pitch = 64;
		const size_t width = pitch;
		const size_t half_width = width / 2;
		const size_t height = 32;
		const size_t count = width * height;
		const size_t half_height = height / 2;
		const size_t half_count = width * half_height;
		const size_t quarter_count = half_width * half_height;

		using collection_type = std::vector<int>;

		std::vector<int> make_default_span_data()
		{
			collection_type span_data(defaults::pitch * defaults::height, 0);
			std::iota(span_data.begin(), span_data.end(), 0);

			return span_data;
		}

		const collection_type test_data_(make_default_span_data());
		const collection_type::const_pointer begin_pointer_(test_data_.data());
		const collection_type::const_pointer end_pointer_(test_data_.data() + test_data_.size());
		const box_view<const int> full_box(
			begin_pointer_,
			width,
			height,
			pitch);

	}}


#pragma region Construction
	TEST(test_box_view, default_constructor)
	{
		const box_view<int> box;

		EXPECT_TRUE(box.empty());
		EXPECT_EQ(box.width(), 0U);
		EXPECT_EQ(box.height(), 0U);
		EXPECT_EQ(box.pitch(), 0U);
		EXPECT_EQ(box.count(), 0U);
		EXPECT_EQ(box.begin(), box.end());
		//EXPECT_EQ(box.rbegin(), box.rend());
	}

	KAOS_CONTAINER_DEATH_TEST(test_box_view, value_constructor_null_start_pointer)
	{
		EXPECT_DEATH(
			box_view<const int>(nullptr, 0, 0, 0),
			"start pointer passed to box view cannot be null");
	}

	KAOS_CONTAINER_DEATH_TEST(test_box_view, value_constructor_zero_width)
	{
		EXPECT_DEATH(
			box_view<const int>(defaults::begin_pointer_, 0, 0, 0),
			"width of box view must be greater than 0");
	}

	KAOS_CONTAINER_DEATH_TEST(test_box_view, value_constructor_zero_rows)
	{
		EXPECT_DEATH(
			box_view<const int>(
				defaults::begin_pointer_,
				defaults::width,
				0,
				0),
			"height of box view must be greater than 0");
	}

	KAOS_CONTAINER_DEATH_TEST(test_box_view, value_constructor_zero_pitch)
	{
		EXPECT_DEATH(
			box_view<const int>(
				defaults::begin_pointer_,
				defaults::width,
				defaults::height,
				0),
			"pitch of box view must be greater or equal to width");
	}

	TEST(test_box_view, value_constructor_full_view)
	{
		box_view<const int> box(
			defaults::begin_pointer_,
			defaults::width,
			defaults::height,
			defaults::pitch);

		EXPECT_FALSE(box.empty());
		EXPECT_EQ(box.width(), defaults::width);
		EXPECT_EQ(box.height(), defaults::height);
		EXPECT_EQ(box.pitch(), defaults::pitch);
		EXPECT_EQ(box.count(), defaults::count);
		EXPECT_EQ(box.begin()->data(), defaults::begin_pointer_ );
		EXPECT_EQ((--box.end())->data() + defaults::pitch, defaults::end_pointer_);
		EXPECT_NE(box.begin(), box.end());

		auto verify_ptr(defaults::begin_pointer_);
		for (const auto& row : box)
		{
			ASSERT_EQ(row.size(), defaults::width);
			ASSERT_EQ(row.data(), verify_ptr);
			ASSERT_TRUE(std::equal(row.begin(), row.end(), verify_ptr, verify_ptr + defaults::width));
			verify_ptr += defaults::pitch;
		}
	}

	TEST(test_box_view, value_constructor_right_edge)
	{
		box_view<const int> box(
			defaults::begin_pointer_ + defaults::half_width,
			defaults::half_width,
			defaults::height,
			defaults::pitch);

		EXPECT_FALSE(box.empty());
		EXPECT_EQ(box.width(), defaults::half_width);
		EXPECT_EQ(box.height(), defaults::height);
		EXPECT_EQ(box.pitch(), defaults::pitch);
		EXPECT_EQ(box.count(), defaults::half_count);
		EXPECT_EQ(box.begin()->data(), defaults::begin_pointer_ + defaults::half_width);
		EXPECT_EQ((--box.end())->data() + defaults::pitch, defaults::end_pointer_ + defaults::half_width);

		auto verify_ptr(defaults::begin_pointer_ + defaults::half_width);
		for (const auto& row : box)
		{
			ASSERT_EQ(row.size(), defaults::half_width);
			ASSERT_EQ(row.data(), verify_ptr);
			ASSERT_TRUE(std::equal(row.begin(), row.end(), verify_ptr, verify_ptr + defaults::half_width));
			verify_ptr += defaults::pitch;
		}
	}

	TEST(test_box_view, value_constructor_lower_right_edge)
	{
		auto offset = ((defaults::height / 2) * defaults::pitch) + defaults::half_width;

		box_view<const int> box(
			defaults::begin_pointer_ + offset,
			defaults::half_width,
			defaults::half_height,
			defaults::pitch);

		EXPECT_FALSE(box.empty());
		EXPECT_EQ(box.width(), defaults::half_width);
		EXPECT_EQ(box.height(), defaults::half_height);
		EXPECT_EQ(box.pitch(), defaults::pitch);
		EXPECT_EQ(box.count(), defaults::quarter_count);
		EXPECT_EQ(box.begin()->data(), defaults::begin_pointer_ + offset);
		EXPECT_EQ((--box.end())->data() + defaults::pitch, defaults::end_pointer_ + defaults::half_width);

		auto verify_ptr(defaults::begin_pointer_ + offset);
		for (const auto& row : box)
		{
			ASSERT_EQ(row.size(), defaults::half_width);
			ASSERT_EQ(row.data(), verify_ptr);
			ASSERT_TRUE(std::equal(row.begin(), row.end(), verify_ptr, verify_ptr + defaults::half_width));
			verify_ptr += defaults::pitch;
		}
	}
#pragma endregion

#pragma region Copy and Move
	TEST(test_box_view, copy_constructor_same_types)
	{
		using defaults::full_box;

		box_view<const int> copied_box(full_box);
		ASSERT_EQ(copied_box.empty(), full_box.empty());
		ASSERT_EQ(copied_box.width(), full_box.width());
		ASSERT_EQ(copied_box.height(), full_box.height());
		ASSERT_EQ(copied_box.pitch(), full_box.pitch());
		ASSERT_EQ(copied_box.count(), full_box.count());
		ASSERT_EQ(copied_box.begin(), full_box.begin());
		ASSERT_EQ(copied_box.end(), full_box.end());
		//ASSERT_EQ(copied_box, full_box);
	}

	TEST(test_box_view, copy_constructor_const_to_non_const_types)
	{
		auto test_data_(defaults::make_default_span_data());
		auto begin_pointer_(test_data_.data());

		const box_view<int> full_box(
			begin_pointer_,
			defaults::width,
			defaults::height,
			defaults::pitch);

		box_view<const int> copied_box(full_box);
		ASSERT_EQ(copied_box.empty(), full_box.empty());
		ASSERT_EQ(copied_box.width(), full_box.width());
		ASSERT_EQ(copied_box.height(), full_box.height());
		ASSERT_EQ(copied_box.pitch(), full_box.pitch());
		ASSERT_EQ(copied_box.count(), full_box.count());
		ASSERT_EQ(copied_box.begin()->data(), full_box.begin()->data());
		ASSERT_EQ((--copied_box.end())->data(), (--full_box.end())->data());
		//ASSERT_EQ(copied_box, full_box);
	}

	TEST(test_box_view, move_constructor)
	{
		using defaults::full_box;

		box_view<const int> copied_box(full_box);
		box_view<const int> moved_box(move(copied_box));

		ASSERT_TRUE(copied_box.empty());
		ASSERT_EQ(copied_box.width(), 0U);
		ASSERT_EQ(copied_box.height(), 0U);
		ASSERT_EQ(copied_box.pitch(), 0U);
		ASSERT_EQ(copied_box.count(), 0U);
		ASSERT_EQ(copied_box.begin(), box_view<const int>().begin());
		ASSERT_EQ(copied_box.end(), box_view<const int>().end());
		ASSERT_EQ(copied_box.begin(), copied_box.end());

		ASSERT_EQ(moved_box.empty(), full_box.empty());
		ASSERT_EQ(moved_box.width(), full_box.width());
		ASSERT_EQ(moved_box.height(), full_box.height());
		ASSERT_EQ(moved_box.pitch(), full_box.pitch());
		ASSERT_EQ(moved_box.count(), full_box.count());
		ASSERT_EQ(moved_box.begin(), full_box.begin());
		ASSERT_EQ(moved_box.end(), full_box.end());
	}



	TEST(test_box_view, copy_assignment_constructor)
	{
		using defaults::full_box;

		box_view<const int> copied_box;
		
		copied_box = full_box;
		ASSERT_EQ(copied_box.empty(), full_box.empty());
		ASSERT_EQ(copied_box.width(), full_box.width());
		ASSERT_EQ(copied_box.height(), full_box.height());
		ASSERT_EQ(copied_box.pitch(), full_box.pitch());
		ASSERT_EQ(copied_box.count(), full_box.count());
		ASSERT_EQ(copied_box.begin(), full_box.begin());
		ASSERT_EQ(copied_box.end(), full_box.end());
		//ASSERT_EQ(copied_box, full_box);
	}

	TEST(test_box_view, move_assignment_constructor)
	{
		using defaults::full_box;

		box_view<const int> copied_box(full_box);
		box_view<const int> moved_box;
		
		moved_box = move(copied_box);

		ASSERT_TRUE(copied_box.empty());
		ASSERT_EQ(copied_box.width(), 0U);
		ASSERT_EQ(copied_box.height(), 0U);
		ASSERT_EQ(copied_box.pitch(), 0U);
		ASSERT_EQ(copied_box.count(), 0U);
		ASSERT_EQ(copied_box.begin(), box_view<const int>().begin());
		ASSERT_EQ(copied_box.end(), box_view<const int>().end());
		ASSERT_EQ(copied_box.begin(), copied_box.end());

		ASSERT_EQ(moved_box.empty(), full_box.empty());
		ASSERT_EQ(moved_box.width(), full_box.width());
		ASSERT_EQ(moved_box.height(), full_box.height());
		ASSERT_EQ(moved_box.pitch(), full_box.pitch());
		ASSERT_EQ(moved_box.count(), full_box.count());
		ASSERT_EQ(moved_box.begin(), full_box.begin());
		ASSERT_EQ(moved_box.end(), full_box.end());
	}
#pragma endregion 




#pragma region Subscript operator
	TEST(test_box_view, subscript_operator)
	{
		box_view<const int> box(
			defaults::begin_pointer_ + defaults::half_width,
			defaults::half_width,
			defaults::height,
			defaults::pitch);

		auto verify_ptr(defaults::begin_pointer_ + defaults::half_width);
		for (auto i(0U); i < box.height(); ++i)
		{
			const auto& row(box[i]);
			ASSERT_EQ(row.size(), defaults::half_width);
			ASSERT_EQ(row.data(), verify_ptr);
			ASSERT_TRUE(std::equal(row.begin(), row.end(), verify_ptr, verify_ptr + defaults::half_width));
			verify_ptr += defaults::pitch;
		}
	}

	KAOS_CONTAINER_DEATH_TEST(test_box_view, subscript_operator_out_of_range_negative)
	{
		EXPECT_DEATH(
			DEBUG_DiscardResult(defaults::full_box[-1]),
			"box view index out of range");
	}

	KAOS_CONTAINER_DEATH_TEST(test_box_view, subscript_operator_out_of_range_positive)
	{
		EXPECT_DEATH(
			DEBUG_DiscardResult(defaults::full_box[defaults::full_box.height()]),
			"box view index out of range");
	}
#pragma endregion




#pragma region Subview
	TEST(test_box_view, subview_zero_width)
	{
		using defaults::full_box;

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(full_box.subview(0, 0, 0, 0)),
			std::range_error,
			"subview width cannot be 0");
	}

	TEST(test_box_view, subview_x_out_of_range)
	{
		using defaults::full_box;

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(full_box.subview(full_box.width(), 0, 1, 0)),
			std::out_of_range,
			"x position of requested subview exceeds bounds of current view");
	}

	TEST(test_box_view, subview_x_plus_width_out_of_range)
	{
		using defaults::full_box;

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(full_box.subview(1, 0, full_box.width(), 0)),
			std::out_of_range,
			"horizontal size of requested subview exceeds bounds of current view");
	}



	TEST(test_box_view, subview_zero_height)
	{
		using defaults::full_box;

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(full_box.subview(0, 0, 1, 0)),
			std::range_error,
			"subview height cannot be 0");
	}

	TEST(test_box_view, subview_y_out_of_range)
	{
		using defaults::full_box;

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(full_box.subview(0, full_box.height(), 1, 1)),
			std::out_of_range,
			"y position of requested subview exceeds bounds of current view");
	}

	TEST(test_box_view, subview_y_plus_height_out_of_range)
	{
		using defaults::full_box;

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(full_box.subview(0, 1, 1, full_box.height())),
			std::out_of_range,
			"vertical size of requested subview exceeds bounds of current view");
	}


	TEST(test_box_view, subview_full)
	{
		using defaults::full_box;
		using defaults::width;
		using defaults::height;

		const auto upper_left_box(full_box.subview(0, 0, width, height));

		ASSERT_EQ(upper_left_box.width(), width);
		ASSERT_EQ(upper_left_box.height(), height);
		ASSERT_EQ(upper_left_box.pitch(), full_box.pitch());

		auto verify_ptr(defaults::begin_pointer_ );
		for (const auto& row : upper_left_box)
		{
			ASSERT_EQ(row.data(), verify_ptr);
			ASSERT_TRUE(std::equal(row.begin(), row.end(), verify_ptr, verify_ptr + width));
			verify_ptr += defaults::pitch;
		}		
	}


	TEST(test_box_view, subview_upper_left)
	{
		using defaults::full_box;

		const auto half_width(full_box.width() / 2);
		const auto half_height(full_box.height() / 2);

		const auto upper_left_box(full_box.subview(0, 0, half_width, half_height));

		ASSERT_EQ(upper_left_box.width(), half_width);
		ASSERT_EQ(upper_left_box.height(), half_height);
		ASSERT_EQ(upper_left_box.pitch(), full_box.pitch());

		auto verify_ptr(defaults::begin_pointer_ );
		for (const auto& row : upper_left_box)
		{
			ASSERT_EQ(row.data(), verify_ptr);
			ASSERT_TRUE(std::equal(row.begin(), row.end(), verify_ptr, verify_ptr + half_width));
			verify_ptr += defaults::pitch;
		}		
	}

	TEST(test_box_view, subview_lower_right)
	{
		using defaults::full_box;

		const auto half_width(full_box.width() / 2);
		const auto half_height(full_box.height() / 2);

		const auto lower_right_box(full_box.subview(half_width, half_height, half_width, half_height));

		ASSERT_EQ(lower_right_box.width(), half_width);
		ASSERT_EQ(lower_right_box.height(), half_height);
		ASSERT_EQ(lower_right_box.pitch(), full_box.pitch());

		auto verify_ptr(defaults::begin_pointer_ + (half_height * full_box.pitch()) + half_width);
		for (const auto& row : lower_right_box)
		{
			ASSERT_EQ(row.data(), verify_ptr);
			ASSERT_TRUE(std::equal(row.begin(), row.end(), verify_ptr, verify_ptr + half_width));
			verify_ptr += defaults::pitch;
		}		
	}
#pragma endregion

}}}}}
