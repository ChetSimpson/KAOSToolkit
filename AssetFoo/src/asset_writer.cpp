// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/asset_writer.h>
#include <kaos/core/exceptions.h>
#include <fstream>
#include <filesystem>


namespace hypertech::kaos::assetfoo
{
	namespace exceptions = core::exceptions;


	void asset_writer::write(const filename_type& filename, const asset_type& asset)
	{
		std::ofstream output_stream(filename, std::ios_base::in | std::ios_base::binary);
		if (!output_stream.is_open())
		{
			throw exceptions::file_access_error("Unable to open file '" + filename + "'");
		}

		write(output_stream, asset, filename);
	}

}
