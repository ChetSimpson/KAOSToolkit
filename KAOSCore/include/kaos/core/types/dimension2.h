// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <boost/numeric/conversion/cast.hpp>
#include <cstdint>
#include <cmath>
#include <type_traits>


namespace hypertech::kaos::core::types
{

	/// @brief 2D dimension containing two values width and height.
	/// 
	/// @tparam Type_ The value type for width and height members
	/// @tparam AllowFastFloatCompare_ if false compares the difference
	/// of values to the epsilon of Type_
	template<class Type_, bool AllowFastFloatCompare_ = false>
	class dimension2 final
	{
	public:

		/// @brief The value type of the dimension2
		using value_type = Type_;


	public:

		/// @brief Create a default dimension2.
		/// 
		/// Creates a default dimension2 with width and height set to 0.
		dimension2() noexcept = default;

		/// @brief Creates a dimension2
		/// 
		/// @param width The width value of the dimension
		/// @param height The height value of the dimension
		dimension2(value_type width, value_type height) noexcept
			: width(width), height(height)
		{}

		/// @brief Creates a copy of a dimension2
		/// @param other The dimension2 to create a copy of
		dimension2(const dimension2& other) noexcept = default;

		/// @brief Creates a copy of a dimension2 that uses a different type for Type_ (value_type).
		/// 
		/// @tparam OtherType_ The Type_ parameter used to define the other dimension2.
		/// @tparam OtherAllowFastFloatCompare_ The fast comparison flag used by the other dimension2.
		/// 
		/// @param other The dimension2 to make a copy of.
		template<class OtherType_, bool OtherAllowFastFloatCompare_>
		dimension2(const dimension2<OtherType_, OtherAllowFastFloatCompare_>& other)
			:
			width(::boost::numeric_cast<Type_>(other.width)),
			height(::boost::numeric_cast<Type_>(other.height))
		{}


		/// @brief Compares two dimension2 instances fo equality.
		/// 
		/// Compares two dimension2 instances for equality. If the values being compared
		/// are decimal types no special handling is performed.
		/// 
		/// @param other The instance of dimension2 to comapre against.
		/// 
		/// @return true if they are equal; false if they are not.
		inline bool operator==(const dimension2& other) const noexcept
		requires ::std::is_integral_v<Type_> || std::bool_constant<AllowFastFloatCompare_>::value
		{
			return width == other.width && height == other.height;
		}


		/// @brief Compares two dimension2 instances fo inequality.
		/// 
		/// Compares two dimension2 instances for inequality. If the values being compared
		/// are decimal types no special handling is performed.
		/// 
		/// @param other The instance of dimension2 to comapre against.
		/// 
		/// @return true if they are not equal; false if they are.
		inline bool operator!=(const dimension2& other) const noexcept
		requires ::std::is_integral_v<Type_> || std::bool_constant<AllowFastFloatCompare_>::value
		{
			return width != other.width || height != other.height;
		}


		/// @brief Compares two dimension2 instances fo equality.
		/// 
		/// Compares two dimension2 instances for equality. If the values being compared
		/// are decimal types the comparison is performed within the tolerance of the
		/// host platform epsilon value
		/// 
		/// @param other The instance of dimension2 to comapre against.
		/// 
		/// @return true if they are equal; false if they are not.
		inline bool operator==(const dimension2& other) const noexcept
		requires ::std::is_floating_point_v<Type_> && std::bool_constant<!AllowFastFloatCompare_>::value
		{
			return
				::std::fabs(width - other.width) < ::std::numeric_limits<Type_>::epsilon()
				&& ::std::fabs(height - other.height) < ::std::numeric_limits<Type_>::epsilon();
		}


		/// @brief Compares two dimension2 instances fo inequality.
		/// 
		/// Compares two dimension2 instances for inequality. If the values being compared
		/// are decimal types the comparison is performed within the tolerance of the
		/// host platform epsilon value
		/// 
		/// @param other The instance of dimension2 to comapre against.
		/// 
		/// @return true if they are not equal; false if they are.
		inline bool operator!=(const dimension2& other) const noexcept
		requires ::std::is_floating_point_v<Type_> && std::bool_constant<!AllowFastFloatCompare_>::value
		{
			return
				::std::fabs(width - other.width) >= ::std::numeric_limits<Type_>::epsilon()
				|| ::std::fabs(height - other.height) >= ::std::numeric_limits<Type_>::epsilon();
		}


		/// @brief Copies an instance of dimension2 using copy semantics
		/// 
		/// Copies the width and height in other to another instance.
		/// 
		/// @param other The instance of dimension2 to copy.
		/// 
		/// @return *this
			dimension2& operator=(const dimension2& other) noexcept
		{
			width = other.width;
			height = other.height;

			return *this;
		}

		/// @brief Copies an instance of dimension2 using move semantics
		/// 
		/// Copies the width and height in other to another instance. After the copy the instance referred
		/// to by \p other is left in its original state.
		/// 
		/// @param other The instance of dimension2 to copy.
		/// 
		/// @return *this
		dimension2& operator=(dimension2&& other) noexcept
		{
			width = other.width;
			height = other.height;

			return *this;
		}


		/// @brief Adds one dimension2 to another
		/// 
		/// @param other The instance of dimension2 on the right side of the expression.
		/// 
		/// @return An instance of dimension2 containing the result of the addition.
		dimension2 operator+(const dimension2& other) const noexcept
		{
			return dimension2(width + other.width, height + other.height);
		}


		/// @brief Adds one dimension2 to another
		/// 
		/// @param other The instance of dimension2 on the right side of the expression.
		/// 
		/// @return *this
		dimension2& operator+=(const dimension2& other) noexcept
		{
			width += other.width;
			height += other.height;

			return *this;
		}


		/// @brief Subtracts one dimension2 from another
		/// 
		/// @param other The instance of dimension2 on the right side of the expression.
		/// 
		/// @return An instance of dimension2 containing the result of the subtraction.
		dimension2 operator-(const dimension2& other) const noexcept
		{
			return dimension2(width - other.width, height - other.height);
		}


		/// @brief Subtracts one dimension2 to another
		/// 
		/// @param other The instance of dimension2 on the right side of the expression.
		/// 
		/// @return *this
		dimension2& operator-=(const dimension2& other) noexcept
		{
			width -= other.width;
			height -= other.height;

			return *this;
		}


		/// @brief Multiplies one dimension2 with another
		/// 
		/// @param other The instance of dimension2 on the right side of the expression.
		/// 
		/// @return An instance of dimension2 containing the result of the multiplication.
		dimension2 operator*(const dimension2& other) const
		{
			return dimension2(width * other.width, height * other.height);
		}


		/// @brief Multiplies one dimension2 to another
		/// 
		/// @param other The instance of dimension2 on the right side of the expression.
		/// 
		/// @return *this
		dimension2& operator*=(const dimension2& other) noexcept
		{
			width *= other.width;
			height *= other.height;

			return *this;
		}


		/// @brief Divides one dimension2 by another
		/// 
		/// @param other The instance of dimension2 on the right side of the expression.
		/// 
		/// @return An instance of dimension2 containing the result of the division.
		dimension2 operator/(const dimension2& other) const noexcept
		{
			return dimension2(width / other.width, height / other.height);
		}


		/// @brief Divides one dimension2 by another
		/// 
		/// @param other The instance of dimension2 on the right side of the division.
		/// 
		/// @return *this
		dimension2& operator/=(const dimension2& other) noexcept
		{
			width /= other.width;
			height /= other.height;

			return *this;
		}


	public:

		/// @brief The width of the dimension
		value_type width = 0;
		/// @brief The height of the dimension
		value_type height = 0;
	};


	using dimension2i = dimension2<int64_t>;
	using dimension2u = dimension2<uint64_t>;
	using dimension2f = dimension2<float>;
	using dimension2d = dimension2<double>;
	using dimension2f_fast = dimension2<float, true>;
	using dimension2d_fast = dimension2<double, true>;

}
