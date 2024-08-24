// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/composites/object.h>
#include <stdexcept>


namespace hypertech::kaos::assetfoo::composites
{

	object::object(
		std::optional<string_type> name,
		std::optional<string_type> class_type,
		position_type position)
		:
		name_(move(name)),
		class_type_(move(class_type)),
		position_(position)
	{
		if (name_.has_value() && name_.value().empty())
		{
			throw std::invalid_argument("object name cannot be empty");
		}

		if (class_type_.has_value() && class_type_.value().empty())
		{
			throw std::invalid_argument("object class type cannot be empty");
		}
	}


	bool object::operator==(const object& other) const noexcept
	{
		return
			name_ == other.name_
			&& class_type_ == other.class_type_
			&& position_ == other.position_;
	}


	bool object::has_name() const noexcept
	{
		return name_.has_value();
	}

	const object::string_type& object::name() const
	{
		return name_.value();
	}

	void object::set_name(string_type name) noexcept
	{
		name_ = move(name);
	}

	void object::remove_name() noexcept
	{
		name_.reset();
	}


	bool object::has_class_type() const noexcept
	{
		return class_type_.has_value();
	}

	const object::string_type& object::class_type() const
	{
		return class_type_.value();
	}

	void object::set_class_type(string_type class_type) noexcept
	{
		class_type_ = move(class_type);
	}

	void object::remove_class_type() noexcept
	{
		class_type_.reset();
	}


	object::position_type object::position() const noexcept
	{
		return position_;
	}

	void object::set_position(position_type position) noexcept
	{
		position_ = position;
	}

}
