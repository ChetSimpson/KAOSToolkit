// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/color_map.h>
#include <utility>
#include <stdexcept>


namespace hypertech::kaos::assetfoo::colors
{

#pragma region Construction
	color_map::color_map()
		: max_colors_(0)
	{}


	color_map::color_map(
		size_type initial_color_count,
		color_type default_color)
		:
		max_colors_(),
		colors_(initial_color_count, default_color)
	{}


	color_map::color_map(
		size_type initial_color_count,
		size_type max_color_count,
		color_type default_color)
		:
		max_colors_(max_color_count),
		colors_(initial_color_count > max_color_count ? 0 : initial_color_count, default_color)
	{
		if (max_colors_ == 0)
		{
			throw std::invalid_argument("Maximum number of colors passed to color_map cannot be 0");
		}

		if (initial_color_count > max_color_count)
		{
			throw std::out_of_range("Initial color count in colormap cannot be greater than maximum number of colors");
		}
	}


	color_map::color_map(collection_type colors) noexcept
		:
		max_colors_(),
		colors_(move(colors))
	{}


	color_map::color_map(collection_type colors, size_type max_color_count)
		:
		max_colors_(max_color_count),
		colors_(move(colors))
	{
		if (max_colors_ == 0)
		{
			throw std::invalid_argument("Maximum number of colors passed to color_map cannot be 0");
		}

		if (colors_.size() > max_colors_)
		{
			throw std::length_error("Number of colors in list passed to color_map exceeds maximum number of colors specified");
		}
	}


	color_map::color_map(const std::initializer_list<color_type>& colors)
		:
		max_colors_(),
		colors_(colors.begin(), colors.end())
	{}


	color_map::color_map(const std::initializer_list<color_type>& colors, size_type max_color_count)
		:
		max_colors_(max_color_count),
		colors_(colors.begin(), colors.end())
	{
		if (max_colors_ == 0)
		{
			throw std::invalid_argument("Maximum number of colors passed to color_map cannot be 0");
		}

		if (colors_.size() > max_colors_)
		{
			throw std::length_error("Number of colors in list passed to color_map exceeds maximum number of colors specified");
		}
	}
#pragma endregion


#pragma region Element Access
	color_map::reference color_map::at(size_type position)
	{
		return colors_.at(position);
	}

	color_map::const_reference color_map::at(size_type position) const
	{
		return colors_.at(position);
	}

	color_map::reference color_map::operator[](size_type position)
	{
		if (position >= colors_.size())
		{
			throw std::out_of_range("Specified position is greater than the number of available colors");
		}

		return colors_[position];
	}


	color_map::const_reference color_map::operator[](size_type position) const
	{
		if (position >= colors_.size())
		{
			throw std::out_of_range("Specified position is greater than the number of available colors");
		}

		return colors_[position];
	}
#pragma endregion



#pragma region Iterators
	color_map::iterator color_map::begin() noexcept
	{
		return colors_.begin();
	}

	color_map::const_iterator color_map::begin() const noexcept
	{
		return colors_.begin();
	}

	color_map::const_iterator color_map::cbegin() const noexcept
	{
		return colors_.cbegin();
	}

	color_map::iterator color_map::end() noexcept
	{
		return colors_.end();
	}

	color_map::const_iterator color_map::end() const noexcept
	{
		return colors_.end();
	}

	color_map::const_iterator color_map::cend() const noexcept
	{
		return colors_.cend();
	}
#pragma endregion



#pragma region Capacity
	bool color_map::empty() const noexcept
	{
		return colors_.empty();
	}

	color_map::size_type color_map::size() const noexcept
	{
		return colors_.size();
	}

	color_map::size_type color_map::capacity() const noexcept
	{
		return colors_.capacity();
	}

	color_map::size_type color_map::max_size() const noexcept
	{
		return max_colors_ != 0 ? max_colors_ : colors_.max_size();
	}
#pragma endregion



#pragma region Modifiers and operations
	void color_map::clear() noexcept
	{
		return colors_.clear();
	}


	color_map::size_type color_map::add(const_reference color)
	{
		if (max_colors_ != 0 && colors_.size() == max_colors_)
		{
			throw std::length_error("Cannnot add color to colormap. Max colormap size reached");
		}

		colors_.emplace_back(color);

		return colors_.size() - 1;
	}


	color_map::size_type color_map::add_unique(const_reference color)
	{
		const auto found_color_iterator(find(colors_.begin(), colors_.end(), color));
		if (found_color_iterator != colors_.end())
		{
			return distance(colors_.begin(), found_color_iterator);
		}

		if (max_colors_ != 0 && colors_.size() == max_colors_)
		{
			throw std::length_error("Cannnot add color to colormap. Max colormap size reached");
		}

		colors_.emplace_back(color);

		return colors_.size() - 1;
	}


	void color_map::set(size_type position, const_reference color)
	{
		if (position >= colors_.size())
		{
			throw std::out_of_range("Specified position is greater than the number of available colors");
		}

		colors_[position] = color;
	}
#pragma endregion



#pragma region Search
	std::optional<color_map::size_type> color_map::index_of(const_reference color) const noexcept
	{
		const auto current_color(find(colors_.begin(), colors_.end(), color));
		if (current_color != colors_.end())
		{
			return distance(colors_.begin(), current_color);
		}

		return {};
	}


	std::optional<color_map::size_type> color_map::index_of(const predicate_type& predicate) const noexcept
	{
		const auto current_color(find_if(colors_.begin(), colors_.end(), predicate));
		if (current_color != colors_.end())
		{
			return distance(colors_.begin(), current_color);
		}

		return {};
	}
#pragma endregion

}
