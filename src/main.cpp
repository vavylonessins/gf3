#include "backend/other/vec.hpp"
#include "backend/frames/frames.h"
#include "backend/honey/lexyacc.hpp"
#include <iostream>
#include <unordered_map>
#include <fstream>


int main(int argc, char** argv) {
    re::Regex regex = re::compile("[1;9R]\\d");

    regex.precompile();

    for (int i = 0; regex.code[i] != re::Token::NONE; i++) {
        re::print_token(regex.code[i]);
    }
}
