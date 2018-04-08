//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_SCANNER_H
#define EMU_SCANNER_H

#include <cctype>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include "AssemblerError.h"
#include "ast/Token.h"

namespace emu
{
    class Scanner
    {
    public:
        std::vector<Token *> scan(std::string &sourceUrl, std::istream &stream);

        std::vector<AssemblerError> const &get_errors() const;

    private:
        std::vector<AssemblerError> errors;
    };
}


#endif //EMU_SCANNER_H
