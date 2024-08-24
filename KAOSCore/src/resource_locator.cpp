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


	resource_locator& resource_locator::operator=(path_type path)
	{
		path_ = std::move(path);

		return *this;
	}

	bool resource_locator::empty() const noexcept
	{
		return path_.empty();
	}


	bool resource_locator::is_absolute() const noexcept
	{
		return path_.is_absolute();
	}

	bool resource_locator::is_relative() const noexcept
	{
		return path_.is_relative();
	}


	resource_locator resource_locator::make_relative_of(const resource_locator& base) const
	{
		//if (root_name() != _Base.root_name() || is_absolute() != _Base.is_absolute()
		//	|| (!has_root_directory() && _Base.has_root_directory()) || _Relative_path_contains_root_name(*this)
		//	|| _Relative_path_contains_root_name(_Base)) {
		//	return _Result;
		//}

		if (is_relative())
		{
			throw std::runtime_error("Cannot make path relative of base. Path is already relative.");
		}

		
		return resource_locator(std::filesystem::relative(base.path_));
	}

	resource_locator resource_locator::make_absolute() const
	{
		return resource_locator(std::filesystem::canonical(path_));
	}

	resource_locator resource_locator::make_absolute(const resource_locator& base) const
	{
		if (!is_absolute())
		{
			return resource_locator(std::filesystem::canonical(base.path_ / path_));
		}

		return resource_locator(std::filesystem::canonical(base.path_ / std::filesystem::relative(path_, base.path_)));
	}


	resource_locator::string_type resource_locator::text() const
	{
		return path_.generic_string();
	}

}