//
// Created by rcarlini on 11/12/19.
//

#include <stddef.h>
#include "../headers/state.h"
#include <stdlib.h>

/**
 * Initializes the state, storing the dungeon in it and setting the current position to the dungeon stating position.
 * Also sets finished flag to FALSE.
 *
 * @param state The state to be initialized.
 * @param dungeon The dungeon to be set as the state dungeon.
 *
 * Pre: Hem de tenir l'estat de la dungeon i la dungeon.
 * Post: Inicialitza state, emmagatzemant la dungeon i configurant la posició actual en la posició de l'estat de la dungeon.
 */
void init_state(State* state, Dungeon* dungeon) {
    state->dungeon = *dungeon;
    state->is_finished = FALSE;
    state->location_user = get_starting_position(dungeon);
    state->user_path.seq = malloc(sizeof(Step) * MAX_STRING);
}

/**
 * Sets the current position from the dungeon associated to the state.
 *
 * @param state The state that stores the current position.
 * @param row The current row coordinate.
 * @param column The current column coordinate.
 *
 * Pre: Necessitem l'estat de la posició de l'usuari i la posició.
 * Post: Estableix la posició de la dungeon asociada amb l'estat (state).
 */
void set_current_position(State* state, Position position) {
    state->location_user = position;
}

/**
 * Retrieves the current position from the dungeon associated to the state.
 *
 * @param state The state that stores the current room.
 * @return The current room of the dungeon.
 *
 * Pre: Necessitem l'estat de la posició.
 * Post: La funció recupera la posició de la dungeon asociada al state.
 */
Position get_current_position(State* state) {
    return state->location_user;
}

/**
 * Retrieves the current room from the dungeon associated to the state.
 *
 * @param state The state that stores the current room.
 * @return The current room of the dungeon.
 *
 * Pre: Necessitem l'estat de la sala i de la posició.
 * Post: La funció recupera la sala asociada al state, inidicant la posició de l'habitació en la matriu.
 */
Room* get_current_room(State* state) {
    return &state->dungeon.map[state->location_user.row][state->location_user.column];
}

/**
 * Sets the finished flag to finisehd value (TRUE or FALSE)
 *
 * @param state The state to be updated.
 * @param is_finished The value marking the game as finished or not.
 *
 * Pre: Necessitem l'estat de la dungeon i un marcador (finished).
 * Post: La funció estableix un marcador que ens indicarà el valor de si s'ha acabat o no.
 */
void set_finished(State* state, int finished) {
    state->is_finished = finished;
}

/**
 * Returns the value of is_finished flag (TRUE or FALSE), marking a game as finished.
 *
 * @param state The state to be updated.
 *
 * Pre: Necessitem l'estat del marcador establit en la funció anterior.
 * Post: La funció ens retorna el valor del marcador establit en la funció anterior, indica si el joc s'ha finalitzat o no.
 */
int is_finished(State* state) {
    return state->is_finished;
}

/**
 * If the move is valid, moves the player in the input direction, updating the current room position.
 * If there is no room in that direction, returns INVALID_DIRECTION code.
 * If the wall in the direction does not have a door, returns NO_DOOR_ERROR.
 * If the target position is no valid, returns INVALID_MOVE code.
 *
 * @param state The current state.
 * @param direction The direction to move to.
 * @return TRUE if the move was successful, INVALID_DIRECTION code if there is no room in that direction, NO_DOOR_ERROR code if there is no door in that direction or INVALID_MOVE if the target position is invalid.
 *
 * Pre: La funció haurà de tenir l'estat de la dungeon i una direcció.
 * Post: La funció mourà el jugador si la direcció introduïda és correcte, actualitzant així la posició actual de la sala. Aquesta funció ens comprovarà si la direcció és vàlida.
 */
int move(State* state, char direction) {
    Room* actual = get_current_room(state);
    if (!has_door(get_wall(actual, direction))) {
        return NO_DOOR_ERROR;
    }
    Position current = get_current_position(state);
    Position new = current;
    int row = new.row;
    int column = new.column;
    mark_visited(actual);
    switch (direction) {
        case NORTH:
            set_position(&new, --row, column);
            break;
        case SOUTH:
            set_position(&new, ++row, column);
            break;
        case EAST:
            set_position(&new, row, ++column);
            break;
        case WEST:
            set_position(&new, row, --column);
            break;
    }
    if (!is_valid_position(new)) {

        return INVALID_MOVE;
    }
    if (get_room_at_position(&state->dungeon, new) != NULL && !get_room_at_position(&state->dungeon, new)->is_enabled) {
        return INVALID_DIRECTION;
    }
    set_current_position(state, new);
    if (get_wall(actual, direction)->is_exit) {
        set_finished(state, TRUE);
    }
    return TRUE;
}

/**
 * If the move is valid, moves the player in the opposite direction, updating the current room position.
 * If there is no room in that direction, returns INVALID_DIRECTION code.
 * If the wall in that direction does not have a door, returns NO_DOOR_ERROR.
 * If the target position is no valid, returns INVALID_MOVE code.
 *
 * @param state The current state.
 * @param direction The direction to move to.
 * @return TRUE if the move was successful, INVALID_DIRECTION code if there is no room in that direction, NO_DOOR_ERROR code if there is no door in that direction or INVALID_MOVE if the target position is invalid.
 *
 * Pre: La funció haurà de tenir l'estat de la dungeon i una direcció.
 * Post: Si el moviment introduït és vàlid, mou al jugador en la direcció oposada. També ens indicarà si en aquesta direcció el jugador pot anar sino ens retornarà error.
 */
int go_back(State* state, char direction) {
    Room* actual = get_current_room(state);
    char new_direction;
    switch (direction) {
        case NORTH:
            new_direction = SOUTH;
            break;
        case SOUTH:
            new_direction = NORTH;
            break;
        case EAST:
            new_direction = WEST;
            break;
        case WEST:
            new_direction = EAST;
            break;
    }
    if (!has_door(get_wall(actual, new_direction))) {
        return NO_DOOR_ERROR;
    }
    return move(state, new_direction);
}

/**
 * Adds the step as the first step of the path sequence.
 *
 * @param state The current state.
 * @param direction The direction of the step.
 */
void add_as_first_step(State* state, Position position, char direction) {
    Step step;
    step.direction = direction;
    step.position = position;
    state->user_path.seq[0] = step;
}

/**
 * Adds the step as the last step of the path sequence.
 *
 * @param state The current state.
 * @param direction The direction of the step.
 */
void add_as_last_step(State* state, Position position, char direction) {
    Step step;
    step.direction = direction;
    step.position = position;
    state->user_path.seq[sizeof(state->user_path.seq)-1] = step;
}

/**
 * Deletes (freeing if needed) all the steps stored in the path of the state.
 * @param state The state with the path to be cleare.
 */
void clear_path(State* state) {
    free(state->user_path.seq);
}

/**
 * Resets the state, clearing the state path and reverting the visited marks on the dungeon rooms.
 *
 * @param state The state to be reset.
 */
void reset(State* state) {
    clear_path(state);
    reset_visited(&state->dungeon);
}