//
// Created by Tobe on 4/7/18.
//

#include <cstdint>
#include "../vm/Opcode.h"
#include "Assembler.h"

emu::Assembler::Assembler(emu::AssemblyContext *ctx) {
    this->ctx = ctx;
}

emu::Assembly *emu::Assembler::assemble() {
    // The gist of it is:
    std::map<std::string, Assembly *> map;
    auto *output = new Assembly;

    // TODO: Ensure there is a _start

    // 1. Compile each label locally, into its own map.
    //  1a. When a jump/call is hit, create a slot for the jump without compiling it.
    for (auto section : ctx->get_sections()) {
        for (auto label : section->get_labels()) {
            // TODO: Make sure labels are not duplicated.
            assembleLocal(label, map);
        }
    }

    // 2. For each label, compute the offset.
    unsigned long offset = 0, startOffset = 0;

    for (const auto &pair: map) {
        if (pair.first == "_start")
            startOffset = offset;


        // 3. Go through each map, compiling each jump.
        for (const auto &pair2: map) {
            pair2.second->resolvePendingJumps(pair.first, offset);
        }

        offset += pair.second->get_data().size();

        for (unsigned char i : pair.second->get_data()) {
            output->write8(i);
        }
    }

    // 4. Next, create the final bundle.
    //  4a. Write the _start offset.
    output->set_start_offset((uint64_t) startOffset);
    return output;
}

std::vector<emu::AssemblerError> const &emu::Assembler::get_errors() const {
    return errors;
}

emu::Register emu::Assembler::compileRegister(Token *token) {
    if (token->get_text() == "al")
        return Register::al;
    else if (token->get_text() == "bl")
        return Register::bl;
    else if (token->get_text() == "cl")
        return Register::cl;
    else if (token->get_text() == "dl")
        return Register::dl;
    else if (token->get_text() == "el")
        return Register::el;

    AssemblerError error;
    error.text = new std::string("Unknown register '");
    error.text->append(token->get_text());
    error.text->append("'.");
    error.sourceUrl = token->get_source_url();
    error.line = token->get_line();
    error.column = token->get_column();
    errors.push_back(error);
    return Register::Unknown;
}

void emu::Assembler::emitMissingOperand(const char *instruction, Token *token) {
    AssemblerError error;
    error.text = new std::string("Missing operand for instruction '");
    error.text->append(instruction);
    error.text->append("'.");
    error.sourceUrl = token->get_source_url();
    error.line = token->get_line();
    error.column = token->get_column();
    errors.push_back(error);
}

void emu::Assembler::emitTypeMismatch(const char *type, Token *token) {
    AssemblerError error;
    error.text = new std::string("Invalid operand '");
    error.text->append(token->get_text());
    error.text->append("', expected ");
    error.text->append(type);
    error.text->append(".");
    error.sourceUrl = token->get_source_url();
    error.line = token->get_line();
    error.column = token->get_column();
    errors.push_back(error);
}

void emu::Assembler::assembleLocal(emu::LabelContext *label, std::map<std::string, Assembly *> &map) {
    auto *assembly = new Assembly;
    map.insert(std::make_pair(label->get_name(), assembly));

    for (const auto *instruction : label->get_instructions()) {
        auto opcode = (Opcode) instruction->get_opcode();

        if (opcode == Opcode::Push) {
            if (instruction->get_operands().empty()) {
                emitMissingOperand("push", instruction->get_opcode_token());
            } else {
                auto *operand = instruction->get_operands().at(0);

                // If pushing a number, switch to PushValue
                if (operand->get_type() == Token::TokenType::Number) {
                    assembly->write8((uint8_t) Opcode::PushValue);
                    assembly->write8(operand->get_number_value());
                } else if (operand->get_type() == Token::TokenType::Identifier) {
                    assembly->write8((uint8_t) Opcode::Push);
                    assembly->write8((uint8_t) compileRegister(operand));
                }
            }
        } else if (opcode == Opcode::Pop) {
            if (instruction->get_operands().empty()) {
                emitMissingOperand("pop", instruction->get_opcode_token());
            } else {
                auto *operand = instruction->get_operands().at(0);

                if (operand->get_type() == Token::TokenType::Identifier) {
                    assembly->write8((uint8_t) Opcode::Pop);
                    assembly->write8((uint8_t) compileRegister(operand));
                } else {
                    emitTypeMismatch("register", operand);
                }
            }
        } else if (opcode == Opcode::Move) {
            if (instruction->get_operands().empty()) {
                emitMissingOperand("mov", instruction->get_opcode_token());
            } else if (instruction->get_operands().size() == 1) {
                emitMissingOperand("mov", instruction->get_operands().at(0));
            } else {
                assembly->write8((uint8_t) Opcode::Move);

                for (unsigned long i = 0; i < 2; i++) {
                    auto *operand = instruction->get_operands().at(i);

                    if (operand->get_type() == Token::TokenType::Identifier) {
                        assembly->write8((uint8_t) compileRegister(operand));
                    } else {
                        emitTypeMismatch("register", operand);
                    }
                }
            }
        } else {
            auto *token = instruction->get_opcode_token();
            AssemblerError error;
            error.text = new std::string("Unknown instruction '");
            error.text->append(token->get_text());
            error.text->append("'.");
            error.sourceUrl = token->get_source_url();
            error.line = token->get_line();
            error.column = token->get_column();
            errors.push_back(error);
        }
    }
}
