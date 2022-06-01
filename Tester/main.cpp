#include <UTF.h>
#include <cstdio>
#include <vector>

void test_getBOM(utf::Encoding encoding) {
	std::string bom = utf::getBOM(encoding);
	unsigned char val;

	printf("BOM:");
	for (char c : bom) {
		val = c;
		printf(" %d", val);
	}
	printf("\n");
}

int main() {
	std::vector<utf::Encoding> encodings{ 
		utf::Encoding::UTF8,
		utf::Encoding::UTF16_BE,
		utf::Encoding::UTF16_LE,
		utf::Encoding::UTF32_BE,
		utf::Encoding::UTF32_LE,
	};

	for(auto encoding : encodings) 
		test_getBOM(encoding);

	printf("Line: %d, Expected: %d Actual: %d\n", __LINE__, 7, utf::encodeAsUTF8("ab\xFF\c\x80", 5).size());

	return 0;
}