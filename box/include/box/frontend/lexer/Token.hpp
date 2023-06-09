#pragma once
#include <string>
#include "../types.hpp"

namespace box::frontend {
	struct Token {
		size_t position;
		TokenType type;
		std::string data;
	};
	const Token NULL_TOKEN{ 0, 0, "" };
}