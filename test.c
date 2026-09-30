#include <stdio.h>

#define NTS_DEBUG 1

#include "libraries\game_itself\start_game.h"
#include "nts_essentials\nts_all.h"

int main(void){
    clear();
    struct scene scenes[100];
    int x = load_story(scenes);
    int (*p)[10] = &scenes[0].choices;
    for (int i = 0; i < LEN(*p); i++){
        printf("%d", (*p)[i]);
    }
}