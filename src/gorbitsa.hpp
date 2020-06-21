#ifndef GORBITSA_HPP
#define GORBITSA_HPP

#include <cstdint>
#include <array>

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

struct Instruction {
	union {
		uint16_t instruction;
		struct { uint8_t op; uint8_t data; };
	};
};

class Gorbitsa {
public:
	inline void run() {
		while (m_pc < 256) {
			auto& inst = advance();
			switch (inst.op) {
				case OP_GRAB: m_x = m_memory[inst.data]; break;
				case OP_OFFER: m_memory[inst.data] = m_x; break;
				case OP_RECEIVE: /* TODO: Implement Input */ break;
				case OP_BRANCH: if (m_x == 0) m_pc = inst.data; break;
				case OP_INCREASE: m_x += inst.data; break;
				case OP_TRANSMIT: /* TODO: Implement Video Output */ break;
				case OP_SET: m_x = inst.data; break;
				case OP_ADD: m_x += m_memory[inst.data]; break;

				case OP_GRAB_EX: m_x = m_memory[m_memory[inst.data]]; break;
				case OP_OFFER_EX: m_memory[m_memory[inst.data]] = m_x; break;
				case OP_RECEIVE_EX: /* TODO: Implement Input */ break;
				case OP_BRANCH_EX: if (m_x == 0) m_pc = m_memory[inst.data]; break;
				case OP_INCREASE_EX: m_memory[inst.data] += m_x; break;
				case OP_TRANSMIT_EX: /* TODO: Implement Video Output */ break;
				case OP_SET_EX: m_x ^= m_memory[inst.data]; break;
				case OP_ADD_EX: m_x += m_memory[m_memory[inst.data]]; break;
			}
		}
	}

private:
	std::array<Instruction, 256> m_program;
	std::array<uint8_t, 256> m_memory;

	uint8_t m_x{ 0 }, m_pc{ 0 };

	inline Instruction& advance() {
		return m_program[m_pc++];
	}
};

#endif // GORBITSA_HPP
