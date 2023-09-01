#ifndef __OBJ_H__
#define __OBJ_H__

#include "../other/dict.hpp"
#include "script.hpp"


class objtype {
    public:

    objtype() {};

    objtype(int id, const char *name) {
        this->id = id;
        this->name = (char *)name;
    };

    char *name;
    int id;
};

class obj {
    public:

    obj() {};

    char *name;
    objtype type;
    int id;
    obj *parent;
    obj *children;
    dict properties;
    script_t script;
};


#endif