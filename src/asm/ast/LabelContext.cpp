//
// Created by Tobe on 4/7/18.
//

#include "LabelContext.h"
#include <utility>

emu::LabelContext::LabelContext(std::string name) {
    this->name = std::move(name);
}

emu::LabelContext::LabelContext(std::string &name) {
    this->name = name;
}

std::vector<emu::InstructionContext *> const &emu::LabelContext::get_instructions() const {
    return instructions;
}

std::string emu::LabelContext::get_name() const {
    return name;
}

void emu::LabelContext::addInstruction(emu::InstructionContext *instruction) {
    instructions.push_back(instruction);
}
