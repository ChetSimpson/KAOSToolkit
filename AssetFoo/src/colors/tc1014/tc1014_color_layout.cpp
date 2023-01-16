// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/assetfoo/colors/tc1014/tc1014_color_layout.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace colors { namespace tc1014
{

	const tc1014_color_layout::tc1014bitfield_type tc1014_color_layout::red_component_bitfield_({ "red", 1, 5, 1, 2 });
	const tc1014_color_layout::tc1014bitfield_type tc1014_color_layout::green_component_bitfield_({ "green", 1, 4, 1, 1});
	const tc1014_color_layout::tc1014bitfield_type tc1014_color_layout::blue_component_bitfield_({ "blue", 1, 3, 1, 0 });
	const tc1014_color_layout::empty_bitfield_type tc1014_color_layout::alpha_component_bitfield_("alpha");


	tc1014_color_layout::tc1014_color_layout()
		: color_layout(
			red_component_bitfield_,
			green_component_bitfield_,
			blue_component_bitfield_,
			alpha_component_bitfield_)
	{}

}}}}}
