//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_LINKER_H
#define EMU_LINKER_H

#include <vector>
#include "../vm/Assembly.h"
#include "ast/AssemblyContext.h"

namespace emu
{
    class Linker
    {
    public:
        Assembly* link(std::vector<Assembly*>&);
    };
}


#endif //EMU_LINKER_H
