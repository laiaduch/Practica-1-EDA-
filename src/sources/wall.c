//
// Created by rcarlini on 22/10/19.
//

#include <string.h>

#include "../headers/wall.h"

/**
 * Initializes the wall with an empty label and no door (so is_open and is_exit are FALSE).
 *
 * @param wall The wall to be initialized.
 *
 * Pre: Com a mínim ha d'haver una paret.
 * Post: La funció ens inicialitza la paret, dient que no hi ha cap porta i per tant tampoc està oberta ni es de sortida.
 */
void init_wall(Wall *wall) {
    wall->has_door = FALSE;
    wall->is_open = FALSE;
    wall->is_exit = FALSE;
}

/**
 * Sets the label of the wall.
 *
 * Hint: The label must be copied!
 *
 * @param door The wall to be modified.
 * @param label The label for the wall.
 *
 * Pre: La funció ha de tenir una paret i una etiqueta.
 * Post: La funció estableix l'etiqueta de la paret.
 */
void set_wall_label(Wall *wall, const char label[MAX_STRING]) {
    strcpy(wall->label, label);
}

/**
 * Returns the label of the wall.
 * @param room The wall to be queried.
 * @return The wall label.
 *
 * Pre: Al menys ha d'haver una paret.
 * Post: La funció ens retorna l'etiqueta de la paret.
 */
char* get_wall_label(Wall *wall) {
    return wall->label;
}

/**
 * Checks if the wall has a door.
 * @param wall
 * @return TRUE if the wall has a door, FALSE otherwise.
 *
 * Pre: Ha d'haver almenys una paret.
 * Post: La funció ens comprova si la paret té porta, si és així ens retorna la paret amb la porta.
 */
int has_door(Wall *wall) {
    return wall->has_door;
}

/**
 * Adds a door to the wall.
 * @param wall
 *
 * Pre: Ha d'haver almenys una paret i una porta per a cada paret.
 * Post: Afegeix portes a la paret.
 */
void add_door(Wall *wall) {
    wall->has_door = TRUE;
}

/**
 * Removes the door from the wall.
 * @param wall
 *
 * Pre: Ha d'haver al menys una paret amb una porta.
 * Post: La funció treu la porta de la paret.
 */
void remove_door(Wall *wall) {
    wall->has_door = FALSE;
}

/**
 * Sets the state of the wall door to state value.
 *
 * @param wall The wall to be modified.
 * @param state TRUE/FALSE if the door is open/closed respectively.
 * @return If the wall has no door, NO_DOOR_ERROR code is returned. SUCCESS code is returned otherwise.
 *
 * Pre:  Almenys ha d'haver una paret. La paret ha de tenir una porta, ja sigui tancada o oberta.
 * Post: La funció estableix l'estat de la porta de la paret
 */
int set_door_open(Wall* wall, int state) {
    wall->is_open = state;
    if (wall->has_door) {
        return wall->is_open;
    } else {
        return NO_DOOR_ERROR;
    }

}

/**
 * IF the wall has a door, set it's state as open.
 *
 * @param wall The wall to be modified.
 * @return If the wall has no door, NO_DOOR_ERROR code is returned. SUCCESS code is returned otherwise.
 *
 * Pre:  Almenys ha d'haver una paret. Si la paret té alguna porta, aquesta ha d'estar oberta.
 * Post: La funció ens mira si la porta està oberta, si n'hi ha.
 */
int open_door(Wall* wall) {
    if (wall->has_door) {
        wall->is_open = TRUE;
        return SUCCESS;
    } else {
        return NO_DOOR_ERROR;
    }
}

/**
 * IF the wall has a door, set it's state as closed.
 *
 * @param wall The wall to be modified.
 * @return If the wall has no door, NO_DOOR_ERROR code is returned. SUCCESS code is returned otherwise.
 *
 * Pre:  Almenys ha d'haver una paret. Si la paret té alguna porta, la porta ha d'estar tancada.
 * Post: La funció comprova que la porta estigui tancada, si n'hi ha.
 */
int close_door(Wall* wall) {
    if (wall->has_door) {
        wall->is_open = FALSE;
        return SUCCESS;
    } else {
        return NO_DOOR_ERROR;
    }
}

/**
 * Checks if the wall has a door and is opened.
 * @param wall The wall to be checked.
 * @return TRUE if the wall has an open door, FALSE otherwise.
 *
 * Pre: Almenys ha d'haver una paret. La paret ha de tenir una porta i a més ha d'estar oberta.
 * Post: Comprova si la paret té alguna porta i si està oberta.
 */
int has_open_door(Wall *wall) {
    return wall->has_door && wall->is_open;
}

/**
 * Checks if the wall has an exit door.
 * @param wall The wall to be checked.
 * @return TRUE if the wall has an exit door, FALSE otherwise.
 *
 * Pre: Almenys ha d'haver una paret. La paret ha de tenir una porta de sortida.
 * Post: La funció comprova si la paret té alguna porta de sortida.
 */
int has_exit_door(Wall *wall) {
        return wall->has_door && wall->is_exit;
}

/**
 * Adds an exit door to the wall.
 * @param wall The wall to be modified.
 *
 * Pre: Almenys ha d'haver una paret per poder afegir-li la porta de sortida.
 * Post: La funció ens afegeix una porta de sortida.
 */
void add_exit_door(Wall *wall) {
    wall->is_exit = TRUE;
}

/**
 * Removes the exit door from the wall.
 * @param wall The wall to be modified.
 *
 * Pre: Almenys ha d'haver una paret i ha de tenir alguna porta de sortida.
 * Post: Ens elimina la porta de sortida de la paret.
 */
void remove_exit_door(Wall *wall) {
    wall->is_exit = FALSE;
}
