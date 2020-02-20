//
// Created by rcarlini on 22/10/19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/dungeon_utils.h"

void draw_top(FILE *fd, Room *room) {
    fprintf(fd, "%s", UPPER_LEFT_CORNER);

    Wall* wall = get_wall(room, NORTH);
    if (has_open_door(wall)) {
        fprintf(fd, HORIZONTAL_OPEN_DOOR);
    } else if (has_door(wall)) {
        fprintf(fd, HORIZONTAL_CLOSED_DOOR);
    } else {
        fprintf(fd, "%s", HORIZONTAL_WALL);
    }
    fprintf(fd, "%s", UPPER_RIGHT_CORNER);
}

void draw_middle(FILE *fd, Room *room, int is_initial, int is_current) {

    Wall* wall = get_wall(room, WEST);
    if (has_open_door(wall)) {
        fprintf(fd, VERTICAL_OPEN_DOOR);
    } else if (has_door(wall)) {
        fprintf(fd, VERTICAL_CLOSED_DOOR);
    } else {
        fprintf(fd, "%s", VERTICAL_WALL);
    }

    if (is_initial == TRUE) {
        fprintf(fd, INITIAL_PLACEHOLDER);
    } else {
        fprintf(fd, EMPTY_SPACE);
    }

    if (is_current == TRUE) {
        fprintf(fd, CURRENT_PLACEHOLDER);
    } else {
        fprintf(fd, EMPTY_SPACE);
    }

    fprintf(fd, EMPTY_SPACE);

    wall = get_wall(room, EAST);
    if (has_open_door(wall)) {
        fprintf(fd, VERTICAL_OPEN_DOOR);
    } else if (has_door(wall)) {
        fprintf(fd, VERTICAL_CLOSED_DOOR);
    } else {
        fprintf(fd, "%s", VERTICAL_WALL);
    }
}

void draw_bottom(FILE *fd, Room *room){
    fprintf(fd, "%s", BOTTOM_LEFT_CORNER);

    Wall *wall = get_wall(room, SOUTH);
    if (has_open_door(wall)) {
        fprintf(fd, HORIZONTAL_OPEN_DOOR);
    } else if (has_door(wall)) {
        fprintf(fd, HORIZONTAL_CLOSED_DOOR);
    } else {
        fprintf(fd, "%s", HORIZONTAL_WALL);
    }
    fprintf(fd, "%s", BOTTOM_RIGHT_CORNER);
}

void draw_room(FILE *fd, Room *room, int line, int is_initial, int is_current, int hide_disabled) {

    if (is_enabled(room) == FALSE && hide_disabled == TRUE) {
        fprintf(fd, EMPTY_CELL);

    } else if (line == 0) {
        draw_top(fd, room);

    } else if (line == 1) {
        draw_middle(fd, room, is_initial, is_current);

    } else if (line == 2) {
        draw_bottom(fd, room);

    } else {
        // error
    }
}

void draw_dungeon(FILE *fd, Dungeon *dungeon, Room* current_room, int hide_disabled) {

    Position position = get_starting_position(dungeon);
    for (int idx=0; idx<ROWS; idx++) {
        for (int line=0; line<3; line++) {
            for (int jdx = 0; jdx < COLUMNS; jdx++) {
                Room* room = get_room_at(dungeon, idx, jdx);

                int is_initial = FALSE;
                if (line == 1 && position.row == idx && position.column == jdx) {
                    is_initial = TRUE;
                }

                int is_current = FALSE;
                if (current_room != NULL && current_room == room) {
                    is_current = TRUE;
                }

                draw_room(fd, room, line, is_initial, is_current, hide_disabled);
                fprintf(fd, " ");
            }
            fprintf(fd, "\n");
        }
    }
    fprintf(fd, "\n");
}

/**
 * Creates a simple dungeon with a single room with a closed entrance door at the west wall, labeled as Entrance, and
 * an open exit door at the east wall, labeled as Exit.
 *
 * @param dungeon Dungeon structure to be initialized.
 */
void init_simple_dungeon(Dungeon* dungeon) {

    init_dungeon(dungeon);

    Room* start = get_starting_room(dungeon);
    enable_room(start);

    Wall* north_wall = get_wall(start, NORTH);
    set_wall_label(north_wall, "Exit");
    add_exit_door(north_wall);
}

/**
 * Creates a simple dungeon with two rooms:
 * - The starting room with a closed entrance door at the west wall, labeled as Entrance, and
 * an opened door at the east wall.
 * - The second room with an opened door at the west wall and an opened door, labeled as Exit, at the north wall.
 *
 * @param dungeon Dungeon structure to be initialized.
 */
void init_two_rooms_dungeon(Dungeon *dungeon) {

    init_dungeon(dungeon);
    {
        Room* start = get_starting_room(dungeon);
        enable_room(start);

        Wall* east_wall = get_wall(start, EAST);
        add_door(east_wall);
    }

    {
        Position position;
        position = get_starting_position(dungeon);
        position.column++;

        Room* second_room = get_room_at_position(dungeon, position);
        enable_room(second_room);

        Wall* west_wall = get_wall(second_room, WEST);
        add_door(west_wall);

        Wall* north_wall =  get_wall(second_room, NORTH);
        set_wall_label(north_wall, "Exit");
        add_exit_door(north_wall);
    }
}

/**
 * Tries to parse the room data contained in data parameter, initializing the corresponding room accordingly.
 *
 * @param dungeon The dungeon to be initialized.
 * @param row Row coordinate of the room.
 * @param column Column coordinate of the room.
 * @param data The encoded room data.
 * @return SUCCESS if the room data was parsed properly or INVALID_ROOM_DATA if the room data is invalid.
 *
 * Pre:
 * Post:
 */
int read_room_data(Dungeon* dungeon, int row, int column, const char* data) {
    int i = 0;
    while (data[i] == '\0') {
        Room* room;
        room = get_room_at(dungeon, row, column);
        switch(data[i]) {
            case 'I':
                set_starting_position(dungeon, row, column);
                break;
            case 'N': // 0
                add_door(get_wall(room, NORTH));
                open_door(get_wall(room, NORTH));
                break;
            case 'S': // 2
                add_door(get_wall(room, SOUTH));
                open_door(get_wall(room, SOUTH));
                break;
            case 'E': // 1
                add_door(get_wall(room, EAST));
                open_door(get_wall(room, EAST));
                break;
            case 'W': // 3
                add_door(get_wall(room, WEST));
                open_door(get_wall(room, WEST));
                break;
            case 'X':
                switch(data[i - 1]) {
                    case 'N':
                        add_exit_door(get_wall(room, NORTH));
                        break;
                    case 'S':
                        add_exit_door(get_wall(room, SOUTH));
                        break;
                    case 'E':
                        add_exit_door(get_wall(room, EAST));
                        break;
                    case 'W':
                        add_exit_door(get_wall(room, WEST));
                        break;
                }
                break;

            case 'C':
                switch(data[i - 1]) {
                    case 'N':
                        close_door(get_wall(room, NORTH));
                        break;
                    case 'S':
                        close_door(get_wall(room, SOUTH));
                        break;
                    case 'E':
                        close_door(get_wall(room, EAST));
                        break;
                    case 'W':
                        close_door(get_wall(room, WEST));
                        break;
                }
                break;
            default:
                return INVALID_ROOM_DATA;
        }
    }
    return SUCCESS;
}

/**
 * Reads a line from the file fd and tries to parse the room data contained in it.
 *
 * @param dungeon The dungeon to be initialized with the contents of the file.
 * @param fd The opened file containing a dungeon map encoded as a text.
 * @return SUCCESS if the room data was parsed properly, INVALID_ROOM_LINE if the format of a room line is invalid or INVALID_ROOM_DATA if the room data is invalid.
 *
 * Pre:
 * Post:
 */
int read_room_line(Dungeon* dungeon, FILE* fd) {
    char buff[MAX_LOADING_BUFFER];
    init_dungeon(dungeon);
    int i = 0;
    while (fgets(buff, MAX_ROOM_DATA, fd) != NULL) {
        if (i == 0) {
            char* delim = "x";
            char* ptrFirstLine = strtok(buff, delim);
            if (!strtol(ptrFirstLine[0], (char **)NULL, 10)) {
                return INVALID_ROOM_LINE;
            }
            if (!strtol(ptrFirstLine[1], (char **)NULL, 10)) {
                return INVALID_ROOM_LINE;
            }
            if (!is_valid_coordinates(ptrFirstLine[0], ptrFirstLine[1])) {
                return INVALID_ROOM_LINE;
            }
        } else {
            char* delim = " ";
            char* ptrLines = strtok(buff, delim);
            if (!strtol(ptrLines[0], (char **)NULL, 10)) {
                return INVALID_ROOM_LINE;
            }
            if (!strtol(ptrLines[1], (char **)NULL, 10)) {
                return INVALID_ROOM_LINE;
            }
            if (read_room_data(dungeon, ptrLines[0], ptrLines[1], ptrLines[2]) == INVALID_ROOM_DATA) {
                return INVALID_ROOM_DATA;
            }
        }
        ++i;
    }
    return SUCCESS;
}

/**
 * Reads the file in fd and tries to read a dungeon map from it.
 *
 * @param dungeon The dungeon to be initialized with the contents of the file.
 * @param fd The opened file containing a dungeon map encoded as a text.
 * @return SUCCESS if the dungeon was loaded properly, INVALID_ROOM_LINE if the format of a room line is invalid or INVALID_ROOM_DATA if the room data is invalid.
 *
 * Pre:
 * Post:
 */
int load_dungeon_file(Dungeon* dungeon, FILE* fd) {
    int error = read_room_line(dungeon, fd);
    if (error == INVALID_ROOM_LINE) {
        return INVALID_ROOM_LINE;
    } else if (error == INVALID_ROOM_DATA) {
        return INVALID_ROOM_DATA;
    }
    return SUCCESS;
}

/**
 * Opens the file in path and tries to read a dungeon map from it.
 *
 * @param dungeon The dungeon to be initialized with the contents of the file in path.
 * @param path The path to the file containing a dungeon map encoded as a text file.
 * @return SUCCESS if the dungeon was loaded properly, FILE_NOT_FOUND code if the file was not found, INVALID_ROOM_LINE if the format of a room line is invalid or INVALID_ROOM_DATA if the room data is invalid.
 *
 * Pre:
 * Post:
 */
int load_dungeon(Dungeon* dungeon, char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return FILE_NOT_FOUND;
    }
    int error = load_dungeon_file(dungeon, file);
    if (error == INVALID_ROOM_LINE) {
        return INVALID_ROOM_LINE;
    } else if (error == INVALID_ROOM_DATA) {
        return INVALID_ROOM_DATA;
    }
    return SUCCESS;
}
