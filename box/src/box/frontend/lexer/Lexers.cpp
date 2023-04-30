#include "box/frontend/lexer/lexers.hpp"

namespace box::frontend::lexers {
	Lexer getBoxLexer() {
		return Lexer({
			{ static_cast<TokenType>(tokens::BoxTokenType::DataType), "(boolean|i8|i16|i32|i64|u8|u16|u32|u64|f32|f64|nil|unknown|any)"},
			{ static_cast<TokenType>(tokens::BoxTokenType::String), "\".*\"" },
			{ static_cast<TokenType>(tokens::BoxTokenType::Numeric), "([\\+\\-]?)[0-9_]+(\\.?)[0-9]*[f|F|d|D|u|U]?" },
			{ static_cast<TokenType>(tokens::BoxTokenType::Identity), "[a-zA-Z_]+[a-zA-Z0-9_]*" },
			{ static_cast<TokenType>(tokens::BoxTokenType::Punctuation), "(:{1,2}|;|\\.)" },
			{ static_cast<TokenType>(tokens::BoxTokenType::Mathematic), "(\\*{1,2}|-{1,2}|\\+{1,2}|\\/{1,2}|=)" },
		});
	}
}