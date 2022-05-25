#include "vm.h"

VM::VM(char *program, int ram_size)
{
    this->program = program;
    cout << "Initializing Machine..." << endl;
    cout << "Program Size: " << sizeof(program) << endl;

    // Init
    this->ram = (char *)malloc(ram_size);
    pc = 0;
    bp = ram_size - 1;
    sp = bp;
    memset(reg_comm, 0, sizeof(reg_comm));
    memset(flag, 0, sizeof(flag));
}

void VM::step()
{
    char cache;
    int imm; // 寻址方式，立即为 1
    switch (program[pc++])
    {
    case OP_ADD:
        cache = program[pc++];
        imm = cache & 0x80;
        cache &= 0x7F;
        if (cache < REG_COMM_SIZE)
            reg_comm[cache] += imm ? program[pc++] : reg_comm[program[pc++]];
        else
            flag[FLAG_ERR] = true;
        break;

    case OP_MOV:
    case OP_JMP:

    default:
        flag[FLAG_ERR] = true;
    }
}

int VM::run()
{
    if (pc >= sizeof(program))
    {
        cout << "Error: program out of scope!" << endl;
        return -1;
    }

    while (!(flag[FLAG_END] || flag[FLAG_ERR]))
    {
        step();
    }

    if (flag[FLAG_ERR])
    {
        cout << "Exec error! Dumping flags..." << endl;
        debug();
        return -1;
    }

    return 0;
}

void VM::debug()
{
    cout << "\n--------- Running Status -------------" << endl
         << "PC: " << pc << "\tBP: " << bp << "\tSP: " << sp << endl
         << "--------------------------------------\n"
         << endl;
}