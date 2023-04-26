#include <iostream>
#include <box/frontend/lexer/Lexers.hpp>
#include <box/frontend/parser/Parser.hpp>

using namespace box::frontend;

static auto TEXT_TO_PARSE = R"(
x : i32 = 1.52f + 10.0F
)";

int main(int argc, char** argv) {
	auto myParser = Parser(lexers::getBoxLexer());

	std::cin.get();
	return 0;
}