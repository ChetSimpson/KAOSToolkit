// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#pragma once
#include <boost/numeric/conversion/cast.hpp>
#include <cstdint>
#include <cmath>
#include <type_traits>


namespace hypertech { namespace kaos { namespace core { namespace types
{

	/// @brief Vector containing two values x and y.
	/// 
	/// @tparam Type_ The value type for x and y members
	/// @tparam AllowFastFloatCompare_ if false compares the difference
	/// of values to the epsilon of Type_
	template<class Type_, bool AllowFastFloatCompare_ = false>
	class vector2 final
	{
	public:

		/// @brief The value type of the vector2
		using value_type = Type_;


	public:

		/// @brief Create a default vector2.
		/// 
		/// Creates a default vector2 with x and y set to 0.
		vector2() noexcept = default;

		/// @brief Creates a vector2
		/// 
		/// @param x The x value of the vector
		/// @param y The y value of the vector
		vector2(value_type x, value_type y) noexcept
			: x(x), y(y)
		{}

		/// @brief Creates a copy of a vector2
		/// @param other The vector2 to create a copy of
		vector2(const vector2& other) noexcept = default;

		/// @brief Creates a copy of a vector2 that uses a different type for Type_ (value_type).
		/// 
		/// @tparam OtherType_ The Type_ parameter used to define the other vector2.
		/// @tparam OtherAllowFastFloatCompare_ The fast comparison flag used by the other vector2.
		/// 
		/// @param other The vector2 to make a copy of.
		template<class OtherType_, bool OtherAllowFastFloatCompare_>
		vector2(const vector2<OtherType_, OtherAllowFastFloatCompare_>& other)
			:
			x(::boost::numeric_cast<Type_>(other.x)),
			y(::boost::numeric_cast<Type_>(other.y))
		{}


		/// @brief Compares two vector2 instances fo equality.
		/// 
		/// Compares two vector2 instances for equality. If the values being compared
		/// are decimal types no special handling is performed.
		/// 
		/// @param other The instance of vector2 to comapre against.
		/// 
		/// @return true if they are equal; false if they are not.
		inline bool operator==(const vector2& other) const noexcept
		requires ::std::is_integral_v<Type_> || std::bool_constant<AllowFastFloatCompare_>::value
		{
			return x == other.x && y == other.y;
		}


		/// @brief Compares two vector2 instances fo inequality.
		/// 
		/// Compares two vector2 instances for inequality. If the values being compared
		/// are decimal types no special handling is performed.
		/// 
		/// @param other The instance of vector2 to comapre against.
		/// 
		/// @return true if they are not equal; false if they are.
		inline bool operator!=(const vector2& other) const noexcept
		requires ::std::is_integral_v<Type_> || std::bool_constant<AllowFastFloatCompare_>::value
		{
			return x != other.x || y != other.y;
		}


		/// @brief Compares two vector2 instances fo equality.
		/// 
		/// Compares two vector2 instances for equality. If the values being compared
		/// are decimal types the comparison is performed within the tolerance of the
		/// host platform epsilon value
		/// 
		/// @param other The instance of vector2 to comapre against.
		/// 
		/// @return true if they are equal; false if they are not.
		inline bool operator==(const vector2& other) const noexcept
		requires ::std::is_floating_point_v<Type_> && std::bool_constant<!AllowFastFloatCompare_>::value
		{
			return
				::std::fabs(x - other.x) < ::std::numeric_limits<Type_>::epsilon()
				&& ::std::fabs(y - other.y) < ::std::numeric_limits<Type_>::epsilon();
		}


		/// @brief Compares two vector2 instances fo inequality.
		/// 
		/// Compares two vector2 instances for inequality. If the values being compared
		/// are decimal types the comparison is performed within the tolerance of the
		/// host platform epsilon value
		/// 
		/// @param other The instance of vector2 to comapre against.
		/// 
		/// @return true if they are not equal; false if they are.
		inline bool operator!=(const vector2& other) const noexcept
		requires ::std::is_floating_point_v<Type_> && std::bool_constant<!AllowFastFloatCompare_>::value
		{
			return
				::std::fabs(x - other.x) >= ::std::numeric_limits<Type_>::epsilon()
				|| ::std::fabs(y - other.y) >= ::std::numeric_limits<Type_>::epsilon();
		}


		/// @brief Copies an instance of vector2 using copy semantics
		/// 
		/// Copies the width and height in other to another instance.
		/// 
		/// @param other The instance of vector2 to copy.
		/// 
		/// @return *this
		vector2& operator=(const vector2& other) noexcept
		{
			x = other.x;
			y = other.y;

			return *this;
		}

		/// @brief Copies an instance of vector2 using move semantics
		/// 
		/// Copies the width and height in other to another instance. After the copy the instance referred
		/// to by \p other is left in its original state.
		/// 
		/// @param other The instance of vector2 to copy.
		/// 
		/// @return *this
		vector2& operator=(vector2&& other) noexcept
		{
			x = other.x;
			y = other.y;

			return *this;
		}


		/// @brief Adds one vector2 to another
		/// 
		/// @param other The instance of vector2 on the right side of the expression.
		/// 
		/// @return An instance of vector2 containing the result of the addition.
		vector2 operator+(const vector2& other) const noexcept
		{
			return vector2(x + other.x, y + other.y);
		}


		/// @brief Adds one vector2 to another
		/// 
		/// @param other The instance of vector2 on the right side of the expression.
		/// 
		/// @return *this
		vector2& operator+=(const vector2& other) noexcept
		{
			x += other.x;
			y += other.y;

			return *this;
		}


		/// @brief Subtracts one vector2 from another
		/// 
		/// @param other The instance of vector2 on the right side of the expression.
		/// 
		/// @return An instance of vector2 containing the result of the subtraction.
		vector2 operator-(const vector2& other) const noexcept
		{
			return vector2(x - other.x, y - other.y);
		}


		/// @brief Subtracts one vector2 to another
		/// 
		/// @param other The instance of vector2 on the right side of the expression.
		/// 
		/// @return *this
		vector2& operator-=(const vector2& other) noexcept
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}


		/// @brief Multiplies one vector2 with another
		/// 
		/// @param other The instance of vector2 on the right side of the expression.
		/// 
		/// @return An instance of vector2 containing the result of the multiplication.
		vector2 operator*(const vector2& other) const
		{
			return vector2(x * other.x, y * other.y);
		}


		/// @brief Multiplies one vector2 to another
		/// 
		/// @param other The instance of vector2 on the right side of the expression.
		/// 
		/// @return *this
		vector2& operator*=(const vector2& other) noexcept
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}


		/// @brief Divides one vector2 by another
		/// 
		/// @param other The instance of vector2 on the right side of the expression.
		/// 
		/// @return An instance of vector2 containing the result of the division.
		vector2 operator/(const vector2& other) const noexcept
		{
			return vector2(x / other.x, y / other.y);
		}


		/// @brief Divides one vector2 by another
		/// 
		/// @param other The instance of vector2 on the right side of the division.
		/// 
		/// @return *this
		vector2& operator/=(const vector2& other) noexcept
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}


	public:

		/// @brief The first (X) value of the vector
		value_type x = 0;
		/// @brief The second (Y) value of the vector
		value_type y = 0;
	};


	using vector2i = vector2<int64_t>;
	using vector2u = vector2<uint64_t>;
	using vector2f = vector2<float>;
	using vector2d = vector2<double>;
	using vector2f_fast = vector2<float, true>;
	using vector2d_fast = vector2<double, true>;

}}}}
