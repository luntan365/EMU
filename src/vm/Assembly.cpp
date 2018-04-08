//
// Created by Tobe on 4/7/18.
//

#include <iostream>
#include "Assembly.h"

std::vector<uint8_t> const &emu::Assembly::get_data() const {
    return data;
}

uint64_t emu::Assembly::get_start_offset() const {
    return startOffset;
}

void emu::Assembly::set_start_offset(uint64_t value) {
    startOffset = value;
}

void *emu::Assembly::read(unsigned long index, size_t size) {
    auto count = size / sizeof(uint8_t);
    auto buf = new uint8_t[count];

    for (unsigned long i = 0; i < size; i++) {
        buf[i] = data.at(index + i);
    }

    return buf;
}

uint8_t emu::Assembly::read8(unsigned long index) {
    return *((uint8_t *) read(index, sizeof(uint8_t)));
}

uint16_t emu::Assembly::read16(unsigned long index) {
    return *((uint16_t *) read(index, sizeof(uint16_t)));
}

uint32_t emu::Assembly::read32(unsigned long index) {
    return *((uint32_t *) read(index, sizeof(uint32_t)));
}

uint64_t emu::Assembly::read64(unsigned long index) {
    //return data.front() + index;
    //return (data.data()[index]);
    return *((uint64_t *) read(index, sizeof(uint64_t)));
}

void emu::Assembly::write(uint8_t *buf, size_t size) {
    for (int i = 0; i < size; i++)
        write8(buf[i]);
}

void emu::Assembly::write8(unistring_uint8_t value) {
    data.push_back(value);
}

void emu::Assembly::write16(unistring_uint16_t value) {
    auto *ptr = (uint8_t *) &value;

    for (int i = 1; i >= 0; i--)
        write8(ptr[i]);
}

void emu::Assembly::write32(unistring_uint32_t value) {
    auto *ptr = (uint8_t *) &value;

    for (int i = 3; i >= 0; i--)
        write8(ptr[i]);
}

void emu::Assembly::write64(uint64_t value) {
    auto *ptr = (uint8_t *) &value;
    //std::cout << "writing 64 " << value << std::endl;

    for (int i = 7; i >= 0; i--) {
        //std::cout << i << ": " << (int) ptr[i] << std::endl;
        write8(ptr[i]);
    }
}

void emu::Assembly::writeString(const char *value) {
    for (int i = 0; i < strlen(value); i++) {
        write8((uint8_t) value[i]);
    }

    write8(0);
}

void emu::Assembly::writeString(std::string &value) {
    writeString(value.c_str());
}

void emu::Assembly::resolvePendingJumps(const std::string &name, uint64_t offset) {
    for (const auto &pair : pendingJumps) {
        if (pair.second == name) {
            auto *ptr = (uint8_t *) &offset;

            for (unsigned long i = 0; i < 8; i++) {
                data.at(pair.first + i) = ptr[i];
            }
        }
    }
}
