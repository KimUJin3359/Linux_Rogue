#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define Y 20
#define X Y
#define ESC 27

typedef struct	MAP{
	char map[Y][X + 1];
	int ny;
	int nx;
	int hp;
	int flag;
}				MAP;

// game.c
void make_map(MAP *m);
void print_map(MAP m);
bool is_movable(MAP m, int n_y, int n_x);
bool touch_MorY(MAP m);
void touch_AorT(MAP *m);

// thread.c
void *monster_move(void *ptr);

#endif
