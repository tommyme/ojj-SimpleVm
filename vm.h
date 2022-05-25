#include <iostream>
#include <cstdlib>
#include <cstring>

#include "machine.h"
using namespace std;

enum VM_FLAGS
{
    FLAG_END,
    FLAG_ERR,
    FLAG_SIZE
};

class VM
{
    char *ram, *program;
    int reg_comm[REG_COMM_SIZE];
    int pc, sp, bp;
    int br;                // 断点
    bool flag[FLAG_SIZE];   // 标志位

public:
    VM(char *program, int ram_size);
    void step();
    int run();
    void debug();
};