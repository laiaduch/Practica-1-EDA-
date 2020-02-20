//
// Created by rcarlini on 15/10/19.
//

#include <string.h>

#include "../headers/room.h"

/**
 * Initializes the room with and empty label, disabled and not visited by default.
 * Also initializes all 4 rooms (N/E/S/W)).
 *
 * @param room The room to be initialized.
 *
 * Pre:
 * Post:
 */
void init_room(Room *room) {
    strcpy(room->label, "");
    room->is_enabled = FALSE;
    room->is_visited = FALSE;
    for (int i = 0; i < 4; i++) {
        init_wall(&room->walls[i]);
    }
}

/**
 * Enables the room, marking it as visible and usable.
 *
 * @param room The room to be modified.
 *
 * Pre:
 * Post:
 */
void enable_room(Room* room) {
    room->is_enabled = TRUE;
}

/**
 * Disables the room, marking it as invisible and unusable.
 *
 * @param room The room to be modified.
 *
 * Pre:
 * Post:
 */
void disable_room(Room* room) {
    room->is_enabled = FALSE;
}
/**
 * Checks if the room is enabled or disabled.
 *
 * @param room The room to be checked.
 * @return TRUE if the room is enabled, FALSE otherwise.
 *
 * Pre:
 * Post:
 */
int is_enabled(Room* room){
    return room->is_enabled;
}

/**
 * Marks the room as visited.
 *
 * @param room The room to be modified.
 *
 * Pre:
 * Post:
 */
void mark_visited(Room* room) {
    room->is_visited = TRUE;
}

/**
 * Removes the visited mark of the room, if marked.
 *
 * @param room The room to be modified.
 *
 * Pre:
 * Post:
 */
void clear_visited(Room* room) {
    room->is_visited = FALSE;
}

/**
 * Checks if the room has been marked as visited.
 *
 * @param room The room to be checked.
 * @return TRUE if the room is marked as visited, FALSE otherwise.
 *
 * Pre:
 * Post:
 */
int is_visited(Room* room) {
    return room->is_visited;
}

/**
 * Returns the (reference to) the wall of the room corresponding to the direction.
 * @param room The room from were the wall is being looked up.
 * @param direction The direction whhere the wall sits.
 * @return (A reference to) The wall of the room sitting in the input direction.
 *
 * Pre:
 * Post:
 */
Wall* get_wall(Room* room, char direction) {
    if (direction == NORTH) {
        return &room->walls[0];
    } else if (direction == SOUTH) {
        return &room->walls[2];
    } else if (direction == EAST) {
        return &room->walls[1];
    } else if (direction == WEST) {
        return &room->walls[3];
    }
}