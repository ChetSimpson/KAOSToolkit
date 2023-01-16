// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <array>


namespace hypertech { namespace kaos { namespace assetfoo { namespace images
{

	class image;

	/// @brief Calculates the MD5 hash value of an image.
	/// 
	/// @param img the image to calcualte the hash of.
	/// 
	/// @return The hash value as 4 32 bit unsigned integers.
	std::array<uint32_t, 4> calculate_md5_hash(const image& img);

}}}}
