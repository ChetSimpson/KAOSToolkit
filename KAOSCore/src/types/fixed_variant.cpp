// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/types/fixed_variant.h>
#include <kaos/core/exceptions.h>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <format>
#include <stdexcept>
#include <typeinfo>
#include <cmath>


namespace hypertech::kaos::core::types
{

	const fixed_variant::string_type fixed_variant::false_string_("false");
	const fixed_variant::string_type fixed_variant::true_string_("true");

#pragma region Helpers
	namespace
	{
		//	Adapted from boost issue #5494
		template <bool>
		struct lexical_precheck
		{
			template<typename StringType_>
			static inline bool is_negative(const StringType_&)
			{
				return false;
			}
		};

		//	Adapted from boost issue #5494
		template <>
		struct lexical_precheck<true>
		{
			template<typename StringType_>
			static bool is_negative(const StringType_ & str)
			{
				return !str.empty() && str[0] == '-';
			}
		};

		template<class OutputType_, class InputType_>
		static OutputType_ extended_numeric_cast(const InputType_& value)
		{
			if constexpr (std::is_unsigned<OutputType_>::value && !std::is_same<bool, InputType_>::value)
			{
				if (value < 0)
				{
					throw exceptions::negative_overflow_error(typeid(InputType_), typeid(OutputType_));
				}
			}

			try
			{
				return ::boost::numeric_cast<OutputType_>(value);
			}
			catch (::boost::numeric::positive_overflow&)
			{
				throw exceptions::positive_overflow_error(typeid(InputType_), typeid(OutputType_));
			}
			catch (::boost::numeric::negative_overflow&)
			{
				throw exceptions::negative_overflow_error(typeid(InputType_), typeid(OutputType_));
			}
		}

		class packedcolor_from_hex   // For use with boost::lexical_cast
		{
			fixed_variant::color_type::unsigned_packed_color_type value;

		public:

			operator fixed_variant::color_type::unsigned_packed_color_type() const
			{
				return value;
			}

			friend std::istream& operator>>( std::istream& in, packedcolor_from_hex& out_value )
			{
				in >> std::hex >> out_value.value;

				return in;
			}
		};

		template<class ReturnType_, class VariantType_>
		ReturnType_ as_vector_impl(VariantType_& variant, fixed_variant::tag_type source_type)
		{
			using tag_type = fixed_variant::tag_type;
			using vector_type = fixed_variant::vector_type;

			switch (source_type)
			{
			case tag_type::Empty:
				throw exceptions::empty_cast_error(typeid(void), typeid(vector_type));

			case tag_type::Boolean:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::boolean_type), typeid(vector_type));

			case tag_type::Integer:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::integer_type), typeid(vector_type));

			case tag_type::Unsigned:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::unsigned_type), typeid(vector_type));

			case tag_type::Float:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::float_type), typeid(vector_type));

			case tag_type::Double:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::double_type), typeid(vector_type));

			case tag_type::String:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::string_type), typeid(vector_type));

			case tag_type::Path:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::path_type), typeid(vector_type));

			case tag_type::Color:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::color_type), typeid(vector_type));

			case tag_type::Uuid:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::uuid_type), typeid(vector_type));

			case tag_type::Vector:
				return get<vector_type>(variant);

			case tag_type::Map:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::map_type), typeid(vector_type));
			}

			throw std::runtime_error("Unknown value type encountered in conversion to vector");
		}

		template<class ReturnType_, class VariantType_>
		ReturnType_ as_map_impl(VariantType_& variant, fixed_variant::tag_type source_type)
		{
			using tag_type = fixed_variant::tag_type;
			using map_type = fixed_variant::map_type;

			switch (source_type)
			{
			case tag_type::Empty:
				throw exceptions::empty_cast_error(typeid(void), typeid(map_type));

			case tag_type::Boolean:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::boolean_type), typeid(map_type));

			case tag_type::Integer:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::integer_type), typeid(map_type));

			case tag_type::Unsigned:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::unsigned_type), typeid(map_type));

			case tag_type::Float:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::float_type), typeid(map_type));

			case tag_type::Double:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::double_type), typeid(map_type));

			case tag_type::String:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::string_type), typeid(map_type));

			case tag_type::Path:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::path_type), typeid(map_type));

			case tag_type::Color:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::color_type), typeid(map_type));

			case tag_type::Uuid:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::uuid_type), typeid(map_type));

			case tag_type::Vector:
				throw exceptions::incompatible_type_error(typeid(fixed_variant::vector_type), typeid(map_type));

			case tag_type::Map:
				return get<map_type>(variant);
			}

			throw std::runtime_error("Unknown value type encountered in conversion to vector");
		}
	}
#pragma endregion


#pragma region Construction
	fixed_variant::fixed_variant(const boolean_type& value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(const integer_type& value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(const unsigned_type& value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(const float_type& value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(const double_type& value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(string_type value) noexcept
		: value_(move(value))
	{}

	fixed_variant::fixed_variant(const char* value) throw()
		: value_(string_type(value))
	{}

	fixed_variant::fixed_variant(path_type path) noexcept
		: value_(std::move(path))
	{}

	fixed_variant::fixed_variant(color_type value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(const uuid_type& value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(vector_type&& value) noexcept
		: value_(move(value))
	{}

	fixed_variant::fixed_variant(const vector_type &value) noexcept
		: value_(value)
	{}

	fixed_variant::fixed_variant(map_type&& value) noexcept
		: value_(move(value))
	{}

	fixed_variant::fixed_variant(const map_type &value) noexcept
		: value_(value)
	{}

#pragma endregion




#pragma region Assignment
	fixed_variant& fixed_variant::operator=(const nullptr_t&) noexcept
	{
		value_ = decltype(value_)();

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const boolean_type& value) noexcept
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const integer_type& value) noexcept
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const unsigned_type& value) noexcept
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const float_type& value) noexcept
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const double_type& value) noexcept
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(string_type value) noexcept
	{
		value_ = move(value);

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const char* value) noexcept
	{
		return operator=(string_type(value));
	}

	fixed_variant& fixed_variant::operator=(path_type value) noexcept
	{
		value_ = std::move(value);

		return *this;
	}

	fixed_variant& fixed_variant::operator=(color_type value) noexcept
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const uuid_type& value) noexcept
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const vector_type& value)
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(vector_type&& value) noexcept
	{
		value_ = move(value);

		return *this;
	}

	fixed_variant& fixed_variant::operator=(const map_type& value)
	{
		value_ = value;

		return *this;
	}

	fixed_variant& fixed_variant::operator=(map_type&& value) noexcept
	{
		value_ = move(value);

		return *this;
	}
#pragma endregion




#pragma region Conversion
	fixed_variant::boolean_type fixed_variant::as_boolean() const
	{
		return convert_value_to_primitive<boolean_type>();
	}

	fixed_variant::integer_type fixed_variant::as_integer() const
	{
		return convert_value_to_primitive<integer_type>();
	}

	fixed_variant::unsigned_type fixed_variant::as_unsigned() const
	{
		return convert_value_to_primitive<unsigned_type>();
	}

	fixed_variant::float_type fixed_variant::as_float() const
	{
		return convert_value_to_primitive<float_type>();
	}

	fixed_variant::double_type fixed_variant::as_double() const
	{
		return convert_value_to_primitive<double_type>();
	}

	fixed_variant::string_type fixed_variant::as_string() const
	{
		switch (type())
		{
		case tag_type::Empty:
			throw exceptions::empty_cast_error(typeid(void), typeid(string_type));

		case tag_type::Boolean:
			return std::get<boolean_type>(value_) ? "true" : "false";

		case tag_type::Integer:
			return std::to_string(std::get<integer_type>(value_));

		case tag_type::Unsigned:
			return std::to_string(std::get<unsigned_type>(value_));

		case tag_type::Float:
			return std::format("{}", std::get<float_type>(value_));

		case tag_type::Double:
			return std::format("{}", std::get<double_type>(value_));

		case tag_type::String:
			return std::get<string_type>(value_);

		case tag_type::Path:
			return std::get<path_type>(value_).string();

		case tag_type::Color:
			return std::format("#{:08X}", std::get<color_type>(value_).to_unsigned());

		case tag_type::Uuid:
			return boost::uuids::to_string(std::get<uuid_type>(value_));

		case tag_type::Vector:
			throw exceptions::incompatible_type_error(typeid(vector_type), typeid(string_type));

		case tag_type::Map:
			throw exceptions::incompatible_type_error(typeid(map_type), typeid(string_type));
		}

		throw std::runtime_error("Unknown value type encountered in conversion to string");
	}

	fixed_variant::path_type fixed_variant::as_path() const
	{
		switch (type())
		{
		case tag_type::Empty:
			throw exceptions::empty_cast_error(typeid(void), typeid(path_type));

		case tag_type::Boolean:
			throw exceptions::incompatible_type_error(typeid(boolean_type), typeid(path_type));

		case tag_type::Integer:
			throw exceptions::incompatible_type_error(typeid(integer_type), typeid(path_type));

		case tag_type::Unsigned:
			throw exceptions::incompatible_type_error(typeid(unsigned_type), typeid(path_type));

		case tag_type::Float:
			throw exceptions::incompatible_type_error(typeid(float_type), typeid(path_type));

		case tag_type::Double:
			throw exceptions::incompatible_type_error(typeid(double_type), typeid(path_type));

		case tag_type::String:
			return std::get<string_type>(value_);

		case tag_type::Path:
			return std::get<path_type>(value_);

		case tag_type::Color:
			throw exceptions::incompatible_type_error(typeid(color_type), typeid(path_type));

		case tag_type::Uuid:
			throw exceptions::incompatible_type_error(typeid(uuid_type), typeid(path_type));

		case tag_type::Vector:
			throw exceptions::incompatible_type_error(typeid(vector_type), typeid(path_type));

		case tag_type::Map:
			throw exceptions::incompatible_type_error(typeid(map_type), typeid(path_type));
		}

		throw std::runtime_error("Unknown value type encountered in conversion to string");
	}

	//	FIXME: We need a "source type" argument to handle converting different types to KAOS RGBA.
	fixed_variant::color_type fixed_variant::as_color() const
	{
		switch (type())
		{
		case tag_type::Empty:
			throw exceptions::empty_cast_error(typeid(void), typeid(color_type));

		case tag_type::Boolean:
			return std::get<boolean_type>(value_) ? color_type(255, 255, 255) : color_type();

		case tag_type::Integer:
			return color_type(extended_numeric_cast<color_type::signed_packed_color_type>(std::get<integer_type>(value_)));

		case tag_type::Unsigned:
			return color_type(extended_numeric_cast<color_type::unsigned_packed_color_type>(std::get<unsigned_type>(value_)));

		case tag_type::Float:
			return color_type(extended_numeric_cast<color_type::signed_packed_color_type>(std::get<float_type>(value_)));

		case tag_type::Double:
			return color_type(extended_numeric_cast<color_type::signed_packed_color_type>(std::get<double_type>(value_)));

		case tag_type::String:
			try
			{
				const auto& value(std::get<string_type>(value_));
				if (value.empty() || value[0] != '#')
				{
					throw exceptions::lexical_error(typeid(string_type), typeid(color_type));
				}

				return color_type(::boost::lexical_cast<packedcolor_from_hex>(value.data() + 1, value.size() - 1));
			}
			catch (::boost::bad_lexical_cast&)
			{
				throw exceptions::lexical_error(typeid(string_type), typeid(color_type));
			}

		case tag_type::Path:
			throw exceptions::incompatible_type_error(typeid(path_type), typeid(color_type));

		case tag_type::Color:
			return std::get<color_type>(value_);

		case tag_type::Uuid:
			throw exceptions::incompatible_type_error(typeid(uuid_type), typeid(color_type));

		case tag_type::Vector:
			throw exceptions::incompatible_type_error(typeid(vector_type), typeid(color_type));

		case tag_type::Map:
			throw exceptions::incompatible_type_error(typeid(map_type), typeid(color_type));
		}

		throw std::runtime_error("Unknown value type encountered in conversion to color");
	}

	fixed_variant::uuid_type fixed_variant::as_uuid() const
	{
		switch (type())
		{
		case tag_type::Empty:
			throw exceptions::empty_cast_error(typeid(void), typeid(uuid_type));

		case tag_type::Boolean:
			throw exceptions::incompatible_type_error(typeid(boolean_type), typeid(uuid_type));

		case tag_type::Integer:
			throw exceptions::incompatible_type_error(typeid(integer_type), typeid(uuid_type));

		case tag_type::Unsigned:
			throw exceptions::incompatible_type_error(typeid(unsigned_type), typeid(uuid_type));

		case tag_type::Float:
			throw exceptions::incompatible_type_error(typeid(float_type), typeid(uuid_type));

		case tag_type::Double:
			throw exceptions::incompatible_type_error(typeid(double_type), typeid(uuid_type));

		case tag_type::String:
			try
			{
				return boost::lexical_cast<uuid_type>(std::get<string_type>(value_));
			}
			catch (::boost::bad_lexical_cast& e)
			{
				throw exceptions::lexical_error(e.source_type(), e.target_type());
			}

		case tag_type::Path:
			throw exceptions::incompatible_type_error(typeid(path_type), typeid(uuid_type));

		case tag_type::Color:
			throw exceptions::incompatible_type_error(typeid(color_type), typeid(uuid_type));

		case tag_type::Uuid:
			return std::get<uuid_type>(value_);	//	FIXME: remove std::

		case tag_type::Vector:
			throw exceptions::incompatible_type_error(typeid(vector_type), typeid(uuid_type));

		case tag_type::Map:
			throw exceptions::incompatible_type_error(typeid(map_type), typeid(uuid_type));
		}

		throw std::runtime_error("Unknown value type encountered in conversion to uuid");
	}

	fixed_variant::vector_type& fixed_variant::as_vector()
	{
		return as_vector_impl<fixed_variant::vector_type&>(value_, type());
	}

	const fixed_variant::vector_type& fixed_variant::as_vector() const
	{
		return as_vector_impl<const fixed_variant::vector_type&>(value_, type());
	}

	fixed_variant::vector_type fixed_variant::as_vector_copy() const
	{
		return as_vector_impl<fixed_variant::vector_type>(value_, type());
	}

	fixed_variant::map_type& fixed_variant::as_map()
	{
		return as_map_impl<fixed_variant::map_type&>(value_, type());
	}

	const fixed_variant::map_type& fixed_variant::as_map() const
	{
		return as_map_impl<const fixed_variant::map_type&>(value_, type());
	}

	fixed_variant::map_type fixed_variant::as_map_copy() const
	{
		return as_map_impl<fixed_variant::map_type>(value_, type());
	}


	template<class OutputType_>
	OutputType_ fixed_variant::convert_value_to_primitive() const
	{
		switch (type())
		{
		case tag_type::Empty:
			throw exceptions::empty_cast_error(typeid(void), typeid(OutputType_));

		case tag_type::Boolean:
			return extended_numeric_cast<OutputType_>(std::get<boolean_type>(value_));

		case tag_type::Integer:
			return extended_numeric_cast<OutputType_>(std::get<integer_type>(value_));

		case tag_type::Unsigned:
			return extended_numeric_cast<OutputType_>(std::get<unsigned_type>(value_));

		case tag_type::Float:
			return extended_numeric_cast<OutputType_>(std::get<float_type>(value_));

		case tag_type::Double:
			return extended_numeric_cast<OutputType_>(std::get<double_type>(value_));

		case tag_type::String:
			try
			{
				//	Adapted from boost issue #5494
				const auto& value(std::get<string_type>(value_));
				const bool is_float(value.find('.') != string_type::npos);

				if constexpr (std::is_same<OutputType_, bool>::value)
				{
					if(!value.empty() && value[0] == '-')
					{
						throw exceptions::negative_overflow_error(typeid(string_type), typeid(OutputType_));
					}

					if(boost::iequals(value, false_string_))
					{
						return false;
					}

					if(boost::iequals(value, true_string_))
					{
						return true;
					}

					if (is_float)
					{
						auto result(::boost::lexical_cast<double>(value));
						if (result > 1.0)
						{
							throw exceptions::positive_overflow_error(typeid(string_type), typeid(OutputType_));
						}

						return result != 0.0;
					}

					return extended_numeric_cast<OutputType_>(::boost::lexical_cast<unsigned_type>(value));
				}

				if (lexical_precheck<std::is_unsigned<OutputType_>::value>::is_negative(value))
				{
					throw exceptions::negative_overflow_error(typeid(string_type), typeid(OutputType_));
				}

				if (is_float)
				{
					return extended_numeric_cast<OutputType_>(::boost::lexical_cast<double>(value));
				}

				return ::boost::lexical_cast<OutputType_>(value);
			}
			catch (::boost::bad_lexical_cast&)
			{
				throw exceptions::lexical_error(typeid(string_type), typeid(OutputType_));
			}

		case tag_type::Path:
			throw exceptions::incompatible_type_error(typeid(path_type), typeid(OutputType_));

		case tag_type::Color:

			if constexpr (std::is_same<OutputType_, bool>::value)
			{
				throw exceptions::incompatible_type_error(typeid(color_type), typeid(OutputType_));
			}

			if constexpr (std::is_unsigned<OutputType_>::value)
			{
				return extended_numeric_cast<OutputType_>(std::get<color_type>(value_).to_unsigned());
			}

			return extended_numeric_cast<OutputType_>(std::get<color_type>(value_).to_signed());

		case tag_type::Uuid:
			throw exceptions::incompatible_type_error(typeid(uuid_type), typeid(OutputType_));

		case tag_type::Vector:
			throw exceptions::incompatible_type_error(typeid(vector_type), typeid(OutputType_));

		case tag_type::Map:
			throw exceptions::incompatible_type_error(typeid(map_type), typeid(OutputType_));
		}

		throw std::runtime_error(std::string("Unknown type encountered in conversion to ") + typeid(OutputType_).name());
	}
#pragma endregion

}
