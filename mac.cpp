#include "vm.h"

int main()
{
    char program[] = {1,2,3,4,5};
    VM mac(program, 8192);

    mac.run();
    
    return 0;
}