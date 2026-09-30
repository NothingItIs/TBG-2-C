#ifndef START_GAME_H
#define START_GAME_H

void start_game(void);

struct scene {
    int id;
    char title[100];
    char event[4096];
    int choices[10];
    int choiceCount;
};

#ifdef NTS_DEBUG
int load_story(struct scene scenes[]);
#endif

#endif