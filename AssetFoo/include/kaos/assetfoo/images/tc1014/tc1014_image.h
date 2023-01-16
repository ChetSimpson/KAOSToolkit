// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/image.h>
#include <kaos/assetfoo/colors/tc1014/tc1014_color_converter.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace tc1014
{

	/// @brief TC1014 (Tandy Color Computer 3) image
	class tc1014_image : public image
	{
	public:

		/// @copydoc colors::tc1014::tc1014_color_converter::color_map_type
		using color_map_type = colors::tc1014::tc1014_color_converter::color_map_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::color_type
		using color_type = colors::tc1014::tc1014_color_converter::color_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::color_space_type
		using color_space_type = colors::tc1014::tc1014_color_converter::color_space_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::native_packed_color_type
		using native_packed_color_type = colors::tc1014::tc1014_color_converter::native_packed_color_type;
		/// @copydoc colors::tc1014::tc1014_color_converter::native_color_map_type
		using native_color_map_type = colors::tc1014::tc1014_color_converter::native_color_map_type;


	public:

		/// @brief Create an empty TC1014 image
		tc1014_image() = default;

		/// @brief Creates a TC1014 based image
		/// 
		/// @param dimensions The size of the image
		/// @param colormap The RGBA colormap
		/// @param native_color_space The original native colorspace the image was created in (RGBA222 or I2C2 composite)
		/// @param native_colormap The original colormap data
		tc1014_image(
			dimensions_type dimensions,
			std::unique_ptr<color_map_type> colormap,
			color_space_type native_color_space,	
			native_color_map_type native_colormap);

		/// @brief Create a copy of a TC1014 based image
		/// 
		/// @param other The TC1014 based image to make a copy of
		tc1014_image(const tc1014_image& other);

		/// @brief Create a TC1014 based image using move semantics
		/// 
		/// @param other The instance to initialize the new TC1014 based image with.
		tc1014_image(tc1014_image&& other) noexcept;


		/// @brief Retrieves the RGBA colormap of the image
		/// 
		/// Gets the RGBA colormap of the image. The colors are stored at the original
		/// colormap indexes. If the image has been default constructed or moved to
		/// another instance calling this function will result in an exception being
		/// thrown.
		/// 
		/// @return the colormap of the image
		/// 
		/// @exception std::runtime_error is no colormap is not available.
		[[nodiscard]] const color_map_type& colormap() const;

		/// @brief Retrieves the native (TC1014) colorspace.
		/// 
		/// Returns the native (TC1014) colorspace the image was saved in.
		/// 
		/// @return The colorspace the image was saved in.
		[[nodiscard]] color_space_type native_color_space() const;

		/// @brief Retrieves the original native (TC1014) colormap of the image.
		/// 
		/// Returns the original colormap data the image was saved in. The format of
		/// the colormap is specified by the original colorspace returns by native_color_space().
		/// 
		/// @return The original colormap data.
		[[nodiscard]] const native_color_map_type& native_colormap() const;


	private:

		/// @brief The converted colormap of the original image
		std::unique_ptr<color_map_type> colormap_;
		/// @brief The colorspace the original image was created in.
		color_space_type native_color_space_ = color_space_type();
		/// @brief The natice colormap of the original image
		native_color_map_type native_colormap_ = native_color_map_type();
	};


	/// @brief Used to indicate that a TC1014 based image object may be "moved".
	/// 
	/// Used to indicate that a TC1014 based image object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of tc1014_image
	inline tc1014_image&& move(tc1014_image& value)
	{
		return static_cast<tc1014_image&&>(value);
	}

}}}}}
