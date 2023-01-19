// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <string>


namespace hypertech::kaos::core::console
{

	/// @brief Basic console for event reporting
	class event_console
	{
	public:

		/// @brief Type of string used by the event console.
		using string_type = std::string;

		/// @brief Issue a warning event message.
		/// @param message The warning message to issue.
		virtual void warning(const string_type& message);

		/// @brief Issue an error event message
		/// @param message The error message to issue.
		virtual void error(const string_type& message);
	};

}
