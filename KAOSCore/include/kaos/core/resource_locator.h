// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <filesystem>


namespace hypertech::kaos::core
{
	/// @brief Basic container for resource locations.
	class resource_locator
	{
	public:

		/// @brief The string type.
		using string_type = std::string;
		/// @brief The file system path type.
		using path_type = std::filesystem::path;


	public:

		/// @brief Constructs a resource locator with an empty path.
		resource_locator() = default;

		/// @brief Constructs a resource locator wiht a file system path.
		/// 
		/// @param path The file path of the resource.
		explicit resource_locator(path_type path);

		/// @brief Assignment operator.
		/// 
		/// @param path The file system based path to assign to the resource locator.
		/// 
		/// @return *this.
		resource_locator& operator=(const path_type& path);

		/// @brief Retrieves the text representation of the resource location.
		/// 
		/// @return The text representation of the resource location.
		string_type text() const noexcept;


		/// @brief Compares two instances of `resource_locator` for equality.
		/// 
		/// @param other A reference to the instance of `resource_locator` to compare against.
		/// 
		/// @return `true` if the instances of `resource_locator` are the same; `false` otherwise.
		bool operator==(const resource_locator& other) const noexcept = default;

		/// @brief Compares two instances of `resource_locator` for equality.
		/// 
		/// @param other A reference to the instance of `resource_locator` to compare against.
		/// 
		/// @return `true` if the instances of `resource_locator` are not the same; `false` otherwise.
		bool operator!=(const resource_locator& other) const noexcept = default;


	private:

		/// @brief A file system based path.
		path_type path_;
	};

}