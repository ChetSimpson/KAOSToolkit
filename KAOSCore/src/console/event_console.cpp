// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/console/event_console.h>
#include <iostream>


namespace hypertech { namespace kaos { namespace core { namespace console
{

	void event_console::warning(const string_type& message)
	{
		std::cerr << "Warning: " << message << "\n";
	}

	void event_console::error(const string_type& message)
	{
		std::cerr << "Error: " << message << "\n";
	}

}}}}
