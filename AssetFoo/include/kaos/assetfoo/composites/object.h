// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/vector2.h>
#include <optional>


namespace hypertech::kaos::assetfoo::composites
{

	/// @brief Base class for objects that can be attached to a composite container
	class object
	{
	public:

		/// @brief String type
		using string_type = std::string;

		/// @brief Position type
		using position_type = core::types::vector2<float>;


	public:

		/// @brief Creates a default initialized object
		object() = default;

		/// @brief Creates an object
		/// 
		/// @param name An optional name to assign to the object
		/// @param class_type An optional class type to assign to the object
		/// @param position The position of the object
		/// 
		/// @exception std::invalid_argument If \p name contains an empty string
		/// @exception std::invalid_argument If \p class_type contains an empty string
		object(
			std::optional<string_type> name,
			std::optional<string_type> class_type,
			position_type position);

		/// @brief Initialize an object using copy semantics
		/// 
		/// @param other The object to copy.
		object(const object& other) = default;

		/// @brief Initialize an object using move semantics
		/// 
		/// @param other The object to move
		object(object&& other) = default;

		/// @brief Destroy the object and release its resources
		virtual ~object() = default;


		/// @brief Compares with another objects
		/// @param other The object to compare against
		/// @return `true` if the objects are equal; `false` if not.
		[[nodiscard]] virtual bool operator==(const object& other) const noexcept;


		/// @brief Determines if the name of the object is set
		/// @return `true` if the name is set; `false` if it is not.
		[[nodiscard]] virtual bool has_name() const noexcept;
		
		/// @brief Retrieves the name of the object
		/// 
		/// Retrieves the name of the object. If the name is not set an exception
		/// is thrown.
		/// 
		/// @return A reference to the name of the object
		/// 
		/// @exception std::bad_optional_access If the name of the object has not been set.
		[[nodiscard]] virtual const string_type& name() const;

		/// @brief Sets the name of the object
		/// 
		/// @param name The new name of the object.
		virtual void set_name(string_type name) noexcept;

		/// @brief Removes the objects name
		virtual void remove_name() noexcept;


		/// @brief Determines if the class type of the object has been set
		/// 
		/// @return `true` if the class type is set; `false` if it is not.
		[[nodiscard]] virtual bool has_class_type() const noexcept;

		/// @brief Retrieves the class type of the object
		/// 
		/// Retrieves the class type of the object. If the name is not set an exception
		/// is thrown.
		/// 
		/// @return A reference to the class type of the object
		/// 
		/// @exception std::bad_optional_access If the class type of the object has not been set.
		[[nodiscard]] virtual const string_type& class_type() const;

		/// @brief Sets the class type of the object
		/// 
		/// @param class_type The new class type of the object.
		virtual void set_class_type(string_type class_type) noexcept;

		/// @brief Removes the objects class type
		virtual void remove_class_type() noexcept;


		/// @brief Retrieves the position of the object
		/// 
		/// @return The position of the object
		[[nodiscard]] virtual position_type position() const noexcept;

		/// @brief Set the position of the object
		/// 
		/// @param position The new position of the object
		virtual void set_position(position_type position) noexcept;


	private:

		std::optional<string_type> name_;
		std::optional<string_type> class_type_;
		position_type position_;
	};

	inline object&& move(object& value)
	{
		return static_cast<object&&>(value);
	}

}
