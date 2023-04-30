#pragma once
#include <string>
#include <vector>
#include "../lexer/token.hpp"

namespace box::frontend {
	class ParserRule {
		const uint32_t _ID;
	public:
        enum class ValueType {
            VALUE, ID
        };

        struct Value {
            ParserRule* parent;
            ValueType type;
            std::vector<std::string> strs;
            std::vector<TokenType> ids;

            Value(const std::string value) : type(ValueType::VALUE) {
                this->strs = { value };
            }

            Value(std::vector<std::string>&& value) : type(ValueType::VALUE) {
                this->strs = std::move(value);
            }

            Value(const TokenType value) : type(ValueType::ID) {
                this->ids = { value };
            }

            Value(std::vector<TokenType>&& value) : type(ValueType::VALUE) {
                this->ids = std::move(value);
            }

            bool operator == (const std::string& value);
            bool operator == (const TokenType& value);
        };
	public:
        ParserRule(const uint32_t& id);
        ~ParserRule();
	};
}