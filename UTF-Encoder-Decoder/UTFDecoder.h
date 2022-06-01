#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include "Encoding.h"

//std::vector<uint16_t> decodeToInt16(const std::string& encoded);
//std::vector<uint16_t> decodeToInt16(const char* encoded);

namespace utf {
	Encoding getEncoding(const std::string& encoded, bool assumeUTF16 = true);
	Encoding getEncoding(const char* encoded, bool assumeUTF16 = true);
	Encoding getEncoding(std::ifstream& file, bool assumeUTF16 = true);

	std::u16string decodeToU16(const std::string& encoded);
	std::u16string decodeToU16(const char* encoded);
	std::u32string decodeToU32(const std::string& encoded);
	std::u32string decodeToU32(const char* encoded);

	std::u16string decodeUTF8toU16(const std::string& encoded);
	std::u16string decodeUTF8toU16(const char* encoded);
	std::u32string decodeUTF8toU32(const std::string& encoded);
	std::u32string decodeUTF8toU32(const char* encoded);

	std::u16string decodeUTF16toU16(const std::string& encoded);
	std::u16string decodeUTF16toU16(const char* encoded);
	std::u16string decodeUTF16toU16(const char16_t* encoded);
	std::u32string decodeUTF16toU32(const std::string& encoded);
	std::u32string decodeUTF16toU32(const char* encoded);
	std::u32string decodeUTF16toU32(const char16_t* encoded);

	std::u32string decodeUTF32toU32(const std::string& encoded);
	std::u32string decodeUTF32toU32(const char* encoded);
	std::u32string decodeUTF32toU32(const char16_t* encoded);
	std::u32string decodeUTF32toU32(const char32_t* encoded);
}