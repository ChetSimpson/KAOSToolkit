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

	void asset_reader::start(const resource_locator_type& location)
	{
		location_ = location;
	}

	asset_reader::string_type asset_reader::location_text() const noexcept
	{
		return location_.text();
	}

	std::unique_ptr<asset> asset_reader::load(const path_type& path)
	{
		if (!std::filesystem::exists(path.string()))
		{
			throw exceptions::file_not_found_error("Unable to open '" + path.string() + "'. File does not exist");
		}

		std::ifstream input_stream(path, std::ios_base::in | std::ios_base::binary);
		if (!input_stream.is_open())
		{
			throw exceptions::file_access_error("Unable to open file '" + path.string() + "'");
		}

		start(resource_locator_type(path));

		return load(input_stream);
	}

	std::unique_ptr<asset> asset_reader::load(std::istream& input_stream, const resource_locator_type& location)
	{
		start(location);

		return load(input_stream);
	}

}
