//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_LABELCONTEXT_H
#define EMU_LABELCONTEXT_H

#include <string>
#include "InstructionContext.h"

namespace emu
{
    class LabelContext
    {
    public:
        explicit LabelContext(std::string name);

        explicit LabelContext(std::string &name);

        std::string get_name() const;

        std::vector<InstructionContext *> const &get_instructions() const;

        void addInstruction(InstructionContext *);

    private:
        std::string name;
        std::vector<emu::InstructionContext *> instructions;

    };
}


#endif //EMU_LABELCONTEXT_H
