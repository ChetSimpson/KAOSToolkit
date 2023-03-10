// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/io/binary_reader.h>
#include <kaos/core/exceptions.h>


namespace hypertech { namespace kaos { namespace core { namespace io
{

	binary_reader::binary_reader(stream_type& input, ordering_type ordering)
		:
		input_(input),
		swap_bytes_(ordering != ordering_type::native)
	{}


	binary_reader::operator bool() const
	{
		return input_.operator bool();
	}

	bool binary_reader::operator!() const
	{
		return input_.operator!();
	}


	binary_reader::iostate_type binary_reader::exceptions() const
	{
		return input_.exceptions();
	}

	void binary_reader::exceptions(iostate_type except)
	{
		input_.exceptions(except);
	}

	binary_reader::pos_type binary_reader::tellg()
	{
		return input_.tellg();
	}

	binary_reader& binary_reader::seekg(pos_type pos)
	{
		input_.seekg(pos);

		return *this;
	}

	binary_reader& binary_reader::seekg(off_type off, std::ios_base::seekdir dir)
	{
		input_.seekg(off, dir);

		return *this;
	}


	bool binary_reader::eof() const
	{
		return input_.eof();
	}

	void binary_reader::clear(iostate_type state)
	{
		return input_.clear(state);
	}

	bool binary_reader::good() const
	{
		return input_.good();
	}

	bool binary_reader::fail() const
	{
		return input_.fail();
	}

	bool binary_reader::bad() const
	{
		return input_.bad();
	}

	
	
	binary_reader& binary_reader::skip(size_t length)
	{
		if (!seekg(length, std::ios::cur))
		{
			throw exceptions::end_of_file_error("file error: attempt to read past end of file");
		}

		return *this;
	}


	binary_reader& binary_reader::read(bool& output)
	{
		uint8_t value;

		if (input_.read(reinterpret_cast<char*>(&value), sizeof(value)))
		{
			output = value != 0;
		}

		return *this;
	}


	binary_reader::string_type binary_reader::read_string(size_type size, bool null_truncate)
	{
		string_type value(size, 0);
		if (!read(span_type<string_type::value_type>(value)))
		{
			throw_on_error();
		}

		if (null_truncate)
		{
			auto new_size(value.find_first_of('\0'));
			if (new_size != string_type::npos)
			{
				value.resize(new_size);
			}
		}

		if (swap_bytes_ && sizeof(string_type::value_type) > 1)
		{
			std::transform(
				begin(value),
				end(value),
				begin(value),
				utility::byteswap<string_type::value_type>);
		}

		return value;
	}


	void binary_reader::throw_on_error() const
	{
		if (eof())
		{
			throw exceptions::end_of_file_error("file error: attempt to read past end of file");
		}

		if (fail())
		{
			throw exceptions::file_error("file error: unable to read from file");
		}

		throw exceptions::file_error("file error: unexpected error encountered while reading from file");
	}



}}}}
