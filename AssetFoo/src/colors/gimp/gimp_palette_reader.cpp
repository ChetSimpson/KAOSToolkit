// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/gimp/gimp_palette_reader.h>
#include <kaos/assetfoo/colors/color_map.h>
#include <kaos/core/exceptions.h>
#include <kaos/core/utility/string.h>
#include <fstream>
#include <filesystem>


//
//	Format extracted from https://github.com/GNOME/gimp/blob/master/app/core/gimppalette-load.c
//
namespace hypertech::kaos::assetfoo::colors::gimp
{
	namespace exceptions = core::exceptions;

	using color_type = color_map::color_type;

	const gimp_palette_reader::string_type gimp_palette_reader::header_fields::name = "Name: ";
	const gimp_palette_reader::string_type gimp_palette_reader::header_fields::columns = "Columns: ";


	std::unique_ptr<asset> gimp_palette_reader::load(std::istream& input_stream, const filename_type& source_name)
	{
		std::vector<string_type> lines;
		for (string_type line; getline(input_stream, line);)
		{
			lines.emplace_back(move(line));
		}

		if (lines.empty())
		{
			throw exceptions::file_format_error("Unable to load empty GIMP palette file '" + source_name + "'");
		}


		auto line_ptr = lines.cbegin();
		if (!line_ptr->starts_with("GIMP Palette"))
		{
			throw exceptions::file_format_error("Incorrect header in GIMP palette file '" + source_name + "'");
		}

		++line_ptr;
		if (line_ptr != lines.cend() && line_ptr->starts_with(header_fields::name))
		{
			++line_ptr;

			//	The columns specifier is only used by the visual editor in GIMP and
			//	does not indicate any variance in the palette file itself.
			if (line_ptr != lines.cend() && line_ptr->starts_with(header_fields::columns))
			{
				++line_ptr;
			}
		}

		color_map::collection_type colors;
		for (; line_ptr != lines.cend(); ++line_ptr)
		{
			if (line_ptr->empty() || line_ptr->front() == '#')
			{
				continue;
			}

			std::istringstream color_parser(*line_ptr);
			
			//	Read in level of red color component
			int red;
			if(!(color_parser >> red))
			{
				throw exceptions::file_format_error("Unable to parse red color component in line '" + *line_ptr +"' from file '" + source_name + "'");
			}

			if (red < 0 || red > 255)
			{
				throw exceptions::file_format_error("Red color level is outside the expected range of 0 to 255 in line '" + *line_ptr +"' from file '" + source_name + "'");
			}

			//	Read in level of green color component
			int green;
			if(!(color_parser >> green))
			{
				throw exceptions::file_format_error("Unable to parse green color component in line '" + *line_ptr +"' from file '" + source_name + "'");
			}

			if (green < 0 || green > 255)
			{
				throw exceptions::file_format_error("Green color level is outside the expected range of 0 to 255 in line '" + *line_ptr +"' from file '" + source_name + "'");
			}

			//	Read in level of blue color component
			int blue;
			if(!(color_parser >> blue))
			{
				throw exceptions::file_format_error("Unable to parse blue color component in line '" + *line_ptr +"' from file '" + source_name + "'");
			}

			if (blue < 0 || blue > 255)
			{
				throw exceptions::file_format_error("Blue color level is outside the expected range of 0 to 255 in line '" + *line_ptr +"' from file '" + source_name + "'");
			}

			//auto comment = algorithm::trim({ std::istreambuf_iterator<char>(color_parser), {} });

			colors.push_back( {
				static_cast<color_type::component_value_type>(red),
				static_cast<color_type::component_value_type>(green),
				static_cast<color_type::component_value_type>(blue) } );
		}

		return std::make_unique<color_map>(move(colors));
	}

}
