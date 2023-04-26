#pragma once
#include <regex>

namespace box::frontend {
	const class RegEx final {
	private:
		std::string _rgx;
		std::string _par;
	public:
		RegEx() = default;
		RegEx(const char* input) : _rgx(input) {}
		RegEx(const char input) { _rgx = input; }

		constexpr auto& Group(const RegEx& group) {
			_rgx += "(";
			_rgx += group.str();
			_par += ")";
			return *this;
		}

		constexpr auto& Exactly(const std::string& word) {
			_rgx += "(?:";
			_rgx += word;
			_par += ")";
			return *this;
		}

		constexpr auto& Or(const std::string& word) {
			_rgx += "|(?:";
			_rgx += word;
			_par += ")";
			return *this;
		}

		constexpr auto& Or(const RegEx& group) {
			_rgx += "|(";
			_rgx += group.str();
			_par += ")";
			return *this;
		}

		constexpr auto& Char(const char character) {
			_rgx += character;
			return *this;
		}

		const auto get() const {
			return std::regex(_rgx + _par);
		}

		const std::string str() const {
			return _rgx + _par;
		}

		constexpr auto& operator + (const RegEx& other) {
			this->_rgx += other.str();
			return *this;
		}
	};
}