// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset.h>
#include <kaos/core/types/vector2.h>
#include <kaos/core/types/dimension2.h>
#include <kaos/core/types/rgba_color.h>
#include <kaos/core/types/box_view.h>
#include <kaos/core/exceptions.h>
#include <any>
#include <vector>
#include <map>
#include <optional>


namespace hypertech::kaos::assetfoo::images
{

	/// @brief RGBA image
	class image : public asset
	{
	public:

		/// @brief The type of pixel stored in the image
		using pixel_type = core::types::rgba_color;
		/// @brief Value size type
		using size_type = std::size_t;
		/// @brief Position type
		using position_type = core::types::vector2<size_type>;
		/// @brief Dimensions (image size) type
		using dimensions_type = core::types::dimension2<size_type>;
		/// @brief Sequence type for flat (linear) views of the pixel data
		using sequence_type = std::span<pixel_type>;
		/// @brief Sequence type for a const qualified flat (linear) views of the pixel data
		using const_sequence_type = std::span<const pixel_type>;
		/// @brief Two dimensional view of the the pixel data
		using view_type = core::types::box_view<pixel_type>;
		/// @brief Const qualified Two dimensional view of the the pixel data
		using const_view_type = core::types::box_view<const pixel_type>;
		/// @brief Collection type used to manage the pixel data
		using collection_type = std::vector<pixel_type>;

		using string_type = std::string;
		using property_type = std::any;
		using property_map_type = std::map<string_type, property_type>;
		//using optional_property_type = std::optional<std::reference_wrapper<const property_type>>;


	public:

		/// @brief Creates an empty image with no size.
		image() noexcept = default;

		/// @brief Creates an images
		/// 
		/// Creates an images of size \p width and \p height and sets all pixels
		/// to black and fully opaque (0, 0, 0, 255)
		/// 
		/// @param width The width of the image.
		/// @param height The height of the image.
		/// @param init_pixel PIxel to initialize the image pixel data with
		/// 
		/// @exception std::invalid_argument if \p width is 0
		/// @exception std::invalid_argument if \p height is 0
		image(size_type width, size_type height, pixel_type init_pixel = pixel_type());

		/// @brief Creates an image with precomposed pixel data
		/// 
		/// Creates an image with precomposed image data. The image data passed in
		/// \p pixel_data must be the exact length of \p width * \p height.
		/// 
		/// @param width Width of the image
		/// @param height Height of the image
		/// @param pixel_data Precomposed pixel data
		/// 
		/// @exception std::invalid_argument if \p width is 0
		/// @exception std::invalid_argument if \p height is 0
		/// @exception std::invalid_argument if the length of \p pixel_data is not the exact size of the dimensions.
		image(size_type width, size_type height, const collection_type& pixel_data);

		/// @brief Creates an image with precomposed pixel data
		/// 
		/// Creates an image with precomposed image data. The image data passed in
		/// \p pixel_data must be the exact length of \p width * \p height. After
		/// the image is successfully created \p pixel_data will be left in a default
		/// empty state.
		/// 
		/// @param width Width of the image
		/// @param height Height of the image
		/// @param pixel_data Precomposed pixel data
		/// 
		/// @exception std::invalid_argument if \p width is 0
		/// @exception std::invalid_argument if \p height is 0
		/// @exception std::invalid_argument if the length of \p pixel_data is not the exact size of the dimensions.
		image(size_type width, size_type height, collection_type&& pixel_data);

		/// @brief Creates an images
		/// 
		/// Creates an images using the width and height specified in \p dimensions
		/// and sets all pixels to black and fully opaque (0, 0, 0, 255)
		/// 
		/// @param dimensions The dimensions (size) of the image.
		/// @param init_pixel PIxel to initialize the image pixel data with
		/// 
		/// @exception std::invalid_argument if width of the \p dimensions is 0
		/// @exception std::invalid_argument if height of the \p dimensions is 0
		explicit image(dimensions_type dimensions, pixel_type init_pixel = pixel_type());

		/// @brief Creates an image with precomposed pixel data
		/// 
		/// Creates an images using the width and height specified in \p dimensions.
		/// The image data passed in \p pixel_data must be the exact length of the
		/// supplied dimensions.
		/// 
		/// @param dimensions The dimensions (size) of the image.
		/// @param pixel_data Precomposed pixel data
		/// 
		/// @exception std::invalid_argument if width of the \p dimensions is 0
		/// @exception std::invalid_argument if height of the \p dimensions is 0
		/// @exception std::invalid_argument if the length of \p pixel_data is not the exact size of the dimensions.
		image(dimensions_type dimensions, const collection_type& pixel_data);

		/// @brief Creates an image with precomposed pixel data
		/// 
		/// Creates an images using the width and height specified in \p dimensions.
		/// The image data passed in \p pixel_data must be the exact length of the
		/// supplied dimensions. After the image is successfully created \p pixel_data
		/// will be left in a default empty state.
		/// 
		/// @param dimensions The dimensions (size) of the image.
		/// @param pixel_data Precomposed pixel data
		/// 
		/// @exception std::invalid_argument if width of the \p dimensions is 0
		/// @exception std::invalid_argument if height of the \p dimensions is 0
		/// @exception std::invalid_argument if the length of \p pixel_data is not the exact size of the dimensions.
		image(dimensions_type dimensions, collection_type&& pixel_data);


		/// @brief Creates an image from a box view
		/// 
		/// Creates an images using box view of type `pixel_type`.
		/// 
		/// @param view the box view containing a view of the data to create an image from.
		/// 
		/// @exception std::invalid_argument if the \p view is empty
		explicit image(const_view_type view);


		/// @brief Creates a copy of an image
		/// 
		/// @param other The image to copy
		image(const image& other) = default;

		/// @brief Creates an image using move semantics
		/// 
		/// Creates an image using the contents of \p other leaving it in a default
		/// empty state (empty() returns true).
		/// 
		/// @param other The image to move.
		image(image&& other) noexcept;


		/// @brief Checks if the image is empty
		/// 
		/// Checks if the image is empty (width and height = 0).
		/// 
		/// @return true if the image is empty; false if the image is not empty.
		[[nodiscard]] bool empty() const noexcept;

		/// @brief Retrieve the dimensions of the image
		/// 
		/// @return The dimentions of the image.
		[[nodiscard]] dimensions_type dimensions() const noexcept;

		/// @brief Retrieve the width of the image
		/// 
		/// @return The width of the image or 0 if the image is empty.
		[[nodiscard]] size_type width() const noexcept;

		/// @brief Retrieve the height of the image
		/// 
		/// @return The height of the image or 0 if the image is empty.
		[[nodiscard]] size_type height() const noexcept;

		/// @brief Retrieves the number of pixels in the image
		/// 
		/// @return The total number of pixels in the image
		[[nodiscard]] size_type length() const noexcept;

		/// @brief Get a pointer to the pixel data
		/// @return A pointer to the pixel data or null if the image is empty.
		[[nodiscard]] pixel_type* data() noexcept;

		/// @brief Get a pointer to the pixel data
		/// @return A const qualified pointer to the pixel data or null if the image is empty.
		[[nodiscard]] const pixel_type* data() const noexcept;


		bool has_property(const string_type& name) const;

		void delete_property(const string_type & name);

		image& set_property(const string_type& name, const property_type& value);

		image& set_property(const string_type& name, property_type&& value);

		[[nodiscard]] const property_type& get_property(const string_type & name) const;

		template<class Type_>
		[[nodiscard]] const Type_& get_property_as(const string_type & name) const;

		const property_type& try_get_property(const string_type & name) const;

		/// @brief Returns a sequence view to a specified row in the image
		/// 
		/// @param index The row to view
		/// 
		/// @return A sequence view to the row specified in \p index.
		/// 
		/// @exception std::runtime_error if the image is empty (empty() returns true)
		/// @exception std::out_of_range if the row specified in \p index is greater
		/// than the number of rows in the image.
		[[nodiscard]] sequence_type at(size_type index);

		/// @brief Returns a sequence view to a specified row in the image
		/// 
		/// Returns const qualified sequence view to a specified row in the image
		/// 
		/// @param index The row to view
		/// 
		/// @return A sequence view to the row specified in \p index.
		/// 
		/// @exception std::runtime_error if the image is empty (empty() returns true)
		/// @exception std::out_of_range if the row specified in \p index is greater
		/// than the number of rows in the image.
		[[nodiscard]] const_sequence_type at(size_type index) const;

		/// @copydoc at()
		[[nodiscard]] sequence_type operator[](size_type index);

		/// @copydoc at()
		[[nodiscard]] const_sequence_type operator[](size_type index) const;


		/// @brief Returns a sequence view of all pixels in the image
		/// 
		/// @return A sequence view to the rowq specified in \p index.
		/// 
		/// @exception std::runtime_error if the image is empty (empty() returns true)
		/// @exception std::out_of_range if the row specified in \p index is greater
		/// than the number of rows in the image.
		[[nodiscard]] sequence_type get_sequence() noexcept;

		/// @copydoc get_sequence()
		[[nodiscard]] const_sequence_type get_sequence() const noexcept;

		/// @brief Creates a 2 dimensional view of the image
		/// 
		/// Creates a 2 dimensional view of the image with a size equal to the
		/// size of the image.
		/// 
		/// @return A view of the image
		/// 
		/// @exception std::runtime_error If the image is empty (empty() returns true)
		[[nodiscard]] view_type create_view();

		/// @brief Creates skewed 2 dimensional view of the image
		/// 
		/// Creates a skewed 2 dimensional view of the image where each row of the view
		/// is a fixed width regardless of the dimensions of the image. 
		/// 
		/// @param view_width The size of each row. The value passed must be a multiple of
		/// the total number of pixels in the image (width * height % view_width)
		/// 
		/// @return The view.
		/// 
		/// @exception std::runtime_error If the image is empty (empty() returns true)
		/// @exception std::out_of_range if \p view_width is 0
		/// @exception std::out_of_range if \p view_width is larger than the width of the
		/// image
		/// @exception std::out_of_range if \p view_width is not a multiple of the total
		/// size of the image (width * height)
		[[nodiscard]] view_type create_view(size_type view_width);

		/// @brief Creates a 2 dimensional view of a portion of the image.
		/// 
		/// Creates a 2 dimensional view of a portion of the the image at the position
		/// specified by \p x and \p y with a size specified by \p view_width and \p view_height
		/// 
		/// @param x The left position in the image of the view
		/// @param y The top position in the image of the view
		/// @param view_width The number of pixels per row (width) of the view
		/// @param view_height The number of rows (height) of the view
		/// 
		/// @return The view
		/// 
		/// @exception std::runtime_error If the image is empty (empty() returns true).
		/// @exception std::out_of_range if \p view_width is 0.
		/// @exception std::out_of_range if \p view_height is 0.
		/// @exception std::out_of_range if \p x is greater than the width of the image.
		/// @exception std::out_of_range if \p y is greater than the height of the image.
		/// @exception std::out_of_range If the size of the view exceeds the right or bottom
		/// edge of the image (x + width, y + height)
		[[nodiscard]] view_type create_view(size_type x, size_type y, size_type view_width, size_type view_height);

		/// @brief Creates a 2 dimensional view of a portion of the image.
		/// 
		/// Creates a 2 dimensional view of a portion of the the image at the position
		/// specified by \p x and \p y with a size specified by \p view_width and \p view_height
		/// 
		/// @param position The left and top positions of the view
		/// @param size The number of pixels per row (width) and number of rows (height) of the view
		/// 
		/// @return The view
		/// 
		/// @exception std::runtime_error If the image is empty (empty() returns true).
		/// @exception std::out_of_range if width specified in \p position is 0.
		/// @exception std::out_of_range if height \p position is 0.
		/// @exception std::out_of_range if x position specified in \p position is greater than the width of the image.
		/// @exception std::out_of_range if y position specified in \p position is greater than the height of the image.
		/// @exception std::out_of_range If the size of the view exceeds the right or bottom
		/// edge of the image (x + width, y + height)
		[[nodiscard]] view_type create_view(position_type position, dimensions_type size);


		/// @copydoc create_view()
		[[nodiscard]] const_view_type create_view() const;
		/// @copydoc create_view(size_type)
		[[nodiscard]] const_view_type create_view(size_type view_width) const;
		/// @copydoc create_view(size_type,size_type,size_type,size_type)
		[[nodiscard]] const_view_type create_view(size_type x, size_type y, size_type view_width, size_type view_height) const;
		/// @copydoc create_view(position_type,dimensions_type)
		[[nodiscard]] const_view_type create_view(position_type position, dimensions_type size) const;


	private:

		template<class SequenceType_, class CollectionType_>
		[[nodiscard]] SequenceType_ at(CollectionType_& data, size_type index) const;

		template<class ViewType_, class CollectionType_>
		[[nodiscard]] ViewType_ create_view(CollectionType_& data) const;

		template<class ViewType_, class CollectionType_>
		[[nodiscard]] ViewType_ create_view(CollectionType_& data, size_type view_width) const;

		template<class ViewType_, class CollectionType_>
		[[nodiscard]] ViewType_ create_view(
			CollectionType_& data,
			size_type x,
			size_type y,
			size_type view_width,
			size_type view_height) const;


	private:

		size_type		width_ = 0;
		size_type		height_ = 0;
		collection_type pixel_data_;
		property_map_type	properties_;
	};


	template<class Type_>
	inline const Type_& image::get_property_as(const string_type& name) const
	{
		try
		{
			return any_cast<const Type_&>(get_property(name));
		}
		catch (std::bad_any_cast&)
		{
			throw core::exceptions::attribute_conversion_error(
				"bad any cast",
				name,
				typeid(Type_));
		}
	}



	//template<class Type_>
	//inline std::optional<std::reference_wrapper<const Type_>> image::try_get_property_as(const string_type& name) const
	//{
	//	try
	//	{
	//		auto property(try_get_property(name));
	//		if (!property.has_value())
	//		{
	//			return {};
	//		}

	//		return any_cast<const Type_&>(property.value().get());
	//	}
	//	catch (std::bad_any_cast&)
	//	{
	//		throw core::exceptions::attribute_conversion_error(
	//			"bad any cast",
	//			name,
	//			typeid(Type_));
	//	}
	//}

	//template<class Type_>
	//requires std::is_integral_v<Type_>
	//	|| std::is_floating_point_v<Type_>
	//	|| std::is_pointer_v<Type_>
	//	|| std::negation_v<typename std::is_reference<Type_>>
	//inline std::optional<Type_> image::try_get_property_as(const string_type& name) const
	//{
	//	try
	//	{
	//		auto property(try_get_property(name));
	//		if (!property.has_value())
	//		{
	//			return {};
	//		}

	//		return any_cast<const Type_&>(property.value().get());
	//	}
	//	catch (std::bad_any_cast&)
	//	{
	//		throw core::exceptions::attribute_conversion_error(
	//			"bad any cast",
	//			name,
	//			typeid(Type_));
	//	}
	//}

	/// @brief Used to indicate that an image object may be "moved".
	/// 
	/// Used to indicate that an image object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of image
	inline image&& move(image& img)
	{
		return static_cast<image&&>(img);
	}

}
