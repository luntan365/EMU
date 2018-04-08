//
// Created by Tobe on 4/7/18.
//

#ifndef VM_PROGRAM_H
#define VM_PROGRAM_H

#include <string>
#include <vector>
#include <unitypes.h>
#include <cstdint>
#include <cstring>
#include <map>

namespace emu
{
    class Assembly
    {
    public:
        static const uint32_t Header = 0xDADDB0DD; // Yes, dad bod.

        void resolvePendingJumps(const std::string& name, uint64_t offset);

        void* read(unsigned long index, size_t size);
        uint8_t read8(unsigned long index);
        uint16_t read16(unsigned long index);
        uint32_t read32(unsigned long index);
        uint64_t read64(unsigned long index);

        void write(uint8_t *buf, size_t size);

        void write8(uint8_t);

        void write16(uint16_t);

        void write32(uint32_t);

        void write64(uint64_t);

        void writeString(const char *);

        void writeString(std::string &);

        std::vector<uint8_t> const &get_data() const;

        uint64_t get_start_offset() const;

        void set_start_offset(uint64_t);

    private:
        std::map<unsigned long, std::string> pendingJumps;
        std::vector<uint8_t> data;
        uint64_t startOffset = 0;
    };
}


#endif //VM_PROGRAM_H
