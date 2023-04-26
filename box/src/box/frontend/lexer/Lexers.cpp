#include "box/frontend/tools/RegEx.hpp"
#include "box/frontend/lexer/Lexers.hpp"

namespace box::frontend::lexers {
	Lexer getBoxLexer() {
		return Lexer({
			{ static_cast<TokenType>(tokens::BoxTokenType::DataType), RegEx("(boolean|i8|i16|i32|i64|u8|u16|u32|u64|f32|f64|nil|unknown|any)").str()},
			{ static_cast<TokenType>(tokens::BoxTokenType::String), RegEx("\".*\"").str() },
			{ static_cast<TokenType>(tokens::BoxTokenType::Numeric), RegEx("([\+\-]?)[0-9_]+(\.?)[0-9]*[f|F|d|D|u|U]?").str() },
			{ static_cast<TokenType>(tokens::BoxTokenType::Identity), RegEx("[a-zA-Z_]+[a-zA-Z0-9_]*").str() },
			{ static_cast<TokenType>(tokens::BoxTokenType::Punctuation), RegEx("(:{1,2}|;|\\.)").str() },
			{ static_cast<TokenType>(tokens::BoxTokenType::Mathematic), RegEx("(\\*{1,2}|-{1,2}|\\+{1,2}|\\/{1,2}|=)").str() },
		});
	}
}