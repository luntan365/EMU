//
// Created by Tobe on 4/7/18.
//

#ifndef EMU_TOKEN_H
#define EMU_TOKEN_H

#include <unitypes.h>
#include <string>

namespace emu
{
    class Token
    {
    public:
        enum class TokenType
        {
            Colon,
            Comma,
            Dot,
            Global,
            Identifier,
            Label,
            Number,
            Section
        };

        Token(std::string& pSourceUrl, std::string& pText, TokenType pType, int pLine, int pColumn);

        Token(std::string& pSourceUrl, const char* pText, TokenType pType, int pLine, int pColumn);

        std::string get_text() const;

        TokenType get_type() const;

        std::string* get_source_url();

        int get_line() const;

        int get_column() const;

        uint8_t get_number_value() const;

        void set_number_value(uint8_t);

    private:
        std::string mText, mSourceUrl;
        TokenType mType;
        int mLine, mColumn;
        uint8_t mNumberValue;
    };
}

#endif //EMU_TOKEN_H
