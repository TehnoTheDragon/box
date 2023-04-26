#include "box/frontend/parser/Parser.hpp"

namespace box::frontend {
	Parser::Parser(Lexer lexer) : _lexer(lexer) {}
	Parser::~Parser() {}
}