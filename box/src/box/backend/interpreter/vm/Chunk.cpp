#include <stdio.h>
#include "box/backend/interpreter/vm/Chunk.hpp"

namespace box::backend::interpreter {
	Chunk::Chunk(const size_t& capacity) : _maxCapacity(capacity) {

	}

	Chunk::~Chunk() {
		this->_bytes.clear();
	}

	std::pair<int, uint8_t*> Chunk::rawGet(const int& offset, const size_t& size) const {
		uint8_t* data = new uint8_t[size];
		std::memcpy(data, this->_bytes.data() + offset, size);
		return std::pair<int, uint8_t*>(offset + size, data);
	}

	void Chunk::rawPush(const void* data, const size_t& size) {
		if (this->isFull(size))
			throw std::runtime_error("Chunk is full");

		size_t sizeNow = this->_bytes.size();
		this->_bytes.resize(sizeNow + size);
		std::memcpy(&this->_bytes[sizeNow], data, size);
	}

	void Chunk::set(const uint8_t* data, const size_t& size, const size_t& address) {
		if (address > this->_maxCapacity)
			throw std::out_of_range("Address is beyond buffer capacity");

		size_t sizeNow = this->_bytes.size();
		if (sizeNow < size)
			this->_bytes.resize(sizeNow + size);

		std::memcpy(&this->_bytes[address], data, size);
	}

	void Chunk::moveFrom(const Chunk* chunk, const int& offset, const size_t& size, const size_t& address) {
		auto& [_, ptr] = chunk->rawGet(offset, size);
		this->set(ptr, size, address);
		delete[] ptr;
	}

	size_t Chunk::size() const {
		return this->_bytes.size();
	}

	size_t Chunk::wrapAroundIndex(const int32_t& index) const {
		size_t dataSize = this->_bytes.size();
		if (dataSize <= 0)
			return index < 0 ? 0 : index;
		return ((index < 0) ? (dataSize - index) % dataSize : index);
	}

	std::vector<uint8_t> Chunk::raw() const {
		return this->_bytes;
	}

	size_t Chunk::getAddress(const size_t& need) {
		size_t sizeNow = this->_bytes.size();
		if (sizeNow < need && !isFull(need))
			this->_bytes.resize(sizeNow + need);
		return sizeNow;
	}

	void Chunk::resize(const size_t& newSize) {
		this->_maxCapacity = newSize;
		this->_bytes.resize(newSize);
	}

	void Chunk::clear() {
		this->_bytes.clear();
	}

	bool Chunk::isFull(const size_t& fake) const {
		return this->_bytes.size() + fake > this->_maxCapacity;
	}
}