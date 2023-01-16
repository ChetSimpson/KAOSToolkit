// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/image.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images
{

	image::image(image&& other) noexcept
		:
		width_(other.width_),
		height_(other.height_),
		pixel_data_(move(other.pixel_data_))
	{
		other.width_ = decltype(other.width_)();
		other.height_ = decltype(other.width_)();
	}

	image::image(size_type width, size_type height, pixel_type init_pixel)
		:
		width_(width),
		height_(height),
		pixel_data_(width * height, init_pixel)
	{
		if (width_ == 0)
		{
			throw std::invalid_argument("image width cannot be 0");
		}

		if (height_ == 0)
		{
			throw std::invalid_argument("image height cannot be 0");
		}
	}

	image::image(size_type width, size_type height, const collection_type& pixel_data)
		:
		width_(width),
		height_(height)
	{
		if (width_ == 0)
		{
			throw std::invalid_argument("image width cannot be 0");
		}

		if (height_ == 0)
		{
			throw std::invalid_argument("image height cannot be 0");
		}

		if (width_ * height_ != pixel_data.size())
		{
			throw std::invalid_argument("specified dimensions of image does not match buffer size");
		}

		pixel_data_ = pixel_data;
	}

	image::image(size_type width, size_type height, collection_type&& pixel_data)
		:
		width_(width),
		height_(height)
	{
		if (width_ == 0)
		{
			throw std::invalid_argument("image width cannot be 0");
		}

		if (height_ == 0)
		{
			throw std::invalid_argument("image height cannot be 0");
		}

		if (width_ * height_ != pixel_data.size())
		{
			throw std::invalid_argument("specified dimensions of image does not match buffer size");
		}

		pixel_data_ = move(pixel_data);
	}

	image::image(dimensions_type dimensions, pixel_type init_pixel)
		: image(dimensions.width, dimensions.height, init_pixel)
	{}

	image::image(dimensions_type dimensions, const collection_type& pixel_data)
		: image(dimensions.width, dimensions.height, pixel_data)
	{}

	image::image(dimensions_type dimensions, collection_type&& pixel_data)
		: image(dimensions.width, dimensions.height, move(pixel_data))
	{}

	image::image(const_view_type view)
		:
		width_(view.width()),
		height_(view.height()),
		pixel_data_(view.width() * view.height())
	{
		if (view.empty())
		{
			throw std::invalid_argument("cannot create image from empty view");
		}

		view_type pixels(pixel_data_.data(), width_, height_);

		auto out_row(pixels.begin());
		for (const auto& row : view)
		{
			std::copy(row.begin(), row.end(), (*out_row).begin());
			++out_row;
		}
	}




	bool image::empty() const noexcept
	{
		return pixel_data_.empty();
	}




	image::dimensions_type image::dimensions() const noexcept
	{
		return dimensions_type(width_, height_);
	}

	image::size_type image::width() const noexcept
	{
		return width_;
	}

	image::size_type image::height() const noexcept
	{
		return height_;
	}

	image::size_type image::length() const noexcept
	{
		return pixel_data_.size();
	}




	image::pixel_type* image::data() noexcept
	{
		return pixel_data_.data();
	}

	const image::pixel_type* image::data() const noexcept
	{
		return pixel_data_.data();
	}




	image::sequence_type image::at(size_type index)
	{
		return at<sequence_type>(pixel_data_, index);
	}

	image::const_sequence_type image::at(size_type index) const
	{
		return at<const_sequence_type>(pixel_data_, index);
	}

	image::sequence_type image::operator[](size_type index)
	{
		return at<sequence_type>(pixel_data_, index);
	}

	image::const_sequence_type image::operator[](size_type index) const
	{
		return at<const_sequence_type>(pixel_data_, index);
	}




	image::sequence_type image::get_sequence() noexcept
	{
		return sequence_type(pixel_data_);
	}

	image::const_sequence_type image::get_sequence() const noexcept
	{
		return const_sequence_type(pixel_data_);
	}


	image::view_type image::create_view()
	{
		return create_view<view_type>(pixel_data_);
	}

	image::view_type image::create_view(size_type view_width)
	{
		return create_view<view_type>(pixel_data_, view_width);
	}

	image::view_type image::create_view(size_type x, size_type y, size_type view_width, size_type view_height)
	{
		return create_view<view_type>(pixel_data_, x, y, view_width, view_height);
	}

	image::view_type image::create_view(position_type position, dimensions_type size)
	{
		return create_view<view_type>(pixel_data_, position.x, position.y, size.width, size.height);
	}

	image::const_view_type image::create_view() const
	{
		return create_view<const_view_type>(pixel_data_);
	}

	image::const_view_type image::create_view(size_type view_width) const
	{
		return create_view<const_view_type>(pixel_data_, view_width);
	}

	image::const_view_type image::create_view(size_type x, size_type y, size_type view_width, size_type view_height) const
	{
		return create_view<const_view_type>(pixel_data_, x, y, view_width, view_height);
	}

	image::const_view_type image::create_view(position_type position, dimensions_type size) const
	{
		return create_view<const_view_type>(pixel_data_, position.x, position.y, size.width, size.height);
	}


	template<class SequenceType_, class CollectionType_>
	[[nodiscard]] SequenceType_ image::at(CollectionType_& data, size_type index) const
	{
		if (data.empty())
		{
			throw std::runtime_error("cannot access subscript on empty image");
		}

		if (index >= height_)
		{
			throw std::out_of_range("image subscript index out of range");
		}

		const auto base_address(data.data() + (index * width_));

		return SequenceType_(base_address, base_address + width_);
	}


	template<class ViewType_, class CollectionType_>
	ViewType_ image::create_view(CollectionType_& data) const
	{
		if (data.empty())
		{
			throw std::runtime_error("cannot create view on empty image");
		}

		return { data.data(), width_, height_ };
	}

	template<class ViewType_, class CollectionType_>
	ViewType_ image::create_view(CollectionType_& data, size_type view_width) const
	{
		if (data.empty())
		{
			throw std::runtime_error("cannot create width based view on empty image");
		}

		if (view_width == 0)
		{
			throw std::out_of_range("image view width cannot be 0");
		}

		if (view_width > width_)
		{
			throw std::out_of_range("image view width cannot be greater than the image width");
		}

		if (data.size() % view_width != 0)
		{
			throw std::out_of_range("image view width must be a multiple of the image data size");
		}

		return { data.data(), view_width, data.size() / view_width };
	}

	template<class ViewType_, class CollectionType_>
	ViewType_ image::create_view(
		CollectionType_& data,
		size_type x,
		size_type y,
		size_type view_width,
		size_type view_height) const
	{
		if (data.empty())
		{
			throw std::runtime_error("cannot create boxed view on empty image");
		}


		//	Check for zero width/height
		if (view_width == 0)
		{
			throw std::out_of_range("image boxed view width cannot be 0");
		}

		if (view_height == 0)
		{
			throw std::out_of_range("image boxed view height cannot be 0");
		}


		//	Check for position out of bounds
		if (x >= width_)
		{
			throw std::out_of_range("x position of requested image boxed view exceeds bounds of image");
		}

		if (y >= height_)
		{
			throw std::out_of_range("y position of requested image boxed view exceeds bounds of image");
		}


		//	Check for right/bottom edge out of bounds
		if (x + view_width > width_)
		{
			throw std::out_of_range("width of requested image boxed view exceeds bounds of image");
		}

		if (y + view_height > height_)
		{
			throw std::out_of_range("height of requested image boxed view exceeds bounds of image");
		}


		//	TADA!
		return ViewType_(data.data() + (y * width_) + x, view_width, view_height, width_);
	}

}}}}
