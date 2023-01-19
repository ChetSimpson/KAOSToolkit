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


	asset_reader::asset_reader(bool is_binary)
		: is_binary_(is_binary)
	{}


	std::unique_ptr<asset> asset_reader::load(const filename_type& filename)
	{
		if (!std::filesystem::exists(filename))
		{
			throw exceptions::file_not_found_error("Unable to open '" + filename + "'. File does not exist");
		}

		std::ifstream input_stream(
			filename,
			std::ios_base::in | (is_binary_ ? std::ios_base::binary : 0));
		if (!input_stream.is_open())
		{
			throw exceptions::file_access_error("Unable to open file '" + filename + "'");
		}

		return load(input_stream, filename);
	}

}
