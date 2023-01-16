// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <kaos/core/memory.h>
#include <memory>


namespace hypertech { namespace kaos { namespace assetfoo
{

	/// @brief Base class for all asset types
	class asset
	{
	public:

		/// @brief Create an asset
		asset() noexcept = default;

		/// @brief Create a copy of an asset
		/// 
		/// @param other The asset to make a copy of
		asset(const asset& other) noexcept = default;

		/// @brief Create an asset using move semantics
		/// 
		/// @param other The instance to initialize the new asset with.
		asset(asset&& other) noexcept = default;

		/// @brief Defaulted destructor
		virtual ~asset() noexcept = default;
	};


	/// @brief Creates a new instance of std::unique_ptr whose stored pointer is obtained
	/// from \p from's stored pointer using a cast expression.
	/// 
	/// Creates a new instance of std::unique_ptr whose stored pointer is obtained from
	/// \p from's stored pointer using a cast expression.
	/// 
	///	If \p from is empty, so is the new unique_ptr (but its stored pointer is not
	///	necessarily null). Otherwise, the new unique_ptr will share ownership with
	/// the initial value of \p from, except that it is empty if the dynamic_cast
	/// performed by dynamic_pointer_cast returns a null pointer.
	/// 
	/// @tparam ToType_ Type to convert to
	/// @tparam Deleter_ Type of deleter function
	/// 
	/// @param from Instance to convert
	/// 
	/// @return Returns a std::unique pointer containing the address of the converted 
	template<class ToType_, class Deleter_>
	std::unique_ptr<ToType_, Deleter_> dynamic_pointer_cast(std::unique_ptr<asset, Deleter_>&& from) noexcept
	{
		return core::dynamic_pointer_cast<ToType_, asset, Deleter_>(move(from));
	}

}}}
