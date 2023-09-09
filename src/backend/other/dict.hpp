#ifndef __DICT_H__
#define __DICT_H__

#include <cstdlib>
#include <cstdio>
#include <string.h>

#define dict_init int** adr
#define dict_set(a, k, v) adr = a.get(k);adr[0] = (int*)v


struct dict {

    dict() {};

    dict(int entries, char **keys, int **items) {
        this->keys = keys;
        this->items = items;
        this->entries = entries;
    };

    dict alloc(int entries){
        dict ins = dict();
        ins.keys = (char **)malloc(sizeof(char *)*entries);
        ins.items = (int **)malloc(sizeof(int)*entries);
        return ins;
    };

    int** get(const char *key) {
        for (int i = 0; i <= this->entries; i++) {
            if (strcmp(key, this->keys[i])) {
                return &this->items[i];
            }
        }
        printf("error: key \"%s\" not defined in dictionary", key);
        return NULL;
    };

    char **keys;
    int **items;
    int entries;
};


#endif