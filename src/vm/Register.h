//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_REGISTER_H
#define EMU_REGISTER_H

namespace emu
{
    enum class Register : uint8_t
    {
        Unknown,
        //ax, bx, cx, dx, ex,
        //ah, bh, ch, dh, eh,
        al, bl, cl, dl, el,
        cf,
    };
}

#endif //EMU_REGISTER_H
