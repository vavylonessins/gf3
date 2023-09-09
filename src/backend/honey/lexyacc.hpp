#ifndef __LEXYACC_H__
#define __LEXYACC_H__

#include "../types.hpp"
#include <iostream>
#include <unordered_set>
#include <fstream>
#include "../other/itoa.hpp"
#include "../other/hacks.hpp"
#include "../other/vec.hpp"

namespace honey {

    using namespace std;

    enum TokenType : int {
        NONE,              // null type
        NAME,              // [A-Za-z_]\w*
        COLON,             // \:
        EQUAL,             // \=
        INT, NE,           // \d+           // \!=|\<\>
        ARLEFT,            // \<-
        CULEFT,            // \{
        BUX,               // \$
        PALEFT,            // \(
        PARIGHT,           // \)
        STRING,            // \".*(?=\")\"
        CURIGHT,           // \}
        GT, LT,            // >             // >
        GE, LE,            // >=            // >=
        ARRIGHT,           // -\>
        SHL, SHR,          // \<\<          // \>\>
        BLLEFT,            // \[
        BLRIGHT,           // \]
        PLUS, MINUS,       // \+            // -
        MULT, DIV,         // \*            // /
        POW, IDIV, MOD,    // \*\*          // \/\/  // \%
        OR, AND, XOR,      // \|            // \&    // \^
        NOT, NEG, BINNEG,  // \!            // -     // \~
        COUNT              // -1 type
    };

    #if COUNT < 255
        typedef u8 token;
    #elif COUNT < 65535
        typedef u16 token;
    #elif COUNT < 4294967295
        typedef u32 token;
    #elif COUNT < 18446744073709599999
        typedef u64 token;
    #endif

    char errors[] = {};

    string toktypes[] = {
        "NONE",     // V
        "NAME",     // V
        "COLON",    // V
        "EQUAL",    // V
        "INT",      // V
        "NE",       // O
        "ARLEFT",   // V
        "CULEFT",   // X
        "BUX",      // X
        "PALEFT",   // X
        "PARIGHT",  // X
        "STRING",   // X
        "CURIGHT",  // X
        "GT",       // V
        "LT",       // V
        "GE",       // V
        "LE",       // V
        "ARRIGHT",  // X
        "SHL",      // X
        "SHR",      // X
        "BLLEFT",   // X
        "BLRIGHT",  // X
        "PLUS",     // X
        "MINUS",    // X
        "MULT",     // X
        "DIV",      // X
        "POW",      // X
        "IDIV",     // X
        "MOD",      // X
        "OR",       // X
        "AND",      // X
        "XOR",      // X
        "NOT",      // X
        "NEG",      // X
        "BINNEG"    // X
    };

    struct Token {
        Token(): type(NONE), value(""), pos(ivec2(0, 0)) {};
        Token(u64 type, string value): type(type), value(value), pos(ivec2(0, 0)) {};
        Token(u64 type, string value, ivec2 pos): type(type), value(value), pos(pos) {};

        void print() {
            cout << "Token<" << toktypes[this->type] << ", " << this->value << "> at ";
            cout << this->pos.to_str() << endl;
        };

        token type;
        string value;
        ivec2 pos;
    };

    struct Lexer {
        Lexer(): tokens((Token *)malloc(sizeof(Token *)*4096)), code("") {cout << "Lexer created" << endl;};
        Lexer(string code): tokens((Token *)malloc(sizeof(Token *)*4096)), code(code) {cout << "Lexer created" << endl;};

        u64 lex() {
            u64 cur = 0;
            char *code = (char *)this->code.c_str();
            u64 tok_cur = 0;
            u64 status = NONE;
            char ch;
            u64 start;
            u64 end;
            char *long_buffer;

            for (cur = 0; cur < this->code.length(); cur++) {
                ch = code[cur];
                if (status == NONE) {
                    if (isalpha(ch)) {
                        status = NAME;
                        start = cur;
                        long_buffer = (char *)malloc(64);
                    } else if ('0' <= ch && ch <= '9') {
                        status = INT;
                        start = cur;
                        long_buffer = (char *)malloc(21);
                    } else if (ch == ':') {
                        this->tokens[tok_cur++] = Token(COLON, ":", ivec2(cur, cur));
                        tok_cur++;
                    } else if (ch == '=') {
                        this->tokens[tok_cur++] = Token(EQUAL, "=", ivec2(cur, cur));
                        tok_cur++;
                    } else if (ch == '<') {
                        if (code[cur+1] == '=') {
                            this->tokens[tok_cur++] = Token(LE, "<=", ivec2(cur, ++cur));
                        } else if (ch == '>') {
                            this->tokens[tok_cur++] = Token(NE, "<>", ivec2(cur, ++cur));
                        } else if (ch == '-') {
                            this->tokens[tok_cur++] = Token(ARLEFT, "<-", ivec2(cur, ++cur));
                        } else {
                            this->tokens[tok_cur++] = Token(LT, "<", ivec2(cur, cur));
                        };
                    } else if (ch == '>') {
                        if (code[cur+1] == '=') {
                            this->tokens[tok_cur++] = Token(GE, ">=", ivec2(cur, ++cur));
                        } else {
                            this->tokens[tok_cur++] = Token(GT, ">", ivec2(cur, cur));
                        };
                    } else if (ch == '!') {
                        if (code[cur+1] == '=') {
                            this->tokens[tok_cur++] = Token(NE, "!=", ivec2(cur, ++cur));
                        }
                    };
                } else if (status == NAME) {
                    if (cur-start > 64) {
                        cout << "Name was cutted, max name length is 63 symbols" << endl;
                        status = NONE;
                        end = cur;
                        this->tokens[tok_cur++] = Token(NAME, long_buffer, ivec2(start, end));
                    } else if (isalnum(ch)) {
                        long_buffer[cur-start-1] = ch;
                    } else {
                        status = NONE;
                        this->tokens[tok_cur++] = Token(NAME, long_buffer, ivec2(start, end));
                    };
                } else if (status == INT) {
                    if (cur-start > 21) {
                        cout << "Integer was cutted, max integer length is 20 symbols" << endl;
                        status = NONE;
                        this->tokens[tok_cur++] = Token(INT, long_buffer, ivec2(start, end));
                    } else if ('0' <= ch && ch <= '9') {
                        long_buffer[cur-start-1] = ch;
                    } else {
                        status = NONE;
                        this->tokens[tok_cur++] = Token(INT, long_buffer, ivec2(start, end));
                    };
                };
            };

            this->tokens[tok_cur] = Token();

            return 0;
        };

        ~Lexer() {
            cout << "Lexer freed" << endl;
            free(this->tokens);
        };

        Token *tokens;
        string code;
        string error;
    };

}

#endif
