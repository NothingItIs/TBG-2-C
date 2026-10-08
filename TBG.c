#include <stdio.h>
#include "libraries/game_funcs.h"
#include "nts_essentials/nts_all.h"

#define DEBUG 1

int main(void){
    clear();
    #ifndef DEBUG
    aprint("Welcome to the game!\n", 25);
    sleep(2);
    clear();
    #endif
    int option = 0;
    struct player player;
    for (;;){
        printf("What would you like to do?\n"GREEN ">1<" RESET " Sign in\n"GREEN ">2<" RESET " Guest mode\n");
        safeScanf("%d", &option);
        if (option == 1){
            signin(&player);
        } else if (option != 2){
            printf(RED "Invalid option. Please try again.\n" RESET);
        }
        clear();
        if (option == 1 || option == 2){
            break;
        }
        option = 0;
    }

    struct scene scenes[100];
    load_story(scenes);

    while (1){
        struct scene *currentScene = &scenes[0];
    }

    return 0;
}