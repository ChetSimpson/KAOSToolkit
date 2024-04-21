// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/resource_locator.h>


namespace hypertech::kaos::core
{

	resource_locator::resource_locator(path_type path)
		: path_(std::move(path))
	{}


	resource_locator& resource_locator::operator=(const path_type& path)
	{
		path_ = path;

		return *this;
	}

	resource_locator::string_type resource_locator::text() const noexcept
	{
		return path_.string();
	}

}