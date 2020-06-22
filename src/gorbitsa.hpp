#ifndef GORBITSA_HPP
#define GORBITSA_HPP

#include <cstdint>
#include <array>
#include <string>
#include <vector>
#include <cctype>

#include "engine.h"

enum OpCode {
	OP_GRAB = 0,
	OP_OFFER,
	OP_RECEIVE,
	OP_BRANCH,
	OP_INCREASE,
	OP_TRANSMIT,
	OP_SET,
	OP_ADD,

	OP_GRAB_EX,
	OP_OFFER_EX,
	OP_RECEIVE_EX,
	OP_BRANCH_EX,
	OP_INCREASE_EX,
	OP_TRANSMIT_EX,
	OP_SET_EX,
	OP_ADD_EX,
};

enum InputIndex {
	II_START = 1,
	II_JUMP,
	II_LEFT,
	II_RIGHT,
	II_UP,
	II_DOWN
};

struct Instruction {
	union {
		uint16_t instruction;
		struct { uint8_t op; uint8_t data; };
	};
};

class Gorbitsa {
public:
	inline Gorbitsa() {
		m_memory.fill(0);
	}

	inline void run(Engine* engine) {
		while (m_pc <= 255) {
			if (!m_waitingInput) {
				auto& inst = next();
				switch (inst.op) {
					case OP_GRAB: m_x = m_memory[inst.data]; break;
					case OP_OFFER: m_memory[inst.data] = m_x; break;
					case OP_RECEIVE: m_waitingInput = true; m_inputTarget = &m_x; break;
					case OP_BRANCH: if (m_x == 0) m_pc = inst.data; break;
					case OP_INCREASE: m_x += inst.data; break;
					case OP_TRANSMIT: /* TODO: Implement Video Output */ break;
					case OP_SET: m_x = inst.data; break;
					case OP_ADD: m_x += m_memory[inst.data]; break;

					case OP_GRAB_EX: m_x = m_memory[m_memory[inst.data]]; break;
					case OP_OFFER_EX: m_memory[m_memory[inst.data]] = m_x; break;
					case OP_RECEIVE_EX: m_waitingInput = true; m_inputTarget = &m_memory[inst.data]; break;
					case OP_BRANCH_EX: if (m_x == 0) m_pc = m_memory[inst.data]; break;
					case OP_INCREASE_EX: m_memory[inst.data] += m_x; break;
					case OP_TRANSMIT_EX: /* TODO: Implement Video Output */ break;
					case OP_SET_EX: m_x ^= m_memory[inst.data]; break;
					case OP_ADD_EX: m_x += m_memory[m_memory[inst.data]]; break;
				}
			}
		}
	}

	inline void joyaction(uint8_t index) {
		m_waitingInput = false;
		*m_inputTarget = index;
	}

	inline void load(const std::string& code) {
		std::vector<char> input(code.begin(), code.end());

		auto advance = [&]() -> char {
			char c = input.front();
			input.erase(input.begin());
			return c;
		};

		auto readNumber = [&]() -> uint8_t {
			std::string ret = "";
			while (::isdigit(input.front())) {
				ret += advance();
			}
			return uint8_t(std::stoi(ret)) & 0xFF;
		};

		uint8_t ptr = 0;
		auto put = [&](uint8_t op, uint8_t data) {
			m_program[ptr].op = op;
			m_program[ptr].data = data;
			ptr++;
		};

		while (!input.empty()) {
			const char c = input.front();
			if (::isalpha(c)) {
				switch (c) {
					case 'G': advance(); put(OP_GRAB, readNumber()); break;
					case 'O': advance(); put(OP_OFFER, readNumber()); break;
					case 'R': advance(); put(OP_RECEIVE, 0xFF); break;
					case 'B': advance(); put(OP_BRANCH, readNumber()); break;
					case 'I': advance(); put(OP_INCREASE, readNumber()); break;
					case 'T': advance(); put(OP_TRANSMIT, 0xFF); break;
					case 'S': advance(); put(OP_SET, readNumber()); break;
					case 'A': advance(); put(OP_ADD, readNumber()); break;

					case 'g': advance(); put(OP_GRAB_EX, readNumber()); break;
					case 'o': advance(); put(OP_OFFER_EX, readNumber()); break;
					case 'r': advance(); put(OP_RECEIVE_EX, readNumber()); break;
					case 'b': advance(); put(OP_BRANCH_EX, readNumber()); break;
					case 'i': advance(); put(OP_INCREASE_EX, readNumber()); break;
					case 't': advance(); put(OP_TRANSMIT_EX, readNumber()); break;
					case 's': advance(); put(OP_SET_EX, readNumber()); break;
					case 'a': advance(); put(OP_ADD_EX, readNumber()); break;

					default: advance(); break;
				}
			} else {
				advance();
			}
		}
	}

private:
	std::array<Instruction, 256> m_program;
	std::array<uint8_t, 256> m_memory;

	uint8_t m_x{ 0 }, m_pc{ 0 };

	bool m_waitingInput{ false };
	uint8_t *m_inputTarget{ nullptr };

	inline Instruction& next() {
		return m_program[m_pc++];
	}
};

#endif // GORBITSA_HPP
