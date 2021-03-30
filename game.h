#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

#define Y 20
#define X Y
#define ESC 27

void make_map(char map[Y][X + 1]);
void print_map(char map[Y][X + 1], int ny, int nx, int hp);
bool is_movable(char map[Y][X + 1], int n_y, int n_x);
bool touch_MorY(char map[Y][X + 1], int ny, int nx, int hp);
void touch_AorT(char map[Y][X + 1], int ny, int nx, int *hp);

#endif
