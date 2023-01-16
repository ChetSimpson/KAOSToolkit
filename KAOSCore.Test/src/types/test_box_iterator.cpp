// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/box_iterator.h>
#include <kaos/test/gtest-extensions.h>
#include <gtest/gtest.h>
#include <numeric>


namespace hypertech { namespace kaos { namespace core { namespace types { namespace unittests
{

#ifdef KAOS_ENABLE_ITERATOR_VERIFY
#define KAOS_ITERATOR_DEATH_TEST(test_case_name, test_name) TEST(test_case_name, test_name)
#else
#define KAOS_ITERATOR_DEATH_TEST(test_case_name, test_name)	KAOS_DEATH_TEST(test_case_name, test_name)
#undef EXPECT_DEATH
#define EXPECT_DEATH(x, y)
#endif

	namespace { namespace defaults
	{
		const size_t pitch = 64;
		const size_t width = pitch / 2;
		const size_t height = 32;

		std::vector<int> make_default_data()
		{
			std::vector<int> data(defaults::width * defaults::height, 0);
			std::iota(data.begin(), data.end(), 0);

			return data;
		}

		const std::vector<int> data(make_default_data());

		const box_iterator<const int> single_line_data(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + pitch,
#endif
			width,
			pitch);
		const box_iterator<const int> two_line_data(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (pitch * 2),
#endif
			width,
			pitch);
	}}


#pragma region Construction
	TEST(test_box_iterator, data_constructed)
	{
		EXPECT_EQ(defaults::single_line_data->size(), defaults::width);
		EXPECT_EQ(defaults::two_line_data->size(), defaults::width);
	}


	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, value_constructor_null_current_pointer)
	{
		EXPECT_DEATH(
			box_iterator<const int>(nullptr, nullptr, nullptr, 0, 0),
			"starting current pointer for box iterator cannot be null");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, value_constructor_null_begin_pointer)
	{
		using defaults::data;

		EXPECT_DEATH(
			box_iterator<const int>(data.data(), nullptr, nullptr, 0, 0),
			"begin pointer for box iterator cannot be null");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, value_constructor_null_end_pointer)
	{
		using defaults::data;

		EXPECT_DEATH(
			box_iterator<const int>(data.data(), data.data(), nullptr, 0, 0),
			"end pointer is less than or equal to begin pointer for box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, value_constructor_zero_width)
	{
		using defaults::data;

		EXPECT_DEATH(
			box_iterator<const int>(data.data(), data.data(), data.data() + 1, 0, 0),
			"width of box iterator must be greater than 0");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, value_constructor_pitch_less_than_width)
	{
		using defaults::data;

		EXPECT_DEATH(
			box_iterator<const int>(data.data(), data.data(), data.data() + 1, 1, 0),
			"pitch of box iterator must be greater or equal to width");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, value_constructor_size_not_multiple_of_pitch)
	{
		using defaults::data;

		EXPECT_DEATH(
			box_iterator<const int>(data.data(), data.data(), data.data() + 17, 1, 8),
			"size of data from beginptr to endptr must be a multiple of the pitch");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, value_constructor_start_pointer_out_of_bounds)
	{
		using defaults::data;

		EXPECT_DEATH(
			box_iterator<const int>(data.data() - 1, data.data(), data.data() + 17, 1, 8),
			"current pointer is not inside the bounds of the current and end pointers");
	}
#pragma endregion




#pragma region Prefix Increment
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, prefix_increment_operator_on_value_initialized)
	{
		EXPECT_DEATH(++box_iterator<int>(), "cannot increment value-initialized box iterator");
	}

	TEST(test_box_iterator, prefix_increment_operator_move_to_next_row)
	{
		auto box(defaults::two_line_data);

		++box;	//	Move to next line
		EXPECT_EQ(box->data(), defaults::data.data() + defaults::pitch);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, prefix_increment_operator_move_past_end)
	{
		auto box(defaults::single_line_data);
		++box;	//	Move to end
		EXPECT_DEATH(++box, "cannot increment box iterator past end");
	}
#pragma endregion




#pragma region Postfix Increment
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, postfix_increment_operator_on_value_initialized)
	{
		EXPECT_DEATH(box_iterator<int>()++, "cannot increment value-initialized box iterator");
	}

	TEST(test_box_iterator, postfix_increment_operator_to_next_row)
	{
		auto box(defaults::two_line_data);
		box++;	//	Move to next row
		EXPECT_EQ(box->data(), defaults::data.data() + defaults::pitch);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, postfix_increment_operator_move_past_end)
	{
		auto box(defaults::single_line_data);
		box++;	//	Move to end
		EXPECT_DEATH(box++, "cannot increment box iterator past end");
	}
#pragma endregion




#pragma region Prefix Decrement
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, prefix_decrement_operator_on_value_initialized)
	{
		EXPECT_DEATH(--box_iterator<int>(), "cannot decrement value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, prefix_decrement_operator_move_before_beginning)
	{
		auto box(defaults::single_line_data);
		EXPECT_DEATH(--box, "cannot decrement box iterator at begin");
	}

	TEST(test_box_iterator, prefixdecrementoperatormovetobeginning)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_EQ(box->data(), defaults::data.data() + defaults::pitch);
		--box;
		EXPECT_EQ(box->data(), defaults::data.data());
	}
#pragma endregion 




#pragma region Postfix Decrement
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, postfix_decrement_operator_on_value_initialized)
	{
		EXPECT_DEATH(box_iterator<int>()--, "cannot decrement value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, postfix_decrement_operator_move_before_beginning)
	{
		auto box(defaults::single_line_data);
		EXPECT_DEATH(box--, "cannot decrement box iterator at begin");
	}

	TEST(test_box_iterator, postfix_decrement_operator_move_to_beginning)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_EQ(box->data(), defaults::data.data() + defaults::pitch);
		box--;
		EXPECT_EQ(box->data(), defaults::data.data());
	}
#pragma endregion 




#pragma region Assignment By Addition
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_addition_on_valid_initialized)
	{
		EXPECT_DEATH(box_iterator<int>() += 1, "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_addition_seek_past_end)
	{
		auto box(defaults::single_line_data);
		++box;
		EXPECT_DEATH(box += 1, "cannot seek box iterator after end");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_addition_seek_past_end_again)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		EXPECT_DEATH(box += 1, "cannot seek box iterator after end");
	}

	TEST(test_box_iterator, assignment_by_addition_seek_to_next_row)
	{
		auto box(defaults::two_line_data);
		box += 1;
		EXPECT_EQ(box->data(), defaults::data.data() + defaults::pitch);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_addition_seek_to_end)
	{
		auto box(defaults::two_line_data);
		box += 2;
		EXPECT_DEATH((void)box->data(), "cannot \\(->\\) dereference ended box iterator");
	}


	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_negative_addition_on_valid_initialized)
	{
		EXPECT_DEATH(box_iterator<int>() += -1, "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_negative_addition_seek_before_begin)
	{
		auto box(defaults::single_line_data);
		EXPECT_DEATH(box += -1, "cannot seek box iterator before begin");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_negative_addition_seek_before_begin_again)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_DEATH(box += -2, "cannot seek box iterator before begin");
	}

	TEST(test_box_iterator, assignment_by_negative_addition_seek_to_previous_row)
	{
		auto box(defaults::two_line_data);
		++box;
		box += -1;
		EXPECT_EQ(box->data(), defaults::data.data());
	}

	TEST(test_box_iterator, assignment_by_negative_addition_seek_to_beginning_two_rows_back)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		box += -2;
		EXPECT_EQ(box->data(), defaults::data.data());
	}
#pragma endregion 




#pragma region Advance By Addition
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_addition_on_valid_initialized)
	{
		EXPECT_DEATH((void)(box_iterator<int>() + 1), "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_addition_seek_past_end)
	{
		auto box(defaults::single_line_data);
		++box;
		EXPECT_DEATH((void)(box + 1), "cannot seek box iterator after end");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_addition_seek_past_end_again)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		EXPECT_DEATH((void)(box + 1), "cannot seek box iterator after end");
	}

	TEST(test_box_iterator, advance_by_addition_seek_to_next_row)
	{
		auto box(defaults::two_line_data);
		auto box1 = box + 1;
		EXPECT_EQ(box1->data(), defaults::data.data() + defaults::pitch);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_addition_seek_to_end)
	{
		auto box(defaults::two_line_data);
		auto box1 = box + 2;
		EXPECT_DEATH((void)(box1->data()), "cannot \\(->\\) dereference ended box iterator");
	}


	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_negative_addition_onvalidinitialized)
	{
		EXPECT_DEATH((void)(box_iterator<int>() += -1), "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_negative_addition_seek_before_begin)
	{
		auto box(defaults::single_line_data);
		EXPECT_DEATH((void)(box + -1), "cannot seek box iterator before begin");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_negative_addition_seek_before_begin_again)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_DEATH(DEBUG_DiscardResult(box + -2), "cannot seek box iterator before begin");
	}

	TEST(test_box_iterator, advance_by_negative_addition_seek_to_previous_row)
	{
		auto box(defaults::two_line_data);
		++box;
		auto box1(box + -1);
		EXPECT_EQ(box1->data(), defaults::data.data());
	}

	TEST(test_box_iterator, advance_by_negative_addition_seek_to_beginning_two_rows_back)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		auto box1(box + -2);
		EXPECT_EQ(box1->data(), defaults::data.data());
	}
#pragma endregion 




#pragma region Assignment By Subtraction
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_subtraction_on_valid_initialized)
	{
		EXPECT_DEATH(box_iterator<int>() -= 1, "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_subtraction_seek_before_begin)
	{
		auto box(defaults::single_line_data);
		EXPECT_DEATH(box -= 1, "cannot seek box iterator before begin");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_subtraction_seek_before_begin_again)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_DEATH(box -= 2, "cannot seek box iterator before begin");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_subtraction_seek_before_begin_yet_again)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		EXPECT_DEATH(box -= 3, "cannot seek box iterator before begin");
	}

	TEST(test_box_iterator, assignment_by_subtraction_seek_to_previous_row)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		box -= 1;
		EXPECT_EQ(box->data(), defaults::data.data() + defaults::pitch);
	}

	TEST(test_box_iterator, assignment_by_subtraction_seek_to_beginning)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		box -= 2;
		EXPECT_EQ(box->data(), defaults::data.data());
	}


	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_negative_subtraction_on_valid_initialized)
	{
		EXPECT_DEATH(box_iterator<int>() -= -1, "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_negative_subtraction_seek_after_end)
	{
		auto box(defaults::single_line_data);
		++box;
		EXPECT_DEATH(box -= -1, "cannot seek box iterator after end");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_negative_subtraction_seek_after_end_again)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_DEATH(box -= -2, "cannot seek box iterator after end");
	}

	TEST(test_box_iterator, assignment_by_negative_subtraction_seek_to_next_row)
	{
		auto box(defaults::two_line_data);
		box -= -1;
		EXPECT_EQ(box->data(), defaults::data.data() + defaults::pitch);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, assignment_by_negative_subtraction_seek_to_end)
	{
		auto box(defaults::two_line_data);
		box -= -2;
		EXPECT_DEATH(DEBUG_DiscardResult(box->data()), "cannot \\(->\\) dereference ended box iterator");
	}
#pragma endregion 





#pragma region Assignment By_Subtraction
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_subtraction_on_valid_initialized)
	{
		EXPECT_DEATH(DEBUG_DiscardResult(box_iterator<int>() - 1), "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_subtraction_seek_before_begin)
	{
		auto box(defaults::single_line_data);
		EXPECT_DEATH(DEBUG_DiscardResult(box - 1), "cannot seek box iterator before begin");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_subtraction_seek_before_begin_again)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_DEATH(DEBUG_DiscardResult(box - 2), "cannot seek box iterator before begin");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_subtraction_seek_before_begin_yet_again)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		EXPECT_DEATH(DEBUG_DiscardResult(box - 3), "cannot seek box iterator before begin");
	}

	TEST(test_box_iterator, advance_by_subtraction_seek_to_previous_row)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		auto box1(box - 1);
		EXPECT_EQ(box1->data(), defaults::data.data() + defaults::pitch);
	}

	TEST(test_box_iterator, advance_by_subtraction_seek_to_beginning)
	{
		auto box(defaults::two_line_data);
		++box;
		++box;
		auto box1(box - 2);
		EXPECT_EQ(box1->data(), defaults::data.data());
	}


	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_negative_subtraction_on_valid_initialized)
	{
		EXPECT_DEATH(DEBUG_DiscardResult(box_iterator<int>() - -1), "cannot seek value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_negative_subtraction_seek_after_end)
	{
		auto box(defaults::single_line_data);
		++box;
		EXPECT_DEATH(DEBUG_DiscardResult(box - -1), "cannot seek box iterator after end");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_negative_subtraction_seek_after_end_again)
	{
		auto box(defaults::two_line_data);
		++box;
		EXPECT_DEATH(DEBUG_DiscardResult(box - -2), "cannot seek box iterator after end");
	}

	TEST(test_box_iterator, advance_by_negative_subtraction_seek_to_next_row)
	{
		auto box(defaults::two_line_data);
		auto box1(box - -1);
		EXPECT_EQ(box1->data(), defaults::data.data() + defaults::pitch);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, advance_by_negative_subtraction_seek_to_end)
	{
		auto box(defaults::two_line_data);
		auto box1(box - -2);
		EXPECT_DEATH(DEBUG_DiscardResult(box1->data()), "cannot \\(->\\) dereference ended box iterator");
	}
#pragma endregion 



#pragma region Difference
	TEST(test_box_iterator, difference)
	{
		auto box(defaults::two_line_data);

		EXPECT_EQ(box - defaults::two_line_data, 0);
		++box;
		EXPECT_EQ(box - defaults::two_line_data, 1);
		++box;
		EXPECT_EQ(box - defaults::two_line_data, 2);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, difference_on_incompatible_iterators)
	{
		EXPECT_DEATH(
			DEBUG_DiscardResult(defaults::two_line_data - defaults::single_line_data),
			"cannot subtract incompatible box iterators");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, difference_on_incompatible_iterators_again)
	{
		const size_t width1 = 8;
		const size_t width2 = 4;
		const size_t pitch = 8;
		const size_t height = 8;

		const std::vector<int> data(pitch * height, 0);
		const box_iterator<const int> box1(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (height * pitch),
#endif
			width1,
			pitch);
		const box_iterator<const int> box2(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (height * pitch),
#endif
			width2,
			pitch);
		EXPECT_DEATH(
			DEBUG_DiscardResult(box2 - box1),
			"cannot subtract incompatible box iterators");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, difference_on_incompatible_iterators_yetagain)
	{
		const size_t width = 4;
		const size_t pitch1 = 4;
		const size_t pitch2 = 8;
		const size_t height = 8;

		const std::vector<int> data(pitch2 * height, 0);
		const box_iterator<const int> box1(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (height * pitch2),
#endif
			width,
			pitch1);
		const box_iterator<const int> box2(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (height * pitch2),
#endif
			width, pitch2);
		EXPECT_DEATH(
			DEBUG_DiscardResult(box2 - box1),
			"cannot subtract incompatible box iterators");
	}
#pragma endregion


#pragma region Dereferencing
	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, dereference_on_value_initialized_instance)
	{
		box_iterator<int> box;

		EXPECT_DEATH(DEBUG_DiscardResult(*box), "cannot \\(\\*\\) dereference value-initialized box iterator");
		EXPECT_DEATH(DEBUG_DiscardResult(box->data()), "cannot \\(->\\) dereference value-initialized box iterator");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, dereference_on_ended_iterator)
	{
		auto box(defaults::single_line_data);
		++box;

		EXPECT_DEATH(DEBUG_DiscardResult(*box), "cannot \\(\\*\\) dereference ended box iterator");
		EXPECT_DEATH(DEBUG_DiscardResult(box->data()), "cannot \\(->\\) dereference ended box iterator");
	}
#pragma endregion


#pragma region Comparison
	TEST(test_box_iterator, compare_equality_on_empty)
	{
		EXPECT_TRUE(box_iterator<int>() == box_iterator<int>());
		EXPECT_FALSE(box_iterator<int>() != box_iterator<int>());
	}

	TEST(test_box_iterator, compare_equality_on_compatible_iterators)
	{
		using defaults::data;
		using defaults::width;
		using defaults::height;
		using defaults::pitch;

		box_iterator<const int> first(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (pitch * height),
#endif
			width,
			pitch);
		box_iterator<const int> second(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (pitch * height),
#endif
			width,
			pitch);

		EXPECT_TRUE(first == second);
		EXPECT_FALSE(first != second);
		++first;
		++second;
		EXPECT_TRUE(first == second);
		EXPECT_FALSE(first != second);
		++second;
		EXPECT_TRUE(first != second);
		EXPECT_FALSE(first == second);
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, compare_equality_on_incompatible_iterators)
	{
		using defaults::data;
		using defaults::width;
		using defaults::height;
		using defaults::pitch;

		box_iterator<const int> first(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (pitch * height),
#endif
			width,
			pitch);
		box_iterator<const int> second(
			data.data() + pitch,
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data() + pitch,
			data.data() + (pitch * height),
#endif
			width,
			pitch);

		EXPECT_DEATH(DEBUG_DiscardResult(first == second), "cannot compare incompatible box iterators for equality");
		EXPECT_DEATH(DEBUG_DiscardResult(first != second), "cannot compare incompatible box iterators");
	}

	KAOS_ITERATOR_DEATH_TEST(test_box_iterator, compare_equality_on_incompatible_iterators_again)
	{
		using defaults::data;
		using defaults::width;
		using defaults::height;
		using defaults::pitch;

		box_iterator<const int> first(
			data.data(),
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data(),
			data.data() + (pitch * height),
#endif
			width,
			pitch);
		box_iterator<const int> second(
			data.data() + pitch,
#ifdef KAOS_ENABLE_ITERATOR_VERIFY
			data.data() + pitch,
			data.data() + (pitch * height),
#endif
			width,
			pitch);

		++first;
		EXPECT_DEATH(DEBUG_DiscardResult(first == second), "cannot compare incompatible box iterators for equality");
		EXPECT_DEATH(DEBUG_DiscardResult(first != second), "cannot compare incompatible box iterators");
	}
#pragma endregion

}}}}}
