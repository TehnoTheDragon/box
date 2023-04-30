#pragma once
#include <array>
#include "Chunk.hpp"

namespace box::backend::interpreter {
	class VirtualMachine {
		using URegisterType = uint32_t;
		using RegisterType = int32_t;
		const size_t MAX_REGISTER_SIZE = static_cast<size_t>(pow(2.0, pow(8.0, sizeof(RegisterType))));

		const Chunk *_program = nullptr;
		Chunk _data;
		RegisterType _ip = 0;
		std::array<RegisterType, 2> _registers;
		struct {
			bool zero = false;
			bool sign = false;
			bool carry = false;
			bool overflow = false;
		} _flags;
	public:
		VirtualMachine(const size_t& capacity = 1024);
		virtual ~VirtualMachine();

		void run(const Chunk* program);

		template <typename T>
		T getInst(const size_t& size = sizeof(T)) {
			auto [next, data] = this->_program->get<T>(this->_ip, size);
			this->_ip += size;
			return std::move(data);
		}

		uint8_t* getInstPtr(const size_t& size) {
			auto [next, data] = this->_program->rawGet(this->_ip, size);
			this->_ip += size;
			return data;
		}

	private:
		void resetRegisters();
		void resetFlags();
		void updateFlags(const uint8_t& a, const uint8_t& b, const char* op);

		RegisterType readRegister(const size_t& index) const;
		void writeRegister(const size_t& index, RegisterType value);
	};
}