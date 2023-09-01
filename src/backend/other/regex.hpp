#ifndef __REGEX_H__
#define __REGEX_H__

#include <string>


namespace re {
    
    enum Token {
        /*
         * This enum contains token ids.
         * For example, regex R"[1;9R]*\d" will be:
         * { BEGIN, '1', '9', RANGE, CLASS, MOREOR0, NUM }
         */
        NONE,
        ANY,
        BEGIN,
        END,
        MOREOR0,
        MOREOR1,
        OR0OR1,
        TIMES,
        OR,
        GROUP,
        LOOKA,
        UNTIL,
        ALPHA,
        ALNUM,
        NUM,
        WHITESPACE,
        NEG,
        SEQ,
        CLASS,
        RANGE,
        ESCAPE,
        SEP
    };

    void print_token(Token tok) {
        const char *token_names[] = {
            "NONE",
            "ANY",
            "BEGIN",
            "END",
            "MOREOR0",
            "MOREOR1",
            "OR0OR1",
            "TIMES",
            "OR",
            "GROUP",
            "LOOKA",
            "UNTIL",
            "ALPHA",
            "ALNUM",
            "NUM",
            "WHITESPACE",
            "NEG",
            "AEQ",
            "CLASS",
            "RANGE",
            "ESCAPE",
            "SEP"
        };

        char *tok_str = (char *)(char[]){(char)tok, '\0'};

        printf("Token::%s", tok > 21 ? token_names[(int)tok] : tok_str);
    }

    typedef Token* Tokens;

    class Regex {
        public:

        Regex(std::string pattern) {
            char *chars = (char *)malloc(1024);
            this->pattern = pattern.copy(chars, 1024, 0);
        };

        void precompile() {
            this->precompile(malloc(2048)); // 2KiBs will be enough for BINARY code
        }

        void precompile(void* buffer) {
            this->code = (Tokens)buffer;

            char ch;
            int pattern_pos = 0;
            int code_pos = 0;
            int stack_pos = 0;
            int *stack = (int *)malloc(64*sizeof(int));

            for (int i = 0; i < (int)this->pattern.length(); i++) {
                ch = pattern.c_str()[i];

                if (ch == '\\') {
                    if (!stack_pos || stack[stack_pos-1] != Token::ESCAPE) {
                        stack[stack_pos++] = Token::ESCAPE;
                    } else {
                        code[code_pos++] = (Token)ch;
                    }
                } else
                if (ch == '[') {
                    if (!stack_pos || stack[stack_pos-1] != Token::ESCAPE) {
                        stack[stack_pos++] = Token::BEGIN;
                    } else {
                        code[code_pos++] = (Token)ch;
                    }
                } else
                if (ch == ']') {
                    if (!stack_pos || stack[stack_pos-1] != Token::ESCAPE) {
                        stack[stack_pos++] = Token::CLASS;
                    } else {
                        code[code_pos++] = (Token)ch;
                    }
                } else
                if (ch == 'R') {
                    if (!stack_pos || stack[stack_pos-1] != Token::ESCAPE) {
                        stack[stack_pos++] = Token::RANGE;
                    } else {
                        code[code_pos++] = (Token)ch;
                    }
                } else
                if (ch == ';') {
                    if (!stack_pos || stack[stack_pos-1] != Token::ESCAPE) {
                        stack[stack_pos++] = Token::SEP;
                    } else {
                        code[code_pos++] = (Token)ch;
                    }
                } else
                if (ch == 'd' and stack[stack_pos-1] == Token::ESCAPE) {
                    stack_pos--;
                    code[code_pos++] = Token::NUM;
                } else
                if (ch == 'w' and stack[stack_pos-1] == Token::ESCAPE) {
                    stack_pos--;
                    code[code_pos++] = Token::ALNUM;
                } else
                if (ch == 'a' and stack[stack_pos-1] == Token::ESCAPE) {
                    stack_pos--;
                    code[code_pos++] = Token::ALPHA;
                } else
                if (ch == 'D' and stack[stack_pos-1] == Token::ESCAPE) {
                    stack_pos--;
                    code[code_pos++] = Token::NEG;
                    code[code_pos++] = Token::NUM;
                } else
                if (ch == 'W' and stack[stack_pos-1] == Token::ESCAPE) {
                    stack_pos--;
                    code[code_pos++] = Token::NEG;
                    code[code_pos++] = Token::ALNUM;
                } else
                if (ch == '[' and stack[stack_pos-1] == Token::ESCAPE) {
                    stack_pos--;
                    code[code_pos++] = (Token)ch;
                } else
                if (ch == ']' and stack[stack_pos-1] == Token::ESCAPE) {
                    stack_pos--;
                    code[code_pos++] = (Token)ch;
                } else
                if (ch == '\0') {
                    code[code_pos++] = Token::NONE;
                    break;
                }
            }

            free(stack);
        }

        std::string pattern;
        Tokens code;
    };

    Regex compile(std::string pattern) {
        return Regex(pattern);
    }
};

#endif
