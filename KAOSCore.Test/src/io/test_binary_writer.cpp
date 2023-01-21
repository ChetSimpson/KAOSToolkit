// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/io/binary_writer.h>
#include <kaos/core/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <boost/numeric/conversion/cast.hpp>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>
#include <fstream>


// FIXME: This set of tests do not cover the writer.bad() flag

namespace hypertech::kaos::core::io::unittests
{

	namespace
	{

		struct big_endian_ordering
		{
			static constexpr binary_writer::ordering_type type()
			{
				return binary_writer::ordering_type::big;
			}
		};

		struct little_endian_ordering
		{
			static constexpr binary_writer::ordering_type type()
			{
				return binary_writer::ordering_type::little;
			}
		};

		template<class Type_, class OrderingType_>
		struct typed_test_data;

		template<class OrderingType_>
		struct typed_test_data<void, OrderingType_>
		{
			static const auto ordering = OrderingType_::type();
		};

		template<>
		struct typed_test_data<void, big_endian_ordering>
		{
			static const auto ordering = big_endian_ordering::type();
			static inline const auto expected = std::string("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F", 16);
		};


		template<class Type_, class OrderingType_>
		requires std::is_same_v<Type_, bool>
		struct typed_test_data<Type_, OrderingType_>
		{
			using value_type = Type_;
			static const auto ordering = OrderingType_::type();
			static inline const auto expected = std::string("\x00\x01\x01\x01\x00\x01\x01\x01\x00\x01\x01\x01\x00\x01\x01\x01", 16);
			static inline const auto data = std::array<value_type, 16>{
				false, true, true, true, false, true, true, true,
				false, true, true, true, false, true, true, true
			};
		};


		template<class Type_, class OrderingType_>
		requires std::is_same_v<Type_, int8_t> || std::is_same_v<Type_, uint8_t> || std::is_same_v<Type_, char>
		struct typed_test_data<Type_, OrderingType_>
		{
			using value_type = Type_;

			static const auto ordering = OrderingType_::type();
			static inline const auto expected = std::string("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F", 16);
			static inline const auto data = std::array<value_type, 16>{
				0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
			};
		};

		template<class Type_>
		requires std::is_same_v<Type_, int16_t> || std::is_same_v<Type_, uint16_t>
		struct typed_test_data<Type_, big_endian_ordering> : typed_test_data<void, big_endian_ordering>
		{
			using value_type = Type_;

			static const auto ordering = big_endian_ordering::type();
			static inline const auto data = std::array<value_type, 8>{
				0x0001, 0x0203, 0x0405, 0x0607, 0x0809, 0x0a0b, 0x0c0d, 0x0e0f
			};
		};

		template<class Type_>
		requires std::is_same_v<Type_, int16_t> || std::is_same_v<Type_, uint16_t>
			struct typed_test_data<Type_, little_endian_ordering>
		{
			using value_type = Type_;

			static const auto ordering = little_endian_ordering::type();
			static inline const auto expected = std::string("\x01\x00\x03\x02\x05\x04\x07\x06\x09\x08\x0B\x0A\x0D\x0C\x0F\x0E", 16);
			static inline const auto data = std::array<value_type, 8>{
				0x0001, 0x0203, 0x0405, 0x0607, 0x0809, 0x0a0b, 0x0c0d, 0x0e0f
			};
		};

		template<class Type_>
		requires std::is_same_v<Type_, int32_t> || std::is_same_v<Type_, uint32_t>
			struct typed_test_data<Type_, big_endian_ordering> : typed_test_data<void, big_endian_ordering>
		{
			using value_type = Type_;

			static const auto ordering = big_endian_ordering::type();
			static inline const auto data = std::array<value_type, 4>{
				0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F
			};
		};

		template<class Type_>
		requires std::is_same_v<Type_, int32_t> || std::is_same_v<Type_, uint32_t>
		struct typed_test_data<Type_, little_endian_ordering>
		{
			using value_type = Type_;

			static const auto ordering = little_endian_ordering::type();
			static inline const auto expected = std::string("\x03\x02\x01\x00\x07\x06\x05\x04\x0B\x0A\x09\x08\x0F\x0E\x0D\x0C", 16);
			static inline const auto data = std::array<value_type, 4>{
				0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F
			};
		};

		template<class Type_>
		requires std::is_same_v<Type_, int64_t> || std::is_same_v<Type_, uint64_t>
			struct typed_test_data<Type_, big_endian_ordering> : typed_test_data<void, big_endian_ordering>
		{
			using value_type = Type_;

			static const auto ordering = big_endian_ordering::type();
			static inline const auto data = std::array<value_type, 2>{
				0x0001020304050607, 0X08090A0B0C0D0E0F
			};
		};

		template<class Type_>
		requires std::is_same_v<Type_, int64_t> || std::is_same_v<Type_, uint64_t>
			struct typed_test_data<Type_, little_endian_ordering>
		{
			using value_type = Type_;

			static const auto ordering = little_endian_ordering::type();
			static inline const auto expected = std::string("\x07\x06\x05\x04\x03\x02\x01\x00\x0F\x0E\x0D\x0C\x0B\x0A\x09\x08", 16);
			static inline const auto data = std::array<value_type, 2>{
				0x0001020304050607, 0X08090A0B0C0D0E0F
			};
		};







		template<class TestDataType_>
		class test_binary_writer : public ::testing::Test
		{
		protected:

			using test_data = TestDataType_;
			static const auto ordering_ = TestDataType_::ordering;

			template<class Type_>
			constexpr Type_ byteswap_if(Type_ value)
			{
				if constexpr (ordering_ == binary_writer::ordering_type::native)
				{
					value = hypertech::kaos::core::utility::byteswap(value);
				}

				return value;
			}
		};


		const std::array<uint8_t, 16> general_test_data_low
		{
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
		};

		const std::array<uint8_t, 16> general_test_data_high
		{
			0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
			0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
		};

		const std::array<uint8_t, 16> general_test_data_lowhigh
		{
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
		};

		const auto string_test_data_low(std::string(general_test_data_low.begin(), general_test_data_low.end()));
		const auto string_test_data_high(std::string(general_test_data_high.begin(), general_test_data_high.end()));
		const auto string_test_data_lowhigh(std::string(general_test_data_lowhigh.begin(), general_test_data_lowhigh.end()));

		const auto string_test_data_high_upper(std::string(
			general_test_data_high.begin() + (general_test_data_high.size() / 2),
			general_test_data_high.end()));
	}


#pragma region operator bool
	TEST(test_binary_writer, operator_bool_opened_stream)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer);
		ASSERT_FALSE(!writer);
	}

	TEST(test_binary_writer, operator_bool_write_to_closed_stream)
	{
		std::ofstream output;
		binary_writer writer(output);

		ASSERT_FALSE(writer.write(0));
		ASSERT_FALSE(writer);
		ASSERT_TRUE(!writer);
	}
#pragma endregion




#pragma region good_bad_fail
	TEST(test_binary_writer, status_flags_defaults)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer.good());
		ASSERT_FALSE(writer.bad());
		ASSERT_FALSE(writer.fail());
		ASSERT_FALSE(writer.eof());
	}

	TEST(test_binary_writer, status_flags_on_closed_fstream)
	{
		std::ofstream output;
		binary_writer writer(output);

		uint8_t value(100);
		ASSERT_FALSE(writer.write(value));

		ASSERT_FALSE(writer.good());
		ASSERT_TRUE(writer.bad());
		ASSERT_TRUE(writer.fail());
		ASSERT_FALSE(writer.eof());
	}

	TEST(test_binary_writer, status_flags_on_seek_out_of_bounds)
	{
		std::ostringstream output;
		binary_writer writer(output);

		//	Beyond upper bounds
		ASSERT_FALSE(writer.seekp(1));
		ASSERT_FALSE(writer.good());
		ASSERT_FALSE(writer.bad());
		ASSERT_TRUE(writer.fail());
		ASSERT_FALSE(writer.eof());

		//	Beyond lower bounds
		ASSERT_FALSE(writer.seekp(-1));
		ASSERT_FALSE(writer.good());
		ASSERT_FALSE(writer.bad());
		ASSERT_TRUE(writer.fail());
		ASSERT_FALSE(writer.eof());
	}

	TEST(test_binary_writer, clear_flags)
	{
		std::ofstream output;
		binary_writer writer(output);

		uint8_t value(100);
		ASSERT_FALSE(writer.write(value));

		ASSERT_FALSE(writer.good());
		ASSERT_TRUE(writer.bad());
		ASSERT_TRUE(writer.fail());
		ASSERT_FALSE(writer.eof());

		writer.clear();
		ASSERT_TRUE(writer.good());
		ASSERT_FALSE(writer.bad());
		ASSERT_FALSE(writer.fail());
		ASSERT_FALSE(writer.eof());
	}
#pragma endregion




#pragma region write
	TYPED_TEST_CASE_P(test_binary_writer);

	TYPED_TEST_P(test_binary_writer, write)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		for (auto value : test_data::data)
		{
			auto original_value(value);

			ASSERT_TRUE(writer.write(value));
			ASSERT_EQ(value, original_value);
		}

		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_stream)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		for (auto value : test_data::data)
		{
			auto original_value(value);

			ASSERT_TRUE(writer << value);
			ASSERT_EQ(value, original_value);
		}

		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_enum)
	{
		using test_data = TypeParam;

		enum test_enum : typename TypeParam::value_type {};

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		for (const auto value : test_data::data)
		{
			auto original_value(value);

			ASSERT_TRUE((writer.write<typename TypeParam::value_type>(test_enum(value))));
			ASSERT_EQ(value, original_value);
		}

		ASSERT_EQ(output.str(), test_data::expected);
	}


	TYPED_TEST_P(test_binary_writer, write_pair)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		for (size_t i(0U); i < test_data::data.size(); i += 2)
		{
			auto value(std::pair(test_data::data[i], test_data::data[i + 1U]));
			auto original_value(value);

			ASSERT_TRUE(writer.write(value));
			ASSERT_EQ(value, original_value);
		}

		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_pair_stream)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		for (size_t i(0U); i < test_data::data.size(); i += 2)
		{
			auto value(std::pair(test_data::data[i], test_data::data[i + 1U]));
			auto original_value(value);

			ASSERT_TRUE(writer << value);
			ASSERT_EQ(value, original_value);
		}

		ASSERT_EQ(output.str(), test_data::expected);
	}


	TYPED_TEST_P(test_binary_writer, write_array)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		std::array value(test_data::data);
		auto original_value(value);

		ASSERT_TRUE(writer.write(value));
		ASSERT_EQ(value, original_value);
		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_array_stream)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		std::array value(test_data::data);
		auto original_value(value);

		ASSERT_TRUE(writer << value);
		ASSERT_EQ(value, original_value);
		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_vector)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		std::vector<typename TypeParam::value_type> value(test_data::data.begin(), test_data::data.end());
		auto original_value(value);

		ASSERT_TRUE(writer.write(value));
		ASSERT_EQ(value, original_value);
		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_vector_stream)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		std::vector<typename TypeParam::value_type> value(test_data::data.begin(), test_data::data.end());
		auto original_value(value);

		ASSERT_TRUE(writer << value);
		ASSERT_EQ(value, original_value);
		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_span)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		std::span value(test_data::data.begin(), test_data::data.end());
		auto original_value(test_data::data);

		ASSERT_TRUE(writer.write(value));
		ASSERT_EQ(test_data::data, original_value);
		ASSERT_EQ(output.str(), test_data::expected);
	}

	TYPED_TEST_P(test_binary_writer, write_span_stream)
	{
		using test_data = TypeParam;

		std::ostringstream output;
		binary_writer writer(output, test_data::ordering);

		std::span value(test_data::data.begin(), test_data::data.end());
		auto original_value(test_data::data);

		ASSERT_TRUE(writer << value);
		ASSERT_EQ(test_data::data, original_value);
		ASSERT_EQ(output.str(), test_data::expected);
	}


	REGISTER_TYPED_TEST_CASE_P(
		test_binary_writer,
		write,
		write_stream,
		write_enum,
		write_pair,
		write_pair_stream,
		write_array,
		write_array_stream,
		write_vector,
		write_vector_stream,
		write_span,
		write_span_stream);

	using read_testing_types = testing::Types<
		typed_test_data<bool, big_endian_ordering>,
		typed_test_data<bool, big_endian_ordering>,
		typed_test_data<char, big_endian_ordering>,
		typed_test_data<char, little_endian_ordering>,
		typed_test_data<int8_t, big_endian_ordering>,
		typed_test_data<int8_t, little_endian_ordering>,
		typed_test_data<uint8_t, big_endian_ordering>,
		typed_test_data<uint8_t, little_endian_ordering>,
		typed_test_data<int16_t, big_endian_ordering>,
		typed_test_data<int16_t, little_endian_ordering>,
		typed_test_data<uint16_t, big_endian_ordering>,
		typed_test_data<uint16_t, little_endian_ordering>,
		typed_test_data<int32_t, big_endian_ordering>,
		typed_test_data<int32_t, little_endian_ordering>,
		typed_test_data<uint32_t, big_endian_ordering>,
		typed_test_data<uint32_t, little_endian_ordering>,
		typed_test_data<int64_t, big_endian_ordering>,
		typed_test_data<int64_t, little_endian_ordering>,
		typed_test_data<uint64_t, big_endian_ordering>,
		typed_test_data<uint64_t, little_endian_ordering>
	>;

	INSTANTIATE_TYPED_TEST_CASE_P(test_binary_writer, test_binary_writer, read_testing_types);

	TEST(test_binary_writer, write_string_big_endian)
	{
		std::ostringstream output;
		binary_writer writer(output, binary_writer::ordering_type::big);

		auto original_value(string_test_data_low);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(string_test_data_low, original_value);
		ASSERT_EQ(output.str(), string_test_data_low);
	}

	TEST(test_binary_writer, write_string_little_endian)
	{
		std::ostringstream output;
		binary_writer writer(output, binary_writer::ordering_type::little);

		auto original_value(string_test_data_low);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(string_test_data_low, original_value);
		ASSERT_EQ(output.str(), string_test_data_low);
	}

	TEST(test_binary_writer, write_string_stream_big_endian)
	{
		std::ostringstream output;
		binary_writer writer(output, binary_writer::ordering_type::big);

		auto original_value(string_test_data_low);

		ASSERT_TRUE(writer << string_test_data_low);
		ASSERT_EQ(string_test_data_low, original_value);
		ASSERT_EQ(output.str(), string_test_data_low);
	}

	TEST(test_binary_writer, write_string_stream_little_endian)
	{
		std::ostringstream output;
		binary_writer writer(output, binary_writer::ordering_type::little);

		auto original_value(string_test_data_low);

		ASSERT_TRUE(writer << string_test_data_low);
		ASSERT_EQ(string_test_data_low, original_value);
		ASSERT_EQ(output.str(), string_test_data_low);
	}
#pragma endregion




#pragma region tellg, seekg, and skip
	TEST(test_binary_writer, tellp_absolute)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size());
	}


	TEST(test_binary_writer, seekp_absolute)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size());
		ASSERT_TRUE(writer.seekp(0));
		ASSERT_EQ(size_t(writer.tellp()), 0U);
		ASSERT_TRUE(writer.write(string_test_data_high));
		ASSERT_EQ(output.str(), string_test_data_high);
	}

	TEST(test_binary_writer, seekp_from_begin)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size());

		ASSERT_TRUE(writer.seekp(string_test_data_low.size() / 2, std::ios_base::beg));	//	FIXME: std::ios_base::cur should be part of binary_ios
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size() / 2);

		ASSERT_TRUE(writer.write(string_test_data_high_upper));
		ASSERT_EQ(output.str(), string_test_data_lowhigh);
	}

	TEST(test_binary_writer, seekp_from_current)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size());
		ASSERT_TRUE(writer.seekp(string_test_data_low.size() / 2));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size() / 2);

		ASSERT_TRUE((writer.seekp(-int(string_test_data_low.size() / 2), std::ios_base::cur)));	//	FIXME: std::ios_base::cur should be part of binary_ios
		ASSERT_EQ(size_t(writer.tellp()), 0U);

		ASSERT_TRUE(writer.write(string_test_data_high));
		ASSERT_EQ(output.str(), string_test_data_high);
	}

	TEST(test_binary_writer, seekp_from_end)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size());
		ASSERT_TRUE(writer.seekp(0));
		ASSERT_TRUE((writer.write(std::span(string_test_data_low.data(), string_test_data_low.size() / 2))));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size() / 2);

		ASSERT_TRUE((writer.seekp(-int(string_test_data_low.size()), std::ios_base::end)));	//	FIXME: std::ios_base::cur should be part of binary_ios
		ASSERT_EQ(size_t(writer.tellp()), 0U);

		ASSERT_TRUE(writer.write(string_test_data_high));
		ASSERT_EQ(output.str(), string_test_data_high);
	}

	TEST(test_binary_writer, skipp_from_begin)
	{
		std::ostringstream output;
		binary_writer writer(output);

		ASSERT_TRUE(writer.write(string_test_data_low));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size());

		ASSERT_TRUE(writer.seekp(0));
		ASSERT_EQ(size_t(writer.tellp()), 0U);

		ASSERT_TRUE(writer.skipp(string_test_data_low.size() / 2));
		ASSERT_EQ(size_t(writer.tellp()), string_test_data_low.size() / 2);

		ASSERT_TRUE(writer.write(string_test_data_high_upper));
		ASSERT_EQ(output.str(), string_test_data_lowhigh);
	}
#pragma endregion




#pragma region exceptions
	//	FIXME: Move into test_binary_ios
	TEST(test_binary_writer, general_get_set_exceptions)
	{
		std::ostringstream output;
		binary_writer writer(output);

		EXPECT_EQ(writer.exceptions(), output.exceptions());
		EXPECT_EQ((writer.exceptions(binary_writer::goodbit), output.exceptions()), binary_writer::goodbit);
		EXPECT_EQ((writer.exceptions(binary_writer::eofbit), output.exceptions()), binary_writer::eofbit);
		EXPECT_EQ((writer.exceptions(binary_writer::failbit), output.exceptions()), binary_writer::failbit);
		EXPECT_EQ((writer.exceptions(binary_writer::badbit), output.exceptions()), binary_writer::badbit);
		EXPECT_EQ((writer.exceptions(binary_writer::allbits), output.exceptions()), binary_writer::allbits);
		EXPECT_EQ((writer.exceptions(binary_writer::goodbit), output.exceptions()), binary_writer::goodbit);
	}

	TEST(test_binary_writer, general_throw_exception_on_eof)
	{
		std::ofstream output;
		binary_writer writer(output);

		writer.exceptions(binary_writer::allbits);

		EXPECT_THROW(writer.write(10), exceptions::file_error);
		ASSERT_FALSE(writer.good());
		ASSERT_TRUE(writer.bad());
		ASSERT_TRUE(writer.fail());
		ASSERT_FALSE(writer.eof());
	}

	TEST(test_binary_writer, general_throw_exception_on_seek_out_of_lower_bounds)
	{
		std::ostringstream output(" ");
		binary_writer writer(output);

		writer.exceptions(binary_writer::allbits);

		EXPECT_THROW(writer.seekp(-1), exceptions::file_error);
		ASSERT_FALSE(writer.good());
		ASSERT_FALSE(writer.bad());
		ASSERT_TRUE(writer.fail());
		ASSERT_FALSE(writer.eof());
	}

	TEST(test_binary_writer, general_throw_exception_on_seek_out_of_upper_bounds)
	{
		std::ostringstream output(" ");
		binary_writer writer(output);

		writer.exceptions(binary_writer::allbits);

		EXPECT_THROW(writer.seekp(2), exceptions::file_error);
		ASSERT_FALSE(writer.good());
		ASSERT_FALSE(writer.bad());
		ASSERT_TRUE(writer.fail());
		ASSERT_FALSE(writer.eof());
	}
#pragma endregion

}
