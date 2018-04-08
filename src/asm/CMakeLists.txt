add_subdirectory(ast)
add_library(asm
        Parser.h Parser.cpp
        Scanner.cpp Scanner.h
        AssemblerError.h
        Linker.cpp Linker.h
        Loader.cpp Loader.h
        asm.h
        Assembler.cpp Assembler.h)
target_link_libraries(asm ast)