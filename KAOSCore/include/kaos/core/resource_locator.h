// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <filesystem>


namespace hypertech::kaos::core
{
	// FIXME: This should be renamed to resource_location

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
		resource_locator& operator=(path_type path);


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

		/// @brief Indicates if the resource location is empty.
		/// 
		/// @return `true` if the resource location is empty; `false` otherwise.
		bool empty() const noexcept;

		/// @brief Indicates if the resource location is an absolute path.
		/// 
		/// @return `true` if the resource location is absolute; `false` otherwise.
		bool is_absolute() const noexcept;

		/// @brief Indicates if the resource location is a relative path.
		/// 
		/// @return `true` if the resource location is relative; `false` otherwise.
		bool is_relative() const noexcept;

		/// @brief Creates a resource location that is relative of another.
		/// 
		/// Creates a resource location from the current resource location
		/// that is relative to the value of `base`.
		/// 
		/// @param base The location the new one will be relative of.
		/// 
		/// @return A resource location relative to value of `base`.
		/// 
		/// @exception TODO
		resource_locator make_relative_of(const resource_locator& base) const;

		/// @brief Creates a resource location that is an absolute path.
		/// 
		/// Creates a resource location from the current resource location that is
		/// an absolute path. If the current resource location is already absolute
		/// the new resource location will be an exact duplicate. Otherwise the new
		/// resource location will be relative to the current working path of the
		/// current resource locations resource type.
		/// 
		/// @return A resource location that is an absolute path to a resource.
		/// 
		/// @exception TODO
		resource_locator make_absolute() const;

		/// @brief Creates a resource location that is an absolute path.
		/// 
		/// Creates a resource location from the current resource location that is
		/// an absolute path. If the current resource location is already absolute
		/// the new resource location will be an exact duplicate. Otherwise the new
		/// resource location will be relative to the value of `base`.
		/// 
		/// @param base The location the new one will be relative of.
		/// 
		/// @return A resource location that is an absolute path to a resource.
		/// 
		/// @exception TODO
		resource_locator make_absolute(const resource_locator& base) const;

		/// @brief Retrieves the text representation of the resource location.
		/// 
		/// @return The text representation of the resource location.
		string_type text() const;


	private:

		/// @brief A file system based path.
		path_type path_;
	};

}