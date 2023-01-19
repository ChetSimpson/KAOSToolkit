// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <stdexcept>


namespace hypertech::kaos::assetfoo::exceptions
{

	/// @brief Exception thrown when an error is encountered with a packed color
	/// value.
	class packed_color_format_error : public std::runtime_error
	{
	public:

		using std::runtime_error::runtime_error;
	};

}
