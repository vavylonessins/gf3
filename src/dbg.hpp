#ifndef __DBG_H__
#define __DBG_H__
#include <iostream>
#include "config.hpp"
#define DBG(msg) if(DEBUG)std::cout << msg;
#define DONE " Done\n"
#endif