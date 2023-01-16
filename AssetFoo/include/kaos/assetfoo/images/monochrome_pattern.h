// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/rgba_color.h>
#include <array>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images
{

	/// @brief Monochrome bitmap pattern
	/// 
	/// @tparam Type_ The underlying type used to store monochrome pixel data.
	/// @tparam ColorType_ The type used to store color information.
	/// 
	/// This class provides an monochrome pattern with background and foreground colors.
	/// 
	/// \todo Add begin() and end() to provide iteration over pixmap rows
	template<class Type_, class ColorType_ = kaos::core::types::rgba_color>
	requires std::unsigned_integral<Type_>
	class monochrome_pattern
	{
	public:

		/// @brief Site type
		using size_type = size_t;

		/// @brief Underlying data type for pixel map data
		using pixelmap_pixel_type = Type_;
		/// @brief Width of the pattern
		static const size_t width = std::numeric_limits<pixelmap_pixel_type>::digits;
		/// @brief Height of the pattern
		static const size_t height = width;
		/// @brief Bits per pixel of the pattern
		static const size_t bits_per_pixel = 1;
		/// @brief The length (number of elements) of the pixelmap data.
		static const size_t pixmap_length = height;

		/// @brief Type representing the foreground and background colors
		using color_type = ColorType_;
		/// @brief Container for pixel map data
		using pixelmap_type = std::array<pixelmap_pixel_type, height>;


	public:

		/// @brief Create an empty pattern
		monochrome_pattern() = default;

		/// @brief Create a pattern.
		/// 
		/// Creates a pattern with the specified background and foreground CLUT indexes
		/// and initial pixelmap data.
		/// 
		/// @param background_color The background color.
		/// @param foreground_color The foregroupnd color.
		/// @param pixelmap The pixelmap data.
		monochrome_pattern(
			color_type background_color,
			color_type foreground_color,
			const pixelmap_type& pixelmap)
			:
			background_color_(background_color),
			foreground_color_(foreground_color),
			pixelmap_(pixelmap)
		{}

		/// @brief Create copy of a monochrome_pattern
		/// 
		/// @param other The monochrome_pattern to make a copy of
		monochrome_pattern(const monochrome_pattern& other) noexcept
			:
			background_color_(other.background_color_),
			foreground_color_(other.foreground_color_),
			pixelmap_(other.pixelmap_)
		{}

		/// @brief Create a monochrome_pattern using move semantics
		/// 
		/// @param other The instance to initialize the new monochrome_pattern with.
		monochrome_pattern(monochrome_pattern&& other) noexcept
			:
			background_color_(other.background_color_),
			foreground_color_(other.foreground_color_),
			pixelmap_(other.pixelmap_)
		{
			other.background_color_ = color_type();
			other.foreground_color_ = color_type();
			other.pixelmap_ = pixelmap_type();
		}

		/// @brief Replaces the contents of the pattern
		/// 
		/// Replaces the contents with those of \p other using copy semantics (i.e. the data
		/// in other is copied from \p other into this container).
		/// 
		/// @param other The monochrome_pattern to copy.
		/// 
		/// @return *this
		monochrome_pattern& operator=(const monochrome_pattern& other) noexcept
		{
			background_color_ = other.background_color_;
			foreground_color_ = other.foreground_color_;
			pixelmap_ = other.pixelmap_;

			return *this;
		}

		/// @brief  Replaces the contents using move semantics
		/// 
		/// Replaces the contents with those of other using move semantics (i.e. the data
		/// in other is moved from other into this container).
		/// 
		/// @param other The monochrome_pattern to use as data source
		/// 
		/// @return *this
		monochrome_pattern& operator=(monochrome_pattern&& other) noexcept
		{
			background_color_ = other.background_color_;
			foreground_color_ = other.foreground_color_;
			pixelmap_ = other.pixelmap_;

			other.background_color_ = color_type();
			other.foreground_color_ = color_type();
			other.pixelmap_ = pixelmap_type();

			return *this;
		}


		/// @brief Compares two patterns for equality.
		/// 
		/// @param other The pattern to compare against.
		/// 
		/// @return true if the patterns are equal; false if they are not equal
		bool operator==(const monochrome_pattern& other) const = default;


		/// @brief Returns the CLUT index of the foreground color.
		/// 
		/// @return The CLUT index of the foreground color.
		color_type foreground_color() const
		{
			return foreground_color_;
		}

		/// @brief Returns the CLUT index of the background color.
		/// 
		/// @return The CLUT index of the background color.
		color_type background_color() const
		{
			return background_color_;
		}

		/// @brief Provides read-only access to the pixelmap data
		/// 
		/// @return A reference to the pixelmap data.
		const pixelmap_type& pixelmap() const
		{
			return pixelmap_;
		}


	private:

		color_type		background_color_ = color_type();
		color_type		foreground_color_ = color_type();
		pixelmap_type	pixelmap_ = pixelmap_type();
	};


	/// @brief Used to indicate that a monochrome pattern object may be "moved".
	/// 
	/// Used to indicate that a monochrome pattern object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @tparam Type_ The underlying type used to store monochrome pixel data.
	/// @tparam ColorType_ The type used to store color information.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of monochrome_pattern
	template<class Type_, class ColorType_>
	inline monochrome_pattern<Type_, ColorType_>&& move(monochrome_pattern<Type_, ColorType_>& value)
	{
		return static_cast<monochrome_pattern<Type_, ColorType_>&&>(value);
	}

}}}}
