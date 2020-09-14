// Module that implements the basic functionality of a 3x3 rubik's cube
// Made by Nelson Walker

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cubeops.h"

#define SIZE 3
#define NUMFACES 6

#define YELLOW 0
#define WHITE 1
#define BLUE 2
#define ORANGE 3
#define GREEN 4
#define RED 5



void initialise_face(face_t *face, int *colour_array) {
    int i, j, n=0;
    face->centre_colour = colour_array[4];
    for (i=0; i<SIZE; i++) {
        for (j=0; j<SIZE; j++) {
            face->grid[i][j] = colour_array[n];
            n++;
        }
    }
    if (face->centre_colour == YELLOW) {
        face->edges[0] = GREEN;
        face->edges[1] = RED;
        face->edges[2] = BLUE;
        face->edges[3] = ORANGE;
    }
    else if (face->centre_colour == WHITE) {
        face->edges[0] = BLUE;
        face->edges[1] = RED;
        face->edges[2] = GREEN;
        face->edges[3] = ORANGE;
    }
    else if (face->centre_colour == BLUE) {
        face->edges[0] = YELLOW;
        face->edges[1] = RED;
        face->edges[2] = WHITE;
        face->edges[3] = ORANGE;
    }
    else if (face->centre_colour == ORANGE) {
        face->edges[0] = YELLOW;
        face->edges[1] = BLUE;
        face->edges[2] = WHITE;
        face->edges[3] = GREEN;
    }
    else if (face->centre_colour == GREEN) {
        face->edges[0] = YELLOW;
        face->edges[1] = ORANGE;
        face->edges[2] = WHITE;
        face->edges[3] = RED;
    }
    else if (face->centre_colour == RED) {
        face->edges[0] = YELLOW;
        face->edges[1] = GREEN;
        face->edges[2] = WHITE;
        face->edges[3] = BLUE;
    }
}


face_t *make_new_face() {
    face_t *face;
    face = (face_t*)malloc(sizeof(*face));
    return face;
}


cube_t *make_new_cube() {
    cube_t *cube;
    cube = (cube_t*)malloc(sizeof(*cube));
    int i;
    for (i=0; i<NUMFACES; i++) {
        cube->faces[i] = make_new_face();
    }
    return cube;
}

void free_cube(cube_t *cube) {
    int i;
    for (i=0; i<NUMFACES; i++) {
        free(cube->faces[i]);
    }
    free(cube);
}

void read_face(face_t *face) {
    int array[SIZE*SIZE];
    int ch, i;
    for (i=0;i<SIZE*SIZE; i++) {
        ch = getchar();
        if (ch == 'w') {
            array[i] = WHITE;
        }
        else if (ch == 'y') {
            array[i] = YELLOW;
        }
        else if (ch == 'b') {
            array[i] = BLUE;
        }
        else if (ch == 'o') {
            array[i] = ORANGE;
        }
        else if (ch == 'g') {
            array[i] = GREEN;
        }
        else {
            array[i] = RED;
        }
    }
    initialise_face(face, array);
}

void read_cube(cube_t *cube) {
    read_face(cube->faces[YELLOW]);
    read_face(cube->faces[WHITE]);
    read_face(cube->faces[BLUE]);
    read_face(cube->faces[ORANGE]);
    read_face(cube->faces[GREEN]);
    read_face(cube->faces[RED]);
}

void print_face(face_t *face) {
    int i,j, num;
    printf("centre: %d\n", face->centre_colour);
    for (i=0; i<SIZE; i++) {
        for (j=0; j<SIZE; j++) {
            num = face->grid[i][j];
            if (num == YELLOW) {
                yellow();
            }
            else if (num == WHITE) {
                white();
            }
            else if (num == BLUE) {
                blue();
            }
            else if (num == ORANGE) {
                orange();
            }
            else if (num == GREEN) {
                green();
            }
            else if (num == RED) {
                red();
            }
            printf("%d ", num);
            reset();
        }
        printf("\n");
    }
}

void print_cube(cube_t *cube) {
    int i;
    printf("printing cube: \n");
    for (i=0; i<NUMFACES; i++) {
        print_face(cube->faces[i]);
        printf("\n");
    }
}

void rotate(cube_t *cube, int face_colour) {
    int i, j;
    int **newface = malloc(SIZE*sizeof(*newface));
    for (i=0; i<SIZE; i++) {
        newface[i] = malloc(SIZE*sizeof(newface[0]));
    }
    int **newedges = malloc(4*sizeof(*newedges));
    for (i=0; i<4; i++) {
        newedges[i] = malloc(SIZE*sizeof(newedges[0]));
    }
    newface[0][0] = cube->faces[face_colour]->grid[2][0];
    newface[0][1] = cube->faces[face_colour]->grid[1][0];
    newface[0][2] = cube->faces[face_colour]->grid[0][0];
    newface[1][2] = cube->faces[face_colour]->grid[0][1];
    newface[2][2] = cube->faces[face_colour]->grid[0][2];
    newface[2][1] = cube->faces[face_colour]->grid[1][2];
    newface[2][0] = cube->faces[face_colour]->grid[2][2];
    newface[1][0] = cube->faces[face_colour]->grid[2][1];
    newface[1][1] = cube->faces[face_colour]->grid[1][1];
    for (i=0; i<SIZE; i++) {
        for (j=0; j<SIZE; j++) {
            cube->faces[face_colour]->grid[i][j] = newface[i][j];
        }
    }

    if (face_colour == YELLOW) {
        for (i=0; i<SIZE; i++) {
            newedges[0][i] = cube->faces[ORANGE]->grid[0][2-i];
            newedges[1][i] = cube->faces[GREEN]->grid[0][2-i];
            newedges[2][i] = cube->faces[RED]->grid[0][2-i];
            newedges[3][i] = cube->faces[BLUE]->grid[0][2-i];
        }
        for (i=0; i<SIZE; i++) {
            cube->faces[GREEN]->grid[0][i] = newedges[0][2-i];
            cube->faces[RED]->grid[0][i] = newedges[1][2-i];
            cube->faces[BLUE]->grid[0][i] = newedges[2][2-i];
            cube->faces[ORANGE]->grid[0][i] = newedges[3][2-i];
        }
    }
    else if (face_colour == BLUE) {
        for (i=0; i<SIZE; i++) {
            newedges[0][i] = cube->faces[ORANGE]->grid[2-i][2];
            newedges[1][i] = cube->faces[YELLOW]->grid[2][i];
            newedges[2][i] = cube->faces[RED]->grid[2-i][0];
            newedges[3][i] = cube->faces[WHITE]->grid[0][i];
        }
        for (i=0; i<SIZE; i++) {
            cube->faces[YELLOW]->grid[2][i] = newedges[0][i];
            cube->faces[RED]->grid[i][0] = newedges[1][i];
            cube->faces[WHITE]->grid[0][i] = newedges[2][i];
            cube->faces[ORANGE]->grid[i][2] = newedges[3][i];
        }
    }
    else if (face_colour == ORANGE) {
        for (i=0; i<SIZE; i++) {
            newedges[0][i] = cube->faces[GREEN]->grid[2-i][2];
            newedges[1][i] = cube->faces[YELLOW]->grid[i][0];
            newedges[2][i] = cube->faces[BLUE]->grid[i][0];
            newedges[3][i] = cube->faces[WHITE]->grid[i][0];
        }
        for (i=0; i<SIZE; i++) {
            cube->faces[YELLOW]->grid[i][0] = newedges[0][i];
            cube->faces[BLUE]->grid[i][0] = newedges[1][i];
            cube->faces[WHITE]->grid[i][0] = newedges[2][i];
            cube->faces[GREEN]->grid[2-i][2] = newedges[3][i];
        }
    }
    else if (face_colour == GREEN) {
        for (i=0; i<SIZE; i++) {
            newedges[0][i] = cube->faces[RED]->grid[i][2];
            newedges[1][i] = cube->faces[YELLOW]->grid[0][i];
            newedges[2][i] = cube->faces[ORANGE]->grid[i][0];
            newedges[3][i] = cube->faces[WHITE]->grid[2][i];
        }
        for (i=0; i<SIZE; i++) {
            cube->faces[YELLOW]->grid[0][i] = newedges[0][i];
            cube->faces[ORANGE]->grid[i][0] = newedges[1][2-i];
            cube->faces[WHITE]->grid[2][i] = newedges[2][i];
            cube->faces[RED]->grid[i][2] = newedges[3][2-i];
        }
    }
    else if (face_colour == RED) {
        for (i=0; i<SIZE; i++) {
            newedges[0][i] = cube->faces[BLUE]->grid[2-i][2];
            newedges[1][i] = cube->faces[YELLOW]->grid[2-i][2];
            newedges[2][i] = cube->faces[GREEN]->grid[i][0];
            newedges[3][i] = cube->faces[WHITE]->grid[2-i][2];
        }
        for (i=0; i<SIZE; i++) {
            cube->faces[YELLOW]->grid[2-i][2] = newedges[0][i];
            cube->faces[GREEN]->grid[i][0] = newedges[1][i];
            cube->faces[WHITE]->grid[2-i][2] = newedges[2][i];
            cube->faces[BLUE]->grid[2-i][2] = newedges[3][i];
        }
    }
        

    for (i=0; i<SIZE; i++) {
        free(newface[i]);
    }
    free(newface);

    for (i=0; i<4; i++) {
        free(newedges[i]);
    }
    free(newedges);
    printf("{");
    if (face_colour == YELLOW) {
        printf("B");
    }
    else if (face_colour == WHITE) {
        printf("WHITE");
    }
    else if (face_colour == BLUE) {
        printf("L");
    }
    else if (face_colour == ORANGE) {
        printf("D");
    }
    else if (face_colour == GREEN) {
        printf("R");
    }
    else if (face_colour == RED) {
        printf("U");
    }
    printf("}");
}

cell_t *make_cell_array(int num_cells) {
    cell_t *cells;
    cells = (cell_t*)malloc(num_cells*sizeof(*cells));
    return cells;
}

void form_white_cross(cube_t *cube) {
    int num, i, x, y;
    cell_t *cells;
    bool top_edge;
    while (!is_cross_formed(cube)) {
        // BLUE FACE
        num = num_white_edges(cube, BLUE);
        cells = make_cell_array(num);
        find_white_edge_squares(cube->faces[BLUE], cells);
        for (i=0; i<num; i++) {
            top_edge = false;
            x = cells[i].x; y = cells[i].y;
            if (x==0) {
                top_edge = true;
                // Set x to 2 for now
                x=2;
            }
            while(cube->faces[YELLOW]->grid[x][y] == WHITE) {
                rotate(cube, YELLOW);
            }
            if (top_edge) {
                x=0;
            }
            if (x==1 && y==0) {
                rotate(cube, ORANGE);
            }
            else if (x==1 && y==2) {
                rotate(cube, RED);
            }
            else if (x==0 && y==1) {
                rotate(cube, BLUE);
                while (cube->faces[YELLOW]->grid[1][2] == WHITE) {
                    rotate(cube, YELLOW);
                }
                rotate(cube, RED);
            }
            else if (x==2 && y==1) {
                rotate(cube, BLUE);
                while (cube->faces[YELLOW]->grid[1][0] == WHITE) {
                    rotate(cube, YELLOW);
                }
                rotate(cube, ORANGE);
                rotate(cube, ORANGE);
                rotate(cube, ORANGE);
            }
        }
        free(cells);

        // ORANGE FACE
        if (cube->faces[ORANGE]->grid[1][0] == WHITE) {
            while (cube->faces[YELLOW]->grid[0][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            // Three rotations for anti-clockwise
            rotate(cube, GREEN);
            rotate(cube, GREEN);
            rotate(cube, GREEN);
        }
        if (cube->faces[ORANGE]->grid[1][2] == WHITE) {
            while (cube->faces[YELLOW]->grid[2][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, BLUE);
        }
        if (cube->faces[ORANGE]->grid[0][1] == WHITE) {
            while (cube->faces[YELLOW]->grid[1][0] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, ORANGE);
            while (cube->faces[YELLOW]->grid[2][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, BLUE);
        }
        if (cube->faces[ORANGE]->grid[2][1] == WHITE) {
            while (cube->faces[YELLOW]->grid[1][0] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, ORANGE);
            while (cube->faces[YELLOW]->grid[0][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, GREEN);
            rotate(cube, GREEN);
            rotate(cube, GREEN);
        }

        // GREEN FACE
        if (cube->faces[GREEN]->grid[1][0] == WHITE) {
            while (cube->faces[YELLOW]->grid[1][2] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, RED);
        }
        if (cube->faces[GREEN]->grid[1][2] == WHITE) {
            while (cube->faces[YELLOW]->grid[1][0] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, ORANGE);
        }
        if (cube->faces[GREEN]->grid[0][1] == WHITE) {
            while (cube->faces[YELLOW]->grid[0][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, GREEN);
            while(cube->faces[YELLOW]->grid[1][0] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, ORANGE);
        }
        if (cube->faces[GREEN]->grid[2][1] == WHITE) {
            while (cube->faces[YELLOW]->grid[0][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, GREEN);
            while(cube->faces[YELLOW]->grid[1][2] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, RED);
        }

        // RED FACE
        if (cube->faces[RED]->grid[1][0] == WHITE) {
            while (cube->faces[YELLOW]->grid[2][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, BLUE);
            rotate(cube, BLUE);
            rotate(cube, BLUE);
        }
        if (cube->faces[RED]->grid[1][2] == WHITE) {
            while (cube->faces[YELLOW]->grid[0][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, GREEN);
        }
        if (cube->faces[RED]->grid[0][1] == WHITE) {
            while(cube->faces[YELLOW]->grid[1][2] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, RED);
            while (cube->faces[YELLOW]->grid[0][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, GREEN);
        }
        if (cube->faces[RED]->grid[2][1] == WHITE) {
            while (cube->faces[YELLOW]->grid[1][2] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, RED);
            while(cube->faces[YELLOW]->grid[2][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, BLUE);
            rotate(cube, BLUE);
            rotate(cube, BLUE);
        }

        // WHITE FACE 
        if (cube->faces[WHITE]->grid[1][0] == WHITE) {
            while (cube->faces[YELLOW]->grid[1][0] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
        }
        if (cube->faces[WHITE]->grid[1][2] == WHITE) {
            while (cube->faces[YELLOW]->grid[1][2] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, RED);
            rotate(cube, RED);
        }
        if (cube->faces[WHITE]->grid[0][1] == WHITE) {
            while (cube->faces[YELLOW]->grid[2][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, BLUE);
            rotate(cube, BLUE);
        }
        if (cube->faces[WHITE]->grid[2][1] == WHITE) {
            while (cube->faces[YELLOW]->grid[0][1] == WHITE) {
                rotate(cube, YELLOW);
            }
            rotate(cube, GREEN);
            rotate(cube, GREEN);
        }
    }
}

void find_white_edge_squares(face_t *face, cell_t *cells) {
    int num = 0;
    if (face->grid[1][0] == WHITE) {
        cells[num].x = 1;
        cells[num++].y = 0;
    }
    if (face->grid[0][1] == WHITE) {
        cells[num].x = 0;
        cells[num++].y = 1;
    }
    if (face->grid[1][2] == WHITE) {
        cells[num].x = 1;
        cells[num++].y = 2;
    }
    if (face->grid[2][1] == WHITE) {
        cells[num].x = 2;
        cells[num++].y = 1;
    }
}


int num_white_edges(cube_t *cube, int face) {
    int count = 0;
    count += (cube->faces[face]->grid[1][0] == WHITE);
    count += (cube->faces[face]->grid[0][1] == WHITE);
    count += (cube->faces[face]->grid[1][2] == WHITE);
    count += (cube->faces[face]->grid[2][1] == WHITE);
    return count;
}

int num_white_corners(cube_t *cube, int face) {
    int count = 0;
    count += (cube->faces[face]->grid[0][0] == WHITE);
    count += (cube->faces[face]->grid[0][2] == WHITE);
    count += (cube->faces[face]->grid[2][0] == WHITE);
    count += (cube->faces[face]->grid[2][2] == WHITE);
    return count;
}

bool is_cross_formed(cube_t *cube) {
    return (cube->faces[YELLOW]->grid[1][0] == WHITE &&
            cube->faces[YELLOW]->grid[0][1] == WHITE &&
            cube->faces[YELLOW]->grid[1][2] == WHITE &&
            cube->faces[YELLOW]->grid[2][1] == WHITE);
}

void solve_first_layer(cube_t *cube) {
    // Turn blue face down
    while ((cube->faces[YELLOW]->grid[2][1] != WHITE) | 
            (cube->faces[BLUE]->grid[0][1] != BLUE)) {
                rotate(cube, YELLOW);
            }
    rotate(cube, BLUE);
    rotate(cube, BLUE);

    // Turn orange face down
    while ((cube->faces[YELLOW]->grid[1][0] != WHITE) |
            (cube->faces[ORANGE]->grid[0][1] != ORANGE)) {
                rotate(cube, YELLOW);
            }
    rotate(cube, ORANGE);
    rotate(cube, ORANGE);

    // Turn green face down
    while ((cube->faces[YELLOW]->grid[0][1] != WHITE) |
            (cube->faces[GREEN]->grid[0][1] != GREEN)) {
                rotate(cube, YELLOW);
            }
    rotate(cube, GREEN);
    rotate(cube, GREEN);

    // Turn red face down
    while ((cube->faces[YELLOW]->grid[1][2] != WHITE) |
            (cube->faces[RED]->grid[0][1] != RED)) {
                rotate(cube, YELLOW);
            }
    rotate(cube, RED);
    rotate(cube, RED);


    while (!is_first_solved(cube)) {
        // Yellow face rotations
        if (cube->faces[YELLOW]->grid[0][0] == WHITE) {
            rotate(cube, ORANGE);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
        }
        if (cube->faces[YELLOW]->grid[0][2] == WHITE) {
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, YELLOW);
            rotate(cube, RED);
        }
        if (cube->faces[YELLOW]->grid[2][0] == WHITE) {
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, ORANGE);
        }
        if (cube->faces[YELLOW]->grid[2][2] == WHITE) {
            rotate(cube, RED);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, RED);
        }

        int face_to_go_to, i;
        // Blue face rotations
        if (cube->faces[ORANGE]->grid[0][2] == WHITE) {
            face_to_go_to = cube->faces[BLUE]->grid[0][0];
            for (i=0; i<rotations_to_face(BLUE, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            left_trigger(cube, face_to_go_to);
        }
        if (cube->faces[RED]->grid[0][0] == WHITE) {
            face_to_go_to = cube->faces[BLUE]->grid[0][2];
            for (i=0; i<rotations_to_face(BLUE, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            right_trigger(cube, face_to_go_to);
        }
        if (cube->faces[BLUE]->grid[2][0] == WHITE) {
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
            rotate(cube, YELLOW);
            rotate(cube, ORANGE);
        }
        if (cube->faces[BLUE]->grid[2][2] == WHITE) {
            rotate(cube, RED);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, RED);
        }

        // Orange face rotations
        if (cube->faces[GREEN]->grid[0][2] == WHITE) {
            face_to_go_to = cube->faces[ORANGE]->grid[0][0];
            for (i=0; i<rotations_to_face(ORANGE, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            left_trigger(cube, face_to_go_to);
        }
        if (cube->faces[BLUE]->grid[0][0] == WHITE) {
            face_to_go_to = cube->faces[ORANGE]->grid[0][2];
            for (i=0; i<rotations_to_face(ORANGE, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            right_trigger(cube, face_to_go_to);
        }
        if (cube->faces[ORANGE]->grid[2][0] == WHITE) {
            rotate(cube, GREEN);
            rotate(cube, GREEN);
            rotate(cube, GREEN);
            rotate(cube, YELLOW);
            rotate(cube, GREEN);
        }
        if (cube->faces[ORANGE]->grid[2][2] == WHITE) {
            rotate(cube, BLUE);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, BLUE);
            rotate(cube, BLUE);
            rotate(cube, BLUE);
        }

        // Green face rotations
        if (cube->faces[RED]->grid[0][2] == WHITE) {
            face_to_go_to = cube->faces[GREEN]->grid[0][0];
            for (i=0; i<rotations_to_face(GREEN, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            left_trigger(cube, face_to_go_to);
        }
        if (cube->faces[ORANGE]->grid[0][0] == WHITE) {
            face_to_go_to = cube->faces[GREEN]->grid[0][2];
            for (i=0; i<rotations_to_face(GREEN, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            right_trigger(cube, face_to_go_to);
        }
        if (cube->faces[GREEN]->grid[2][0] == WHITE) {
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, RED);
            rotate(cube, YELLOW);
            rotate(cube, RED);
        }
        if (cube->faces[GREEN]->grid[2][2] == WHITE) {
            rotate(cube, ORANGE);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
            rotate(cube, ORANGE);
        }

        // Red face rotations
        if (cube->faces[BLUE]->grid[0][2] == WHITE) {
            face_to_go_to = cube->faces[RED]->grid[0][0];
            for (i=0; i<rotations_to_face(RED, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            left_trigger(cube, face_to_go_to);
        }
        if (cube->faces[GREEN]->grid[0][0] == WHITE) {
            face_to_go_to = cube->faces[RED]->grid[0][2];
            for (i=0; i<rotations_to_face(RED, face_to_go_to); i++) {
                rotate(cube, YELLOW);
            }
            right_trigger(cube, face_to_go_to);
        }
        if (cube->faces[RED]->grid[2][0] == WHITE) {
            rotate(cube, BLUE);
            rotate(cube, BLUE);
            rotate(cube, BLUE);
            rotate(cube, YELLOW);
            rotate(cube, BLUE);
        }
        if (cube->faces[RED]->grid[2][2] == WHITE) {
            rotate(cube, GREEN);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, YELLOW);
            rotate(cube, GREEN);
            rotate(cube, GREEN);
            rotate(cube, GREEN);
        }
    }
}

bool is_first_solved(cube_t *cube) {
    return (cube->faces[WHITE]->grid[0][0] == WHITE &&
            cube->faces[WHITE]->grid[0][1] == WHITE &&
            cube->faces[WHITE]->grid[0][2] == WHITE &&
            cube->faces[WHITE]->grid[1][0] == WHITE &&
            cube->faces[WHITE]->grid[1][1] == WHITE &&
            cube->faces[WHITE]->grid[1][2] == WHITE &&
            cube->faces[WHITE]->grid[2][0] == WHITE &&
            cube->faces[WHITE]->grid[2][1] == WHITE &&
            cube->faces[WHITE]->grid[2][2] == WHITE &&
            cube->faces[BLUE]->grid[2][0] == BLUE &&
            cube->faces[BLUE]->grid[2][1] == BLUE &&
            cube->faces[BLUE]->grid[2][2] == BLUE &&
            cube->faces[ORANGE]->grid[2][0] == ORANGE &&
            cube->faces[ORANGE]->grid[2][1] == ORANGE &&
            cube->faces[ORANGE]->grid[2][2] == ORANGE &&
            cube->faces[GREEN]->grid[2][0] == GREEN &&
            cube->faces[GREEN]->grid[2][1] == GREEN &&
            cube->faces[GREEN]->grid[2][2] == GREEN &&
            cube->faces[RED]->grid[2][0] == RED &&
            cube->faces[RED]->grid[2][1] == RED &&
            cube->faces[RED]->grid[2][2] == RED);
}

int rotations_to_face(int face_from, int face_to) {
    if (face_from <= face_to) {
        return (face_to - face_from);
    }
    else {
        return (4 - (face_from - face_to));
    }
}

void left_trigger(cube_t *cube, int face) {
    if (face == BLUE) {
        rotate(cube, ORANGE);
        rotate(cube, ORANGE);
        rotate(cube, ORANGE);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, ORANGE);
    }
    else if (face == ORANGE) {
        rotate(cube, GREEN);
        rotate(cube, GREEN);
        rotate(cube, GREEN);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, GREEN);
    }
    else if (face == GREEN) {
        rotate(cube, RED);
        rotate(cube, RED);
        rotate(cube, RED);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, RED);
    }
    else if (face == RED) {
        rotate(cube, BLUE);
        rotate(cube, BLUE);
        rotate(cube, BLUE);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, BLUE);
    }
}

void right_trigger(cube_t *cube, int face) {
    if (face == BLUE) {
        rotate(cube, RED);
        rotate(cube, YELLOW);
        rotate(cube, RED);
        rotate(cube, RED);
        rotate(cube, RED);
    }
    else if (face == ORANGE) {
        rotate(cube, BLUE);
        rotate(cube, YELLOW);
        rotate(cube, BLUE);
        rotate(cube, BLUE);
        rotate(cube, BLUE);
    }
    else if (face == GREEN) {
        rotate(cube, ORANGE);
        rotate(cube, YELLOW);
        rotate(cube, ORANGE);
        rotate(cube, ORANGE);
        rotate(cube, ORANGE);
    }
    else if (face == RED) {
        rotate(cube, GREEN);
        rotate(cube, YELLOW);
        rotate(cube, GREEN);
        rotate(cube, GREEN);
        rotate(cube, GREEN);
    }

}

void solve_second_layer(cube_t *cube) {
    int top_face, side_face;
    while (!second_layer_solved(cube)) {
        if (cube->faces[YELLOW]->grid[2][1] != YELLOW &&
            cube->faces[BLUE]->grid[0][1] != YELLOW) {
                top_face = cube->faces[YELLOW]->grid[2][1];
                side_face = cube->faces[BLUE]->grid[0][1];
                if (top_face == BLUE) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                
                }
                else if (top_face == ORANGE) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                }
                // No need to rotate if green
                else if (top_face == RED) {
                    rotate(cube, YELLOW);
                }
                if (rotations_to_face(side_face, top_face) == 3) {
                    right_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    left_trigger(cube, top_face);
                }
                else if (rotations_to_face(side_face, top_face) == 1) {
                    left_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    right_trigger(cube, top_face);
                }
        }
        else if (cube->faces[YELLOW]->grid[1][0] != YELLOW &&
            cube->faces[ORANGE]->grid[0][1] != YELLOW) {
                top_face = cube->faces[YELLOW]->grid[1][0];
                side_face = cube->faces[ORANGE]->grid[0][1];
                if (top_face == ORANGE) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                
                }
                else if (top_face == GREEN) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                }
                // No need to rotate if red
                else if (top_face == BLUE) {
                    rotate(cube, YELLOW);
                }
                if (rotations_to_face(side_face, top_face) == 3) {
                    right_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    left_trigger(cube, top_face);
                }
                else if (rotations_to_face(side_face, top_face) == 1) {
                    left_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    right_trigger(cube, top_face);
                }
        }
        else if (cube->faces[YELLOW]->grid[0][1] != YELLOW &&
            cube->faces[GREEN]->grid[0][1] != YELLOW) {
                top_face = cube->faces[YELLOW]->grid[0][1];
                side_face = cube->faces[GREEN]->grid[0][1];
                if (top_face == GREEN) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                
                }
                else if (top_face == RED) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                }
                // No need to rotate if blue
                else if (top_face == ORANGE) {
                    rotate(cube, YELLOW);
                }
                if (rotations_to_face(side_face, top_face) == 3) {
                    right_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    left_trigger(cube, top_face);
                }
                else if (rotations_to_face(side_face, top_face) == 1) {
                    left_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    right_trigger(cube, top_face);
                }
        }
        else if (cube->faces[YELLOW]->grid[1][2] != YELLOW &&
            cube->faces[RED]->grid[0][1] != YELLOW) {
                top_face = cube->faces[YELLOW]->grid[1][2];
                side_face = cube->faces[RED]->grid[0][1];
                if (top_face == RED) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                
                }
                else if (top_face == BLUE) {
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                }
                // No need to rotate if orange
                else if (top_face == GREEN) {
                    rotate(cube, YELLOW);
                }
                if (rotations_to_face(side_face, top_face) == 3) {
                    right_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    rotate(cube, YELLOW);
                    left_trigger(cube, top_face);
                }
                else if (rotations_to_face(side_face, top_face) == 1) {
                    left_trigger(cube, side_face);
                    rotate(cube, YELLOW);
                    right_trigger(cube, top_face);
                }
        }
        else {
            // Perform a RT/LT to dislodge yellow squares
            if (cube->faces[BLUE]->grid[1][0] != BLUE) {
                left_trigger(cube, BLUE);
                rotate(cube, YELLOW);
                right_trigger(cube, ORANGE);
            }
            else if (cube->faces[BLUE]->grid[1][2] != BLUE) {
                right_trigger(cube, BLUE);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                left_trigger(cube, RED);
            }
            else if (cube->faces[ORANGE]->grid[1][0] != ORANGE) {
                left_trigger(cube, ORANGE);
                rotate(cube, YELLOW);
                right_trigger(cube, GREEN);
            }
            else if (cube->faces[ORANGE]->grid[1][2] != ORANGE) {
                right_trigger(cube, ORANGE);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                left_trigger(cube, BLUE);
            }
            else if (cube->faces[GREEN]->grid[1][0] != GREEN) {
                left_trigger(cube, GREEN);
                rotate(cube, YELLOW);
                right_trigger(cube, RED);
            }
            else if (cube->faces[GREEN]->grid[1][2] != GREEN) {
                right_trigger(cube, GREEN);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                left_trigger(cube, ORANGE);
            }
            else if (cube->faces[RED]->grid[1][0] != RED) {
                left_trigger(cube, RED);
                rotate(cube, YELLOW);
                right_trigger(cube, BLUE);
            }
            else if (cube->faces[RED]->grid[1][2] != RED) {
                right_trigger(cube, RED);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                rotate(cube, YELLOW);
                left_trigger(cube, GREEN);
            }
        }
    }
}

bool second_layer_solved(cube_t *cube) {
    if (is_first_solved(cube)) {
        return (cube->faces[BLUE]->grid[1][0] == BLUE &&
                cube->faces[BLUE]->grid[1][2] == BLUE &&
                cube->faces[ORANGE]->grid[1][0] == ORANGE &&
                cube->faces[ORANGE]->grid[1][2] == ORANGE &&
                cube->faces[GREEN]->grid[1][0] == GREEN &&
                cube->faces[GREEN]->grid[1][2] == GREEN &&
                cube->faces[RED]->grid[1][0] == RED &&
                cube->faces[RED]->grid[1][2] == RED);
    }
    else {
        return false;
    }
}

int fish_formed(cube_t *cube) {
    int corner1 = 0, corner2 = 0, corner3 = 0, corner4 = 0;
    if (cube->faces[YELLOW]->grid[0][0] == YELLOW) {
        corner1 = 1;
    }
    if (cube->faces[YELLOW]->grid[0][2] == YELLOW) {
        corner2 = 1;
    }
    if (cube->faces[YELLOW]->grid[2][2] == YELLOW) {
        corner3 = 1;
    }
    if (cube->faces[YELLOW]->grid[2][0] == YELLOW) {
        corner4 = 1;
    }
    if (cube->faces[YELLOW]->grid[1][0] == YELLOW &&
            cube->faces[YELLOW]->grid[0][1] == YELLOW &&
            cube->faces[YELLOW]->grid[1][2] == YELLOW &&
            cube->faces[YELLOW]->grid[2][1] == YELLOW &&
            (corner1 + corner2 + corner3 + corner4 == 1)) {
                if (corner1) {
                    return ORANGE;
                }
                if (corner2) {
                    return GREEN;
                }
                if (corner3) {
                    return RED;
                }
                if (corner4) {
                    return BLUE;
                }
                else {
                    printf("ERROR"); return 0;
                }
            }
    else {
        return 0;
    }
}
void rururuur(cube_t *cube, int face) {
    r(cube, face);
    rotate(cube, YELLOW);
    r(cube, face); r(cube, face); r(cube, face);
    rotate(cube, YELLOW);
    r(cube, face);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    r(cube, face); r(cube, face); r(cube, face);
}

void form_cross(cube_t *cube) {
    int front_face;
    while (!(front_face = nine_twelve_formed(cube))) {
        fururf(cube, BLUE);
    }
    while (!top_cross_formed(cube)) {
        fururf(cube, front_face);
    }
}

void r(cube_t *cube, int face) {
    if (face == BLUE) {
        rotate(cube, RED);
    }
    else if (face == ORANGE) {
        rotate(cube, BLUE);
    }
    else if (face == GREEN) {
        rotate(cube, ORANGE);
    }
    else if (face == RED) {
        rotate(cube, GREEN);
    }
}

void l(cube_t *cube, int face) {
    if (face == BLUE) {
        rotate(cube, ORANGE);
        rotate(cube, ORANGE);
        rotate(cube, ORANGE);
    }
    else if (face == ORANGE) {
        rotate(cube, GREEN);
        rotate(cube, GREEN);
        rotate(cube, GREEN);
    }
    else if (face == GREEN) {
        rotate(cube, RED);
        rotate(cube, RED);
        rotate(cube, RED);
    }
    else if (face == RED) {
        rotate(cube, BLUE);
        rotate(cube, BLUE);
        rotate(cube, BLUE);
    }
}

void fururf(cube_t *cube, int face) {
    rotate(cube, face);
    rotate(cube, YELLOW);
    r(cube, face);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    r(cube, face);
    r(cube, face);
    r(cube, face);
    rotate(cube, face);
    rotate(cube, face);
    rotate(cube, face);
}

int nine_twelve_formed(cube_t *cube) {
    if (cube->faces[YELLOW]->grid[1][0] == YELLOW && 
        cube->faces[YELLOW]->grid[0][1] == YELLOW) {
            return BLUE;
    }
    else if (cube->faces[YELLOW]->grid[1][2] == YELLOW && 
        cube->faces[YELLOW]->grid[0][1] == YELLOW) {
            return ORANGE;
    }
    else if (cube->faces[YELLOW]->grid[1][2] == YELLOW && 
        cube->faces[YELLOW]->grid[2][1] == YELLOW) {
            return GREEN;
    }
    else if (cube->faces[YELLOW]->grid[1][0] == YELLOW && 
        cube->faces[YELLOW]->grid[2][1] == YELLOW) {
            return RED;
    }
    else {
        return 0;
    }

}
bool all_yellow(cube_t *cube) {
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (cube->faces[YELLOW]->grid[i][j] != YELLOW) {
                return false;
            }
        }
    }
    return true;
}

int has_top_match(cube_t *cube) {
    int face_from = 0, face_to = 0;
    if (cube->faces[BLUE]->grid[0][0] == cube->faces[BLUE]->grid[0][2]) {
        face_from = BLUE;
        face_to = cube->faces[BLUE]->grid[0][0];
        for (int i=0; i<rotations_to_face(face_from, face_to); i++) {
            rotate(cube, YELLOW);
        }
    }
    else if (cube->faces[ORANGE]->grid[0][0] == cube->faces[ORANGE]->grid[0][2]) {
        face_from = ORANGE;
        face_to = cube->faces[ORANGE]->grid[0][0];
        for (int i=0; i<rotations_to_face(face_from, face_to); i++) {
            rotate(cube, YELLOW);
        }
    }
    else if (cube->faces[GREEN]->grid[0][0] == cube->faces[GREEN]->grid[0][2]) {
        face_from = GREEN;
        face_to = cube->faces[GREEN]->grid[0][0];
        for (int i=0; i<rotations_to_face(face_from, face_to); i++) {
            rotate(cube, YELLOW);
        }
    }
    else if (cube->faces[RED]->grid[0][0] == cube->faces[RED]->grid[0][2]) {
        face_from = RED;
        face_to = cube->faces[RED]->grid[0][0];
        for (int i=0; i<rotations_to_face(face_from, face_to); i++) {
            rotate(cube, YELLOW);
        }
    }
    else {
        return 0;
    }
    if (face_to == BLUE) {
            return RED;
        }
    else if (face_to == ORANGE) {
        return BLUE;
    }
    else if (face_to == GREEN) {
        return ORANGE;
    }
    else if (face_to == RED) {
        return GREEN;
    }
}

void lurulur(cube_t *cube, int face) {
    l(cube, face);
    rotate(cube, YELLOW);
    r(cube, face);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    l(cube, face);
    l(cube, face);
    l(cube, face);
    rotate(cube, YELLOW);
    r(cube, face);
    r(cube, face);
    r(cube, face);
    rururuur(cube, face);
}

bool top_cross_formed(cube_t *cube) {
    return (cube->faces[YELLOW]->grid[1][0] == YELLOW &&
            cube->faces[YELLOW]->grid[0][1] == YELLOW &&
            cube->faces[YELLOW]->grid[1][2] == YELLOW &&
            cube->faces[YELLOW]->grid[2][1] == YELLOW);
}

bool cube_solved(cube_t *cube) {
    for (int n=0; n<6; n++) {
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                if (cube->faces[n]->grid[i][j] != n) {
                    return false;
                }
            }
        }
    }
    return true;
}

int find_completed_side(cube_t *cube) {
    if (cube->faces[BLUE]->grid[0][1] == BLUE) {
        return GREEN;
    }
    else if (cube->faces[ORANGE]->grid[0][1] == ORANGE) {
        return RED;
    }
    else if (cube->faces[GREEN]->grid[0][1] == GREEN) {
        return BLUE;
    }
    else if (cube->faces[RED]->grid[0][1] == RED) {
        return ORANGE;
    }
    else {
        return 0;
    }
}

void fluff1(cube_t *cube, int face) {
    rotate(cube, face);
    rotate(cube, face);
    rotate(cube, YELLOW);
    l(cube, face);
    l(cube, face);
    l(cube, face);
    r(cube, face);
    r(cube, face);
    r(cube, face);
    rotate(cube, face);
    rotate(cube, face);
    l(cube, face);
    r(cube, face);
    rotate(cube, YELLOW);
    rotate(cube, face);
    rotate(cube, face);
}

void fluff2(cube_t *cube, int face) {
    rotate(cube, face);
    rotate(cube, face);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    l(cube, face);
    l(cube, face);
    l(cube, face);
    r(cube, face);
    r(cube, face);
    r(cube, face);
    rotate(cube, face);
    rotate(cube, face);
    l(cube, face);
    r(cube, face);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    rotate(cube, YELLOW);
    rotate(cube, face);
    rotate(cube, face);
}

int find_direction(cube_t *cube, int opposite_side) {
    rotate(cube, YELLOW);
    if (cube->faces[opposite_side]->grid[0][1] == opposite_side) {
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        return 1;
    }
    else {
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        rotate(cube, YELLOW);
        return 2;
    }
}


void solve_third_layer(cube_t *cube) {
    int face;
    form_cross(cube);
    while (!(face = fish_formed(cube))) {
        if (all_yellow(cube)) {
            break;
        }
        if (cube->faces[ORANGE]->grid[0][2] == YELLOW) {
            rururuur(cube, BLUE);
        }
        else if (cube->faces[GREEN]->grid[0][2] == YELLOW) {
            rururuur(cube, ORANGE);
        }
        else if (cube->faces[RED]->grid[0][2] == YELLOW) {
            rururuur(cube, GREEN);
        }
        else if (cube->faces[BLUE]->grid[0][2] == YELLOW) {
            rururuur(cube, RED);
        }
    }
    while (!all_yellow(cube)) {
        rururuur(cube, face);
        face = fish_formed(cube);
    }
    
    while (!(face = has_top_match(cube))) {
        lurulur(cube, BLUE);
    }
    lurulur(cube, face);
    
    if (!cube_solved(cube)) {
        int opposite_side;
        if (opposite_side = find_completed_side(cube)) {
            if (find_direction(cube, opposite_side) == 1) {
                fluff1(cube, opposite_side);
            }
            else {
                fluff2(cube, opposite_side);
            }
        }
        else {
            fluff2(cube, face);
            opposite_side = find_completed_side(cube);
            if (find_direction(cube, opposite_side) == 1) {
                fluff1(cube, opposite_side);
            }
            else {
                fluff2(cube, opposite_side);
            }
        }
    }

    if (!cube_solved(cube)) {
        solve_third_layer(cube);
    }

}


// Creates a script output.ahk to solve a shuffled rubix cube at the site
// http://iamthecu.be/
void create_hotkey_script() {
    printf("^;::\nSendInput, ");
    cube_t *cube = make_new_cube();

    read_cube(cube);

    form_white_cross(cube);
    solve_first_layer(cube);
    solve_second_layer(cube);
    solve_third_layer(cube);

    free_cube(cube);

    printf("\n");
    printf("return");
}

// Good for testing and debugging
void test_outputs(int num_testcases) {
    for (int i=0; i<num_testcases; i++) {
        cube_t *cube = make_new_cube();

        read_cube(cube);
        print_cube(cube);

        form_white_cross(cube);
        solve_first_layer(cube);
        solve_second_layer(cube);
        solve_third_layer(cube);
        print_cube(cube);

        free_cube(cube);
        // Eat newline character
        getchar();
        printf("\n\n\n\n\n");
    }
}


void yellow() {
  printf("\033[1;33m");
}

void white() {
    printf("\033[1;36m");
}

void blue() {
    printf("\033[0;34m");
}

void orange() {
    printf("\033[0;35m");
}

void green() {
    printf("\033[0;32m");
}

void red() {
  printf("\033[1;31m");
}

void reset() {
    printf("\033[0m");
}
