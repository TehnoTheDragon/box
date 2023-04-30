#include "box/backend/interpreter/vm/VirtualMachine.hpp"

#define MATH_OPERATION(OP)\
			const auto& mode = getInst<uint8_t>();\
			switch (mode) {\
			case Flag::FLAG_REG2: {\
				const auto& regA = getInst<uint8_t>();\
				const auto& regB = getInst<uint8_t>();\
				const auto& stack = getInst<int32_t>();\
				this->_data.push<RegisterType>(\
					this->readRegister(regA) OP this->readRegister(regB),\
					this->_data.wrapAroundIndex(stack)\
				);\
				this->updateFlags(regA, regB, #OP);\
				break;\
			}\
			case Flag::FLAG_STACK2: {\
				const auto& stackA = getInst<int32_t>();\
				const auto& stackB = getInst<int32_t>();\
				const auto& stack = getInst<int32_t>();\
				this->_data.push<RegisterType>(\
					this->_data.get<RegisterType>(this->_data.wrapAroundIndex(stackA)).second\
					OP\
					this->_data.get<RegisterType>(this->_data.wrapAroundIndex(stackB)).second,\
					this->_data.wrapAroundIndex(stack)\
				);\
				break;\
			}\
			case Flag::FLAG_REG_STACK: {\
				const auto& regA = getInst<int8_t>();\
				const auto& stackB = getInst<int32_t>();\
				const auto& stack = getInst<int32_t>();\
				this->_data.push<RegisterType>(\
					this->readRegister(regA)\
					OP\
					this->_data.get<RegisterType>(this->_data.wrapAroundIndex(stackB)).second,\
					this->_data.wrapAroundIndex(stack)\
				);\
				break;\
			}\
			case Flag::FLAG_STACK_REG: {\
				const auto& stackA = getInst<int32_t>();\
				const auto& regB = getInst<int8_t>();\
				const auto& stack = getInst<int32_t>();\
				this->_data.push<RegisterType>(\
					this->_data.get<RegisterType>(this->_data.wrapAroundIndex(stackA)).second\
					OP\
					this->readRegister(regB),\
					this->_data.wrapAroundIndex(stack)\
				);\
				break;\
			}\
		}

#define BINARY_OPERATION_NOT\
	const auto& mode = getInst<uint8_t>();\
	switch (mode) {\
	case Flag::FLAG_REG2: {\
			const auto& regA = getInst<uint8_t>(); \
			const auto& stack = getInst<int32_t>(); \
			this->_data.push<RegisterType>(\
				~this->readRegister(regA), \
				this->_data.wrapAroundIndex(stack)\
			); \
			this->updateFlags(regA, regA, "~"); \
			break; \
		}\
	case Flag::FLAG_STACK2: {\
			const auto& stackA = getInst<int32_t>(); \
			const auto& stack = getInst<int32_t>(); \
			this->_data.push<RegisterType>(\
				~this->_data.get<RegisterType>(this->_data.wrapAroundIndex(stackA)).second,\
				this->_data.wrapAroundIndex(stack)\
			); \
			break; \
		}\
	case Flag::FLAG_REG_STACK: {\
			const auto& regA = getInst<int8_t>(); \
			const auto& stack = getInst<int32_t>(); \
			this->_data.push<RegisterType>(\
				~this->readRegister(regA), \
				this->_data.wrapAroundIndex(stack)\
			); \
			break; \
		}\
	case Flag::FLAG_STACK_REG: {\
			const auto& stackA = getInst<int32_t>(); \
			const auto& stack = getInst<int32_t>(); \
			this->_data.push<RegisterType>(\
				~this->_data.get<RegisterType>(this->_data.wrapAroundIndex(stackA)).second,\
				this->_data.wrapAroundIndex(stack)\
			); \
			break; \
		}\
	}

namespace box::backend::interpreter {
	VirtualMachine::VirtualMachine(const size_t& capacity) {
		this->_data = Chunk(capacity);

		resetRegisters();
		resetFlags();
	}

	VirtualMachine::~VirtualMachine() {
	}

	void VirtualMachine::run(const Chunk* program) {
		resetRegisters();
		resetFlags();
		this->_ip = 0;
		this->_program = program;

		bool running = true;

		while (running && this->_ip < this->_program->size()) {
			const auto& instruction = getInst<uint16_t>();

			switch (instruction) {
				// Stack & Registers
			case OpCode::OPCODE_REGISTER_CONSTANT: {
				const auto& reg = getInst<uint8_t>();
				const auto& value = getInst<RegisterType>();
				this->writeRegister(reg, value);
				break;
			}
			case OpCode::OPCODE_STACK_CONSTANT: {
				this->_data.push<RegisterType>(getInst<RegisterType>());
				break;
			}
			case OpCode::OPCODE_SAVE: {
				const auto& reg = getInst<uint8_t>();

				this->_data.push<RegisterType>(this->readRegister(reg));

				break;
			}
			case OpCode::OPCODE_LOAD: {
				const auto& reg = getInst<uint8_t>();
				const auto& stack = getInst<int32_t>();

				size_t dataSize = this->_data.size();
				this->writeRegister(reg, this->_data.get<RegisterType>(this->_data.wrapAroundIndex(stack)).second);

				break;
			}
				// Math
			case OpCode::OPCODE_ADD: {
				MATH_OPERATION(+);
				break;
			}
			case OpCode::OPCODE_SUB: {
				MATH_OPERATION(-);
				break;
			}
			case OpCode::OPCODE_MUL: {
				MATH_OPERATION(*);
				break;
			}
			case OpCode::OPCODE_MOD: {
				MATH_OPERATION(%);
				break;
			}
				// Binary
			case OpCode::OPCODE_BAND: {
				MATH_OPERATION(&);
				break;
			}
			case OpCode::OPCODE_BOR: {
				MATH_OPERATION(|);
				break;
			}
			case OpCode::OPCODE_BXOR: {
				MATH_OPERATION(^);
				break;
			}
			case OpCode::OPCODE_BNOT: {
				BINARY_OPERATION_NOT;
				break;
			}
				// Control-Flow
			case OpCode::OPCODE_HALT: {
				running = false;
				break;
			}
			default: {
				running = false;
				char msg[127];
				sprintf(msg, "Uknown OpCode: %d\n", instruction);
				throw std::exception(msg);
			}
			}
		}
	}

	void VirtualMachine::resetRegisters() {
		for (int i = 0; i < _registers.size(); i++)
			_registers[i] = 0;
	}

	void VirtualMachine::resetFlags() {
		_flags.zero = false;
		_flags.carry = false;
		_flags.overflow = false;
	}

	void VirtualMachine::updateFlags(const uint8_t& a, const uint8_t& b, const char* opC) {
		const auto& A = this->readRegister(a);
		const auto& B = this->readRegister(b);
		RegisterType result = 0;

		const int8_t op = opC[0];
		switch (op)
		{
			// Math
		case '+': {
			result = A + B;
			break;
		}
		case '-': {
			result = A - B;
			break;
		}
		case '*': {
			result = A * B;
			break;
		}
		case '/': {
			result = A / B;
			break;
		}
		case '%': {
			result = A % B;
			break;
		}
			// Binary
		case '&': { // AND
			result = A & B;
			break;
		}
		case '|': { // OR
			result = A | B;
			break;
		}
		case '^': { // XOR
			result = A ^ B;
			break;
		}
		case '~': { // NOT
			result = ~A;
			break;
		}
		}

		this->_flags.zero = result == 0;
		this->_flags.sign = result < 0;
		this->_flags.carry = static_cast<URegisterType>(result) > MAX_REGISTER_SIZE;
		this->_flags.overflow = ((A < 0 && B < 0 && result >= 0) || (B > 0 && A > 0 && result <= 0));
	}

	VirtualMachine::RegisterType VirtualMachine::readRegister(const size_t& index) const {
		return this->_registers[index];
	}

	void VirtualMachine::writeRegister(const size_t& index, RegisterType value) {
		this->_registers[index] = value;
	}

}

#undef BINARY_OPERATION_NOT
#undef MATH_OPERATION