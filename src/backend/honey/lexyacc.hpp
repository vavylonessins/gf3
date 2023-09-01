#ifndef __LEXYACC_H__
#define __LEXYACC_H__

#include "../other/regex.hpp"
#include <iostream>
#include <unordered_set>
#include <fstream>
#include "../other/itoa.hpp"
#include "../other/hacks.hpp"

typedef uint32 lineno;

enum TokType {
    ELLIPSE,
    DOT,
    NAME,
    FLOAT,
    INT,
    STR
};

class LexRules {
    public:

    LexRules(TokType *names, std::string *regexes): names(names), regexes(regexes) {};

    TokType* names;
    std::string* regexes;
};

std::string regexes[6] = {
    "\\.{3}",
    "\\.(?!\\.)",
    "\\b[A-Za-zА-Яа-яЁё_]\\w*\\b",
    "\\b\\d*\\.\\d+\\b",
    "\\b\\d+\\b",
    "\".*(?=\")\""
};

const LexRules LEXRULES = LexRules(
    (TokType[]){
        ELLIPSE,
        DOT,
        NAME,
        FLOAT,
        INT,
        STR
    },
    regexes
);

class Token {
    /*
     *  A simple Token std::stringucture.
     *  Contains the token type, value and position.
     */

    public:

    Token(const std::string& tokenValue_, TokType tokenType_): tokenValue(tokenValue_), tokenType(tokenType_), real(true){ /* empty */ }

    Token(const Token& token): tokenValue(token.tokenValue), tokenType(token.tokenType), real(true){ /* empty */ }

    Token(): real(false){ /* empty */ }

    /* char *toa() {
        char itoa_buffer[32];
        itoa(this->pos, itoa_buffer, 32, 10);
        char *rval = (char*)malloc(std::stringlen(TokenTypeNames[(int)this->type])+std::stringlen(this->val)+std::stringlen(itoa_buffer)+6);
        memcpy(rval, TokenTypeNames[(int)this->type], std::stringlen(TokenTypeNames[(int)this->type]));
        memcpy(rval+std::stringlen(TokenTypeNames[(int)this->type]), "(", 1);
        memcpy(rval+std::stringlen(TokenTypeNames[(int)this->type])+1, this->val, std::stringlen(this->val));
        memcpy(rval+std::stringlen(TokenTypeNames[(int)this->type])+std::stringlen(this->val)+1, ") at ", 5);
        memcpy(rval+std::stringlen(TokenTypeNames[(int)this->type])+std::stringlen(this->val)+6, itoa_buffer, std::stringlen(itoa_buffer));
        return rval;
    }; */

    std::string tokenValue;
    TokType tokenType;
    bool real;
};


class Lexer {
    public:

    Lexer(const std::string rules[][2], bool skip_ws) {
        this->rules = (std::string**)rules;
        this->skip_ws = skip_ws;
    };

    void input(std::string buf) {
        this->buffer = buffer;
        this->pos = 0;
    };

    Token token() {
        bool m;
        Lexer self = *this;
        if (this->pos >= (int)this->buffer.length()) {
            return Token();
        } else {
            if (this->skip_ws) {
                //m = std::regex_search(this->buffer, match, std::regex("\\S"));

                if (m) {
                    //this->pos = match.position();
                } else {
                    return Token();
                };
            };
        };

        for (int i = 0; i < 6; i++) {
            //m = std::regex_match(this->buffer, match, std::regex((*this).rules.regexes[i]));
        }
    };

    std::string **rules;
    bool skip_ws;
    std::string buffer;
    int pos;
};


#endif
