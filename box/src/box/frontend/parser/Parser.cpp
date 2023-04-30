#include "box/frontend/parser/parser.hpp"

namespace box::frontend {
	Parser::Parser(Lexer lexer, std::vector<ParserRule>&& rules) : _lexer(lexer), _rules(std::move(rules)) {}
	Parser::~Parser() {}
}