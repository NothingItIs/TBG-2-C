#include <stdio.h>
#include "../game_global/game_global.h"
#include "../../nts_essentials/nts_all.h"

/* disclaimer logic to let them know that 
it's stored on a database that's not only 
encrypted but also their own password encrypted, 
salted, and converted into comparable characters 
that are unreadable and undecipherable by human, 
ai, or code. */

// struct 

void signin(struct player *player){
    clear();
    no_feature();
}