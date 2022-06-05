#pragma once
#include <string>

namespace utf {
	enum class Encoding { UTF8, UTF16_LE, UTF16_BE, UTF32_LE, UTF32_BE };

	std::string getBOM(Encoding encoding);
}

