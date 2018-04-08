//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_LOADER_H
#define EMU_LOADER_H

#include "../vm/Assembly.h"
#include "ast/AssemblyContext.h"

namespace emu
{
    class Loader
    {
    public:
        explicit Loader(AssemblyContext*);
        Assembly *load();

    private:
        AssemblyContext* assembly;
    };
}


#endif //EMU_LOADER_H
