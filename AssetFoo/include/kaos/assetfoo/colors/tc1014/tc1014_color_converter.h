// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset_reader.h>
#include <kaos/assetfoo/colors/tc1014/tc1014_color_layout.h>
#include <kaos/assetfoo/colors/color_map.h>
#include <kaos/assetfoo/colors/color_space.h>
#include <kaos/assetfoo/colors/color_converter.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors { namespace tc1014
{

	/// @brief Color converter for TC1014 packed color values
	///
	/// This class extends the base color_converter and provides additional
	/// facilities for converting TC1014 colors to an RGBA color representation.
	class tc1014_color_converter : public color_converter
	{
	public:

		/// @copydoc colors::color_map
		using color_map_type = color_map;
		/// @copydoc colors::color_map::color_type
		using color_type = color_map_type::color_type;
		/// @copydoc colors::color_space
		using color_space_type = color_space;

		/// @copydoc colors::tc1014::tc1014_color_layout::native_packed_color_type
		using native_packed_color_type = tc1014_color_layout::native_packed_color_type;	
		/// @brief Array of native (TC1014) packed color values
		using native_color_map_type = std::vector<native_packed_color_type>;


	public:

		/// @brief Create a default color converter using tc1014_color_layer
		tc1014_color_converter();

		/// @brief Create a color converter
		/// @param color_format The color layer to use for conversion
		explicit tc1014_color_converter(std::shared_ptr<const color_layout> color_format);

		/// @brief Create copy of a tc1014_color_converter
		/// 
		/// @param other The color_converter to make a copy of
		tc1014_color_converter(const tc1014_color_converter& other) = default;

		/// @brief Create a tc1014_color_converter using move semantics
		/// 
		/// @param other The instance to initialize the new tc1014_color_converter with.
		tc1014_color_converter(tc1014_color_converter&& other) = default;


		/// @brief Retrieves the table used to convert native colors
		/// 
		/// @return Returns the table used to convert native colors from composite to rgb.
		virtual const native_color_map_type& composite_to_rgb_table() const noexcept;

		/// @brief Convert native colormap from one colorspace to another
		/// 
		/// @param from_color_space The colorspace the values in \p native_colormap is in.
		/// @param to_color_space The colorspace format to convert to.
		/// @param native_colormap The native colormap in the \p from_color_space format.
		virtual void convert_color_to_colorspace(
			color_space_type from_color_space,
			color_space_type to_color_space,
			native_color_map_type& native_colormap) const;

		/// @brief Converts TC1014 packed colors to RGBA
		/// 
		/// Converts a list of native TC1014 packed colors to a list of RGBA colors.
		/// If the \p color_space is color_space_type::composite
		/// the native colors are converted to the native RGB format before the
		/// colors are converted to RGBA.
		/// 
		/// @param color_space The colorspace of the color data in \p native_colormap.
		/// @param native_colormap The native colormap data.
		/// 
		/// @return A list of RGBA colors.
		virtual std::vector<color_type> convert_colors(
			color_space_type color_space,
			native_color_map_type native_colormap) const;

		/// @brief Creates a colormap
		/// 
		/// Converts a native TC1014 colormap and creates a RGBA colormap containing the
		/// converted colors. If the \p color_space is color_space_type::composite
		/// the native color map is converted to the native RGB format before the
		/// colors are converted to RGBA.
		/// 
		/// @param color_space The colorspace of the color data in \p native_colormap.
		/// @param native_colormap The native colormap data.
		/// 
		/// @return A KAOS colormap object
		virtual std::unique_ptr<colors::color_map> create_colormap(
			color_space_type color_space,
			native_color_map_type native_colormap) const;


	protected:

		/// @brief Table for converting native TC1014 composite colors to TC1014 RGB colors.
		static const native_color_map_type composite_to_rgb_table_;
	};


	/// @brief Used to indicate that a TC1014 color converter object may be "moved".
	/// 
	/// Used to indicate that a TC1014 color converter object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of tc1014_color_converter
	inline tc1014_color_converter&& move(tc1014_color_converter& value)
	{
		return static_cast<tc1014_color_converter&&>(value);
	}

}}}}}
