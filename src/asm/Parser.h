//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_PARSER_H
#define EMU_PARSER_H

#include "ast/ast.h"
#include "../vm/Opcode.h"
#include "AssemblerError.h"
#include "ast/AssemblyContext.h"
#include "ast/SectionContext.h"
#include "Scanner.h"

namespace emu
{
    class Parser
    {
    public:
        explicit Parser(std::vector<Token *> &tokens);

        AssemblyContext *parseAssembly();

        std::vector<AssemblerError> const &get_errors() const;

    private:
        Token *next();

        Token *next(Token::TokenType);

        Token *nextExpression();

        InstructionContext *parseInstruction();

        SectionContext *parseSection();

        LabelContext *parseLabel();

        std::vector<AssemblerError> errors;
        std::vector<Token *> tokens;
        unsigned long index = 0;
    };
}


#endif //EMU_PARSER_H
