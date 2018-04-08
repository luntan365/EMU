//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_ASSEMBLY_H
#define EMU_ASSEMBLY_H

#include <vector>
#include "SectionContext.h"

namespace emu
{
    class AssemblyContext
    {
    public:
        std::vector<SectionContext *> const &get_sections() const;
        void addSection(SectionContext*);

    private:
        std::vector<SectionContext *> mSections;
    };

}

#endif //EMU_ASSEMBLY_H
