// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset_reader.h>
#include <string>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors { namespace gimp
{

	/// @brief Asset reader for GIMP palette files.
	///
	/// This class loads GIMP (GNU Image Manipulation Program) palette file.
	class gimp_palette_reader : public ascii_asset_reader
	{
	protected:

		/// @brief Type used to store strings.
		using string_type = std::string;

		/// @brief Text fields used in the GIMP palette file format.
		struct header_fields
		{
			static const string_type name;		//!<	Text of the name field encountered in the GIMP palette file format
			static const string_type columns;	//!<	Text of the columns field encountered in the GIMP palette file format
		};


	public:

		using asset_reader::load;

		std::unique_ptr<asset> load(std::istream& input_stream, const filename_type& source_name) override;
	};


	/// @brief Used to indicate that a GIMP palette reader object may be "moved".
	/// 
	/// Used to indicate that a GIMP palette reader object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of gimp_palette_reader
	inline gimp_palette_reader&& move(gimp_palette_reader& value)
	{
		return static_cast<gimp_palette_reader&&>(value);
	}

}}}}}
