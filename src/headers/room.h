//
// Created by rcarlini on 15/10/19.
//

#ifndef DUNGEON_ROOM_H
#define DUNGEON_ROOM_H

#include "common.h"
#include "wall.h"

#define NORTH 'N' // 0
#define EAST 'E' // 1
#define SOUTH 'S' // 2
#define WEST 'W' // 3
#define QUIT 'Q'
#define PATH 'P'

typedef struct {
    Wall walls[4];
    int is_enabled;
    int is_visited;
    char label[MAX_STRING];
} Room;

void init_room(Room* room);

void enable_room(Room* room);
void disable_room(Room* room);
int is_enabled(Room* room);

void mark_visited(Room* room);
void clear_visited(Room* room);
int is_visited(Room* room);

Wall* get_wall(Room* room, char direction);

void set_room_label(Room *room, const char label[MAX_STRING]);

#endif //DUNGEON_ROOM_H
