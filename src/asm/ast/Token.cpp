//
// Created by Tobe on 4/7/18.
//

#include "Token.h"

emu::Token::Token(std::string &pSourceUrl, std::string &pText, emu::Token::TokenType pType, int pLine, int pColumn)
{
    mSourceUrl = pSourceUrl;
    mText = pText;
    mType = pType;
    mLine = pLine;
    mColumn = pColumn;
}

emu::Token::Token(std::string &pSourceUrl, const char *pText, emu::Token::TokenType pType, int pLine, int pColumn)
{
    std::string text(pText);
    mSourceUrl = pSourceUrl;
    mText = text;
    mType = pType;
    mLine = pLine;
    mColumn = pColumn;
}

std::string emu::Token::get_text() const
{
    return mText;
}

emu::Token::TokenType emu::Token::get_type() const
{
    return mType;
}

std::string* emu::Token::get_source_url()
{
    return &mSourceUrl;
}

int emu::Token::get_line() const
{
    return mLine;
}

int emu::Token::get_column() const
{
    return mColumn;
}

uint8_t emu::Token::get_number_value() const
{
    return mNumberValue;
}

void emu::Token::set_number_value(uint8_t value)
{
    mNumberValue = value;
}
