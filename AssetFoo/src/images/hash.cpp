// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/images/hash.h>
#include <kaos/assetfoo/images/image.h>
#include <boost/uuid/detail/md5.hpp>


namespace hypertech::kaos::assetfoo::images
{

	using boost::uuids::detail::md5;

	std::array<uint32_t, 4> calculate_md5_hash(const image& img)
	{
		md5 hash;

		for (const auto& pixel : img.get_sequence())
		{
			std::array<image::pixel_type::component_value_type, 4> color_components;

			color_components[0] = pixel.R;
			color_components[1] = pixel.G;
			color_components[2] = pixel.B;
			color_components[3] = pixel.A;

			hash.process_bytes(color_components.data(), color_components.size());
		}

		md5::digest_type md5digest;
		hash.get_digest(md5digest);

		std::array<uint32_t, 4> digest;
		digest[0] = md5digest[0];
		digest[1] = md5digest[1];
		digest[2] = md5digest[2];
		digest[3] = md5digest[3];

		return digest;
	}

}
