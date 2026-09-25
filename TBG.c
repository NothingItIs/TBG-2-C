#include <stdio.h>
#include "libraries/system_funcs.h"

void no_feature(void){
    printf("Sorry, this feature has not been implemented yet! Choose Another option.");
    getchar();
}

void signin(void){
    no_feature();
}



int main(void){
    clear();
    printf("Welcome to the game!\n");
    getchar();
    clear();
    int option = 0;
    while (option != 1 && option != 2){
        printf("What would you like to do?\n>1< Sign in\n>2< Guest mode\n");
        scanf("%d", &option);
        if (option == 1){
            signin();
            option = 0;
        } else if (option == 2){
            continue;
        } else {
            clear(;)
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}