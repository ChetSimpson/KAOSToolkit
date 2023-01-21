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

	/// @brief Attribute extension allowing derived classes to provide access
	/// to pre-defined and user-defined attributes.
	class attribute_extension
	{
	public:

		/// @brief String type used for attribute names.
		using string_type = std::string;
		/// @brief Container type of individual attributes.
		using attribute_type = std::any;
		/// @brief Map type for storing collections of attributes.
		using attribute_map_type = std::map<string_type, attribute_type>;

		/// @brief Attribute definition allowing the type and name of
		/// attribute to be predefined.
		/// 
		/// @tparam Type_ The underlying type of the attribute.
		template<class Type_>
		struct attribute_definition
		{
			/// @brief The value type of the attribute.
			using value_type = Type_;

			/// @brief Creates a attribute definition
			///
			/// @param name The name of the attribute being defined.
			explicit attribute_definition(string_type name)
				: name(move(name))
			{}


			/// @brief The name of the attribute
			const string_type name;
		};


	public:

		/// @brief Create a attribute extension
		attribute_extension() noexcept = default;

		/// @brief Create a copy of a attribute extension
		/// 
		/// @param other The attribute extension to make a copy of
		attribute_extension(const attribute_extension& other) noexcept = default;

		/// @brief Defaulted destructor
		virtual ~attribute_extension() noexcept = default;

		/// @brief Checks if a attribute exists
		/// 
		/// @tparam Type_ The underlying type of the attribute.
		template<class Type_>
		bool has_attribute(const attribute_definition<Type_>& def) const noexcept;

		/// @brief Adds a new attribute or replaces an existing one
		/// 
		/// Adds a new attribute or replaces an existing one with the value passed in
		/// \p value using copy semantics. The value passed must be an instance of
		/// \p Type_ or convertible to \p Type_.
		/// 
		/// @tparam Type_ The underlying type of the attribute.
		/// @tparam ValueType_ The type of attribute value to accept. This value
		/// must be convertible to \p Type_
		/// 
		/// @param def The attribute definition containing the name and type information of the attribute to set.
		/// @param value The value to save.
		/// 
		/// @return *this
		template<class Type_, class ValueType_ = Type_>
		requires std::is_convertible_v<ValueType_, Type_>
			attribute_extension& set_attribute(const attribute_definition<Type_>& def, const ValueType_& value);

		/// @brief Adds a new attribute or replaces an existing one
		/// 
		/// Adds a new attribute or replaces an existing one with the value passed in
		/// \p value using move semantics. The value passed must be an instance of
		/// \p Type_ or convertible to \p Type_.
		/// 
		/// @tparam Type_ The underlying type of the attribute.
		/// @tparam ValueType_ The type of attribute value to accept. This value
		/// must be convertible to \p Type_
		/// 
		/// @param def The attribute definition containing the name and type information of the attribute to set.
		/// @param value The value to save.
		/// 
		/// @return *this
		template<class Type_, class ValueType_ = Type_>
		requires std::is_convertible_v<ValueType_, Type_>
			attribute_extension& set_attribute(const attribute_definition<Type_>& def, ValueType_&& value);

		/// @brief Gets a attribute.
		/// 
		/// @tparam Type_ The expected type of the attribute being retrieved
		/// 
		/// @param def The attribute definition containing the name and type information
		/// of the attribute to set.
		/// 
		/// @return If the attribute exists and the type of the attribute matches the one specified
		/// in \p Type_ a `const` reference to the attribute value otherwise an exception is thrown.
		/// 
		/// @exception hypertech::kaos::core::exceptions::attribute_conversion_error If the type of
		/// the attribute does not match the type specified in the attribute definition \p def.
		template<class Type_>
		[[nodiscard]] const Type_& get_attribute(const attribute_definition<Type_>& def) const;

		/// @brief Gets a attribute.
		/// 
		/// @tparam Type_ The expected type of the attribute being retrieved
		/// 
		/// @param def The attribute definition containing the name and type information
		/// of the attribute to set.
		/// 
		/// @return If the attribute exists and the type of the attribute matches the one specified
		/// in \p Type_ a `const` pointer to the attribute value otherwise an empty `std::optional`.
		template<class Type_>
		[[nodiscard]] std::optional<const Type_*> try_get_attribute(const attribute_definition<Type_>& def) const;

		/// @brief Deletes a attribute
		/// 
		/// Deletes a attribute by name. If the attribute does not exist no action
		/// is taken.
		/// 
		/// @param name The name of the attribute to delete.
		/// 
		/// @return true if the attribute was deleted; false if the attribute does
		/// not exist.
		bool delete_attribute(const string_type& name) noexcept
		{
			return attributes_.erase(name) != 0;
		}

	protected:

		/// @brief Create an attribute extension using move semantics
		/// 
		/// @param other The instance to initialize the new attribute extension with.
		attribute_extension(attribute_extension&& other) noexcept = default;


	private:

		attribute_map_type	attributes_;
	};


	template<class Type_>
	bool attribute_extension::has_attribute(const attribute_definition<Type_>& def) const noexcept
	{
		auto attribute_ptr = attributes_.find(def.name);
		if (attribute_ptr == attributes_.end())
		{
			return false;
		}

		return attribute_ptr->second.type() == typeid(Type_);
	}

	template<class Type_, class ValueType_>
	requires std::is_convertible_v<ValueType_, Type_>
		attribute_extension& attribute_extension::set_attribute(
			const attribute_definition<Type_>& def,
			const ValueType_& value)
	{
		attributes_[def.name] = Type_(value);

		return *this;
	}

	template<class Type_, class ValueType_>
	requires std::is_convertible_v<ValueType_, Type_>
		attribute_extension& attribute_extension::set_attribute(
			const attribute_definition<Type_>& def,
			ValueType_&& value)
	{
		attributes_[def.name] = std::move<>(Type_(value));

		return *this;
	}

	template<class Type_>
	inline const Type_& attribute_extension::get_attribute(const attribute_definition<Type_>& def) const
	{
		try
		{
			auto attribute_ptr = attributes_.find(def.name);
			if (attribute_ptr == attributes_.end())
			{
				throw core::exceptions::attribute_not_found_error(def.name);
			}

			return any_cast<const Type_&>(attribute_ptr->second);
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
	inline std::optional<const Type_*> attribute_extension::try_get_attribute(const attribute_definition<Type_>& def) const
	{
		try
		{
			auto attribute_ptr = attributes_.find(def.name);
			if (attribute_ptr == attributes_.end())
			{
				return {};
			}

			return &any_cast<const Type_&>(attribute_ptr->second);
		}
		catch (std::bad_any_cast&)
		{
			return {};
		}
	}

}
