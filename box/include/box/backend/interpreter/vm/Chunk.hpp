#pragma once
#include <vector>
#include <stdexcept>
#include "Instructions.hpp"

namespace box::backend::interpreter {
	class Chunk {
		size_t _maxCapacity;
		std::vector<uint8_t> _bytes;
	public:
		Chunk(const size_t& capacity = 1024);
		virtual ~Chunk();

		/*
		* @return offset + size
		*/
		template <typename T>
		std::pair<int, T> get(const int& offset, const size_t& size = sizeof(T)) const;
		std::pair<int, uint8_t*> rawGet(const int& offset, const size_t& size) const;

		template <typename T>
		void push(const T& data);
		template <typename T>
		void push(const T& data, const size_t& offset);
		void rawPush(const void* data, const size_t& size);
		void set(const uint8_t* data, const size_t& size, const size_t& address);
		void moveFrom(const Chunk* chunk, const int& offset, const size_t& size, const size_t& address);

		size_t size() const;
		size_t wrapAroundIndex(const int32_t& index) const;

		std::vector<uint8_t> raw() const;
		size_t getAddress(const size_t& need = 1);

		/*
		* @brief Don't use it often, it's just for more control over `Chunk`. After resizing, the data beyond newSize will be deleted!
		*/
		void resize(const size_t& newSize);

		void clear();
		bool isFull(const size_t& fake = 0) const;
	};

	template <typename T>
	inline std::pair<int, T> Chunk::get(const int& offset, const size_t& size) const {
		T data;
		std::memcpy(&data, this->_bytes.data() + offset, size);
		return std::pair<int, T>(offset + size, std::move(data));
	}

	template <typename T>
	inline void Chunk::push(const T& data) {
		size_t size = sizeof(T);

		if (this->isFull(size)) {
			throw std::runtime_error("Chunk is full");
		}

		size_t sizeNow = this->_bytes.size();
		this->_bytes.resize(this->_bytes.size() + size);
		std::memcpy(&this->_bytes[sizeNow], &data, size);
	}

	template <typename T>
	inline void Chunk::push(const T& data, const size_t& address) {
		size_t size = sizeof(T);

		size_t dataSize = this->_bytes.size();
		if (address > this->_maxCapacity)
			throw std::out_of_range("Address is beyond buffer capacity");
		else if (dataSize == 0 || address > dataSize)
			this->_bytes.resize(dataSize + size);

		std::memcpy(&this->_bytes[address], &data, size);
	}
}