#include "backend/other/vec.hpp"
#include "backend/frames/frames.h"
#include "backend/honey/lexyacc.hpp"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "dbg.hpp"

using namespace std;


int main(int argc, char** argv) {
    DBG("Allocating buffer for file read...")

    char *buffer = (char *)malloc(1024);
    std::string line;
    u64 cur = 0;
    std::ifstream file;

    DBG(DONE << "Reading file...")

    file.open("dummy.hny");
    if (file.is_open()) {
        while (getline(file, line)) {
            strcpy(buffer+cur, line.c_str());
            cur += line.length();
            buffer[cur++] = '\n';
        }
    }
    std::string code = std::string(buffer);

    DBG(DONE)

    honey::Lexer lexer = honey::Lexer(code);
    std::cout << lexer.code;

    lexer.lex();

    u64 idx = 0;
    for (; lexer.tokens[idx].type != honey::TokenType::NONE; idx++) {
        lexer.tokens[idx].print();
    }
}


