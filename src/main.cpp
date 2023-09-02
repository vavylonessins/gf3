#include "backend/other/vec.hpp"
#include "backend/frames/frames.h"
#include "backend/honey/lexyacc.hpp"
#include <iostream>
#include <unordered_map>
#include <fstream>


std::string pattern = "\\B1;9\\R\\C*\\D";


int main(int argc, char** argv) {
    re::Regex regex = re::compile(pattern);

    regex.precompile();

    std::cout << "Pattern to parse: \"" << pattern << "\"\n";

    for (int i = 0; regex.code[i] != re::Token::NONE; i++) {
        printf("[*] TOKEN %d : ", (int)regex.code[i]);
        re::print_token(regex.code[i]);
    }
}
