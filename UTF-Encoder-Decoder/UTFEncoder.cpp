#include "UTFEncoder.h"

namespace utf {
// helpers
	struct EncodedBytes {
		char data[4];
		uint8_t size;
	};

	EncodedBytes encodeValueToUTF8(uint32_t value) {
		EncodedBytes encoded;
		if (value < 0x80) {
			encoded.data[0] = value;
			encoded.size = 1;
		}
		else if (value < 0x800) {
			encoded.data[1] = 0b10000000 | (value & 0b00111111);
			value >>= 6;
			encoded.data[0] = 0b11000000 | (value & 0b00011111);
			encoded.size = 2;
		}
		else if (value < 0x10000) {
			encoded.data[2] = 0b10000000 | (value & 0b00111111);
			value >>= 6;
			encoded.data[1] = 0b10000000 | (value & 0b00111111);
			value >>= 6;
			encoded.data[0] = 0b11100000 | (value & 0b00001111);
			encoded.size = 3;
		}
		else {
			encoded.data[3] = 0b10000000 | (value & 0b00111111);
			value >>= 6;
			encoded.data[2] = 0b10000000 | (value & 0b00111111);
			value >>= 6;
			encoded.data[1] = 0b10000000 | (value & 0b00111111);
			value >>= 6;
			encoded.data[0] = 0b11110000 | (value & 0b00000111);
			encoded.size = 4;
		}

		return encoded;
	}


// Implementation
	std::string encodeAsUTF8(const char* data, const size_t size, const bool includeBOM) {
		std::string encoded;

		if (includeBOM) {
			encoded = getBOM(Encoding::UTF8);
		}

		for (int i = 0; i < size; i++) {
			if (data[i] & 0x80) { // needs 2-byte representation
				EncodedBytes encodedBytes = encodeValueToUTF8(data[i]);
				encoded += encodedBytes.data[0];
				encoded += encodedBytes.data[1];
			}
			else {
				encoded += data[i];
			}
		}

		return encoded;
	}

	std::string encodeAsUTF8(const char16_t* data, const size_t size, const bool includeBOM);
	std::string encodeAsUTF8(const char32_t* data, const size_t size, const bool includeBOM);

	std::string encodeAsUTF16BE(const char* data, const size_t size);
	std::string encodeAsUTF16BE(const char16_t* data, const size_t size);
	std::string encodeAsUTF16BE(const char32_t* data, const size_t size);

	std::string encodeAsUTF16LE(const char* data, const size_t size);
	std::string encodeAsUTF16LE(const char16_t* data, const size_t size);
	std::string encodeAsUTF16LE(const char32_t* data, const size_t size);

	std::string encodeAsUTF32BE(const char* data, const size_t size);
	std::string encodeAsUTF32BE(const char16_t* data, const size_t size);
	std::string encodeAsUTF32BE(const char32_t* data, const size_t size);

	std::string encodeAsUTF32LE(const char* data, const size_t size);
	std::string encodeAsUTF32LE(const char16_t* data, const size_t size);
	std::string encodeAsUTF32LE(const char32_t* data, const size_t size);

	std::string getBOM(Encoding encoding) {
		switch (encoding) {
		case Encoding::UTF8     : return "\xEF\xBB\xBF";
		case Encoding::UTF16_BE : return "\xFE\xFF";
		case Encoding::UTF16_LE : return "\xFF\xFE";
		case Encoding::UTF32_BE : return std::string("\x00\x00\xFE\xFF", 4);
		case Encoding::UTF32_LE : return std::string("\xFF\xFE\x00\x00", 4);
		default : return "";
		}
	}
}