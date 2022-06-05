#include "UTFDecoder.h"
#include <cstring>

namespace utf {
	Encoding getEncoding(const std::string& encoded, const bool assumeUTF16) {
		
		// 4 bytes needed for utf-32
		if (encoded.size() > 3) {
			std::string bom = encoded.substr(0, 4);

			if (bom == getBOM(Encoding::UTF32_BE)) 
				return Encoding::UTF32_BE;

			// utf-16 and utf-32 LE share bom byte values so assumption needs to be made
			else if (!assumeUTF16 and bom == getBOM(Encoding::UTF32_LE)) 
				return Encoding::UTF32_LE;
		}
		
		// 3 bytes needed for utf-8
		if (encoded.size() > 2) {
			if (encoded.substr(0, 3) == getBOM(Encoding::UTF8)) {
				return Encoding::UTF8;
			}
		}

		// could be utf-16
		if (encoded.size() > 1) {
			std::string bom = encoded.substr(0, 2);

			if (bom == getBOM(Encoding::UTF16_BE))
				return Encoding::UTF16_BE;

			else if (bom == getBOM(Encoding::UTF16_LE))
				return Encoding::UTF16_LE;
		}

		// utf-8 doesn't need a BOM
		return Encoding::UTF8;
	}

	Encoding getEncoding(const char* encoded, const size_t length, const bool assumeUTF16) {
		std::string encodedStr(encoded, length);
		return getEncoding(encodedStr, assumeUTF16);
	}

	Encoding getEncoding(std::ifstream& file, const bool assumeUTF16) {
		const size_t pos = file.tellg();
		const std::ios_base::iostate state = file.rdstate();
		file.seekg(0, file.beg);

		std::string bom;
		char c;
		for (int i = 0; i < 4 and file.get(c); i++) {
			bom += c;
		}

		file.clear(state);
		file.seekg(pos);

		return getEncoding(bom, assumeUTF16);
	}
}