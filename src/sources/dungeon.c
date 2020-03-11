//
// Created by rcarlini on 14/10/19.
//
#include <stdio.h>
#include <stdlib.h>


#include "../headers/dungeon.h"

/**
 * Sets the value for row and column into the position.
 *
 * @param position The position to be modified.
 * @param row The row value.
 * @param column The column value.
 *
 * Pre: Ha d'haver una posició de columnes i una posició de files
 * Post: La funció estableix una valor de files i columnes en la posició de cadascuna.
 */
void set_position(Position* position, int row, int column) {
    position->row = row;
    position->column = column;
}

/**
 * Sets the starting position of the dungeon.
 * @param dungeon The dungeon to be set.
 *
 * Pre: Hem de tenir la posició d'una fila i d'una columna.
 * Post: Estableix la posició inicial de la dungeon.
 */
void set_starting_position(Dungeon *dungeon, int row, int column) {
    dungeon->initial_position.row = row;
    dungeon->initial_position.column = column;
    //mark_visited(get_room_at(dungeon, row, column));
}

/**
 * Returns the starting position of the dungeon.
 * @param dungeon The dungeon to be queried.
 * @return The starting position of the dungeon.
 *
 * Pre: Necessitem la posició inical de la dungeon.
 * Post: La funció ens retorna la posició inicial de la dungeon.
 */
Position get_starting_position(Dungeon *dungeon) {
    return dungeon->initial_position;
}

/**
 * Returns the starting room of the dungeon.
 * @param dungeon The dungeon to be queried.
 * @return The starting room of the dungeon.
 *
 * Pre: Necessitem almenys una sala de la dungeon.
 * Post: La funció ens retorna la sala d'inici de la dungeon.
 */
Room* get_starting_room(Dungeon *dungeon) {
    return  &dungeon->map[dungeon->initial_position.row][dungeon->initial_position.column];
}

/**
 * Checks if the row and column values fits in the dungeon room matrix.
 *
 * @param row The row value.
 * @param column The column value.
 *
 * @return TRUE if the values are between 0 and ROWS for row and between 0 and COLUMN for column. If the row value is out of range, it returns INVALID_ROW code. If the column value is out of range, it returns INVALID_COLUMN code.
 *
 * Pre: Necessitem dues coordenades, una que correspon a les columnes i l'altra a les files.
 * Post: Comprova si la els valors de la columna i de la fila són vàlids per la matriu de l'habitació de la dungeon. Si no ho són retornarà un error.
 */
int is_valid_coordinates(int row, int column) {
    if (row < 0 || row > ROWS)
        return INVALID_ROW;
    else if (column < 0 || column > COLUMNS)
        return INVALID_COLUMN;
    else return TRUE;
}

/**
 * Checks if the position fits in the dungeon room matrix.
 *
 * @param position The position to be checked.
 * @return TRUE if the position is between 0 and ROWS and between 0 and COLUMN. If the row value is out of range, it returns INVALID_ROW code. If the column value is out of range, it returns INVALID_COLUMN code.
 *
 * Pre: Com a mínim ha d'haver una posició (posició de columna i posició de fila).
 * Post: Comprova si la posició està compressa entre els valors vàlids de les posicions de les files i columnes.
 */
int is_valid_position(Position position) {
    return is_valid_coordinates(position.row, position.column);
}

/**
 * Returns the dungeon room at the input row and column position.
 *
 * @param dungeon The dungeon from which the room should be retrieved.
 * @param row The row position of the room.
 * @param column The column position of the room.
 * @return The (reference to the) room of the dungeon corresponding to the row and column values if those are valid. NULL otherwise.
 *
 * Pre: Hi ha d'haver una sala de la dungeon, una columna i una fila.
 * Post: La funció ens passa la referència si els valors corresponents de la columna i de la fila són vàlids, en cas de que no ho siguin la funicó ens retorna NULL.
 */
Room *get_room_at(Dungeon *dungeon, int row, int column) {
    if (is_valid_coordinates(row, column)) {
        return &dungeon->map[row][column];
    } else {
        return NULL;
    }
}

/**
 * Returns the dungeon room at the input position.
 *
 * @param dungeon The dungeon from which the room should be retrieved.
 * @param position The position of the room.
 * @return The (reference to the) room of the dungeon corresponding to the position if valid. NULL otherwise.
 *
 * Pre: Necessitem almenys una sala de la dungeon i una posició( posició de columna i posició de fila).
 * Post: La funció ens retorna la sala de la dungeon en la posició d'entrada, és a dir, ens retorna si la posició és vàlida, si no ho és ens retornarà NULL.
 */
Room* get_room_at_position(Dungeon *dungeon, Position position) {
    if (is_valid_coordinates(position.row, position.column)) {
        return &dungeon->map[position.row][position.column];
    } else return NULL;
}

/**
 * Initializes the dungeon, setting the starting position to (0,0) and initializes each room in the matrix.
 * @param dungeon The dungeon to be initialized
 * @return SUCCESS code if the initialization was successful, ERROR code if something went wrong.
 *
 * Pre: Hi hem de tenir com a mínim una sala de la dungeon.
 * Post: La funció inicialitza la dungeon, ajustant la posició inical a les coordenades (0,0) i inicialitzant cada sala a la matriu. Si s'inicia amb èxit la funció ens retorna SUCCESS.
 */
int init_dungeon(Dungeon *dungeon) { //reservarà la mateixa quantitat de rooms que abans per reservar la memòria. Sempre s'inicialitza amb les mateixes constants
    set_starting_position(dungeon, 0, 0);

   dungeon->map =  (Room**) malloc(sizeof(Room*) * ROWS);
   for (int r = 0; r < ROWS; ++r) {
        dungeon->map[r] = (Room*) malloc(sizeof(Room) * COLUMNS);
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j){
            init_room(&dungeon->map[i][j]);
        }

    }
    return SUCCESS;
}

/**
 * Resizes the dungeon, freeing the previously allocated rooms if needed.
 * @param dungeon  The dungeon to be resized.
 * @param rows The rows of the new dungeon
 * @param columns The columns of the new dungeon.
 * @return SUCCESS code if the initialization was successful, ERROR code if something went wrong.
 */
int resize_dungeon(Dungeon* dungeon, int rows, int columns) { //reservar memòria per les noves dimensions. Podem fer realloc (+ difícil) o alliberant la memòria anterior i reservar de nova
    for (int r = 0; r < ROWS; ++r) {
        free(dungeon->map[r]);
    }
    free(dungeon->map);

    dungeon->map = (Room**) malloc(sizeof(Room*) * rows);
    for (int r = 0; r < rows; ++r) {
        dungeon->map[r] = (Room*) malloc(sizeof(Room) * columns);
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j){
            init_room(&dungeon->map[i][j]);
        }

    }
    return SUCCESS;
}

/**
 * Releases the memory allocated when constructing the dungeon, if any.
 * @param dungeon The dungeon to be freed.
 */
void free_dungeon(Dungeon* dungeon) {
    free(dungeon);
}

/**
 * Resets the visited flag in all the rooms, clearing it.
 * @param dungeon The dungeon to be reset.
 * @return SUCCESS code if the reset was successful, ERROR code if something went wrong.
 */
int reset_visited(Dungeon* dungeon) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            Room *room = get_room_at(dungeon, i, j);
            if (room == NULL) return ERROR;
            clear_visited(room);
        }
    }
    return SUCCESS;
}