// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image.h>
#include <string>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace rat
{

	/// @brief RGBA image with background color, RGBA colormap, and original colormap
	class rat_image : public tc1014::tc1014_image
	{
	public:

		/// @copydoc color_map_type::color_type
		using color_type = color_map_type::color_type;


	public:

		rat_image() = default;

		/// @brief Creates a RAT image
		/// 
		/// @param dimensions The size of the image
		/// @param colormap The RGBA colormap
		/// @param native_color_space The original native colorspace the image was created in (RGBA222 or I2C2 composite)
		/// @param native_colormap The original colormap data
		/// @param background_color The background color the original image was saved with.
		rat_image(
			dimensions_type dimensions,
			std::unique_ptr<color_map_type> colormap,
			color_space_type native_color_space,
			native_color_map_type native_colormap,
			color_type background_color);

		/// @brief Create a copy of a RAT image
		/// 
		/// @param other The RAT image to make a copy of
		rat_image(const rat_image& other) noexcept = default;

		/// @brief Create a RAT image using move semantics
		/// 
		/// @param other The instance to initialize the new RAT image with.
		rat_image(rat_image&& other) noexcept;


		/// @brief Retrieves the background color
		/// @return the background color the original image was saved with
		[[nodiscard]] color_type background_color() const;


	private:

		color_type background_color_;
	};


	/// @brief Used to indicate that a RAT image object may be "moved".
	/// 
	/// Used to indicate that a RAT image object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of rat_image
	inline rat_image&& move(rat_image& value)
	{
		return static_cast<rat_image&&>(value);
	}

}}}}}
