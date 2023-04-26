#pragma once
#include "Lexer.hpp"

namespace box::frontend {
	namespace lexers {
		Lexer getBoxLexer();
	}
	namespace tokens {
		enum class BoxTokenType : TokenType {
			DataType,
			String,
			Numeric,
			Identity,
			Punctuation,
			Mathematic,
		};
	}
}