#include <stdio.h>
#include "libraries\game_funcs.h"
#include "nts_essentials\nts_all.h"



int main(void){
    clear();
    aprint("Welcome to the game!\n", 25);
    sleep(2);
    clear();
    int option = 0;
    for (;;){
        printf("What would you like to do?\n"GREEN ">1<" RESET " Sign in\n"GREEN ">2<" RESET " Guest mode\n");
        safeScanf("%d", &option);
        if (option == 1){
            signin();
        } else if (option == 2){
            clear();
            no_feature();
        } else {
            clear();
            printf(RED "Invalid option. Please try again.\n" RESET);
        }
        if (option == 1 || option == 2){
            break;
        }
        option = 0;
    }

    return 0;
}