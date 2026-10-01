#include <stdio.h>
#include "libraries\game_funcs.h"
#include "nts_essentials\nts_all.h"
#include <stdlib.h>

// I'll use comments because I'm getting old and loosing track where is what and what I'm supposed to do next </3

int main(void){
    
    // Welcoming, don't want it to clutter. Uses custom animation print!
    clear(); aprint("Welcome to the game!\n", 25); sleep(2); clear();

    int optionStageOne;
    int optionStageTwo;

    for (;;){

        optionStageOne = 0;
        optionStageTwo = 0;

        // Starting, figures out what the person wants. Uses safeScan, a self-made function to ensure no crazy RAM inputs occur.
        printf(
            "What would you like to do?\n"
            GREEN ">1<" RESET " Sign in\n" 
            GREEN ">2<" RESET " Guest mode\n"
        );
        
        safeScanf("%d", &optionStageOne);

        bool stageOneValid = (optionStageOne == 1 || optionStageOne == 2);
        bool stageTwoValid = 0;

        // struct {} playerData; // in the future once I figure out how to load and store playerdata 
        if (optionStageOne == 1){


            // Signin, function made in a different library to not clog the code here.
            signin(); // signin(&playerData); // in the future when I figure out how to store playerdata.
        
        
        }
        
        if (stageOneValid){
            clear();
            aprint("Great! Now, let's choose the type of game you want to play.\n", 25); sleep(1);
            printf(
                "Which type of game would you like to play?\n"
                GREEN ">1<" RESET " Story mode\n"
                GREEN ">2<" RESET " RPG mode\n"
            );
            safeScanf("%d", &optionStageTwo);

            stageTwoValid = (optionStageTwo == 1 || optionStageTwo == 2);
        }

        if (!stageOneValid || !stageTwoValid){
            clear();
            printf(RED "Invalid option. Please try again.\n" RESET);
        }

        // If they chose a valid option, continue to the actual game.

        if (
            stageOneValid 
            &&
            stageTwoValid
        ){
            break;
        }

    }

    if (optionStageTwo == 2) {
        no_feature();
        exit(EXIT_SUCCESS);
    }

    return 0;
}