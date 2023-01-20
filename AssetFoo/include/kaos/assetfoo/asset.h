// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/memory.h>
#include <kaos/core/exceptions.h>
#include <memory>
#include <string>
#include <any>
#include <map>

namespace hypertech::kaos::assetfoo
{

	/// @brief Base class for all asset types
	class asset
	{
	public:

		using string_type = std::string;
		using property_type = std::any;
		using property_map_type = std::map<string_type, property_type>;


	public:

		/// @brief Create an asset
		asset() noexcept = default;

		/// @brief Create a copy of an asset
		/// 
		/// @param other The asset to make a copy of
		asset(const asset& other) noexcept = default;

		/// @brief Create an asset using move semantics
		/// 
		/// @param other The instance to initialize the new asset with.
		asset(asset&& other) noexcept = default;

		/// @brief Defaulted destructor
		virtual ~asset() noexcept = default;





		bool has_property(const string_type& name) const;

		void delete_property(const string_type & name);

		asset& set_property(const string_type& name, const property_type& value);

		asset& set_property(const string_type& name, property_type&& value);

		template<class Type_>
		asset& set_property_as(const string_type& name, const Type_& value);

		template<class Type_>
		asset& set_property_as(const string_type& name, Type_&& value);

		[[nodiscard]] const property_type& get_property(const string_type & name) const;

		template<class Type_>
		[[nodiscard]] const Type_& get_property_as(const string_type & name) const;

		const property_type& try_get_property(const string_type & name) const;


	private:

		property_map_type	properties_;
	};


	template<class Type_>
	asset& asset::set_property_as(const string_type& name, const Type_& value)
	{
		return set_property(name, value);
	}

	template<class Type_>
	asset& asset::set_property_as(const string_type& name, Type_&& value)
	{
		return set_property(name, std::move(value));
	}


	template<class Type_>
	inline const Type_& asset::get_property_as(const string_type& name) const
	{
		try
		{
			return any_cast<const Type_&>(get_property(name));
		}
		catch (std::bad_any_cast&)
		{
			throw core::exceptions::attribute_conversion_error(
				"bad any cast",
				name,
				typeid(Type_));
		}
	}


	//template<class Type_>
	//inline std::optional<std::reference_wrapper<const Type_>> image::try_get_property_as(const string_type& name) const
	//{
	//	try
	//	{
	//		auto property(try_get_property(name));
	//		if (!property.has_value())
	//		{
	//			return {};
	//		}

	//		return any_cast<const Type_&>(property.value().get());
	//	}
	//	catch (std::bad_any_cast&)
	//	{
	//		throw core::exceptions::attribute_conversion_error(
	//			"bad any cast",
	//			name,
	//			typeid(Type_));
	//	}
	//}

	//template<class Type_>
	//requires std::is_integral_v<Type_>
	//	|| std::is_floating_point_v<Type_>
	//	|| std::is_pointer_v<Type_>
	//	|| std::negation_v<typename std::is_reference<Type_>>
	//inline std::optional<Type_> image::try_get_property_as(const string_type& name) const
	//{
	//	try
	//	{
	//		auto property(try_get_property(name));
	//		if (!property.has_value())
	//		{
	//			return {};
	//		}

	//		return any_cast<const Type_&>(property.value().get());
	//	}
	//	catch (std::bad_any_cast&)
	//	{
	//		throw core::exceptions::attribute_conversion_error(
	//			"bad any cast",
	//			name,
	//			typeid(Type_));
	//	}
	//}



	/// @brief Creates a new instance of std::unique_ptr whose stored pointer is obtained
	/// from \p from's stored pointer using a cast expression.
	/// 
	/// Creates a new instance of std::unique_ptr whose stored pointer is obtained from
	/// \p from's stored pointer using a cast expression.
	/// 
	///	If \p from is empty, so is the new unique_ptr (but its stored pointer is not
	///	necessarily null). Otherwise, the new unique_ptr will share ownership with
	/// the initial value of \p from, except that it is empty if the dynamic_cast
	/// performed by dynamic_pointer_cast returns a null pointer.
	/// 
	/// @tparam ToType_ Type to convert to
	/// @tparam Deleter_ Type of deleter function
	/// 
	/// @param from Instance to convert
	/// 
	/// @return Returns a std::unique pointer containing the address of the converted 
	template<class ToType_, class Deleter_>
	std::unique_ptr<ToType_, Deleter_> dynamic_pointer_cast(std::unique_ptr<asset, Deleter_>&& from) noexcept
	{
		return core::dynamic_pointer_cast<ToType_, asset, Deleter_>(move(from));
	}

}
