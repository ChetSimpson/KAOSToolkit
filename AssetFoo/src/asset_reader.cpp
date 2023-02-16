// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/asset_reader.h>
#include <kaos/core/exceptions.h>
#include <fstream>
#include <filesystem>


namespace hypertech::kaos::assetfoo
{
	namespace exceptions = core::exceptions;


	std::unique_ptr<asset> asset_reader::load(const filename_type& filename)
	{
		if (!std::filesystem::exists(filename))
		{
			throw exceptions::file_not_found_error("Unable to open '" + filename + "'. File does not exist");
		}

		std::ifstream input_stream(filename, std::ios_base::in |std::ios_base::binary);
		if (!input_stream.is_open())
		{
			throw exceptions::file_access_error("Unable to open file '" + filename + "'");
		}

		source_name_ = filename;

		return load(input_stream);
	}

	std::unique_ptr<asset> asset_reader::load(std::istream& input_stream, const filename_type& source_name)
	{
		source_name_ = source_name;

		return load(input_stream);
	}

}
