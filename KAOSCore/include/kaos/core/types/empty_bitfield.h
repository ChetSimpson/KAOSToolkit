// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/abstract_bitfield.h>


namespace hypertech { namespace kaos { namespace core { namespace types
{

	/// @brief An optionally named empty bitfield with a size of 0 bits.
	/// 
	/// @tparam ValueType_ The underlying value type containing the bitfield data.
	template<class ValueType_>
	class empty_bitfield final : public abstract_bitfield<ValueType_>
	{
	public:

		/// @inheritdoc
		using value_type = typename abstract_bitfield<ValueType_>::value_type;

		/// @inheritdoc
		using size_type = typename abstract_bitfield<ValueType_>::size_type;

		/// @inheritdoc
		using string_type =  typename abstract_bitfield<ValueType_>::string_type;


	public:

		/// @brief Creates an empty bitfield.
		/// 
		/// Creates an unnamed (anonymous) bitfield with a size of 0 bits.
		/// 
		/// the bounds (size) of the underlying data type.
		empty_bitfield() = default;


		/// @brief Creates an empty named bitfield.
		/// 
		/// Creates a named empty bitfield with a size of 0 bits.
		/// 
		/// @param name The name of the bitfield.
		/// 
		/// @exception std::invalid_argument If the \p name parameter is empty or set
		/// to "\<anonymous>".
		explicit empty_bitfield(string_type name)
			: name_(move(name))
		{
			if (name_.empty())
			{
				throw std::invalid_argument("Bitfield name cannot be empty");
			}

			if (name_ == abstract_bitfield<value_type>::anonymous_name())
			{
				throw std::invalid_argument("Bitfield cannot be explicitly named `" + abstract_bitfield<value_type>::anonymous_name() + "`");
			}
		}


	public:


		/// @brief Compares two bitfield definitions for equality.
		/// 
		/// @param other The bitfield on the right size of the comparison.
		/// 
		/// @return true if the bitfields are the same; false if they are not.
		bool operator==(const empty_bitfield& other) const noexcept
		{
			return name_ == other.name_;
		}

		/// @brief Compares two bitfield definitions for inequality.
		/// 
		/// @param other The bitfield on the right size of the comparison.
		/// 
		/// @return true if the bitfields are not the same; false if they are.
		bool operator!=(const empty_bitfield& other) const noexcept
		{
			return name_ != other.name_;
		}


		/// @inheritdoc
		const string_type& name() const noexcept override
		{
			return name_.empty() ? abstract_bitfield<value_type>::anonymous_name() : name_;
		}

		/// @inheritdoc
		size_type size() const noexcept override
		{
			return 0;
		}

		/// @inheritdoc
		value_type max_value() const noexcept override
		{
			return 0;
		}

		/// @inheritdoc
		value_type mask() const noexcept override
		{
			return 0;
		}


		/// @inheritdoc
		value_type get_from(value_type /*value*/) const noexcept override
		{
			return 0;
		}

		/// @inheritdoc
		value_type set_in(value_type base_value, value_type field_value) const override
		{
			if(field_value > 0)
			{
				throw std::overflow_error("value is too large to fit in the null bitfield");
			}

			return base_value;
		}

	private:

		const string_type name_;
	};

}}}}
