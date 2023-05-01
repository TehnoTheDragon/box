#pragma once
#include <string>
#include <vector>
#include "../lexer/token.hpp"

namespace box::frontend {
	class ParserRule {
        struct Value;

		const uint32_t _ID;
        uint32_t _counter = 0;
        std::vector<std::vector<Value>> _cases;
	private:
        enum class ValueType {
            VALUE, ID
        };

        struct Value {
            ValueType type;
            std::vector<std::string> strs;
            std::vector<TokenType> ids;

            Value(const std::string& value) : type(ValueType::VALUE) {
                this->strs = { value };
            }

            Value(std::vector<std::string>&& value) : type(ValueType::VALUE) {
                this->strs = std::move(value);
            }

            Value(const TokenType& value) : type(ValueType::ID) {
                this->ids = { value };
            }

            Value(std::vector<TokenType>&& value) : type(ValueType::VALUE) {
                this->ids = std::move(value);
            }

            bool operator == (const std::string& value) const;
            bool operator == (const TokenType& value) const;
            bool operator == (const Token& value) const;
        };
	public:
        ParserRule(const uint32_t& id);
        ~ParserRule();

        ParserRule& operator & (Value&& value);
        ParserRule& operator | (Value&& value);

        static Value VALUE(const std::string& value);
        static Value ID(const TokenType& value);
        static Value VALUE(std::vector<std::string>&& value);
        static Value ID(std::vector<TokenType>&& value);

        bool validate(const std::vector<Token>& tokens, size_t actionOffset = 0);
        bool validate(const Token& token, size_t actionOffset = 0);
	};
}