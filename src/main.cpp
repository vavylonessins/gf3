#include "backend/other/vec.hpp"
#include "backend/frames/frames.h"
#include "backend/honey/lexyacc.hpp"
#include <iostream>
#include <unordered_map>
#include <fstream>


int main(int argc, char** argv) {
    char *buffer = (char *)malloc(1024);
    std::string line;
    u64 cur = 0;
    std::ifstream file;
    file.open("dummy.hny");
    if (file.is_open()) {
        while (getline(file, line)) {
            strcpy(buffer+cur, line.c_str());
            cur += line.length();
            buffer[cur] = '\n';
            cur++;
        }
    }
    std::string code = std::string(buffer);
    honey::Lexer lexer = honey::Lexer(code);
    std::cout << lexer.code;

    u64 idx = 0;

    for (; lexer.tokens[idx].type != honey::TokenType::NONE; idx++) {
        lexer.tokens[idx].print();
    }

    lexer.lex();
}


