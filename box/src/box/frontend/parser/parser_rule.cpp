#include "box/frontend/parser/parser_rule.hpp"

namespace box::frontend {
	// PaerserRule :: Value

	bool ParserRule::Value::operator==(const std::string& value) {
		return std::count(this->strs.begin(), this->strs.end(), value);
	}

	bool ParserRule::Value::operator==(const TokenType& value) {
		return std::count(this->ids.begin(), this->ids.end(), value);
	}

	// Parser Rule

	ParserRule::ParserRule(const uint32_t& id) : _ID(id) {

	}
	ParserRule::~ParserRule()
	{
	}
}