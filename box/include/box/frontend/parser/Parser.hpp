#pragma once
#include "box/frontend/lexer/Lexer.hpp"
#include "ParserRule.hpp"
#include <vector>

namespace box::frontend {
	class Parser {
		Lexer _lexer;
	public:
		Parser(Lexer lexer);
		~Parser();
	};
}