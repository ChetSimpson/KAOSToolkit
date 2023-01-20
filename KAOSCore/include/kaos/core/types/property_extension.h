// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/exceptions.h>
#include <string>
#include <any>
#include <map>
#include <optional>


namespace hypertech::kaos::core::types
{

	/// @brief Property extension allowing derived classes to provide access
	/// to pre-defined and user-defined properties.
	class property_extension
	{
	public:

		/// @brief String type used for property names.
		using string_type = std::string;
		/// @brief Container type of individual properties.
		using property_type = std::any;
		/// @brief Map type for storing collections of properties.
		using property_map_type = std::map<string_type, property_type>;

		/// @brief Property definition allowing the type and name of
		/// property to be predefined.
		/// 
		/// @tparam Type_ The underlying type of the property.
		template<class Type_>
		struct property_def
		{
			/// @brief The value type of the property.
			using value_type = Type_;

			/// @brief Creates a property definition
			///
			/// @param name The name of the property being defined.
			explicit property_def(string_type name)
				: name(move(name))
			{}


			/// @brief The name of the property
			const string_type name;
		};


	public:

		/// @brief Create a property extension
		property_extension() noexcept = default;

		/// @brief Create a copy of a property extension
		/// 
		/// @param other The property extension to make a copy of
		property_extension(const property_extension& other) noexcept = default;

		/// @brief Defaulted destructor
		virtual ~property_extension() noexcept = default;

		/// @brief Checks if a property exists
		/// 
		/// @tparam Type_ The underlying type of the property.
		template<class Type_>
		bool has_property(const property_def<Type_>& def) const noexcept;

		/// @brief Adds a new property or replaces an existing one
		/// 
		/// Adds a new property or replaces an existing one with the value passed in
		/// \p value using copy semantics. The value passed must be an instance of
		/// \p Type_ or convertible to \p Type_.
		/// 
		/// @tparam Type_ The underlying type of the property.
		/// @tparam ValueType_ The type of property value to accept. This value
		/// must be convertible to \p Type_
		/// 
		/// @param def The property definition containing the name and type information of the property to set.
		/// @param value The value to save.
		/// 
		/// @return *this
		template<class Type_, class ValueType_ = Type_>
		requires std::is_convertible_v<ValueType_, Type_>
		property_extension& set_property(const property_def<Type_>& def, const ValueType_& value);

		/// @brief Adds a new property or replaces an existing one
		/// 
		/// Adds a new property or replaces an existing one with the value passed in
		/// \p value using move semantics. The value passed must be an instance of
		/// \p Type_ or convertible to \p Type_.
		/// 
		/// @tparam Type_ The underlying type of the property.
		/// @tparam ValueType_ The type of property value to accept. This value
		/// must be convertible to \p Type_
		/// 
		/// @param def The property definition containing the name and type information of the property to set.
		/// @param value The value to save.
		/// 
		/// @return *this
		template<class Type_, class ValueType_ = Type_>
		requires std::is_convertible_v<ValueType_, Type_>
		property_extension& set_property(const property_def<Type_>& def, ValueType_&& value);

		/// @brief Gets a property.
		/// 
		/// @tparam Type_ The expected type of the property being retrieved
		/// 
		/// @param def The property definition containing the name and type information
		/// of the property to set.
		/// 
		/// @return If the property exists and the type of the property matches the one specified
		/// in \p Type_ a `const` reference to the property value otherwise an exception is thrown.
		/// 
		/// @exception hypertech::kaos::core::exceptions::attribute_conversion_error If the type of
		/// the property does not match the type specified in the property definition \p def.
		template<class Type_>
		[[nodiscard]] const Type_& get_property(const property_def<Type_>& def) const;

		/// @brief Gets a property.
		/// 
		/// @tparam Type_ The expected type of the property being retrieved
		/// 
		/// @param def The property definition containing the name and type information
		/// of the property to set.
		/// 
		/// @return If the property exists and the type of the property matches the one specified
		/// in \p Type_ a `const` pointer to the property value otherwise an empty `std::optional`.
		template<class Type_>
		[[nodiscard]] std::optional<const Type_*> try_get_property(const property_def<Type_>& def) const;

		/// @brief Deletes a property
		/// 
		/// Deletes a property by name. If the property does not exist no action
		/// is taken.
		/// 
		/// @param name The name of the property to delete.
		/// 
		/// @return true if the property was deleted; false if the property does
		/// not exist.
		bool delete_property(const string_type& name) noexcept
		{
			return properties_.erase(name) != 0;
		}

	protected:

		/// @brief Create an property extension using move semantics
		/// 
		/// @param other The instance to initialize the new property extension with.
		property_extension(property_extension&& other) noexcept = default;


	private:

		property_map_type	properties_;
	};


	template<class Type_>
	bool property_extension::has_property(const property_def<Type_>& def) const noexcept
	{
		auto property_ptr = properties_.find(def.name);
		if (property_ptr == properties_.end())
		{
			return false;
		}

		return property_ptr->second.type() == typeid(Type_);
	}

	template<class Type_, class ValueType_>
	requires std::is_convertible_v<ValueType_, Type_>
		property_extension& property_extension::set_property(const property_def<Type_>& def, const ValueType_& value)
	{
		properties_[def.name] = Type_(value);

		return *this;
	}

	template<class Type_, class ValueType_>
	requires std::is_convertible_v<ValueType_, Type_>
		property_extension& property_extension::set_property(const property_def<Type_>& def, ValueType_&& value)
	{
		properties_[def.name] = std::move<>(Type_(value));

		return *this;
	}

	template<class Type_>
	inline const Type_& property_extension::get_property(const property_def<Type_>& def) const
	{
		try
		{
			auto property_ptr = properties_.find(def.name);
			if (property_ptr == properties_.end())
			{
				throw core::exceptions::attribute_not_found_error(def.name);
			}

			return any_cast<const Type_&>(property_ptr->second);
		}
		catch (std::bad_any_cast&)
		{
			throw core::exceptions::attribute_conversion_error(
				"bad any cast",
				def.name,
				typeid(Type_));
		}
	}


	template<class Type_>
	inline std::optional<const Type_*> property_extension::try_get_property(const property_def<Type_>& def) const
	{
		try
		{
			auto property_ptr = properties_.find(def.name);
			if (property_ptr == properties_.end())
			{
				return {};
			}

			return &any_cast<const Type_&>(property_ptr->second);
		}
		catch (std::bad_any_cast&)
		{
			return {};
		}
	}

}
