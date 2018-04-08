//
// Created by Tobe on 4/7/18.
//

#include "SectionContext.h"
#include <utility>

emu::SectionContext::SectionContext(std::string name) {
    this->name = std::move(name);
}

emu::SectionContext::SectionContext(std::string &name) {
    this->name = name;
}

std::vector<emu::LabelContext *> const &emu::SectionContext::get_labels() const {
    return labels;
}

std::string emu::SectionContext::get_name() const {
    return name;
}

void emu::SectionContext::addLabel(emu::LabelContext *instruction) {
    labels.push_back(instruction);
}
