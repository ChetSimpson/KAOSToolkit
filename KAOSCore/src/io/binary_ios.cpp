// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/io/binary_ios.h>
#include <kaos/core/exceptions.h>


namespace hypertech::kaos::core::io
{

	binary_ios::binary_ios(base_stream_type& stream, ordering_type ordering)
		:
		base_stream_(stream),
		swap_bytes_(ordering != ordering_type::native)
	{}


	binary_ios::operator bool() const
	{
		return base_stream_.operator bool();
	}

	bool binary_ios::operator!() const
	{
		return base_stream_.operator!();
	}


	binary_ios::iostate_type binary_ios::exceptions() const
	{
		return base_stream_.exceptions();
	}

	void binary_ios::exceptions(iostate_type except)
	{
		base_stream_.exceptions(except);
	}

	bool binary_ios::eof() const
	{
		return base_stream_.eof();
	}

	void binary_ios::clear(iostate_type state)
	{
		return base_stream_.clear(state);
	}

	bool binary_ios::good() const
	{
		return base_stream_.good();
	}

	bool binary_ios::fail() const
	{
		return base_stream_.fail();
	}

	bool binary_ios::bad() const
	{
		return base_stream_.bad();
	}

}
