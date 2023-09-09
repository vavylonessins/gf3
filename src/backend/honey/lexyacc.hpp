#ifndef __LEXYACC_H__
#define __LEXYACC_H__

#include "../types.hpp"
#include <iostream>
#include <unordered_set>
#include <fstream>
#include "../other/itoa.hpp"
#include "../other/hacks.hpp"
#include "../other/vec.hpp"
#include "../../dbg.hpp"

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
        Token(): type(NONE), value(""), pos(ivec2(0, 0)) {DBG("Token created\n")};
        Token(u64 type, string value): type(type), value(value), pos(ivec2(0, 0)) {DBG("Token created\n")};
        Token(u64 type, string value, ivec2 pos): type(type), value(value), pos(pos) {DBG("Token created\n")};

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
            DBG("honey::Lexer::lex was called\n")
            u64 cur = 0;
            char *code = (char *)this->code.c_str();
            u64 tok_cur = 0;
            u64 status = TokenType::NONE;
            char ch = '\0';
            u64 start = 0;
            u64 end = 0;
            char *long_buffer = 0;

            while (cur < this->code.length()) {
                ch = code[cur];
                DBG("Lex loop:\n\tcur = " << cur << "\n\ttok_cur = " << tok_cur << "\n\tstatus = " << toktypes[status])
                DBG("\n\tch = '" << ch << "'\n\tstart = " << start << "\n\tend = " << end << "\n\tlong_buffer = \"" << long_buffer)
                DBG("\"\n")
                if (status == TokenType::NONE) {
                    DBG("\tstatus == NONE\n")
                    if (isalpha(ch)) {
                        DBG("\t\tisalpha(ch) == true\n")
                        status = TokenType::NAME;
                        start = cur;
                        long_buffer = (char *)malloc(64);
                    } else if (isdigit(ch)) {
                        DBG("\t\tisdigit(ch) == true\n")
                        status = TokenType::INT;
                        start = cur;
                        long_buffer = (char *)malloc(21);
                    } else if (ch == ':') {
                        DBG("\t\tch == ':'\n")
                        this->tokens[tok_cur++] = Token(TokenType::COLON, ":", ivec2(cur, cur));
                        tok_cur++;
                    } else if (ch == '=') {
                        DBG("\t\tch == '='\n")
                        this->tokens[tok_cur++] = Token(TokenType::EQUAL, "=", ivec2(cur, cur));
                        tok_cur++;
                    } else if (ch == '<') {
                        DBG("\t\tch == '<'\n")
                        if (code[cur+1] == '=') {
                            DBG("\t\t\tdh == '='\n")
                            this->tokens[tok_cur++] = Token(TokenType::LE, "<=", ivec2(cur, ++cur));
                        } else if (ch == '>') {
                            DBG("\t\t\tdh == '>'\n")
                            this->tokens[tok_cur++] = Token(TokenType::NE, "<>", ivec2(cur, ++cur));
                        } else if (ch == '-') {
                            DBG("\t\t\tdh == '-'\n")
                            this->tokens[tok_cur++] = Token(TokenType::ARLEFT, "<-", ivec2(cur, ++cur));
                        } else {
                            this->tokens[tok_cur++] = Token(TokenType::LT, "<", ivec2(cur, cur));
                        };
                    } else if (ch == '>') {
                        DBG("\t\tch == '>'\n")
                        if (code[cur+1] == '=') {
                            DBG("\t\t\tdh == '='\n")
                            this->tokens[tok_cur++] = Token(TokenType::GE, ">=", ivec2(cur, ++cur));
                        } else {
                            this->tokens[tok_cur++] = Token(TokenType::GT, ">", ivec2(cur, cur));
                        };
                    } else if (ch == '!') {
                        DBG("\t\tch == '!'\n")
                        if (code[cur+1] == '=') {
                            DBG("\t\t\tdh == '='\n")
                            this->tokens[tok_cur++] = Token(TokenType::NE, "!=", ivec2(cur, ++cur));
                        } else {
                            this->tokens[tok_cur++] = Token(TokenType::NEG, "!", ivec2(cur, cur));
                        }
                    };
                } else if (status == TokenType::NAME) {
                    DBG("\tstatus == NAME\n")
                    if (cur-start > 64) {
                        DBG("\t\tcur - start > 64\n")
                        cout << "Name was cutted, max name length is 63 symbols" << endl;
                        status = TokenType::NONE;
                        end = cur;
                        this->tokens[tok_cur++] = Token(TokenType::NAME, long_buffer, ivec2(start, end));
                    } else if (isalnum(ch)) {
                        DBG("\t\tisalnum(ch) == true\n")
                        long_buffer[cur-start-1] = ch;
                    } else {
                        status = TokenType::NONE;
                        this->tokens[tok_cur++] = Token(TokenType::NAME, long_buffer, ivec2(start, end));
                    };
                } else if (status == TokenType::INT) {
                    DBG("\tstatus == INT\n")
                    if (cur-start > 21) {
                        DBG("\t\tcur - start > 21\n")
                        cout << "Integer was cutted, max integer length is 20 symbols" << endl;
                        status = TokenType::NONE;
                        this->tokens[tok_cur++] = Token(TokenType::INT, long_buffer, ivec2(start, end));
                    } else if (isdigit(ch)) {
                        DBG("\t\tisdigit(ch) == true\n")
                        long_buffer[cur-start-1] = ch;
                    } else {
                        status = TokenType::NONE;
                        this->tokens[tok_cur++] = Token(TokenType::INT, long_buffer, ivec2(start, end));
                    };
                };

                cur++;
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
