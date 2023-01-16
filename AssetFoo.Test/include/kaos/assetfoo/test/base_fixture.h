// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/types/rgba_color.h>
#include <gtest/gtest.h>


namespace hypertech { namespace kaos { namespace assetfoo { namespace unittests
{

	class base_fixture : public ::testing::Test
	{
	protected:

		using color_type = core::types::rgba_color;

		struct test_colors
		{
			static const inline color_type black{ 0, 0, 0 };
			static const inline color_type dark_gray{ 85, 85, 85 };
			static const inline color_type light_gray{ 170, 170, 170 };
			static const inline color_type white{ 255, 255, 255 };

			static const inline color_type dark_red{ 85, 0, 0 };
			static const inline color_type medium_red{ 170, 0, 0 };
			static const inline color_type bright_red{ 255, 0, 0 };

			static const inline color_type dark_green{ 0, 85, 0 };
			static const inline color_type medium_green{ 0, 170, 0 };
			static const inline color_type bright_green{ 0, 255, 0 };

			static const inline color_type dark_blue{ 0, 0, 85 };
			static const inline color_type medium_blue{ 0, 0, 170 };
			static const inline color_type bright_blue{ 0, 0, 255 };

			static const inline color_type dark_yellow{ 255, 255, 0 };
			static const inline color_type medium_yellow{ 170, 170, 0 };
			static const inline color_type bright_yellow{ 85, 85, 0 };
		};
	};

}}}}
