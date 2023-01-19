// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/abstract_bitfield.h>
#include <optional>


namespace hypertech::kaos::core::types::unittests::mocks
{

	template<class ValueType_>
	class mocked_bitfield : public abstract_bitfield<ValueType_>
	{
	public:

		using value_type = typename abstract_bitfield<ValueType_>::value_type;
		using size_type = typename abstract_bitfield<ValueType_>::size_type;
		using string_type =  typename abstract_bitfield<ValueType_>::string_type;


	public:

		mocked_bitfield(
			size_type field_size,
			size_type field_position,
			size_type max_value,
			value_type mask)
			:
			size_(field_size),
			field_position_(field_position),
			max_value_(max_value),
			fieldBitmask_(mask)
		{}

		mocked_bitfield(
			string_type name,
			size_type field_size,
			size_type field_position,
			size_type max_value,
			value_type mask)
			:
			name_(move(name)),
			size_(field_size),
			field_position_(field_position),
			max_value_(max_value),
			fieldBitmask_(mask)
		{}

		const string_type& name() const noexcept override
		{
			return name_.empty() ? abstract_bitfield<value_type>::anonymous_name() : name_;
		}

		size_type size() const noexcept override
		{
			return size_;
		}

		value_type max_value() const noexcept override
		{
			return max_value_;
		}

		value_type mask() const noexcept override
		{
			return fieldBitmask_;
		}

		value_type get_from(value_type value) const noexcept override
		{
			if (get_from_value_.has_value())
			{
				return *get_from_value_;
			}

			return (value & fieldBitmask_) >> field_position_;
		}

		value_type set_in(value_type base_value, value_type field_value) const override
		{
			if(field_value > max_value_)
			{
				throw std::overflow_error("value is too large to fit in the allocated bitfield");
			}

			return (base_value & ~fieldBitmask_) | ((field_value << field_position_) & fieldBitmask_);
		}


	public:

		string_type name_;
		size_type size_;
		value_type max_value_;
		size_type field_position_;
		value_type fieldBitmask_;
		std::optional<value_type> get_from_value_;
	};

}
