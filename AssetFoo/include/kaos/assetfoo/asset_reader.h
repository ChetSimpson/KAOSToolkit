// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset.h>
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
		using filename_type = std::string;


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
		/// @param filename The name of the asset file to load.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		virtual std::unique_ptr<asset> load(const filename_type& filename);

		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the file specified in \p filename and returns it as the type
		/// specified in \p Type_.
		/// 
		/// @tparam Type_ The type (derived from asset) to load the asset as. 
		/// 
		/// @param filename The name of the asset file to load.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		template<class Type_>
		requires std::is_convertible_v<Type_, asset>
		std::unique_ptr<Type_, std::default_delete<asset>> load_as(const filename_type& filename)
		{
			return assetfoo::dynamic_pointer_cast<Type_, std::default_delete<asset>>(load(filename));
		}


		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the stream specified in \p input_stream.
		/// 
		/// @param input_stream The stream to load the asset from.
		/// @param source_name The name of the asset file being loaded. This may be a filename or
		/// another name describing the source of the asset such as a network stream or a memory
		/// buffer.
		/// 
		/// @return A pointer to the loaded asset.
		/// 
		/// @exception hypertech::kaos::core::exceptions::file_not_found_error Thrown if the file does not exist.
		/// @exception hypertech::kaos::core::exceptions::file_access_error Thrown if the file is not accessible due to locking or access rights.
		/// @exception hypertech::kaos::core::exceptions::file_format_error Thrown if an error is detected in the format of the asset file.
		virtual std::unique_ptr<asset> load(std::istream& input_stream, const filename_type& source_name);

		/// @brief Loads an asset.
		/// 
		/// Loads the asset from the stream specified in \p input_stream and returns it as the type
		/// specified in \p Type_.
		/// 
		/// @tparam Type_ The type (derived from asset) to load the asset as. 
		/// 
		/// @param input_stream The stream to load the asset from.
		/// @param source_name The name of the asset file being loaded. This may be a filename or
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
		std::unique_ptr<Type_> load_as(std::istream& input_stream, const filename_type& source_name)
		{
			return assetfoo::dynamic_pointer_cast<Type_, std::default_delete<asset>>(load(input_stream, source_name));
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


	protected:

		/// @brief The name of the source file or resource containing the asset being
		///	loaded. The value of source_name_ must be set by the load and load_as
		/// functions taking the source_name as a parameter. The value contained
		/// in source_name_ is only valid during a load operation.
		filename_type source_name_;
	};

}
