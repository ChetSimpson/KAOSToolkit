// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/color_map.h>
#include <boost/numeric/conversion/cast.hpp>
#include <gtest/gtest.h>


namespace hypertech::kaos::assetfoo::colors::unittests
{
	using color_type = color_map::color_type;

	namespace test_colors
	{
		const color_type black(0, 0, 0);
		const color_type red(255, 0, 0);
		const color_type green(0, 255, 0);
		const color_type blue(0, 0, 255);
		const color_type white(255, 255, 255);
	}

	const std::initializer_list<color_type> color_list_init_list =
	{
		color_type(16, 16, 16),
		color_type(255, 0, 0),
		color_type(0, 255, 0),
		color_type(0, 0, 255),
		color_type(85, 85, 85),
		color_type(170, 170, 170),
		color_type(255, 170, 85),
		color_type(255, 255, 255)
	};

	const std::vector<color_type> color_list_vector(color_list_init_list);

	//	Default ctor
	TEST(color_map_default_ctor, default_state)
	{
		color_map map;

		EXPECT_TRUE(map.empty());
		EXPECT_EQ(map.size(), 0U);
		EXPECT_EQ(map.capacity(), 0U);

		//	The max size is determined by the container type used and is
		//	implementation dependant so we only check for greater than 0.
		EXPECT_GT(map.max_size(), 0U);
	}

	//	Ctor with initial color count
	TEST(color_map_ctor_with_initial_color_size, zero_colors)
	{
		color_map map(0);

		EXPECT_TRUE(map.empty());
		EXPECT_EQ(map.size(), 0U);
		EXPECT_EQ(map.capacity(), 0U);

		//	The max size is determined by the container type used and is
		//	implementation dependant so we only check for greater than 0.
		EXPECT_GT(map.max_size(), 0U);
	}

	TEST(color_map_ctor_with_initial_color_size, with_default_colors)
	{
		const color_map map(4);

		EXPECT_FALSE(map.empty());
		EXPECT_EQ(map.size(), 4U);
		EXPECT_GE(map.capacity(), 4U);
		for (const auto& color : map)
		{
			ASSERT_EQ(color, color_map::color_type());
		}

		//	The max size is determined by the container type used and is
		//	implementation dependant so we only check for greater than 0.
		EXPECT_GT(map.max_size(), 0U);
	}

	TEST(color_map_ctor_with_initial_color_size, with_specific_color)
	{
		const auto color(color_map::color_type(25, 50, 60));
		const color_map map(4, color);

		EXPECT_FALSE(map.empty());
		EXPECT_EQ(map.size(), 4U);
		EXPECT_GE(map.capacity(), 4U);
		for (const auto& color : map)
		{
			ASSERT_EQ(color, color);
		}

		//	The max size is determined by the container type used and is
		//	implementation dependant so we only check for greater than 0.
		EXPECT_GT(map.max_size(), 0U);
	}

	//	Ctor with initial color count and max colors
	TEST(color_map_ctor_with_max_colors, valid_16_max_colors)
	{
		const color_map colormap(0, 16);

		EXPECT_EQ(colormap.max_size(), 16);
	}

	TEST(color_map_ctor_with_max_colors, zero_max_colors)
	{
		EXPECT_THROW(color_map(0, 0), std::invalid_argument);
	}

	TEST(color_map_ctor_with_max_colors, initial_color_greater_than_max_colors)
	{
		EXPECT_THROW(color_map(2, 1), std::out_of_range);
	}

	//	Ctor from vector with max colors argument
	TEST(color_map_ctor_from_vector, contents_initialized)
	{
		const color_map colormap(color_list_vector);

		//	The max size is determined by the container type used and is
		//	implementation dependant so we only check for greater than the size
		//	of the size of init data.
		EXPECT_GT(colormap.max_size(), color_list_vector.size());	

		//	Check size and contents
		EXPECT_EQ(colormap.size(), color_list_vector.size());
		for (auto i = 0U; i < color_list_vector.size(); ++i)
		{
			EXPECT_EQ(colormap[i], color_list_vector[i]);
		}
	}

	TEST(color_map_ctor_from_vector, zero_max_colors)
	{
		EXPECT_THROW(color_map(std::vector<color_type>(), 0), std::invalid_argument);
	}

	TEST(color_map_ctor_from_vector, exceed_max_colors)
	{
		EXPECT_THROW(color_map(color_list_vector, color_list_vector.size() - 1), std::length_error);
	}

	TEST(color_map_ctor_from_vector, more_max_colors_than_init_data)
	{
		const auto max_size = color_list_vector.size() + 20;
		const color_map colormap(color_list_vector, max_size);

		EXPECT_EQ(colormap.max_size(), max_size);
	}

	//	Ctor from initializer list
	TEST(color_map_ctor_from_initializer_list, contents_initialized)
	{
		const color_map colormap(color_list_init_list);

		//	The max size is determined by the container type used and is
		//	implementation dependant so we only check for greater than the size
		//	of the size of init data.
		EXPECT_GT(colormap.max_size(), color_list_init_list.size());	

		//	Check size and contents
		EXPECT_EQ(colormap.size(), color_list_init_list.size());
		for (auto i = 0U; i < color_list_init_list.size(); ++i)
		{
			EXPECT_EQ(colormap[i], std::data(color_list_init_list)[i]);
		}
	}

	TEST(color_map_ctor_from_initializer_list, zero_max_colors)
	{
		EXPECT_THROW(color_map(std::vector<color_type>(), 0), std::invalid_argument);
	}

	TEST(color_map_ctor_from_initializer_list, exceed_max_colors)
	{
		EXPECT_THROW(color_map(color_list_init_list, color_list_init_list.size() - 1), std::length_error);
	}

	TEST(color_map_ctor_from_initializer_list, same_max_colors_as_init_data)
	{
		EXPECT_NO_THROW(color_map(color_list_init_list, color_list_init_list.size()));
	}

	TEST(color_map_ctor_from_initializer_list, more_max_colors_than_init_data)
	{
		const auto max_size = color_list_init_list.size() + 20;

		EXPECT_EQ(color_map(color_list_init_list, max_size).max_size(), max_size);
	}

	//	color_map::at
	TEST(color_map_at, non_const_access)
	{
		color_map colormap(color_list_vector);

		for (color_map::size_type i = 0U; i < colormap.size(); ++i)
		{
			EXPECT_EQ(colormap.at(i), color_list_vector[i]);

			auto new_color(color_type(
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i)));
			colormap.at(i) = new_color;
			EXPECT_EQ(colormap.at(i), new_color);
		}

		EXPECT_THROW(colormap.at(colormap.size() + 10), std::out_of_range);
	}

	TEST(color_map_at, const_access)
	{
		const color_map colormap(color_list_vector);

		for (color_map::size_type i = 0U; i < colormap.size(); ++i)
		{
			EXPECT_EQ(colormap.at(i), color_list_vector[i]);

		}

		EXPECT_THROW(colormap.at(colormap.size() + 10), std::out_of_range);	}


	//	color_map:operator[]
	TEST(color_map_subscript_operator, non_const_access)
	{
		color_map colormap(color_list_vector);

		for (color_map::size_type i = 0U; i < colormap.size(); ++i)
		{
			EXPECT_EQ(colormap[i], color_list_vector[i]);

			auto new_color(color_type(
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i)));
			colormap[i] = new_color;
			EXPECT_EQ(colormap[i], new_color);
		}

		EXPECT_THROW(colormap[colormap.size() + 10], std::out_of_range);
	}

	TEST(color_map_subscript_operator, const_access)
	{
		const color_map colormap(color_list_vector);

		for (color_map::size_type i = 0U; i < colormap.size(); ++i)
		{
			EXPECT_EQ(colormap[i], color_list_vector[i]);
		}

		EXPECT_THROW(colormap[colormap.size() + 10], std::out_of_range);
	}

	//	Capacity
	TEST(color_map_capacity, empty)
	{
		EXPECT_TRUE(color_map().empty());
		EXPECT_FALSE(color_map(color_list_init_list).empty());
	}

	TEST(color_map_capacity, size)
	{
		EXPECT_EQ(color_map().size(), 0);
		EXPECT_NE(color_map(color_list_init_list).size(), 0);
	}

	TEST(color_map_capacity, max_size)
	{
		EXPECT_NE(color_map().max_size(), 0);
		EXPECT_EQ(color_map(0, 16).max_size(), 16);
	}

	//	Modifiers and operations
	TEST(color_map_modifiers, clear)
	{
		color_map colormap(color_list_init_list);

		EXPECT_FALSE(colormap.empty());
		colormap.clear();
		EXPECT_TRUE(colormap.empty());
		EXPECT_EQ(colormap.size(), 0);
	}

	TEST(color_map_modifiers, add)
	{
		color_map colormap;

		EXPECT_EQ(colormap.add(test_colors::black), 0);
		EXPECT_FALSE(colormap.empty());
		EXPECT_EQ(colormap.size(), 1);
		EXPECT_EQ(colormap[0], test_colors::black);

		EXPECT_EQ(colormap.add(test_colors::white), 1);
		EXPECT_EQ(colormap.size(), 2);
		EXPECT_EQ(colormap[0], test_colors::black);
		EXPECT_EQ(colormap[1], test_colors::white);

		EXPECT_EQ(colormap.add(test_colors::green), 2);
		EXPECT_EQ(colormap.size(), 3);
		EXPECT_EQ(colormap[0], test_colors::black);
		EXPECT_EQ(colormap[1], test_colors::white);
		EXPECT_EQ(colormap[2], test_colors::green);

		EXPECT_EQ(colormap.add(test_colors::black), 3);
		EXPECT_EQ(colormap.size(), 4);
		EXPECT_EQ(colormap[0], test_colors::black);
		EXPECT_EQ(colormap[1], test_colors::white);
		EXPECT_EQ(colormap[2], test_colors::green);
		EXPECT_EQ(colormap[3], test_colors::black);
	}

	TEST(color_map_modifiers, add_exceed_max_colors)
	{
		color_map colormap(0, 2);

		EXPECT_EQ(colormap.add(test_colors::black), 0);
		EXPECT_EQ(colormap.add(test_colors::white), 1);

		EXPECT_THROW(colormap.add(test_colors::green), std::length_error);
	}

	TEST(color_map_modifiers, add_unique)
	{
		color_map colormap;

		EXPECT_EQ(colormap.add(test_colors::black), 0);
		EXPECT_FALSE(colormap.empty());
		EXPECT_EQ(colormap.size(), 1);
		EXPECT_EQ(colormap[0], test_colors::black);

		EXPECT_EQ(colormap.add_unique(test_colors::white), 1);
		EXPECT_EQ(colormap.size(), 2);
		EXPECT_EQ(colormap[0], test_colors::black);
		EXPECT_EQ(colormap[1], test_colors::white);

		EXPECT_EQ(colormap.add_unique(test_colors::green), 2);
		EXPECT_EQ(colormap.size(), 3);
		EXPECT_EQ(colormap[0], test_colors::black);
		EXPECT_EQ(colormap[1], test_colors::white);
		EXPECT_EQ(colormap[2], test_colors::green);


		EXPECT_EQ(colormap.add_unique(test_colors::black), 0);
		EXPECT_EQ(colormap.add_unique(test_colors::white), 1);
		EXPECT_EQ(colormap.add_unique(test_colors::green), 2);
	}

	TEST(color_map_modifiers, add_unique_exceed_max_colors)
	{
		color_map colormap(0, 2);

		EXPECT_EQ(colormap.add_unique(test_colors::black), 0);
		EXPECT_EQ(colormap.add_unique(test_colors::white), 1);

		EXPECT_THROW(colormap.add_unique(test_colors::green), std::length_error);
	}

	TEST(color_map_modifiers, set)
	{
		color_map colormap(color_list_vector);

		for (color_map::size_type i = 0U; i < colormap.size(); ++i)
		{
			const color_type new_color(
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i));

			colormap.set(i, color_type(
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i),
				boost::numeric_cast<color_type::component_value_type>(i)));
			EXPECT_EQ(colormap[i], new_color);
		}
	}

	TEST(color_map_modifiers, set_out_of_bounds)
	{
		color_map colormap(color_list_vector);

		EXPECT_THROW(colormap.set(color_list_vector.size() + 1, test_colors::black), std::out_of_range);
	}

	TEST(color_map_search, index_of)
	{
		color_map colormap{ test_colors::black, test_colors::red, test_colors::white };

		auto position(colormap.index_of(test_colors::black));
		EXPECT_TRUE(position.has_value());
		EXPECT_EQ(position.value(), 0);

		position = colormap.index_of(test_colors::red);
		EXPECT_TRUE(position.has_value());
		EXPECT_EQ(position.value(), 1);

		position = colormap.index_of(test_colors::white);
		EXPECT_TRUE(position.has_value());
		EXPECT_EQ(position.value(), 2);
	}

	TEST(color_map_search, indexof_no_color_exists)
	{
		color_map colormap{ test_colors::black, test_colors::red, test_colors::white };

		EXPECT_FALSE(colormap.index_of(test_colors::green).has_value());
		EXPECT_FALSE(colormap.index_of(test_colors::blue).has_value());
	}

}
