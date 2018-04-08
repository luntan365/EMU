//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_INSTRUCTION_H
#define EMU_INSTRUCTION_H

#include <ostream>
#include <vector>
#include <unitypes.h>
#include "Token.h"

namespace emu
{
    class InstructionContext
    {
    public:
        InstructionContext(uint8_t opcode, Token* opcodeToken);

        uint8_t get_opcode() const;

        std::vector<Token *> const &get_operands() const;

        Token* get_opcode_token() const;

        void addOperand(Token *);

    private:
        uint8_t opcode;
        Token* opcodeToken;
        std::vector<Token *> operands;
    };
}


#endif //EMU_INSTRUCTION_H
