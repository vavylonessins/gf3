#ifndef __SCRIPT_H__
#define __SCRIPT_H__


static int reg_sp;
static int stack[4096]; // in-script stack, not real. emulated stack for scripts.

class script_t {
    public:

    script_t(){};

    char *source;
    char **symbol_names;
    int *symbol_offsets;
    char *bytecode;

    int reg_ip;
    int reg_ax;
    int reg_bx;
    int reg_cx;
    int reg_si;
    int reg_di;
};


#endif
