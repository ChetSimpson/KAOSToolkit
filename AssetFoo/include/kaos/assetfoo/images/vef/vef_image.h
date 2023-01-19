// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/images/tc1014/tc1014_image.h>


namespace hypertech::kaos::assetfoo::images::vef
{

	/// @brief VEF Image
	///
	/// This class extends the \ref tc1014_image to provide additional details of an
	/// image converted from a VEF image file.
	class vef_image : public tc1014::tc1014_image
	{
	public:

		using tc1014_image::tc1014_image;
	};


	/// @brief Used to indicate that a VEF image object may be "moved".
	/// 
	/// Used to indicate that a VEF image object may be "moved from",
	/// i.e. allowing the efficient transfer of resources from \p value to
	/// another object.
	/// 
	/// In particular, move produces an xvalue expression that identifies
	/// its argument \p value. It is exactly equivalent to a static_cast to
	/// an rvalue reference type.
	/// 
	/// @param value The instance to be moved.
	/// 
	/// @return An rvalue reference to an instance of vef_image
	inline vef_image&& move(vef_image& value)
	{
		return static_cast<vef_image&&>(value);
	}

}
