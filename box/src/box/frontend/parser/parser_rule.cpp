#include "box/frontend/parser/parser_rule.hpp"

namespace box::frontend {
	// PaerserRule :: Value

	bool ParserRule::Value::operator==(const std::string& value) const {
		return std::count(this->strs.begin(), this->strs.end(), value);
	}

	bool ParserRule::Value::operator==(const TokenType& value) const {
		return std::count(this->ids.begin(), this->ids.end(), value);
	}

	bool ParserRule::Value::operator==(const Token& value) const {
		return this->type == ParserRule::ValueType::VALUE ?
			this->operator==(value.data) : this->operator==(value.type);
	}

	// Parser Rule

	ParserRule::ParserRule(const uint32_t& id) : _ID(id) {

	}

	ParserRule::~ParserRule() {
	}

	ParserRule& ParserRule::operator & (ParserRule::Value&& value) {
		this->_cases.push_back({ std::move(value) });
		this->_counter++;
		
		return *this;
	}

	ParserRule& ParserRule::operator | (ParserRule::Value&& value) {
		this->_cases[this->_counter - 1].push_back(std::move(value));
		
		return *this;
	}

	ParserRule::Value ParserRule::VALUE(const std::string& value) {
		return Value(value);
	}

	ParserRule::Value ParserRule::ID(const TokenType& value) {
		return Value(value);
	}

	ParserRule::Value ParserRule::VALUE(std::vector<std::string>&& value) {
		return Value(std::move(value));
	}

	ParserRule::Value ParserRule::ID(std::vector<TokenType>&& value) {
		return Value(std::move(value));
	}

	bool ParserRule::validate(const std::vector<Token>& tokens, size_t actionOffset) {
		bool result = false;
		for (const auto& ruleset : this->_cases) {
			if (tokens.size() == ruleset.size() && actionOffset < ruleset.size()) {
				for (size_t i = actionOffset; i < ruleset.size() - actionOffset; i++) {
					if (ruleset.at(i) == tokens[i]) {
						result = true;
					} else {
						result = false;
						break;
					}
				}
			}
		}
		return result;
	}

    bool ParserRule::validate(const Token& token, size_t actionOffset) {
		for (const auto& ruleset : this->_cases) {
			if (actionOffset < ruleset.size() && ruleset.at(actionOffset) == token)
				return true;
		}
		return false;
	}
}

#undef AutoOperator_Value