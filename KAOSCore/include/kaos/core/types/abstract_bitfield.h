// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <limits>
#include <stdexcept>


namespace hypertech::kaos::core::types
{

	/// @brief An optionally named value with an explicit size and position in bits.
	/// 
	/// This class represents a variable sized bitfield value stored in an unsigned integrat type.
	/// It provides access to set and retrieve the value along with attributes about the
	/// bitfields configuration including name, size, and mask.
	/// 
	/// @tparam ValueType_ The underlying value type containing the bitfield data.
	template<class ValueType_>
	class abstract_bitfield
	{
		static_assert(std::is_unsigned<ValueType_>::value, "ValueType_ passed to abstract_bitfield<> must be of unsigned type");

	public:

		/// @brief Type the bitfield is stored in.
		using value_type = ValueType_;

		/// @brief Type used to return the size of bitfield properties.
		using size_type = size_t;

		/// @brief String type
		using string_type = std::string;


	public:

		virtual ~abstract_bitfield() = default;

		/// @brief Returns the name of the bitfield.
		/// 
		/// @return The name of the bitfield or "<anonymous>" if no name has been assigned.
		virtual const string_type& name() const noexcept = 0;

		/// @brief REturns the size of the bitfield.
		/// 
		/// @return The size in bits (digits) of the bitfield.
		virtual size_type size() const noexcept = 0;

		/// @brief Returns the maximum value the bitfield can hold.
		/// 
		/// @return The maximum value the bitfield can hold.
		virtual value_type max_value() const noexcept = 0;

		/// @brief Returns the bitfield mask.
		/// 
		/// @return The mask indicating which bits in a value the bitfield occupies.
		virtual value_type mask() const noexcept = 0;

		/// @brief Retrieves the bitfield value.
		/// 
		/// @param value The value containing the bitfield data.
		/// 
		/// @return A zero based value of the bitfield.
		virtual value_type get_from(value_type value) const noexcept = 0;

		/// @brief Sets a value in the bitfield.
		/// 
		/// @param base_value The zero based value to store the bitfield in.
		/// @param field_value The value to store.
		/// 
		/// @return The new value of comprised of the original base_value with the value of
		/// field_value stored in it.
		/// 
		/// @exception std::overflow_error If the value specified in \p field_value is
		/// too large to fit in the bitfield.
		virtual value_type set_in(value_type base_value, value_type field_value) const = 0;


	protected:

		/// @brief Returns the name of an anonymous bitfield.
		/// @return The name used to indicate an anonymous bitfield.
		static const string_type& anonymous_name()
		{
			static const string_type anonymous("<anonymous>");

			return anonymous;
		}
	};

}
