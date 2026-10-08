#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int currentSceneIndex = 0;
    while(1){
        struct scene *currentScene = &scenes[currentSceneIndex];

        printf("Scene: %d\n", currentScene->id);
        printf("Title: %s\n", currentScene->title);
        char *sceneEvent = strtok(currentScene->event, "\\n");
        for (int i = 0; i < LEN(sceneEvent); i++){
            printf("%s", sceneEvent[i]);
        }
        safeScanf("%d", &currentSceneIndex);
    }

    return 0;
}