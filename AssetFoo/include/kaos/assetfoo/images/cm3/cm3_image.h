// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image.h>
#include <kaos/assetfoo/images/monochrome_pattern.h>
#include <array>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images { namespace cm3
{

	/// @brief RGBA image with title, RGBA colormap, and original colormap
	/// 
	/// \todo Add accessor to retrieve individual patterns
	/// \todo Change patterns() to return span
	class cm3_image : public tc1014::tc1014_image
	{
	public:

		/// @brief Details about the features supported by the CM3 image.
		struct feature_details
		{
			/// @brief The maximum number of patterns allowed in the image
			static const size_type max_pattern_count = 24;
			/// @brief The number of colors used for color cycling
			static const size_type fixed_cycle_color_count = 8;
			/// @brief The number of colors in the color map
			static const size_type max_colormap_size = 16;
			/// @brief The maximum value allowed for the animation rate
			static const size_type max_animation_rate = 255;
			/// @brief The maximum value allowed for the color cycling rate
			static const size_type max_cycle_rate = 255;
		};

		/// @brief The monochroome pixelmap pattern type.
		using pattern_type = monochrome_pattern<uint8_t, size_t>;
		/// @brief The type use for maintaining a list of monochrome pixelmap patterns.
		using pattern_list_type = std::vector<pattern_type>;
		/// @brief List of colors to cycle.
		using cycle_colors_list_type = std::vector<color_type>;


	public:

		/// @brief Create an empty CM3 image
		cm3_image() = default;

		/// @brief Creates a CM3 image
		/// 
		/// @param dimensions The size of the image
		/// @param colormap The RGBA colormap
		/// @param native_color_space The original native colorspace the image was created in (RGBA222 or I2C2 composite)
		/// @param native_colormap The original colormap data
		/// @param animation_rate Color animation delay. Specifies the number of 60hz vertical sync events to delay between animation updates.
		/// @param cycle_rate Color cycling delay. Specifies the number of 60hz vertical sync events to delay between animation updates.
		/// @param cycle_colors List of colors to cycle during color cycling.
		/// @param patterns List of monochrome pixelmap patterns.
		cm3_image(
			dimensions_type dimensions,
			std::unique_ptr<color_map_type> colormap,
			color_space_type native_color_space,
			native_color_map_type native_colormap,
			size_type animation_rate,
			size_type cycle_rate,
			cycle_colors_list_type cycle_colors,
			pattern_list_type patterns);

		/// @brief Create a copy of a CM3 image
		/// 
		/// @param other The CM3 image to make a copy of
		cm3_image(const cm3_image& other);

		/// @brief Create a CM3 image using move semantics
		/// 
		/// @param other The instance to initialize the CM3 image with.
		cm3_image(cm3_image&& other) noexcept;


		/// @brief Retrieves the color animation rate.
		/// 
		/// @return The number of 60hz vertical sync events to delay between color animation updates.
		[[nodiscard]] size_type animation_rate() const;

		/// @brief Retrieves the color cycling rate.
		/// 
		/// @return The number of 60hz vertical sync events to delay between color cycling updates.
		[[nodiscard]] size_type cycle_rate() const;

		/// @brief Retrieves the color cycling rate.
		/// 
		/// @return The number of 60hz vertical sync events to delay between color cycling updates.
		[[nodiscard]] const cycle_colors_list_type& cycle_colors() const;

		/// @brief Retrieves the editor pixelmap patterns
		/// 
		/// @return A reference to the list of monochroome pixelmap patterns attached to the image.
		[[nodiscard]] const pattern_list_type& patterns() const;


	private:

		size_type animation_rate_ = 0;
		size_type cycle_rate_ = 0;
		cycle_colors_list_type cycle_colors_ = cycle_colors_list_type();
		pattern_list_type patterns_ = pattern_list_type();
	};


	/// @brief Used to indicate that a CM3 image object may be "moved".
	/// 
	/// Used to indicate that a CM3 image object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of cm3_image
	inline cm3_image&& move(cm3_image& value)
	{
		return static_cast<cm3_image&&>(value);
	}

}}}}}
