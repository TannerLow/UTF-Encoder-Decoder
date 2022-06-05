#include "Encoding.h"

namespace utf {
	std::string getBOM(Encoding encoding) {
		switch (encoding) {
		case Encoding::UTF8: return "\xEF\xBB\xBF";
		case Encoding::UTF16_BE: return "\xFE\xFF";
		case Encoding::UTF16_LE: return "\xFF\xFE";
		case Encoding::UTF32_BE: return std::string("\x00\x00\xFE\xFF", 4);
		case Encoding::UTF32_LE: return std::string("\xFF\xFE\x00\x00", 4);
		default: return "";
		}
	}
}