// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image.h>
#include <string>


namespace hypertech::kaos::assetfoo::images::mge
{

	/// @brief RGBA image with title, RGBA colormap, and original colormap
	class mge_image : public tc1014::tc1014_image
	{
	public:

		/// @brief Details about the features supported by the MGE image.
		struct feature_details
		{
			/// @brief Maximum length of the title property
			static const size_type max_title_length = 30;
			/// @brief Number of colors expected in the colormap
			static const size_type colormap_size = 16;
		};

		/// @brief String type
		using string_type = std::string;

	public:

		mge_image() = default;

		/// @brief Creates a MGE image
		/// 
		/// @param dimensions The size of the image
		/// @param colormap The RGBA colormap
		/// @param title The title stored in the image
		/// @param native_color_space The original native colorspace the image was created in (RGBA222 or I2C2 composite)
		/// @param native_colormap The original colormap data
		mge_image(
			dimensions_type dimensions,
			std::unique_ptr<color_map_type> colormap,
			color_space_type native_color_space,
			native_color_map_type native_colormap,
			string_type title);

		/// @brief Create a copy of a MGE image
		/// 
		/// @param other The MGE image to make a copy of
		mge_image(const mge_image& other) = default;

		/// @brief Create a MGE image using move semantics
		/// 
		/// @param other The instance to initialize the MGE image with.
		mge_image(mge_image&& other) noexcept = default;


		/// @brief Retrieves the title of the image
		/// @return the title of the image
		[[nodiscard]] const string_type& title() const;


	private:

		string_type title_;
	};


	/// @brief Used to indicate that a MGE image object may be "moved".
	/// 
	/// Used to indicate that a MGE image object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of mge_image
	inline mge_image&& move(mge_image& value)
	{
		return static_cast<mge_image&&>(value);
	}

}
