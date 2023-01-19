// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/abstract_bitfield.h>


namespace hypertech::kaos::core::types
{

	/// @brief An optionally named value with an explicit size and position in bits.
	/// 
	/// @tparam ValueType_ The underlying value type containing the bitfield data.
	template<class ValueType_>
	class single_bitfield : public abstract_bitfield<ValueType_>
	{
	public:

		/// @inheritdoc
		using value_type = typename abstract_bitfield<ValueType_>::value_type;

		/// @inheritdoc
		using size_type = typename abstract_bitfield<ValueType_>::size_type;

		/// @inheritdoc
		using string_type =  typename abstract_bitfield<ValueType_>::string_type;


	public:

		/// @brief Creates a bitfield.
		/// 
		/// Creates an unnamed (anonymous) bitfield with a specific number of bits
		/// at a specific position.
		/// 
		/// @param field_size The size in bits of the bitfield.
		/// @param field_position The position of least significant bit of the bitfield.
		/// 
		/// @exception std::invalid_argument If the size of the bitfield is 0.
		/// @exception std::overflow_error If the bitfield does not fit in the underlying
		/// data type or if the specified size and position causes the bitfield to exceed
		/// the bounds (size) of the underlying data type.
		single_bitfield(size_type field_size, size_type field_position)
			: single_bitfield({}, field_size, field_position, false)
		{}


		/// @brief Creates a named bitfield.
		/// 
		/// Creates a named bitfield with a specific number of bits at a specific position.
		/// 
		/// @param name The name of the bitfield.
		/// @param field_size The size in bits of the bitfield.
		/// @param field_position The position of least significant bit of the bitfield.
		/// 
		/// @exception std::invalid_argument If the \p name parameter is empty or set
		/// to "\<anonymous>".
		/// @exception std::invalid_argument If the size of the bitfield is 0.
		/// @exception std::overflow_error If the bitfield does not fit in the underlying
		/// data type or if the specified size and position causes the bitfield to exceed
		/// the bounds (size) of the underlying data type.
		single_bitfield(string_type name, size_type field_size, size_type field_position)
			: single_bitfield(move(name), field_size, field_position, true)
		{}


	private:

		/// @brief Creates an optionally named bitfield.
		/// 
		/// Creates an optionally named bitfield with a specific number of bits at a
		/// specific position.
		/// 
		/// @param name The name of the bitfield.
		/// @param field_size The size in bits of the bitfield.
		/// @param field_position The position of least significant bit of the bitfield.
		/// @param name_is_present Specifies if the \p name paramter is present.
		/// 
		/// @exception std::invalid_argument If the \p name parameter is empty or set
		/// to "\<anonymous>" and \p name_is_present is true.
		/// @exception std::invalid_argument If the size of the bitfield is 0.
		/// @exception std::overflow_error If the bitfield does not fit in the underlying
		/// data type or if the specified size and position causes the bitfield to exceed
		/// the bounds (size) of the underlying data type.
		single_bitfield(string_type name, size_type field_size, size_type field_position, bool name_is_present)
			:
			name_(move(name)),
			size_(field_size),
			field_position_(field_position),
			max_value_(make_mask(field_size, 0)),
			field_bitmask_(make_mask(field_size, field_position))
		{
			if (name_is_present)
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

			if (size_ == 0)
			{
				throw std::invalid_argument("Field size passed to single_bitfield cannot be 0");
			}

			const auto value_type_digits(std::numeric_limits<value_type>::digits);
			if (size_ > value_type_digits)
			{
				throw std::overflow_error("Field size passed to single_bitfield is too large");
			}

			if (field_position_ >= value_type_digits)
			{
				throw std::overflow_error("Field position passed to single_bitfield exceeds bounds of storage type");
			}

			if ((field_position_ + size_) > value_type_digits)
			{
				throw std::overflow_error("Field size passed to single_bitfield exceeds value type based on position");
			}
		}


	public:


		/// @brief Compares two bitfield definitions for equality.
		/// 
		/// @param other The bitfield on the right size of the comparison.
		/// 
		/// @return true if the bitfields are the same; false if they are not.
		bool operator==(const single_bitfield& other) const noexcept
		{
			return name_ == other.name_
				&& size_ == other.size_
				&& field_position_ == other.field_position_
				&& max_value_ == other.max_value_
				&& field_bitmask_ == other.field_bitmask_;
		}

		/// @brief Compares two bitfield definitions for inequality.
		/// 
		/// @param other The bitfield on the right size of the comparison.
		/// 
		/// @return true if the bitfields are not the same; false if they are.
		bool operator!=(const single_bitfield& other) const noexcept
		{
			return name_ != other.name_
				|| size_ != other.size_
				|| field_position_ != other.field_position_
				|| max_value_ != other.max_value_
				|| field_bitmask_ != other.field_bitmask_;
		}


		/// @inheritdoc
		const string_type& name() const noexcept override
		{
			return name_.empty() ? abstract_bitfield<value_type>::anonymous_name() : name_;
		}

		/// @inheritdoc
		size_type size() const noexcept override
		{
			return size_;
		}

		/// @inheritdoc
		value_type max_value() const noexcept override
		{
			return max_value_;
		}

		/// @inheritdoc
		value_type mask() const noexcept override
		{
			return field_bitmask_;
		}
		

		/// @inheritdoc
		value_type get_from(value_type value) const noexcept override
		{
			return (value & field_bitmask_) >> field_position_;
		}


		/// @inheritdoc
		value_type set_in(value_type base_value, value_type field_value) const override
		{
			if(field_value > max_value_)
			{
				throw std::overflow_error("value is too large to fit in the allocated bitfield");
			}

			return (base_value & ~field_bitmask_) | ((field_value << field_position_) & field_bitmask_);
		}


	protected:

		/// @brief Creates a mask value representing all bits used by the bitfield.
		/// 
		/// @param field_size The size in bits of the bitfield.
		/// @param field_position The position of least significant bit of the bitfield.
		/// 
		/// @return The bitfield mask.
		static value_type make_mask(size_type field_size, size_type field_position) noexcept
		{
			const auto unused_digits(std::numeric_limits<value_type>::digits - field_size);

			return static_cast<value_type>((std::numeric_limits<value_type>::max() >> unused_digits) << field_position);
		}


	private:

		const string_type name_;
		const size_type size_;
		const size_type field_position_;
		const value_type max_value_;
		const value_type field_bitmask_;
	};

}
