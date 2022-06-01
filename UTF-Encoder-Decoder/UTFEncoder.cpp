#include "UTFEncoder.h"

namespace utf {
	std::string encodeAsUTF8(const char* data);
	std::string encodeAsUTF8(const char16_t* data);
	std::string encodeAsUTF8(const char32_t* data);

	std::string encodeAsUTF16BE(const char* data);
	std::string encodeAsUTF16BE(const char16_t* data);
	std::string encodeAsUTF16BE(const char32_t* data);
	
	std::string encodeAsUTF16LE(const char* data);
	std::string encodeAsUTF16LE(const char16_t* data);
	std::string encodeAsUTF16LE(const char32_t* data);

	std::string encodeAsUTF32BE(const char* data);
	std::string encodeAsUTF32BE(const char16_t* data);
	std::string encodeAsUTF32BE(const char32_t* data);

	std::string encodeAsUTF32LE(const char* data);
	std::string encodeAsUTF32LE(const char16_t* data);
	std::string encodeAsUTF32LE(const char32_t* data);

	std::string getBOM(Encoding encoding) {
		switch (encoding) {
		case Encoding::UTF8     : return "\xEF\xBB\xBF";
		case Encoding::UTF16_BE : return "\xFE\xFF";
		case Encoding::UTF16_LE : return "\xFF\xFE";
		case Encoding::UTF32_BE : return "\x00\x00\xFE\xFF";
		case Encoding::UTF32_LE : return "\xFF\xFE\x00\x00";
		default : return "";
		}
	}
}