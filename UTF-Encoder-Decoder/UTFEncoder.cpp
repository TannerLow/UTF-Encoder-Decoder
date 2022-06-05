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

	EncodedBytes encodeValueToUTF16(uint32_t value) {
		EncodedBytes encoded;
		if (value < 0xFFFF) {
			encoded.data[0] = (value & 0xFF00) >> 8;
			encoded.data[1] = value & 0x00FF;
			encoded.size = 2;
		}
		else {
			uint16_t highSurrogate = (value >> 10) + 0xD800;
			uint16_t lowSurrogate = (value & 0x3FF) + 0xDC00;
			encoded.data[0] = (highSurrogate >> 8) & 0xFF;
			encoded.data[1] = highSurrogate & 0xFF;
			encoded.data[2] = (lowSurrogate >> 8) & 0xFF;
			encoded.data[3] = lowSurrogate & 0xFF;
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

	std::string encodeAsUTF8(const char16_t* data, const size_t size, const bool includeBOM) {
		std::string encoded;

		if (includeBOM) {
			encoded = getBOM(Encoding::UTF8);
		}

		for (int i = 0; i < size; i++) {
			if (data[i] > 0x7F) { // needs 2+ byte representation
				EncodedBytes encodedBytes = encodeValueToUTF8(data[i]);
				for (int j = 0; j < encodedBytes.size; j++) {
					encoded += data[j];
				}
			}
			else {
				encoded += data[i];
			}
		}

		return encoded; 
	}

	std::string encodeAsUTF8(const char32_t* data, const size_t size, const bool includeBOM) {
		std::string encoded;

		if (includeBOM) {
			encoded = getBOM(Encoding::UTF8);
		}

		for (int i = 0; i < size; i++) {
			if (data[i] > 0x7F) { // needs 2+ byte representation
				EncodedBytes encodedBytes = encodeValueToUTF8(data[i]);
				for (int j = 0; j < encodedBytes.size; j++) {
					encoded += data[j];
				}
			}
			else {
				encoded += data[i];
			}
		}

		return encoded;
	}

	std::string encodeAsUTF16BE(const char* data, const size_t size);
	//std::string encodeAsUTF16BE(const char* data, const size_t size) {
	//	std::string encoded;

	//	const size_t evenSize = size / 2 * 2;

	//	uint32_t value32 = 0;
	//	uint16_t value16 = 0;
	//	for (int i = 0; i < size; i++) {
	//		if (i & 1) {
	//			value16 |= data[i];

	//			if (value16 > 0xD7FF) {

	//			if (value > 0x7F) { // needs 2+ byte representation
	//				EncodedBytes encodedBytes = encodeValueToUTF8(value);
	//				for (int j = 0; j < encodedBytes.size; j++) {
	//					encoded += data[j];
	//				}
	//			}
	//			else {
	//				encoded += data[i];
	//			}
	//		}
	//		else {
	//			value16 = (uint16_t)data[i] << 8;
	//		}
	//	}

	//	return encoded;
	//}

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
}