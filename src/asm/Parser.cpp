//
// Created by Tobe on 4/7/18.
//

#include "Parser.h"
#include <iostream>

emu::Parser::Parser(std::vector<Token *> &tokens) {
    this->tokens = tokens;
}

std::vector<emu::AssemblerError> const &emu::Parser::get_errors() const {
    return errors;
}

emu::AssemblyContext *emu::Parser::parseAssembly() {
    auto *assembly = new AssemblyContext;
    auto *section = parseSection();

    while (section != nullptr) {
        assembly->addSection(section);
        section = parseSection();
    }

    /*
    while (index < tokens.size()) {
        auto *section = parseSection();
        if (section != nullptr)
            assembly->addSection(section);
        index++;
    }*/

    return assembly;
}

emu::Token *emu::Parser::next() {
    if (index < tokens.size()) {
        return tokens.at(index++);
    }

    return nullptr;
}

emu::Token *emu::Parser::next(emu::Token::TokenType type) {
    auto *token = next();
    if (token == nullptr || token->get_type() == type)
        return token;
    index--;
    return nullptr;
}

emu::Token *emu::Parser::nextExpression() {
    auto *token = next(Token::TokenType::Identifier);
    if (token != nullptr) return token;
    return next(Token::TokenType::Number);
}

emu::SectionContext *emu::Parser::parseSection() {
    auto *token = next(Token::TokenType::Section);

    if (token == nullptr)
        return nullptr;

    auto *dot = next(Token::TokenType::Dot);

    if (dot == nullptr) {
        AssemblerError error;
        error.sourceUrl = token->get_source_url();
        error.text = new std::string("Missing '.' after 'section'.");
        error.line = token->get_line();
        error.column = token->get_column();
        errors.push_back(error);
        return nullptr;
    }

    auto *id = next(Token::TokenType::Identifier);

    if (id == nullptr) {
        AssemblerError error;
        error.sourceUrl = dot->get_source_url();
        error.text = new std::string("Missing identifier after '.'.");
        error.line = dot->get_line();
        error.column = dot->get_column();
        errors.push_back(error);
        return nullptr;
    }

    auto *section = new SectionContext(id->get_text());
    auto *label = parseLabel();

    while (label != nullptr) {
        section->addLabel(label);
        label = parseLabel();
    }

    return section;
}

emu::LabelContext *emu::Parser::parseLabel() {
    auto *token = next(Token::TokenType::Label);

    if (token == nullptr)
        return nullptr;

    auto *colon = next(Token::TokenType::Colon);

    if (colon == nullptr) {
        AssemblerError error;
        error.sourceUrl = token->get_source_url();
        error.text = new std::string("Missing ':' after label '");
        error.text->append(token->get_text());
        error.text->append("'.");
        error.line = token->get_line();
        error.column = token->get_column();
        errors.push_back(error);
        return nullptr;
    }

    auto *label = new LabelContext(token->get_text());
    auto *instruction = parseInstruction();

    while (instruction != nullptr) {
        label->addInstruction(instruction);
        instruction = parseInstruction();
    }

    return label;
}

emu::InstructionContext *emu::Parser::parseInstruction() {
    auto *id = next(Token::TokenType::Identifier);

    if (id == nullptr)
        return nullptr;

    Opcode opcode = Opcode::Unknown;

    if (id->get_text() == "push")
        opcode = Opcode::Push;
    else if (id->get_text() == "pop")
        opcode = Opcode::Pop;
    else if (id->get_text() == "mov")
        opcode = Opcode::Move;
    else if (id->get_text() == "cmp")
        opcode = Opcode::Compare;
    else if (id->get_text() == "and")
        opcode = Opcode::And;
    else if (id->get_text() == "or")
        opcode = Opcode::Or;
    else if (id->get_text() == "xor")
        opcode = Opcode::Xor;
    else if (id->get_text() == "not")
        opcode = Opcode::Negate;

    // Find the instruction that corresponds.
    if (opcode == Opcode::Unknown) {
        AssemblerError error;
        error.sourceUrl = id->get_source_url();
        error.text = new std::string("Unknown opcode '");
        error.text->append(id->get_text());
        error.text->append("'.");
        error.line = id->get_line();
        error.column = id->get_column();
        errors.push_back(error);
        return nullptr;
    }

    auto *instruction = new InstructionContext((uint8_t) opcode, id);
    auto *operand = nextExpression();

    while (operand != nullptr) {
        instruction->addOperand(operand);

        if (next(Token::TokenType::Comma) == nullptr)
            break;

        operand = nextExpression();
    }

    return instruction;
}
