// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/io/binary_writer.h>
#include <kaos/core/exceptions.h>


namespace hypertech::kaos::core::io
{

	binary_writer::binary_writer(stream_type& output, ordering_type ordering)
		:
		binary_ios(output, ordering),
		output_(output)
	{}


	binary_writer::pos_type binary_writer::tellp()
	{
		try
		{
			return output_.tellp();
		}
		catch (std::exception& e)
		{
			throw exceptions::file_error(e.what());
		}
	}

	binary_writer& binary_writer::seekp(pos_type pos)
	{
		try
		{
			output_.seekp(pos);
		}
		catch (std::exception& e)
		{
			throw exceptions::file_error(e.what());
		}

		return *this;
	}

	binary_writer& binary_writer::seekp(off_type off, std::ios_base::seekdir dir)
	{
		try
		{
			output_.seekp(off, dir);
		}
		catch (std::exception& e)
		{
			throw exceptions::file_error(e.what());
		}

		return *this;
	}

	binary_writer& binary_writer::skipp(size_t length)
	{
		return seekp(length, std::ios::cur);
	}

	void binary_writer::throw_on_write_error() const
	{
		if (eof())
		{
			throw exceptions::end_of_file_error("file error: attempt to write past end of file");
		}

		if (fail())
		{
			throw exceptions::file_error("file error: unable to write to file");
		}

		throw exceptions::file_error("file error: unexpected error encountered while writing to file");
	}

}
