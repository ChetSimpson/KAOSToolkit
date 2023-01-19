// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/single_bitfield.h>


namespace hypertech::kaos::core::types
{
	
	/// @brief An optionally named value with an explicit size in bits occupying two
	/// distinct positions in the underlying data value.
	/// 
	/// @tparam ValueType_ The underlying value type containing the bitfield data.
	/// @tparam BitFieldType_ The bitfield type defining each portion of the
	/// split bitfield data.
	template<class ValueType_, class BitFieldType_ = single_bitfield<ValueType_>>
	class split_bitfield : public abstract_bitfield<ValueType_>
	{
	protected:

		/// @inheritdoc
		using value_type = typename BitFieldType_::value_type;

		/// @inheritdoc
		using size_type = typename BitFieldType_::size_type;

		/// @inheritdoc
		using string_type =  typename BitFieldType_::string_type;

		/// @inheritdoc
		using bitfield_type = BitFieldType_;


	public:

		/// @brief Creates a bitfield.
		/// 
		/// Creates an unnamed (anonymous) bitfield with a specific number of bits
		/// occupying two distinct portions of the underlying data value.
		/// 
		/// @param msp_size The size in bits of the bitfield occupying the most significant
		/// portion (top) of the underlying data value.
		/// @param msp_position The position of least significant bit of the bitfield
		/// occupying the most significant portion (top) of the underlying data value.
		/// @param lsp_size The size in bits of the bitfield occupying the least significant
		/// portion (bottom) of the underlying data value.
		/// @param lsp_position The position of least significant bit of the bitfield
		/// occupying the least significant portion (bottom) of the underlying data value.
		/// 
		/// @exception std::invalid_argument If the size of the most significant portion
		/// or least significant portion of the bitfield is 0.
		/// @exception std::overflow_error If either portion of the bitfield does not fit
		/// in the underlying data type or if the specified size and position of either
		/// portion of the bitfield causes it to exceed the bounds (size) of the underlying
		/// data type.
		split_bitfield(
			size_type msp_size,
			size_type msp_position,
			size_type lsp_size,
			size_type lsp_position)
			: split_bitfield({}, msp_size, msp_position, lsp_size, lsp_position, false)
		{}

		/// @brief Creates a bitfield.
		/// 
		/// Creates an unnamed (anonymous) bitfield with a specific number of bits
		/// occupying two distinct portions of the underlying data value.
		/// 
		/// @param name The name of the bitfield.
		/// @param msp_size The size in bits of the bitfield occupying the most significant
		/// portion (top) of the underlying data value.
		/// @param msp_position The position of least significant bit of the bitfield
		/// occupying the most significant portion (top) of the underlying data value.
		/// @param lsp_size The size in bits of the bitfield occupying the least significant
		/// portion (bottom) of the underlying data value.
		/// @param lsp_position The position of least significant bit of the bitfield
		/// occupying the least significant portion (bottom) of the underlying data value.
		/// 
		/// @exception std::invalid_argument If the \p name parameter is empty or set
		/// to "\<anonymous>".
		/// @exception std::invalid_argument If the size of the most significant portion
		/// or least significant portion of the bitfield is 0.
		/// @exception std::overflow_error If either portion of the bitfield does not fit
		/// in the underlying data type or if the specified size and position of either
		/// portion of the bitfield causes it to exceed the bounds (size) of the underlying
		/// data type.
		split_bitfield(
			string_type name,
			size_type msp_size,
			size_type msp_position,
			size_type lsp_size,
			size_type lsp_position)
			: split_bitfield(move(name), msp_size, msp_position, lsp_size, lsp_position, true)
		{}


	private:

		/// @brief Creates a bitfield.
		/// 
		/// Creates an unnamed (anonymous) bitfield with a specific number of bits
		/// occupying two distinct portions of the underlying data value.
		/// 
		/// @param name An optional name of the bitfield.
		/// @param msp_size The size in bits of the bitfield occupying the most significant
		/// portion (top) of the underlying data value.
		/// @param msp_position The position of least significant bit of the bitfield
		/// occupying the most significant portion (top) of the underlying data value.
		/// @param lsp_position The size in bits of the bitfield occupying the least significant
		/// portion (bottom) of the underlying data value.
		/// @param lsp_position The position of least significant bit of the bitfield
		/// occupying the least significant portion (bottom) of the underlying data value.
		/// @param name_is_present Specifies if the \p name paramter should be checked
		/// for the presence of a name string.
		/// 
		/// @exception std::invalid_argument If the \p name parameter is empty or set
		/// to "\<anonymous>" and \p name_is_present is true.
		/// @exception std::invalid_argument If the size of the most significant portion
		/// or least significant portion of the bitfield is 0.
		/// @exception std::overflow_error If either portion of the bitfield does not fit
		/// in the underlying data type or if the specified size and position of either
		/// portion of the bitfield causes it to exceed the bounds (size) of the underlying
		/// data type.
		split_bitfield(
			string_type name,
			size_type msp_size,
			size_type msp_position,
			size_type lsp_size,
			size_type lsp_position,
			bool name_is_present)
			:
			name_(move(name)),
			split_size_(lsp_size),
			ls_mask_(make_mask(lsp_size)),
			max_value_(make_mask(lsp_size + msp_size)),
			ms_bitfield_(msp_size, msp_position),
			ls_bitfield_(lsp_size, lsp_position)
		{
			if (name_is_present)
			{
				if (name_.empty())
				{
					throw std::invalid_argument("Split bitfield name cannot be empty");
				}

				if (name_ == abstract_bitfield<value_type>::anonymous_name())
				{
					throw std::invalid_argument("Split bitfield cannot be explicitly named `" + abstract_bitfield<value_type>::anonymous_name() + "`");
				}
			}
		}


	public:


		/// @brief Compares two bitfield definitions for equality.
		/// 
		/// @param other The bitfield on the right size of the comparison.
		/// 
		/// @return true if the bitfields are the same; false if they are not.
		bool operator==(const split_bitfield& other) const noexcept
		{
			return name_ == other.name_
				&& split_size_ == other.split_size_
				&& ls_mask_ == other.ls_mask_
				&& max_value_ == other.max_value_
				&& ms_bitfield_ == other.ms_bitfield_
				&& ls_bitfield_ == other.ls_bitfield_;
		}

		/// @brief Compares two bitfield definitions for inequality.
		/// 
		/// @param other The bitfield on the right size of the comparison.
		/// 
		/// @return true if the bitfields are not the same; false if they are.
		bool operator!=(const split_bitfield& other) const noexcept
		{
			return name_ != other.name_
				|| split_size_ != other.split_size_
				|| ls_mask_ != other.ls_mask_
				|| max_value_ != other.max_value_
				|| ms_bitfield_ != other.ms_bitfield_
				|| ls_bitfield_ != other.ls_bitfield_;
		}


		/// @inheritdoc
		const string_type& name() const noexcept override
		{
			return name_.empty() ? abstract_bitfield<value_type>::anonymous_name() : name_;
		}

		/// @inheritdoc
		size_type size() const noexcept override
		{
			return ms_bitfield_.size() + ls_bitfield_.size();
		}

		/// @inheritdoc
		value_type max_value() const noexcept override
		{
			return max_value_;
		}

		/// @inheritdoc
		value_type mask() const noexcept override
		{
			return ms_bitfield_.mask() | ls_bitfield_.mask();
		}


		/// @inheritdoc
		value_type get_from(value_type value) const noexcept override
		{
			return (ms_bitfield_.get_from(value) << split_size_) | ls_bitfield_.get_from(value);
		}

		/// @inheritdoc
		value_type set_in(value_type base_value, value_type field_value) const override
		{
			if(field_value > max_value_)
			{
				throw std::overflow_error("value is too large to fit in the allocated split bitfields");
			}

			base_value = ls_bitfield_.set_in(base_value, field_value & ls_mask_);
			base_value = ms_bitfield_.set_in(base_value, field_value >> split_size_);

			return base_value;
		}


	protected:

		/// @brief Createa a bitmask
		/// 
		/// Creates a bitmask with the least significant bit starting at bit 0.
		/// 
		/// @param digits The number of bits to mask.
		/// 
		/// @return The bitmask.
		static value_type make_mask(size_type digits) noexcept
		{
			const auto unused_digits(std::numeric_limits<value_type>::digits - digits);
			
			return static_cast<value_type>(std::numeric_limits<value_type>::max() >> unused_digits);
		}


	private:

		const string_type name_;
		const size_t split_size_;
		const value_type ls_mask_;
		const value_type max_value_;
		const bitfield_type	ms_bitfield_;
		const bitfield_type	ls_bitfield_;
	};

}
