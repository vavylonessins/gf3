#ifndef __FRAMES_H__
#define __FRAMES_H__

#include "../other/vec.hpp"
#include "../other/hacks.hpp"
#include "../objects/obj.hpp"


objtype FRAME_TYPE = objtype(1, "frame");

class frame : obj {
    frame() {
        dict_init;
        this->type = FRAME_TYPE;
        this->properties = dict(2, (char**)(char*[]){(char*)"size", (char*)"color"},
            (int**)(int*[]){(int*)malloc(sizeof(ivec2)), (int*)malloc(sizeof(ivec3))});

        dict_set(this->properties, "size", ivec2(800, 600).ptr());
        dict_set(this->properties, "color", ivec3(255, 255, 255).ptr());
    };
};

#endif
