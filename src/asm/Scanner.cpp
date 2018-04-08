//
// Created by Tobe on 4/7/18.
//

#include <iostream>
#include "Scanner.h"
#include "AssemblerError.h"

std::vector<emu::AssemblerError> const &emu::Scanner::get_errors() const {
    return errors;
}

std::vector<emu::Token *> emu::Scanner::scan(std::string &sourceUrl, std::istream &stream) {
    int line = 1, column = 0;
    std::vector<emu::Token *> tokens;
    char ch;

    while ((ch = (char) stream.get()) != EOF) {
        column++;

        // Ignore comments
        if (ch == ';') {
            while ((ch = (char) stream.get()) != EOF) {
                if (ch == '\n')
                    break;
            }
        }

        if (ch == '\n') {
            line++;
            column = 0;
            continue;
        }

        if (iswspace(ch))
            continue;

        if (ch == ':') {
            tokens.push_back(new Token(sourceUrl, ":", Token::TokenType::Colon, line, column));
            continue;
        }

        if (ch == ',') {
            tokens.push_back(new Token(sourceUrl, ",", Token::TokenType::Comma, line, column));
            continue;
        }

        if (ch == '.') {
            tokens.push_back(new Token(sourceUrl, ".", Token::TokenType::Dot, line, column));
            continue;
        }

        // Scan for hex
        if (ch == '0') {
            ch = (char) stream.peek();

            if (ch != 'x') {
                stream.putback('0');
            } else {
                std::stringstream buf;
                stream.get();

                while ((ch = (char) stream.get())!= EOF) {
                    if (!isdigit(ch)) {
                        stream.putback(ch);
                        break;
                    } else {
                        buf << ch;
                    }
                }

                std::string text("0x");
                text.append(buf.str());
                auto *token = new Token(sourceUrl, text, Token::TokenType::Number, line, column);

                if (buf.str().empty()) {
                    AssemblerError error;
                    error.sourceUrl = &sourceUrl;
                    error.text = new std::string("Expected a numeral after '0x'.");
                    error.line = line;
                    error.column = column < 0 ? 0 : column;
                    errors.push_back(error);
                    continue;
                }

                // Parse as base-16
                auto value = (uint8_t) std::stoi(buf.str(), nullptr, 16);
                token->set_number_value(value);
                tokens.push_back(token);
                column += buf.str().length() - 1;
            }
        }

        // Check for base-10 numbers
        if (isdigit(ch)) {
            std::stringstream buf;
            buf << ch;

            while ((ch = (char) stream.get()) != EOF) {
                if (!isdigit(ch)) {
                    stream.putback(ch);
                    break;
                } else {
                    buf << ch;
                }
            }

            auto *token = new Token(sourceUrl, buf.str().c_str(), Token::TokenType::Number, line, column);
            // Parse as base-10
            auto value = (uint8_t) std::stoi(buf.str());
            token->set_number_value(value);
            tokens.push_back(token);
            column += buf.str().length() - 1;
        }

        // Finally, check for ID/keywords
        if (isalpha(ch) || ch == '_') {
            std::stringstream buf;
            buf << ch;

            while ((ch = (char) stream.get()) != EOF) {
                if (iswspace(ch) || (!isalnum(ch) && ch != '_')) {
                    stream.putback(ch);
                    break;
                } else {
                    buf << ch;
                }
            }

            Token::TokenType type = Token::TokenType::Identifier;

            if (buf.str() == "section")
                type = Token::TokenType::Section;
            if (buf.str().find('_') == 0)
                type = Token::TokenType::Label;

            auto *token = new Token(sourceUrl, buf.str().c_str(), type, line, column);
            tokens.push_back(token);
            column += buf.str().length() - 1;
            continue;
        }

        if (ch != EOF && !iswspace(ch)) {
            // Or, emit a scanner error
            AssemblerError error;
            error.sourceUrl = &sourceUrl;
            error.text = new std::string("unexpected character: '");
            error.text->append(&ch, 1);
            error.text->append("'");
            error.line = line;
            error.column = column < 0 ? 0 : column;
            errors.push_back(error);
        }
    }

    return tokens;
}
