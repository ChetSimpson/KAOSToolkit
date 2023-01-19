// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/colors/color_layout.h>
#include <kaos/core/types/split_bitfield.h>
#include <kaos/core/types/empty_bitfield.h>


namespace hypertech::kaos::assetfoo::colors::tc1014
{

	/// @brief Provides details about the format of packed colors for the
	/// Tandy Corp. TCC1014 series of chips.
	/// 
	/// Provides details and about the packed color format used by the Tandy Corp. TCC1014 and
	/// TCC1014A GIME (Graphics, Interrupt, Memory Enhancement) chip found in the Tandy Color
	/// Computer 3.
	class tc1014_color_layout : public color_layout
	{
	public:

		/// @brief The bitfield type used to describe, access, and modify the color
		/// components of a TC1014 packed color vlaue.
		using tc1014bitfield_type = core::types::split_bitfield<bitfield_type::value_type>;

		/// @brief The null/empty bitfield type used to describe, access, and modify
		/// the alpha color component of a TC1014 packed color vlaue.
		using empty_bitfield_type = core::types::empty_bitfield<bitfield_type::value_type>;

		/// @brief Packed color data type for entries in the native colormap
		using native_packed_color_type = uint8_t;	

		/// @brief Bitmask of all valid bits in a native packed color
		static const native_packed_color_type native_packed_color_mask = 0x3f;


	public:

		tc1014_color_layout();

		tc1014_color_layout(const tc1014_color_layout&) = delete;
		tc1014_color_layout(tc1014_color_layout&&) = delete;


	private:

		/// @brief Bitfield used to pack and unpack the red component in a packed color value.
		static const tc1014bitfield_type red_component_bitfield_;

		/// @brief Bitfield used to pack and unpack the geen component in a packed color value.
		static const tc1014bitfield_type green_component_bitfield_;

		/// @brief Bitfield used to pack and unpack the blue component in a packed color value.
		static const tc1014bitfield_type blue_component_bitfield_;

		/// @brief Bitfield used to pack and unpack the alpha component in a packed color value.
		static const empty_bitfield_type alpha_component_bitfield_;
	};

}
