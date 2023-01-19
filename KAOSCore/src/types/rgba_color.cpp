// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/rgba_color.h>
#include <stdexcept>


namespace hypertech::kaos::core::types
{

	float rgba_color::brightness() const
	{
		float max = std::max(R, std::max(G, B));
		float min = std::min(R, std::min(G, B));

		auto brightness = ((max + min) / 2.0f) / max_component_value_as<float>();

#ifdef _DEBUG
		if (brightness < 0.0f || brightness > 1.0f)
		{
			throw std::range_error("Calculated brightness exceeds bounds of allowable value");
		}
#endif

		return brightness;
	}

}
