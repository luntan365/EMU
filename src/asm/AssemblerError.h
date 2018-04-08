//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_ASSEMBLERERROR_H
#define EMU_ASSEMBLERERROR_H

#include <string>

namespace emu
{
    typedef struct
    {
        std::string *sourceUrl, *text;
        int line, column;
        bool isError = true;
    } AssemblerError;
}

#endif //EMU_ASSEMBLERERROR_H
