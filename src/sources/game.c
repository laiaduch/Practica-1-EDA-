//
// Created by rcarlini on 4/1/20.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/utils.h"
#include "../headers/state.h"
#include "../headers/dungeon_utils.h"
#include "../headers/game.h"

int print_wall_info(Wall* wall, char *side) {

    int doors = 0;
    if (has_door(wall) == TRUE) {
        printf("There is a door at the %s wall. ", side);
        doors++;

        if (has_open_door(wall) == TRUE) {
            printf("Seems to be OPEN.   ");

        } else {
            printf("Seems to be CLOSED. ");
        }

//        if (strlen(wall->label) > 0) {
//            printf("It has a label: \"%s\". ", wall->label);
//        }
        printf("\n");
    }

    return doors;
}

char choose_direction(Room* room) {

    int doors = 0;

    printf("\n");
    doors += print_wall_info(get_wall(room, NORTH), "North");
    doors += print_wall_info(get_wall(room, EAST), "East");
    doors += print_wall_info(get_wall(room, SOUTH), "South");
    doors += print_wall_info(get_wall(room, WEST), "West");

    char option;
    if (doors == 0) {
        option = read_char_option("There are no door! Press Q for quit and try again...\n");

    } else {
        option = read_char_option("Which direction do you want to go? (N/E/S/W)\nPress Q for quit\n");
    }

    return option;
}

int is_valid_direction_option(char direction) {
    if (direction == NORTH || direction == EAST ||
        direction == SOUTH || direction == WEST) {
        return TRUE;

    } else {
        return INVALID_OPTION;
    }
}

void do_move(State* state, char direction) {

    int move_result = move(state, direction);
    switch (move_result) {
        case SUCCESS:
            // Do nothing, next move...
            break;

        case NO_DOOR_ERROR:
            printf("This side has no door!\n");
            break;

        case INVALID_MOVE:
            printf("This move is invalid!\n");
            break;

        case INVALID_DIRECTION:
            printf("This direction is invalid!\n");
            break;

        default:
            printf("Unexpected move result code!\n");
            break;
    }
}

void start_game(Dungeon* dungeon) {

    State state;
    init_state(&state, dungeon);

    int quit = FALSE;
    printf("Starting game...\n\n");
    while (quit == FALSE) {

        Room* current_room = get_current_room(&state);
        if (current_room == NULL) {
            quit = TRUE;
            printf("No current room found! Quitting...\n");

        } else {
            draw_dungeon(stdout, dungeon, current_room, TRUE);

            char direction = choose_direction(current_room);

            if (direction == QUIT) {
                quit = TRUE;

            } else if (is_valid_direction_option(direction) == TRUE) {
                do_move(&state, direction);
                if (is_finished(&state) == TRUE) {
                    quit = TRUE;
                }

            } else {
                printf("Invalid option! Try again...\n");
            }
        }
    }

    if (is_finished(&state) == TRUE) {
        printf("You found the exit!\n\n");
    }
}

void solve(Dungeon* dungeon) {
}
