#pragma once

namespace box::backend::interpreter {
	enum OpCode : unsigned short {
		OPCODE_HALT,

		OPCODE_REGISTER_CONSTANT,
		OPCODE_STACK_CONSTANT,

		OPCODE_SAVE,
		OPCODE_LOAD,

		OPCODE_NEGATE,
		OPCODE_ADD,
		OPCODE_SUB,
		OPCODE_MUL,
		OPCODE_DIV,
		OPCODE_MOD,

		OPCODE_BAND,
		OPCODE_BOR,
		OPCODE_BXOR,
		OPCODE_BNOT,
	};

	enum Flag : unsigned char {
		FLAG_REG2,
		FLAG_STACK2,
		FLAG_REG_STACK,
		FLAG_STACK_REG,
	};
}