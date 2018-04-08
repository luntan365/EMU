//
// Created by Tobe on 4/7/18.
//

#include "VM.h"
#include "Register.h"
#include <iostream>

emu::VM::VM(emu::Assembly *assembly) {
    this->assembly = assembly;
    errorMessage = std::string("An error occurred while running the program.");
}

std::string emu::VM::get_error_message() const {
    return errorMessage;
}

void emu::VM::dump(std::ostream &stream) {
    stream << "Register al: 0x" << std::hex << (int) registers[0] << std::endl;
    stream << "Register bl: 0x" << std::hex << (int) registers[1] << std::endl;
    stream << "Register cl: 0x" << std::hex << (int) registers[2] << std::endl;
    stream << "Register dl: 0x" << std::hex << (int) registers[3] << std::endl;
    stream << "Register el: 0x" << std::hex << (int) registers[4] << std::endl;
    stream << "Register cf: 0x" << std::hex << (int) carryFlag << std::endl;

    stream << "\nStack (" << stack.size() << ") entries: " << std::endl;

    while (!stack.empty()) {
        stream << "  * 0x" << std::hex << (int) stack.top() << std::endl;
        stack.pop();
    }

    stream << "\nProgram (" << std::dec << ((int) assembly->get_data().size()) << " bytes): " << std::endl;

    for (unsigned long i = 0; i < assembly->get_data().size(); i++) {
        auto byte = assembly->get_data().at(i);

        if (i == index)
            stream << "  > ";
        else stream << "    ";
        stream << "0x" << std::hex << (int) byte << std::endl;
    }
}

uint8_t emu::VM::getRegister(Register reg) {
    switch (reg) {
        case Register::al:
            return registers[0];
        case Register::bl:
            return registers[1];
        case Register::cl:
            return registers[2];
        case Register::dl:
            return registers[3];
        case Register::el:
            return registers[4];
        case Register::cf:
            return carryFlag;
        default:
            return 0;
    }
}

bool emu::VM::setRegister(emu::Register reg, uint8_t value) {
    switch (reg) {
        case Register::al:
            registers[0] = value;
            break;
        case Register::bl:
            registers[1] = value;
            break;
        case Register::cl:
            registers[2] = value;
            break;
        case Register::dl:
            registers[3] = value;
            break;
        case Register::el:
            registers[4] = value;
            break;
        case Register::cf:
            carryFlag = value;
            break;
        default:
            errorMessage.clear();
            errorMessage.append("Unknown register.");
            return false;

    }

    return true;
}

bool emu::VM::run() {
    while (index < assembly->get_data().size()) {
        if (!exec()) {
            // TODO: Error handling?
            return false;
        }
    }

    return true;
}

bool emu::VM::exec() {
    auto opcode = (Opcode) assembly->read8(index++);

    switch (opcode) {
        case Opcode::Move:
            return runMove();
        case Opcode::Pop:
            return runPop();
        case Opcode::Push:
            return runPush();
        case Opcode::PushValue:
            return runPushValue();
        default:
            errorMessage.clear();
            errorMessage.append("Unknown instruction.");
            return false;
    }
}

bool emu::VM::runMove() {
    auto reg1 = (Register) assembly->read8(index++);
    auto reg2 = (Register) assembly->read8(index++);
    return setRegister(reg1, getRegister(reg2));
}


bool emu::VM::runPop() {
    auto reg = (Register) assembly->read8(index++);
    if (!setRegister(reg, stack.top())) return false;
    stack.pop();
    return true;
}

bool emu::VM::runPush() {
    auto reg = (Register) assembly->read8(index++);
    stack.push(getRegister(reg));
    return true;
}

bool emu::VM::runPushValue() {
    stack.push(assembly->read8(index++));
    return true;
}
