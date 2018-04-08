//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_INSTRUCTIONS_H
#define EMU_INSTRUCTIONS_H

#include <cstdint>

namespace emu
{
    enum class Opcode : uint8_t
    {
        Unknown,

        // Stack
                Push,
        PushValue,
        PopToAddress,
        Pop,

        // Register
        Move,
        Allocate,
        Free,

        // Booleans
                Compare,
        And,
        Or,
        Xor,
        Negate,

        // Arithmetic
        Multiply,
        Divide,
        Modulo,
        Add,
        Subtract,

        // Control flow
                Call,
        Loop,
        Jump,
        JumpIfZero,
        JumpIfEqual,
        JumpIfNotEqual,
        JumpIfLesser,
        JumpIfLesserOrEqual,
        JumpIfGreater,
        JumpIfGreaterOrEqual,
        Return
    };
}

#endif //EMU_INSTRUCTIONS_H
