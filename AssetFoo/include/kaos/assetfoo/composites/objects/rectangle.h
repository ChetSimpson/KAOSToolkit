// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/composites/object.h>
#include <kaos/core/types/dimension2.h>


namespace hypertech::kaos::assetfoo::composites::objects
{

	/// @brief A rectangle object with a position and size
	class rectangle : public object
	{
	public:

		/// @brief The type represneting the dimensions (size) of the rectangle
		using dimensions_type = core::types::dimension2<float>;


	public:

		/// @brief Create a rectangle with default values for position and size.
		rectangle() = default;

		/// @brief Creates a rectangle
		/// 
		/// Creates a rectangle with position and size with an optional name and
		/// class type.
		/// 
		/// @param name An optional name to assign to the rectangle
		/// @param class_type An optional class type to assign to the rectangle
		/// @param position The position of the rectangle
		/// @param dimensions The dimensions (size) of the rectangle
		/// 
		/// @exception std::invalid_argument If \p name contains an empty string
		/// @exception std::invalid_argument If \p class_type contains an empty string
		rectangle(
			std::optional<string_type> name,
			std::optional<string_type> class_type,
			position_type position,
			dimensions_type dimensions);


		[[nodiscard]] bool operator==(const object& other) const noexcept override;

		/// @brief Retrieves the dimensions of the rectangle
		/// 
		/// @return The dimensions of the rectangle
		[[nodiscard]] virtual dimensions_type dimensions() const noexcept;

		/// @brief Set the dimensions of the rectangle
		/// 
		/// @param dimensions The new dimensions of the rectangle
		virtual void set_dimensions(dimensions_type dimensions) noexcept;


	private:

		dimensions_type dimensions_;
	};
}
