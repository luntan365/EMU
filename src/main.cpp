#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "asm/asm.h"
#include "vm/VM.h"

int asmMain(int argc, const char **argv);

void printUsage(std::ostream &);

void printAsmUsage(std::ostream &);

void printErrors(std::vector<emu::AssemblerError>);

void printUsage(std::ostream &stream) {
    stream << "Usage: emu [options...] <command>\n" << std::endl;
    stream << "Commands:" << std::endl;
    stream << "\tasm: Assemble a source file." << std::endl;
    stream << "\tvm:  Execute an assembly." << std::endl;
}

void printAsmUsage(std::ostream &stream) {
    stream << "Usage: emu asm [options...] <input_file>\n" << std::endl;
}

int main(int argc, const char **argv) {
    if (argc < 2) {
        printUsage(std::cerr);
        return 1;
    }

    const char *arg = argv[1];

    if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
        printUsage(std::cout);
        return 0;
    }

    if (!strcmp(arg, "asm"))
        return asmMain(argc - 1, argv + 2);

    printUsage(std::cerr);
    return 1;
}

void printErrors(std::vector<emu::AssemblerError> errors) {
    for (auto error: errors) {
        if (!error.isError)
            std::cerr << "warning";
        else std::cerr << "error";

        std::cerr << ": " << *error.sourceUrl << ":" << error.line << ":" << error.column << ": " << *error.text
                  << std::endl;
    }
}

int asmMain(int argc, const char **argv) {
    if (argc < 2) {
        printAsmUsage(std::cerr);
        return 1;
    }

    const char *inputFile = nullptr;

    for (int i = 0; i < argc; i++) {
        const char *arg = argv[i];

        if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
            printAsmUsage(std::cout);
            return 0;
        } else {
            inputFile = arg;
            break;
        }
    }

    if (inputFile == nullptr) {
        printAsmUsage(std::cerr);
        return 1;
    }

    std::ifstream ifs(inputFile);

    if (!ifs) {
        std::cerr << inputFile << ": file does not exist" << std::endl;
        return 1;
    }

    auto *scanner = new emu::Scanner;
    std::string sourceUrl(inputFile);
    auto tokens = scanner->scan(sourceUrl, ifs);

    if (!scanner->get_errors().empty()) {
        printErrors(scanner->get_errors());
        return 1;
    }

    /*
    for (auto token : tokens) {
        std::cout << token->get_text() << ":" << (int) token->get_type() << std::endl;
    }
    */

    // Parse the scanned text
    auto *parser = new emu::Parser(tokens);
    auto *ctx = parser->parseAssembly();

    if (!parser->get_errors().empty()) {
        printErrors(parser->get_errors());
        return 1;
    }

    // Now, compile.
    auto *assembler = new emu::Assembler(ctx);
    auto *assembly = assembler->assemble();

    if (!assembler->get_errors().empty()) {
        printErrors(assembler->get_errors());
        return 1;
    }

    // TODO: Separate linking into a dedicated process

    // Finally, we can run the program.
    auto *vm = new emu::VM(assembly);

    if (!vm->run()) {
        std::cerr << "Error: " << vm->get_error_message() << std::endl << std::endl;
        vm->dump(std::cerr);
        return 1;
    }

    vm->dump(std::cout);

    return 0;
}