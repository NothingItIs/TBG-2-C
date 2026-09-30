#include <stdio.h>
#include "start_game.h"
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

// void get_story(position){
//     FILE *story = fopen("C:\\Users\\jwjnt\\OneDrive\\Desktop\\GitLab_UNI\\TBG-2-C\\story.txt", "r");
//     if (story == NULL) {
//         perror("Error");
//     }
//     char line[8096];
//     while(fgets(line, sizeof(line), story) != NULL){
//         printf("%s", line);
//     }
//     fclose(story);
// }

void createScene(struct scene *Scene, int id, char *title, char *event, int choices[10]){
    Scene->id = id;
    strcpy(Scene->title, title);
    strcpy(Scene->event, event);    

}

int load_story(struct scene scenes[]){
    FILE *story = fopen("story.txt", "r");

    if (!story) {
        perror("Error opening story.txt");
        return 0;
    }

    int sceneCount = 0;
    char line[8096];
    char *current;
    while (sceneCount < 100 && fgets(line, sizeof(line), story)){
        for (int i = 0; (i < 4); i++)  {
            switch(i){
                case 0:
                    current = strtok(line, "|\r\n");
                    scenes[sceneCount].id = atoi(current);
                    break;
                case 1:
                    current = strtok(NULL, "|\r\n");
                    strcpy(scenes[sceneCount].title, current);
                    break;
                case 2:
                    current = strtok(NULL, "|\r\n");
                    strcpy(scenes[sceneCount].event, current);
                    break;   
                case 3:
                    current = strtok(NULL, "|\r\n");
                    if (!current){
                        fprintf(stderr, "Error: Scene %d has no options for the next scene.", sceneCount);
                        exit(EXIT_FAILURE);
                    }
                    scenes[sceneCount].choices[0] = atoi(strtok(current, ","));
                    for (int j = 1; j < 10; j++){
                        char *optionCurrent = strtok(NULL, ",");
                        if (!optionCurrent){
                            break;
                        }
                        scenes[sceneCount].choices[j] = atoi(optionCurrent);
                        scenes[sceneCount].choiceCount = j + 1;
                    }
                    break;
            }
        }
        sceneCount++;
    }

    fclose(story);
    return sceneCount;
}

// int main(void){
//     struct scene scenes[100];
//     load_story(scenes);
//     int x;
//     scanf("%d", &x);
//     printf("%s", scenes[x].title);
//     return 0;
// }



