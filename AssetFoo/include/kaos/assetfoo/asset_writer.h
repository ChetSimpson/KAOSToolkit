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

	/// @brief Abstract class for writing media files as KAOS assets.
	///
	/// This class provides the base interface and functional support for
	/// writing media files as KAOS intermediate asset objects.
	/// 
	///	\todo Add ability to pass options to the readers allowing control over
	/// the importing process such as the type of conversion to occur for RGB
	/// and native colorspaces.
	class asset_writer
	{
	public:

		/// @brief Defines the type representing a filename.
		using filename_type = std::string;
		/// @brief The base type for assets to write
		using asset_type = asset;


	public:

		/// @brief Create an asset reader
		asset_writer() = default;

		/// @brief Create a copy of an asset reader
		/// 
		/// @param other The asset_writer to make a copy of
		asset_writer(const asset_writer& other) = default;

		/// @brief Create an asset reader using move semantics
		/// 
		/// @param other The instance to initialize the new asset reader with.
		asset_writer(asset_writer&& other) = default;


		/// @brief Defaulted destructor.
		virtual ~asset_writer() = default;

		/// @brief Loads an asset.
		/// 
		/// Writes an asset to the file specified in \p filename.
		/// 
		/// @param filename The name of the asset file to write.
		/// @param asset The asset to write.
		/// 
		/// FIXME: Add exceptions thrown
		virtual void write(const filename_type& filename, const asset_type& asset);


		/// @brief Loads an asset.
		/// 
		/// Writes an asset to the stream specified in \p output_stream.
		/// 
		/// @param output_stream The stream to write the asset to.
		/// @param asset The asset to write.
		/// @param source_name The name of the asset file being written. This may be a filename or
		/// another name describing the source of the asset such as a network stream or a memory
		/// buffer.
		/// 
		/// FIXME: Add exceptions thrown
		virtual void write(std::ostream& output_stream, const asset_type& asset, const filename_type& source_name) = 0;
	};

}
