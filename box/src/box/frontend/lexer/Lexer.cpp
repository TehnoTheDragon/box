#include "box/frontend/lexer/lexer.hpp"

namespace box::frontend {
	LexicSnapshot::LexicSnapshot(const std::regex& regex, const std::string& text) :
		buffer(text),
		regex(regex)
	{
		itr = std::sregex_iterator(buffer.begin(), buffer.end(), this->regex);
		end = std::sregex_iterator(buffer.end(), buffer.end(), this->regex);
	}

	Lexer::Lexer(const std::vector<std::pair<TokenType, std::string>>& rules) : _rules(rules) {}
	Lexer::~Lexer() {}

	LexicSnapshot* Lexer::begin(LexicSnapshot* data) {
		if (_data == data) return data;
		if (_data != nullptr) delete _data;
		_data = data;
		return _data;
	}

	LexicSnapshot* Lexer::begin(const std::string& text) {
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

		_data = new LexicSnapshot(std::regex(combinedRules), text);
		return _data;
	}

	Token Lexer::next() {
		if (_data->itr == _data->end)
			return NULL_TOKEN;

		const std::smatch token = *_data->itr++;
		const auto& data = token.str();
		size_t position = token.position();
		TokenType tokenType = 0;

		for (const auto& rule : _rules) {
			if (std::regex_match(data, std::regex(rule.second))) {
				tokenType = rule.first;
				break;
			}
		}

		return {
			position,
			tokenType,
			data
		};
	}
}