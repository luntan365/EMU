//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_SECTION_H
#define EMU_SECTION_H

#include <string>
#include <vector>
#include "LabelContext.h"

namespace emu
{
    class SectionContext
    {
    public:
        explicit SectionContext(std::string name);
        explicit SectionContext(std::string& name);
        std::string get_name() const;
        std::vector<LabelContext *> const &get_labels() const;
        void addLabel(LabelContext*);

    private:
        std::string name;
        std::vector<emu::LabelContext*> labels;
    };
}


#endif //EMU_SECTION_H
