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
 * Pre:
 * Post:
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
 * Pre:
 * Post:
 */
void set_wall_label(Wall *wall, const char label[MAX_STRING]) {
    strcpy(wall->label, label);
}

/**
 * Returns the label of the wall.
 * @param room The wall to be queried.
 * @return The wall label.
 *
 * Pre:
 * Post:
 */
char* get_wall_label(Wall *wall) {
    return wall->label;
}

/**
 * Checks if the wall has a door.
 * @param wall
 * @return TRUE if the wall has a door, FALSE otherwise.
 *
 * Pre:
 * Post:
 */
int has_door(Wall *wall) {
    return wall->has_door;
}

/**
 * Adds a door to the wall.
 * @param wall
 *
 * Pre:
 * Post:
 */
void add_door(Wall *wall) {
    wall->has_door = TRUE;
}

/**
 * Removes the door from the wall.
 * @param wall
 *
 * Pre:
 * Post:
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
 * Pre:
 * Post:
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
 * Pre:
 * Post:
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
 * Pre:
 * Post:
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
 * Pre:
 * Post:
 */
int has_open_door(Wall *wall) {
    return wall->has_door && wall->is_open;
}

/**
 * Checks if the wall has an exit door.
 * @param wall The wall to be checked.
 * @return TRUE if the wall has an exit door, FALSE otherwise.
 *
 * Pre:
 * Post:
 */
int has_exit_door(Wall *wall) {
        return wall->has_door && wall->is_exit;
}

/**
 * Adds an exit door to the wall.
 * @param wall The wall to be modified.
 *
 * Pre:
 * Post:
 */
void add_exit_door(Wall *wall) {
    wall->is_exit = TRUE;
}

/**
 * Removes the exit door from the wall.
 * @param wall The wall to be modified.
 *
 * Pre:
 * Post:
 */
void remove_exit_door(Wall *wall) {
    wall->is_exit = FALSE;
}
