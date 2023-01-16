// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/rgba_color.h>
#include <kaos/core/types/abstract_bitfield.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors
{

	/// @brief Information about the layout of RGB and RGBA colors.
	/// 
	/// This class provides general information about the layout of packed
	/// colors in RGB and RGBA colorspaces.
	class color_layout
	{
	public:

		/// @brief The size value type used to return size information.
		using size_type = size_t;

		/// @brief The color value type used for conversions to RGB.
		using color_type = core::types::rgba_color;

		/// @brief The type representing values used in RGB color components.
		using component_value_type = color_type::component_value_type;

		/// @brief The type respresenting values containing packed pixels.
		using packed_color_type = uint64_t;

		/// @brief Bitfield type used to get and set a color component of a packed color.
		using bitfield_type = core::types::abstract_bitfield<packed_color_type>;


	public:

		/// @brief Creates a color format
		/// 
		/// The component bitfields passed to the constructor must have the same or a greater
		/// lifetime than the instance of the color_layout.
		/// 
		/// @param red_component_bitfield A bitfield describing the red component of a packed color.
		/// @param green_component_bitfield A bitfield describing the green component of a packed color.
		/// @param blue_component_bitfield A bitfield describing the blue component of a packed color.
		/// @param alpha_component_bitfield A bitfield describing the alpha component of a packed color.
		color_layout(
			const bitfield_type& red_component_bitfield,
			const bitfield_type& green_component_bitfield,
			const bitfield_type& blue_component_bitfield,
			const bitfield_type& alpha_component_bitfield);

		color_layout(const color_layout&) = delete;
		color_layout(color_layout&&) = delete;

		virtual ~color_layout() = default;

		/// @brief Returns a bitmask indicating all valid bits in a packed color.
		virtual packed_color_type packed_color_bitmask() const noexcept;

		/// @brief Returns the size of the red color component.
		/// 
		/// @return The size in bits of the red color component or 0 if the
		/// component is not available.
		virtual size_type red_component_size() const noexcept;

		/// @brief Returns the size of the green color component.
		/// 
		/// @return The size in bits of the green color component or 0 if the
		/// component is not available.
		virtual size_type green_component_size() const noexcept;

		/// @brief Returns the size of the blue color component.
		/// 
		/// @return The size in bits of the blue color component or 0 if the
		/// component is not available.
		virtual size_type blue_component_size() const noexcept;

		/// @brief Returns the size of the alpha color component.
		/// 
		/// @return The size in bits of the alpha color component or 0 if the
		/// component is not available.
		virtual size_type alpha_component_size() const noexcept;


		/// @brief Returns the maximum value allowed in the red color component
		/// of a packed pixel.
		virtual component_value_type red_component_max_value() const noexcept;

		/// @brief Returns the maximum value allowed in the green color component
		/// of a packed pixel.
		virtual component_value_type green_component_max_value() const noexcept;

		/// @brief Returns the maximum value allowed in the blue color component
		/// of a packed pixel.
		virtual component_value_type blue_component_max_value() const noexcept;

		/// @brief Returns the maximum value allowed in the alpha color component
		/// of a packed pixel or 0 if the component is not available.
		virtual component_value_type alpha_component_max_value() const noexcept;


		/// @brief Returns the bitfield for the red color component 
		/// 
		/// @return A bitfield describing the red component value stored in a
		/// packed pixel.
		virtual const bitfield_type& red_component_bitfield() const noexcept;

		/// @brief Returns the bitfield for the green color component 
		/// 
		/// @return A bitfield describing the green component value stored in a
		/// packed pixel.
		virtual const bitfield_type& green_component_bitfield() const noexcept;

		/// @brief Returns the bitfield for the blue color component 
		/// 
		/// @return A bitfield describing the blue component value stored in a
		/// packed pixel.
		virtual const bitfield_type& blue_component_bitfield() const noexcept;

		/// @brief Returns the bitfield for the alpha color component 
		/// 
		/// @return A bitfield describing the alpha component value stored in a
		/// packed pixel.
		virtual const bitfield_type& alpha_component_bitfield() const noexcept;


	private:

		/// @brief Bitfield used to pack and unpack the red component in a packed color value.
		const bitfield_type& red_component_bitfield_;

		/// @brief Bitfield used to pack and unpack the geen component in a packed color value.
		const bitfield_type& green_component_bitfield_;

		/// @brief Bitfield used to pack and unpack the blue component in a packed color value.
		const bitfield_type& blue_component_bitfield_;

		/// @brief Bitfield used to pack and unpack the alpha component in a packed color value.
		const bitfield_type& alpha_component_bitfield_;
	};

}}}}
