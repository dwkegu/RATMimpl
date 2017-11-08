#include "test.h"
#include "strtokenizer.h"

using std::string;


int main(int argc, char ** argv) {
	test("hello my friend. please send me your email? if you can help me do something it will be grateful!");
}

void test(string str) {
	strtokenizer token(str, " .!?", ".?!");
	printf("sentance count:%d\n", token.s_count_tokens());
	printf("word count:%d\n", token.count_tokens());
	for (int i = 0; i < token.s_count_tokens(); i++) {
		printf("sentance %d length is %d\n", i, token.count_tokens(i));
	}
}