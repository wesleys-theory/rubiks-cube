#ifndef CUBEOPS_H
#define CUBEOPS_H

#define SIZE 3
#define NUMFACES 6

#define YELLOW 0
#define WHITE 1
#define BLUE 2
#define ORANGE 3
#define GREEN 4
#define RED 5

typedef struct {
    int grid[SIZE][SIZE];
    int centre_colour;
    int edges[4];
} face_t;

typedef struct {
    face_t *faces[NUMFACES];
} cube_t;

typedef struct {
    int x;
    int y;
} cell_t;

cell_t *make_cell_array();
void initialise_face(face_t *face, int *colour_array);
void initialise_cube(cube_t *cube, int **face_array);
face_t *make_new_face();
cube_t *make_new_cube();
void free_cube(cube_t *cube);
void read_face(face_t *face);
void read_cube(cube_t *cube);
void print_face(face_t *face);
void print_cube(cube_t *cube);
void rotate(cube_t *cube, int face_colour);
bool is_cross_formed(cube_t *cube);
int num_white_edges(cube_t *cube, int face);
int num_white_corners(cube_t *cube, int face);
void form_white_cross(cube_t *cube);
void find_white_edge_squares(face_t *face, cell_t *cells);
void solve_first_layer(cube_t *cube);
bool is_first_solved(cube_t *cube);
int rotations_to_face(int face_from, int face_to);
void left_trigger(cube_t *cube, int face);
void right_trigger(cube_t *cube, int face);
void solve_second_layer(cube_t *cube);
bool second_layer_solved(cube_t *cube);
int nine_twelve_formed(cube_t *cube);
void form_nine_twelve(cube_t *cube);
void fururf(cube_t *cube, int face);
void r(cube_t *cube, int face);
int fish_formed(cube_t *cube);
void solve_third_layer(cube_t *cube);
bool top_cross_formed(cube_t *cube);
void fluff1(cube_t *cube, int face);
void fluff2(cube_t *cube, int face);
void test_outputs(int num_testcases);
void create_hotkey_script();

void yellow();
void white();
void blue();
void orange();
void green();
void red();
void reset();


#endif