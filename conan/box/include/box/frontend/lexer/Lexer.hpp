#pragma once
#include <vector>
#include <regex>
#include "Token.hpp"

namespace box::frontend {
	struct LexerData {
		const std::string buffer;
		const std::regex regex;
		std::sregex_iterator itr;
		std::sregex_iterator end;

		LexerData(const std::regex& regex, const std::string& text = "");
	};

	class Lexer final {
		std::vector<std::pair<TokenType, std::string>> _rules;
		LexerData* _data = nullptr;
	public:
		Lexer(const std::vector<std::string>& rules);
		Lexer(const std::vector<std::pair<TokenType, std::string>>& rules);
		~Lexer();

		LexerData* begin(LexerData* data);
		LexerData* begin(const std::string& text);
		Token next();
		std::vector<Token> nextAll();
	};
}