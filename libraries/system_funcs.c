#include <stdlib.h>
#include "system_funcs.h"

void clear(void){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
