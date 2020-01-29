//
// Created by rcarlini on 11/12/19.
//

#ifndef DUNGEON_STATE_H
#define DUNGEON_STATE_H

#include "dungeon.h"

typedef struct {
    Dungeon dungeon;
    Position location_user;
    int is_finished;
} State;

void init_state(State* state, Dungeon* dungeon);

int is_finished(State* state);

Room* get_current_room(State* state);
int move(State* state, char direction);
int go_back(State* state, char direction);

#endif //DUNGEON_STATE_H
