// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/composites/object.h>


namespace hypertech::kaos::assetfoo::composites::objects
{

	/// @brief A point object with only a coordinate
	class point : public object
	{
	public:

		using object::object;

		[[nodiscard]] bool operator==(const object& other) const noexcept override;
	};
}

