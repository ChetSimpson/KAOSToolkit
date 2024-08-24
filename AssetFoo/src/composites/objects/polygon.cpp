// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/composites/objects/polygon.h>


namespace hypertech::kaos::assetfoo::composites::objects
{

	polygon::polygon(
		std::optional<string_type> name,
		std::optional<string_type> class_type,
		position_type position,
		point_list_type points)
		:
		object(move(name), move(class_type), position),
		points_(points)
	{}


	bool polygon::operator==(const object& other_object) const noexcept
	{
		auto other(dynamic_cast<const polygon*>(&other_object));
		if (!other)
		{
			return false;
		}

		return
			object::operator==(*other)
			&& points_ == other->points_;
	}


	polygon::iterator polygon::begin() noexcept
	{
		return points_.begin();
	}

	polygon::iterator polygon::end() noexcept
	{
		return points_.end();
	}


	polygon::const_iterator polygon::begin() const noexcept
	{
		return points_.begin();
	}

	polygon::const_iterator polygon::end() const noexcept
	{
		return points_.end();
	}


	polygon::const_iterator polygon::cbegin() const noexcept
	{
		return points_.cbegin();
	}

	polygon::const_iterator polygon::cend() const noexcept
	{
		return points_.cend();
	}

	polygon::size_type polygon::count() const noexcept
	{
		return points_.size();
	}

}
