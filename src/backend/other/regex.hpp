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

        if (tok > 21) {
            printf("Char::");
            putc((char)tok, stdout);
            printf("\n");
        } else {
            printf("Token::%s\n", (char *)token_names[(int)tok]);
        }
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

            char ch = '\0';
            int pattern_pos = 0;
            int code_pos = 0;
            int stack_pos = 64;
            int *stack = (int *)malloc(64*sizeof(int));

            for (auto ch : this->pattern) {
                // ch = this->pattern[i];

                putc(ch, stdout);

                if (ch == '\\') {
                    if (!stack_pos || stack[stack_pos] != Token::ESCAPE) {
                        stack[--stack_pos] = Token::ESCAPE;
                    } else {
                        code[code_pos++] = (Token)ch;
                    }
                } else
                if (stack_pos && stack[stack_pos] == Token::ESCAPE) {
                    if (ch == 'B') {
                        code[code_pos++] = Token::BEGIN;
                        stack_pos++;
                    }
                }

                if (ch == '\0') {
                    code[code_pos++] = Token::NONE;
                    break;
                }
                print_token(code[code_pos]);
            }

            print_token(code[0]);

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
