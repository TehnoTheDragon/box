#include "box/frontend/lexer/Lexer.hpp"

namespace box::frontend {
	LexerData::LexerData(const std::regex& regex, const std::string& text) :
		buffer(text),
		regex(regex)
	{
		itr = std::sregex_iterator(buffer.begin(), buffer.end(), this->regex);
		end = std::sregex_iterator(buffer.end(), buffer.end(), this->regex);
	}

	Lexer::Lexer(const std::vector<std::string>& rules) {
		TokenType idx = 0;
		for (const auto& regex : rules)
			_rules.emplace_back(idx++, regex);
	}
	Lexer::Lexer(const std::vector<std::pair<TokenType, std::string>>& rules) : _rules(rules) {}
	Lexer::~Lexer() {}

	LexerData* Lexer::begin(LexerData* data) {
		if (_data == data) return data;
		if (_data != nullptr) delete _data;
		_data = data;
		return _data;
	}

	LexerData* Lexer::begin(const std::string& text) {
		if (_data != nullptr)
			delete _data;

		std::string combinedRules;
		size_t i = 0;
		for (const auto& rule : _rules) {
			combinedRules += "(";
			combinedRules += rule.second;
			combinedRules += ")";
			if (i++ < _rules.size() - 1)
				combinedRules += "|";
		}

		_data = new LexerData(std::regex(combinedRules), text);
		return _data;
	}

	Token Lexer::next() {
		if (_data->itr == _data->end)
			return NULL_TOKEN;

		const std::smatch token = *_data->itr++;
		const auto& data = token.str();
		TokenType tokenType = 0;
		for (const auto& rule : _rules) {
			if (std::regex_match(data, std::regex(rule.second)))
				tokenType = rule.first;
				break;
		}
		size_t position = token.position() - 1;

		return {
			position,
			tokenType,
			data
		};
	}

	std::vector<Token> Lexer::nextAll() {
		auto tokens = std::vector<Token>();

		auto tkn = this->next();
		while (!tkn.data.empty()) {
			tokens.emplace_back(tkn);
			tkn = this->next();
		}

		return tokens;
	}
}