#pragma once
#include "box/frontend/lexer/lexer.hpp"
#include "parser_rule.hpp"
#include <vector>

namespace box::frontend {
	class Parser {
		Lexer _lexer;
		std::vector<ParserRule> _rules;
	public:
		Parser(Lexer lexer, std::vector<ParserRule>&& rules);
		~Parser();
	};
}