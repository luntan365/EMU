//
// Created by Tobe on 4/7/18.
//

#include "InstructionContext.h"

emu::InstructionContext::InstructionContext(uint8_t opcode, Token* opcodeToken) {
    this->opcode = opcode;
    this->opcodeToken = opcodeToken;
}

uint8_t emu::InstructionContext::get_opcode() const {
    return opcode;
}

std::vector<emu::Token *> const &emu::InstructionContext::get_operands() const {
    return operands;
}

void emu::InstructionContext::addOperand(emu::Token *token) {
    operands.push_back(token);
}

emu::Token *emu::InstructionContext::get_opcode_token() const {
    return opcodeToken;
}
