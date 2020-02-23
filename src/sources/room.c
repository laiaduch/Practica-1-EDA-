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
 * Pre: Ha d'haver una habitació.
 * Post: La funció ens inicialitza l'habitació. Ens marca com a que no ha estat visitada i que no està disponible, a més, ens inicialitza les parets(Nord, Sud, Est, Oest)
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
  * Pre: Ha d'haver una habitació disponible.
 * Post: La funció ens diu que aquella habitació està disponible.
 */
void enable_room(Room* room) {
    room->is_enabled = TRUE;
}

/**
 * Disables the room, marking it as invisible and unusable.
 *
 * @param room The room to be modified.
 *
 * Pre: Ha d'haver una habitació.
 * Post: La funció marca que aquella habitació no està disponible.
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
 * Pre: Com a mínim ha de tenir una habitació.
 * Post:La funció comprova si l'habitació està disponible o no.
 */
int is_enabled(Room* room){
    return room->is_enabled;
}

/**
 * Marks the room as visited.
 *
 * @param room The room to be modified.
 *
 * Pre: Ha d'haver almenys una habitació que es pugui visitar.
 * Post: La funció ens marca com visitada aquella habitació.
 */
void mark_visited(Room* room) {
    room->is_visited = TRUE;
}

/**
 * Removes the visited mark of the room, if marked.
 *
 * @param room The room to be modified.
 *
 * Pre:  Ha d'haver almenys una habitació que ja hagi sigut visitda.
 * Post: La funció ens marca com a no visitada l'habitació.
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
 * Pre: Com a mínim hi haurà una habitació que no s'haurà visitat abans.
 * Post: Comprova si l'habitació ha sigut marcada com a visitada.
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
 * Pre: Com a mínim hi ha una habitació i una direcció.
 * Post: La funció en retorna la referència de la direcció de la paret de l'habitació
 */
Wall* get_wall(Room* room, char direction) {
    Wall* wallRes;
    if (direction == NORTH) {
        wallRes = &room->walls[0];
    } else if (direction == SOUTH) {
        wallRes = &room->walls[2];
    } else if (direction == EAST) {
        wallRes = &room->walls[1];
    } else if (direction == WEST) {
        wallRes = &room->walls[3];
    }
    return wallRes;
}

void set_room_label(Room *room, const char label[MAX_STRING]) {
    strcpy(room->label, label);
}
