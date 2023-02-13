// Copyright (c) 2023 HyperTech Gaming and Chet Simpson
//
// Distributed under the MIT License. See accompanying LICENSE file or copy
// at https://github.com/ChetSimpson/KAOSToolkit/blob/main/LICENSE
#include <kaos/core/io/binary_reader.h>
#include <kaos/core/exceptions.h>
#include <kaos/test/gtest-extensions.h>
#include <boost/numeric/conversion/cast.hpp>
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>
//#include <fstream>


// FIXME: This set of tests do not cover the reader.bad() flag

namespace hypertech::kaos::core::io::unittests
{

	namespace
	{

		struct big_endian_ordering
		{
			static constexpr binary_reader::ordering_type type()
			{
				return binary_reader::ordering_type::big;
			}
		};

		struct little_endian_ordering
		{
			static constexpr binary_reader::ordering_type type()
			{
				return binary_reader::ordering_type::little;
			}
		};

		template<class Type_, class OrderingType_>
		struct typed_test_data;

		template<class OrderingType_>
		struct typed_test_data<void, OrderingType_>
		{
			static const auto ordering = OrderingType_::type();
			static inline const auto data = std::string("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F", 16);
		};


		template<class Type_, class OrderingType_>
		requires std::is_same_v<Type_, bool>
			struct typed_test_data<Type_, OrderingType_>
		{
			using value_type = Type_;
			static const auto ordering = OrderingType_::type();
			static inline const auto data = std::string("\x00\x01\x02\x03\x00\x05\x06\x07\x00\x09\x0A\x0B\x00\x0D\x0E\x0F", 16);
			static inline const auto expected = std::array<value_type, 16>{
				false, true, true, true, false, true, true, true,
				false, true, true, true, false, true, true, true
			};
		};


		template<class Type_, class OrderingType_>
		requires std::is_same_v<Type_, int8_t> || std::is_same_v<Type_, uint8_t>
			struct typed_test_data<Type_, OrderingType_> : typed_test_data<void, OrderingType_>
		{
			using value_type = Type_;
			static inline const auto expected = std::array<value_type, 16>{
				0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
			};
		};

		template<class Type_, class OrderingType_>
		requires std::is_same_v<Type_, int16_t> || std::is_same_v<Type_, uint16_t>
			struct typed_test_data<Type_, OrderingType_> : typed_test_data<void, OrderingType_>
		{
			using value_type = Type_;
			static inline const auto expected = std::array<value_type, 8>{
				0x0001, 0x0203, 0x0405, 0x0607, 0x0809, 0x0a0b, 0x0c0d, 0x0e0f
			};
		};

		template<class Type_, class OrderingType_>
		requires std::is_same_v<Type_, int32_t> || std::is_same_v<Type_, uint32_t>
			struct typed_test_data<Type_, OrderingType_> : typed_test_data<void, OrderingType_>
		{
			using value_type = Type_;
			static inline const auto expected = std::array<value_type, 4>{
				0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F
			};
		};

		template<class Type_, class OrderingType_>
		requires std::is_same_v<Type_, int64_t> || std::is_same_v<Type_, uint64_t>
			struct typed_test_data<Type_, OrderingType_> : typed_test_data<void, OrderingType_>
		{
			using value_type = Type_;
			static inline const auto expected = std::array<value_type, 2>{
				0x0001020304050607, 0X08090A0B0C0D0E0F
			};
		};


		template<class TestDataType_>
		class test_binary_reader : public ::testing::Test
		{
		protected:

			using test_data = TestDataType_;
			static const auto ordering_ = TestDataType_::ordering;

			template<class Type_>
			constexpr Type_ byteswap_if(Type_ value)
			{
				if constexpr (ordering_ == binary_reader::ordering_type::native)
				{
					value = hypertech::kaos::core::utility::byteswap(value);
				}

				return value;
			}
		};





		const std::array<uint8_t, 16> general_test_data
		{
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
		};

		const auto string_test_data(std::string(general_test_data.begin(), general_test_data.end()));
	}


#pragma region operator bool
	TEST(test_binary_reader, operator_bool)
	{
		std::istringstream input;
		binary_reader reader(input);

		ASSERT_TRUE(reader);
		ASSERT_FALSE(!reader);
	}

	TEST(test_binary_reader, operator_bool_past_end)
	{
		std::istringstream input(" ");
		binary_reader reader(input);

		uint8_t value;
		ASSERT_TRUE(reader.read(value));
		ASSERT_FALSE(reader.read(value));

		input = std::istringstream(" ");
		ASSERT_FALSE(!reader.read(value));
		ASSERT_TRUE(!reader.read(value));
	}
#pragma endregion




#pragma region good_bad_fail_eof
	//	FIXME: Move into test_binary_ios
	TEST(test_binary_reader, status_flags_defaults)
	{
		std::istringstream input;
		binary_reader reader(input);

		ASSERT_TRUE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_FALSE(reader.fail());
		ASSERT_FALSE(reader.eof());
	}

	TEST(test_binary_reader, status_flags_after_eof)
	{
		std::istringstream input;
		binary_reader reader(input);

		uint8_t value;
		ASSERT_FALSE(reader.read(value));

		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_TRUE(reader.eof());
	}


	TEST(test_binary_reader, status_flags_on_closed_stream)
	{
		std::istringstream input;
		binary_reader reader(input);

		uint8_t value;
		ASSERT_FALSE(reader.read(value));

		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_TRUE(reader.eof());
	}

	TEST(test_binary_reader, status_flags_on_seek_out_of_bounds)
	{
		std::istringstream input(string_test_data);
		binary_reader reader(input);

		//	Beyond upper bounds
		ASSERT_FALSE(reader.seekg(string_test_data.size() + 1));
		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_FALSE(reader.eof());

		//	Beyond lower bounds
		input = std::istringstream(string_test_data);
		ASSERT_FALSE(reader.seekg(-1));
		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_FALSE(reader.eof());

	}
#pragma endregion




#pragma region read
	TYPED_TEST_CASE_P(test_binary_reader);

	TYPED_TEST_P(test_binary_reader, read)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);
		binary_reader reader(input, test_data::ordering);

		for (const auto expected_value : test_data::expected)
		{
			typename test_data::value_type value = 0;
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, this->byteswap_if(expected_value));
		}
	}

	TYPED_TEST_P(test_binary_reader, read_past_eof)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);

		binary_reader reader(input, test_data::ordering);
		reader.exceptions(binary_reader::allbits);

		reader.seekg(test_data::data.size());

		ASSERT_TRUE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_FALSE(reader.fail());
		ASSERT_FALSE(reader.eof());

		typename test_data::value_type value = 0;
		EXPECT_THROW(reader.read(value), std::ios::failure);
		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_TRUE(reader.eof());
	}

	TYPED_TEST_P(test_binary_reader, read_direct)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);
		binary_reader reader(input, test_data::ordering);

		for (const auto expected_value : test_data::expected)
		{
			ASSERT_EQ(reader.read<test_data::value_type>(), this->byteswap_if(expected_value));
		}
	}

	TYPED_TEST_P(test_binary_reader, read_direct_past_eof)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);

		binary_reader reader(input, test_data::ordering);
		reader.exceptions(binary_reader::allbits);

		reader.seekg(test_data::data.size());

		ASSERT_TRUE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_FALSE(reader.fail());
		ASSERT_FALSE(reader.eof());

		EXPECT_THROW(DEBUG_DiscardResult(reader.read<test_data::value_type>()), std::ios::failure);
		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_TRUE(reader.eof());
	}

	TYPED_TEST_P(test_binary_reader, read_streamed)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);
		binary_reader reader(input, test_data::ordering);

		for (const auto expected_value : test_data::expected)
		{
			typename test_data::value_type value = 0;
			ASSERT_TRUE(reader >> value);
			ASSERT_EQ(value, this->byteswap_if(expected_value));
		}
	}

	TYPED_TEST_P(test_binary_reader, read_span)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);
		binary_reader reader(input, test_data::ordering);

		std::array<test_data::value_type, test_data::expected.size()> read_data = {};
		EXPECT_TRUE(reader.read(std::span<test_data::value_type>(read_data)));

		for (auto i(0U); i < test_data::expected.size(); ++i)
		{
			ASSERT_EQ(read_data[i], this->byteswap_if(test_data::expected[i]));
		}
	}

	TYPED_TEST_P(test_binary_reader, read_span_streamed)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);
		binary_reader reader(input, test_data::ordering);

		std::array<test_data::value_type, test_data::expected.size()> read_data = {};
		EXPECT_TRUE(reader >> std::span<test_data::value_type>(read_data));

		for (auto i(0U); i < test_data::expected.size(); ++i)
		{
			ASSERT_EQ(read_data[i], this->byteswap_if(test_data::expected[i]));
		}
	}

	TYPED_TEST_P(test_binary_reader, read_array_direct)
	{
		using test_data = TypeParam;

		std::istringstream input(test_data::data);
		binary_reader reader(input, test_data::ordering);

		auto read_data = reader.read_array<test_data::value_type, test_data::expected.size()>();
		EXPECT_TRUE(reader);

		for (auto i(0U); i < test_data::expected.size(); ++i)
		{
			ASSERT_EQ(read_data[i], this->byteswap_if(test_data::expected[i]));
		}
	}

	TYPED_TEST_P(test_binary_reader, read_array_direct_past_eof)
	{
		using test_data = TypeParam;

		std::istringstream input;
		binary_reader reader(input, test_data::ordering);

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult((reader.read_array<test_data::value_type, 1>())),
			exceptions::end_of_file_error,
			"file error: attempt to read past end of file");
	}

	TYPED_TEST_P(test_binary_reader, read_vector_direct)
	{
		if constexpr (!std::is_same_v<typename TypeParam::value_type, bool>)
		{
			using test_data = TypeParam;

			std::istringstream input(test_data::data);
			binary_reader reader(input, test_data::ordering);

			auto read_data = reader.read_vector<test_data::value_type>(test_data::expected.size());
			EXPECT_TRUE(reader);

			for (auto i(0U); i < test_data::expected.size(); ++i)
			{
				ASSERT_EQ(read_data[i], this->byteswap_if(test_data::expected[i]));
			}
		}
	}

	TYPED_TEST_P(test_binary_reader, read_vector_direct_past_eof)
	{
		if constexpr (!std::is_same_v<typename TypeParam::value_type, bool>)
		{
			using test_data = TypeParam;

			std::istringstream input;
			binary_reader reader(input, test_data::ordering);

			EXPECT_THROWS_MESSAGE(
				DEBUG_DiscardResult(reader.read_vector<test_data::value_type>(1)),
				exceptions::end_of_file_error,
				"file error: attempt to read past end of file");
		}
	}


	REGISTER_TYPED_TEST_CASE_P(
		test_binary_reader,
		read,
		read_past_eof,
		read_direct,
		read_direct_past_eof,
		read_streamed,
		read_span,
		read_span_streamed,
		read_array_direct,
		read_array_direct_past_eof,
		read_vector_direct,
		read_vector_direct_past_eof);

	using read_testing_types = testing::Types<
		typed_test_data<bool, big_endian_ordering>,
		typed_test_data<bool, big_endian_ordering>,
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

	INSTANTIATE_TYPED_TEST_CASE_P(test_binary_reader, test_binary_reader, read_testing_types);

	TEST(test_binary_reader, read_string_direct)
	{
		const std::string test_data("this is a string\0hello word", 27);
		std::istringstream input(test_data);
		binary_reader reader(input);

		auto read_data = reader.read_string(test_data.size(), false);
		EXPECT_TRUE(reader);
		EXPECT_EQ(read_data, test_data);
	}

	TEST(test_binary_reader, read_string_direct_truncated)
	{
		const std::string test_data("this is a string\0hello word", 27);
		const std::string expected_data("this is a string");
		std::istringstream input(test_data);
		binary_reader reader(input);

		auto read_data = reader.read_string(test_data.size(), true);
		EXPECT_TRUE(reader);
		EXPECT_EQ(read_data, expected_data);
	}

	TEST(test_binary_reader, read_string_direct_past_eof)
	{
		std::istringstream input;
		binary_reader reader(input);

		EXPECT_THROWS_MESSAGE(
			DEBUG_DiscardResult(reader.read_string(1)),
			exceptions::end_of_file_error,
			"file error: attempt to read past end of file");
	}


	TEST(test_binary_reader, read_enum)
	{
		enum class test_enum
		{
			value0,
			value1,
			value2
		};

		const std::string test_data("\x00\x00\x00\x01\x00\x02", 6);
		std::istringstream input(test_data);
		binary_reader reader(input, binary_reader::ordering_type::big);

		EXPECT_EQ((reader.read_enum<uint16_t, test_enum>()), test_enum::value0);
		EXPECT_EQ((reader.read_enum<uint16_t, test_enum>()), test_enum::value1);
		EXPECT_EQ((reader.read_enum<uint16_t, test_enum>()), test_enum::value2);
	}

#pragma endregion




#pragma region tellg, seekg, and skip
	TEST(test_binary_reader, skip)
	{
		std::istringstream input("hello there fine world");
		binary_reader reader(input);

		ASSERT_TRUE(reader.skipg(6));
		EXPECT_EQ(reader.read_string(5), "there");
		ASSERT_TRUE(reader.skipg(6));
		EXPECT_EQ(reader.read_string(5), "world");
	}

	TEST(test_binary_reader, skip_past_end_of_file)
	{
		static const std::string test_string("hello there fine world");
		std::istringstream input(test_string);
		binary_reader reader(input);

		ASSERT_TRUE(reader.skipg(6));	//	Skip past "hello "
		EXPECT_EQ(reader.read_string(5), "there");
		EXPECT_EQ(reader.tellg(), 11);
		ASSERT_THROWS_MESSAGE(reader.skipg(16), exceptions::file_error, "file error: attempt to read past end of file");
		EXPECT_EQ(reader.tellg(), -1);
	}

	TEST(test_binary_reader, tellg)
	{
		std::istringstream input(string_test_data);
		binary_reader reader(input);

		uint8_t value;

		ASSERT_EQ(reader.tellg(), 0);
		for (auto i(0U); i < general_test_data.size(); ++i)
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[i]);
			ASSERT_EQ(reader.tellg(), i + 1);
		}
	}

	TEST(test_binary_reader, seekg_absolute)
	{
		std::istringstream input(string_test_data);
		binary_reader reader(input);

		uint8_t value;

		ASSERT_EQ(reader.tellg(), 0);
		for (auto i(0U); i < general_test_data.size(); ++i)
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[i]);
			ASSERT_EQ(reader.tellg(), i + 1);
		}

		ASSERT_TRUE(reader.seekg(0));
		ASSERT_EQ(reader.tellg(), 0);
		for (auto i(0U); i < general_test_data.size(); ++i)
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[i]);
			ASSERT_EQ(reader.tellg(), i + 1);
		}

		const binary_reader::pos_type data_size(general_test_data.size());
		const binary_reader::pos_type mid_position(data_size / 2);
		ASSERT_TRUE(reader.seekg(mid_position));
		ASSERT_EQ(reader.tellg(), mid_position);
		for (auto i(mid_position); i < data_size; )
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[boost::numeric_cast<size_t>(static_cast<std::streamoff>(i))]);

			i += 1;
			ASSERT_EQ(reader.tellg(), i);
		}
	}


	TEST(test_binary_reader, seekg_from_current)
	{
		std::istringstream input(string_test_data);
		binary_reader reader(input);

		const binary_reader::pos_type data_size(general_test_data.size());
		const binary_reader::pos_type mid_position(data_size / 2);
		const binary_reader::pos_type offset(4);

		uint8_t value;

		ASSERT_EQ(reader.tellg(), 0);
		ASSERT_TRUE(reader.seekg(mid_position, std::ios_base::cur));
		ASSERT_EQ(reader.tellg(), mid_position);
		for (auto i(mid_position); i < data_size; )
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[boost::numeric_cast<size_t>(static_cast<std::streamoff>(i))]);

			i += 1;
			ASSERT_EQ(reader.tellg(), i);
		}

		ASSERT_TRUE(reader.seekg(-(data_size - offset), std::ios_base::cur));
		ASSERT_EQ(reader.tellg(), offset);
		for (auto i(offset); i < data_size; )
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[boost::numeric_cast<size_t>(static_cast<std::streamoff>(i))]);

			i += 1;
			ASSERT_EQ(reader.tellg(), i );
		}
	}

	TEST(test_binary_reader, seekg_from_begin)
	{
		std::istringstream input(string_test_data);
		binary_reader reader(input);

		const binary_reader::pos_type data_size(general_test_data.size());
		const binary_reader::pos_type offset(4);
		uint8_t value;

		ASSERT_EQ(reader.tellg(), 0);
		for (auto i(0U); i < data_size; ++i)
		{
			ASSERT_TRUE(reader.read(value));
		}

		ASSERT_EQ(reader.tellg(), data_size);
		ASSERT_TRUE(reader.seekg(offset, std::ios_base::beg));
		ASSERT_EQ(reader.tellg(), offset);
		for (auto i(offset); i < data_size; )
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[boost::numeric_cast<size_t>(static_cast<std::streamoff>(i))]);

			i += 1;
			ASSERT_EQ(reader.tellg(), i);
		}
	}

	TEST(test_binary_reader, seekg_from_end)
	{
		std::istringstream input(string_test_data);
		binary_reader reader(input);

		const binary_reader::pos_type data_size(general_test_data.size());
		const binary_reader::pos_type offset(4);
		uint8_t value;

		ASSERT_EQ(reader.tellg(), 0);
		ASSERT_TRUE(reader.seekg(-(data_size - offset), std::ios_base::end));
		ASSERT_EQ(reader.tellg(), offset);
		for (auto i(offset); i < data_size; )
		{
			ASSERT_TRUE(reader.read(value));
			ASSERT_EQ(value, general_test_data[boost::numeric_cast<size_t>(static_cast<std::streamoff>(i))]);

			i += 1;
			ASSERT_EQ(reader.tellg(), i);
		}
	}
#pragma endregion


#pragma region exceptions
	//	FIXME: Move into test_binary_ios
	TEST(test_binary_reader, general_get_set_exceptions)
	{
		std::istringstream input;
		binary_reader reader(input);

		EXPECT_EQ(reader.exceptions(), input.exceptions());
		EXPECT_EQ((reader.exceptions(binary_reader::goodbit), input.exceptions()), binary_reader::goodbit);
		EXPECT_EQ((reader.exceptions(binary_reader::eofbit), input.exceptions()), binary_reader::eofbit);
		EXPECT_EQ((reader.exceptions(binary_reader::failbit), input.exceptions()), binary_reader::failbit);
		EXPECT_EQ((reader.exceptions(binary_reader::badbit), input.exceptions()), binary_reader::badbit);
		EXPECT_EQ((reader.exceptions(binary_reader::allbits), input.exceptions()), binary_reader::allbits);
		EXPECT_EQ((reader.exceptions(binary_reader::goodbit), input.exceptions()), binary_reader::goodbit);
	}

	TEST(test_binary_reader, general_throw_exception_on_eof)
	{
		std::istringstream input(" ");
		binary_reader reader(input);

		reader.exceptions(binary_reader::allbits);

		uint8_t value;
		EXPECT_TRUE(reader.read(value));
		EXPECT_THROW(reader.read(value), std::ios::failure);
		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_TRUE(reader.eof());
	}

	TEST(test_binary_reader, general_throw_exception_on_seek_out_of_lower_bounds)
	{
		std::istringstream input(" ");
		binary_reader reader(input);

		reader.exceptions(binary_reader::allbits);

		EXPECT_THROW(reader.seekg(-1), std::ios::failure);
		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_FALSE(reader.eof());
	}


	TEST(test_binary_reader, general_throw_exception_on_seek_out_of_upper_bounds)
	{
		std::istringstream input(" ");
		binary_reader reader(input);

		reader.exceptions(binary_reader::allbits);

		EXPECT_THROW(reader.seekg(2), std::ios::failure);
		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_FALSE(reader.eof());
	}
#pragma endregion


	TEST(test_binary_reader, clear_flags)
	{
		std::istringstream input;
		binary_reader reader(input);

		uint8_t value;
		ASSERT_FALSE(reader.read(value));

		ASSERT_FALSE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_TRUE(reader.fail());
		ASSERT_TRUE(reader.eof());

		reader.clear();
		ASSERT_TRUE(reader.good());
		ASSERT_FALSE(reader.bad());
		ASSERT_FALSE(reader.fail());
		ASSERT_FALSE(reader.eof());
	}

}
