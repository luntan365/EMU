//
// Created by Tobe on 4/7/18.
//

#ifndef VM_VM_H
#define VM_VM_H

#include <ostream>
#include <stack>
#include <string>
#include "Assembly.h"
#include "Opcode.h"
#include "Register.h"

namespace emu
{
    class VM
    {
    public:
        explicit VM(emu::Assembly *);

        void dump(std::ostream &);

        bool run();

        std::string get_error_message() const;

    private:
        uint8_t getRegister(Register reg);
        bool setRegister(Register reg, uint8_t value);
        bool exec();
        bool runMove();
        bool runPop();
        bool runPush();
        bool runPushValue();

        std::string errorMessage;
        Assembly *assembly;
        uint8_t carryFlag;
        unsigned long index;
        uint8_t registers[5];
        std::stack<uint8_t> stack;
    };
}


#endif //VM_VM_H
