// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/composites/objects/point.h>
#include <stdexcept>


namespace hypertech::kaos::assetfoo::composites::objects
{

	bool point::operator==(const object& other) const noexcept
	{
		return object::operator==(other);
	}

}
