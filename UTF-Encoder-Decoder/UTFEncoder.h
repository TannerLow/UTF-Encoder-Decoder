#pragma once
#include <vector>
#include <string>
#include "Encoding.h"

namespace utf {
	std::string encodeAsUTF8(const char* data);
	std::string encodeAsUTF8(const char16_t* data);
	std::string encodeAsUTF8(const char32_t* data);

	std::string encodeAsUTF16BE(const char* data);
	std::string encodeAsUTF16LE(const char* data);
	std::string encodeAsUTF16BE(const char16_t* data);
	std::string encodeAsUTF16LE(const char16_t* data);
	std::string encodeAsUTF16BE(const char32_t* data);
	std::string encodeAsUTF16LE(const char32_t* data);

	std::string encodeAsUTF32BE(const char* data);
	std::string encodeAsUTF32LE(const char* data);
	std::string encodeAsUTF32BE(const char16_t* data);
	std::string encodeAsUTF32LE(const char16_t* data);
	std::string encodeAsUTF32BE(const char32_t* data);
	std::string encodeAsUTF32LE(const char32_t* data);

	std::string getBOM(Encoding encoding);
}