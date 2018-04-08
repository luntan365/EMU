//
// Created by Tobe on 4/7/18.
//

#include "AssemblyContext.h"

std::vector<emu::SectionContext *> const &emu::AssemblyContext::get_sections() const {
    return mSections;
}

void emu::AssemblyContext::addSection(emu::SectionContext *section) {
    mSections.push_back(section);
}
