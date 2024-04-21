// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/assetfoo/asset_reader.h>
#include <kaos/assetfoo/test/base_fixture.h>


namespace hypertech::kaos::assetfoo::unittests
{

	class asset_loader_fixture : public base_fixture
	{
	protected:

		using base_fixture::base_fixture;


	protected:

		static inline const auto test_resource_locator = asset_reader::resource_locator_type("<TEST>");
		static inline const auto string_stream_locator = asset_reader::resource_locator_type("<string stream>");
	};

}
