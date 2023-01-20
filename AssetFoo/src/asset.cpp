// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/asset.h>


namespace hypertech::kaos::assetfoo
{

	bool asset::has_property(const string_type& name) const
	{
		return properties_.contains(name);
	}

	void asset::delete_property(const string_type& name)
	{
		properties_.erase(name);
	}

	asset& asset::set_property(const string_type& name, const property_type& value)
	{
		properties_[name] = value;

		return *this;
	}

	asset& asset::set_property(const string_type& name, property_type&& value)
	{
		properties_[name] = move(value);

		return *this;
	}

	const asset::property_type& asset::get_property(const string_type& name) const
	{
		auto property_ptr = properties_.find(name);
		if (property_ptr == properties_.end())
		{
			throw core::exceptions::attribute_not_found_error(name);
		}

		return property_ptr->second;
	}

	const asset::property_type& asset::try_get_property(const string_type& name) const
	{
		static const property_type empty_property;

		auto property_ptr = properties_.find(name);
		if (property_ptr == properties_.end())
		{
			return empty_property;
		}

		return property_ptr->second;
	}

}
