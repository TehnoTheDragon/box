#pragma once
#include <vector>
#include <regex>
#include "token.hpp"

namespace box::frontend {
	struct LexicSnapshot {
		const std::string buffer;
		const std::regex regex;
		std::sregex_iterator itr;
		std::sregex_iterator end;

		LexicSnapshot(const std::regex& regex, const std::string& text = "");
	};

	class Lexer final {
		const std::vector<std::pair<TokenType, std::string>> _rules;
		LexicSnapshot* _data = nullptr;
	public:
		Lexer(const std::vector<std::pair<TokenType, std::string>>& rules);
		~Lexer();

		LexicSnapshot* begin(LexicSnapshot* data);
		LexicSnapshot* begin(const std::string& text);
		Token next();
	};
}