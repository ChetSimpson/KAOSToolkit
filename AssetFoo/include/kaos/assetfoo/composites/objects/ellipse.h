// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/composites/object.h>
#include <kaos/core/types/dimension2.h>

// FIXME: These should maybe be in a different namespace like documents::???::objects
// deferred until after initial tiled support is complete.
namespace hypertech::kaos::assetfoo::composites::objects
{

	/// @brief An ellipse object with a position and size
	class ellipse : public object
	{
	public:

		/// @brief The type represneting the dimensions (size) of the ellipse
		using dimensions_type = core::types::dimension2<float>;


	public:

		/// @brief Create an ellipse with default values for position and size.
		ellipse() = default;

		/// @brief Creates an ellipse
		/// 
		/// Creates an ellipse with position and size with an optional name and
		/// class type.
		/// 
		/// @param name An optional name to assign to the ellipse
		/// @param class_type An optional class type to assign to the ellipse
		/// @param position The position of the ellipse
		/// @param dimensions The dimensions (size) of the ellipse
		/// 
		/// @exception std::invalid_argument If \p name contains an empty string
		/// @exception std::invalid_argument If \p class_type contains an empty string
		ellipse(
			std::optional<string_type> name,
			std::optional<string_type> class_type,
			position_type position,
			dimensions_type dimensions);
		

		[[nodiscard]] bool operator==(const object& other) const noexcept override;

		/// @brief Retrieves the dimensions of the ellipse
		/// 
		/// @return The dimensions of the ellipse
		[[nodiscard]] virtual dimensions_type dimensions() const noexcept;

		/// @brief Set the dimensions of the ellipse
		/// 
		/// @param dimensions The new dimensions of the ellipse
		virtual void set_dimensions(dimensions_type dimensions) noexcept;


	private:

		dimensions_type dimensions_;
	};
}
