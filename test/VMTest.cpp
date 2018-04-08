#include "../src/vm/VM.h"

using namespace emu;

int main(int argc, char** argv)
{
    emu::Assembly program;
    emu::VM vm;

    // Set register 0 to 1337
    uint64_t leet = 1337;
    auto *leetPtr = reinterpret_cast<uint8_t *>(&leet);
    program.get_data()->push_back(emu::VM::Instructions::SetRegister);

    // Write 8 bytes of 1337
    for (int i = 0; i < 8; i++)
        program.get_data()->push_back(leetPtr[i]);

    vm.run(program);

    return 0;
}