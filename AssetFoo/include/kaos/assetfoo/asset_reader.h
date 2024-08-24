// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset.h>
#include <kaos/core/resource_locator.h>
#include <filesystem>
#include <memory>
#include <string>


namespace hypertech::kaos::assetfoo
{

	/// @brief Abstract class for loading media files as KAOS assets.
	///
	/// This class provides the base interface and functional support for
	/// loading media files as KAOS intermediate asset objects.
	/// 
	///	\todo Add ability to pass options to the readers allowing control over
	/// the importing process such as the type of conversion to occur for RGB
	/// and native colorspaces.
	class asset_reader
	{
	public:

		/// @brief Defines the type representing a filename.
		using resource_locator_type = core::resource_locator;
		/// @copydoc resource_locator_type::path_type
		using path_type = resource_locator_type::path_type;
		/// @copydoc resource_locator_type::string_type
		using string_type = resource_locator_type::string_type;


	public:

		/// @brief Create an asset reader
		explicit asset_reader() = default;

		/// @brief Create a copy of an asset reader
		/// 
		/// @param other The asset_reader to make a copy of
		asset_reader(const asset_reader& other) = default;

		/// @brief Create an asset reader using move semantics
		/// 
		/// @param other The instance to initialize the new asset reader with.
		asset_reader(asset_reader&& other) = default;


		/// @brief Defaulted destructor.
		virtual ~asset_reader() = default;

		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the file specified in \p filename.
		/// 
		/// @param path The path to the asset to load.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		virtual std::unique_ptr<asset> load(const path_type& path);

		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the file specified in \p filename and returns it as the type
		/// specified in \p Type_.
		/// 
		/// @tparam Type_ The type (derived from asset) to load the asset as. 
		/// 
		/// @param path The path to the asset to load.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		template<class Type_>
		requires std::is_convertible_v<Type_, asset>
		std::unique_ptr<Type_, std::default_delete<asset>> load_as(const path_type& path)
		{
			return assetfoo::dynamic_pointer_cast<Type_, std::default_delete<asset>>(load(path));
		}


		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the stream specified in \p input_stream.
		/// 
		/// @param input_stream The stream to load the asset from.
		/// @param location The location of the asset file being loaded. This may be a filename or
		/// another name describing the source of the asset such as a network stream or a memory
		/// buffer.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		virtual std::unique_ptr<asset> load(std::istream& input_stream, const resource_locator_type& location);

		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the stream specified in \p input_stream and returns it as the type
		/// specified in \p Type_.
		/// 
		/// @tparam Type_ The type (derived from asset) to load the asset as. 
		/// 
		/// @param input_stream The stream to load the asset from.
		/// @param location The location of the asset file being loaded. This may be a filename or
		/// another name describing the source of the asset such as a network stream or a memory
		/// buffer.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		template<class Type_>
		requires std::is_convertible_v<Type_, asset>
		std::unique_ptr<Type_> load_as(std::istream& input_stream, const resource_locator_type& location)
		{
			return assetfoo::dynamic_pointer_cast<Type_, std::default_delete<asset>>(load(input_stream, location));
		}


	protected:

		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the stream specified in \p input_stream.
		/// 
		/// @param input_stream The stream to load the asset from.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		virtual std::unique_ptr<asset> load(std::istream& input_stream) = 0;

		/// @brief Starts the loading process.
		/// 
		/// Initializes the asset loader and prepares it to load an asset.
		/// 
		/// @param location The location of the resource to load.
		virtual void start(const resource_locator_type& location);

		/// @copydoc resource_locator_type::text
		string_type location_text() const noexcept;


	private:

		/// @brief The location of the resource file or resource containing the asset being
		///	loaded. The value of location_ must be set by the load, load_as, or start
		/// functions taking the resource location as a parameter. The value contained
		/// in location_ is only valid during a load operation.
		resource_locator_type location_;
	};

}
