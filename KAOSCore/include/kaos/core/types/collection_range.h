// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once

namespace hypertech::kaos::core::types
{

	/// @brief Provides a range of data in a container based on begin and
	/// end iterators.
	/// 
	/// @tparam IteratorType_ Type of iterator
	template<class IteratorType_>
	struct collection_range
	{
		/// @brief The iterator type
		using iterator_type = IteratorType_;

		/// @brief Create a collection range
		/// @param begin Iterator referencing the first element in the range.
		/// @param end Iterator referencing the last element in the range.
		collection_range(iterator_type begin, iterator_type end)
			:
			begin_(begin),
			end_(end)
		{}

		/// @brief Returns the first iterator of the range
		/// @return An iterator referencing the first element in the range.
		iterator_type begin() const
		{
			return begin_;
		}

		/// @brief Returns the last iterator of the range
		/// @return An iterator referencing the last element in the range.
		iterator_type end() const
		{
			return end_;
		}


	private:

		iterator_type begin_;
		iterator_type end_;
	};

}
