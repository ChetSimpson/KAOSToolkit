// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/composites/objects/ellipse.h>


namespace hypertech::kaos::assetfoo::composites::objects
{

	ellipse::ellipse(
		std::optional<string_type> name,
		std::optional<string_type> class_type,
		position_type position,
		dimensions_type dimensions)
		:
		object(move(name), move(class_type), position),
		dimensions_(dimensions)
	{}


	bool ellipse::operator==(const object& other_object) const noexcept
	{
		auto other(dynamic_cast<const ellipse*>(&other_object));
		if (!other)
		{
			return false;
		}

		return
			object::operator==(*other)
			&& dimensions_ == other->dimensions_;
	}


	ellipse::dimensions_type ellipse::dimensions() const noexcept
	{
		return dimensions_;
	}

	void ellipse::set_dimensions(dimensions_type dimensions) noexcept
	{
		dimensions_ = dimensions;
	}

}
