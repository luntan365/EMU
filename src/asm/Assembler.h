//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_ASSEMBLER_H
#define EMU_ASSEMBLER_H

#include <string>
#include <vector>
#include "../vm/Assembly.h"
#include "../vm/Register.h"
#include "ast/ast.h"
#include "AssemblerError.h"

namespace emu
{
    class Assembler
    {
    public:
        explicit Assembler(AssemblyContext *);

        Assembly *assemble();

        std::vector<AssemblerError> const &get_errors() const;

    private:
        void assembleLocal(LabelContext *, std::map<std::string, Assembly *> &);
        void emitMissingOperand(const char *instruction, Token *token);
        void emitTypeMismatch(const char *type, Token *token);
        Register compileRegister(Token*);
        AssemblyContext *ctx;
        std::vector<AssemblerError> errors;
    };
}

#endif //EMU_ASSEMBLER_H
