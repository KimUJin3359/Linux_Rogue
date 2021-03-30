#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#define Y 20
#define X Y
#define ESC 27

char map[Y][X + 1];
int ny = 1;
int nx = 1;
int hp = 100;

// setting a random map
void make_map()
{
	int t_y, t_x;

	// make a basic setting
	for (int i = 0; i < Y; i++)
	{
		int j;

		for (j = 0; j < X; j++)
		{
			if (i == 0 || i == Y - 1 || j == 0 || j == X - 1)
				map[i][j] = '#';
			else
				map[i][j] = ' ';
		}
		map[i][j] = '\0';
	}
	srand((unsigned int)time(NULL));	

	// make a random wall
	for (int i = 0; i < Y; i++)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			map[t_y][t_x] = '#';
	}

	// make a random apple
	for (int i = 0; i < Y / 5; i++)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			map[t_y][t_x] = 'a';
	}

	// make a random thorn
	for (int i = 0; i < Y; i++)
	{
 		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			map[t_y][t_x] = '^';
	}

	// make a random monster
	for (int i = 0; i < Y / 5; i++)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			map[t_y][t_x] = 'M';
	}

	// make a random holy grail
	while (true)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
		{
			map[t_y][t_x] = 'Y';
			break;
		}
	}
}

// print a map
void print_map()
{
	clear();
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			if (y==ny && x==nx)
				printw("🧍");
			else if (map[y][x] == '#')
				printw("%s", "⬛");
			else if (map[y][x] == 'M')
				printw("%s", "🐲");
			else if (map[y][x] == 'Y')
				printw("%s", "🌟");
			else if (map[y][x] == 'a')
				printw("%s", "🍓");
			else if (map[y][x] == '^')
				printw("%s", "🔥");
			else if (map[y][x] == ' ')
				printw("%s", "  " );
		}
		printw("\n");
	}
	printw("\n\n\n HP : %d", hp);
	refresh();
}

// judge if movable
bool is_movable(int n_y, int n_x)
{
	if (n_y < 0 || n_y >= Y || n_x < 0 || n_x >= X)
		return (false);
	else if (map[n_y][n_x] == '#')
		return (false);
	return (true);
}

// judge meeting a monster, a holy grail or a thorn
bool touch_MorY()
{
	if (map[ny][nx] == 'M')
	{
		usleep(1000 * 500);
		clear();
		refresh();
		move(10, 20);
		printw("Game Over\n");
		refresh();
		sleep(1);
		return (true);
	}
	else if (map[ny][nx] == 'Y')
	{
		usleep(1000 * 500);
		clear();
		refresh();
		move(10, 20);
		printw("WIN\n");
		move(11, 20);
		printw("HP : %d\n", hp);
		refresh();
		sleep(1);
		return (true);
	}
	else if (map[ny][nx] == '^')
	{
		if (hp == 0)
		{
			usleep(1000 * 500);
			clear();
			refresh();
			move(10, 20);
			printw("Game Over\n");
			refresh();
			sleep(1);
			return (true);
		}
	}
	return (false);
}

// meet apple, or thorn
void touch_AorT()
{
	if (map[ny][nx] == '^') hp -= 10;
	else if (map[ny][nx] == 'a')
	{
		hp += 10;
		map[ny][nx] = ' ';
	}
}

int main()
{
	int ch;

	// korean
	setlocale(LC_CTYPE, "ko_KR.utf8");
	initscr();
	// input keyboard
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	make_map();
	while (1)
	{
		curs_set(0);
		if (touch_MorY())
			break;
		print_map();
		ch = getch();
		usleep(1000 * 100);
		if (ch == ERR)
			ch = 0;
		if (ch == KEY_LEFT && is_movable(ny, nx - 1))
		{
			nx--;
			touch_AorT();
		}
		else if (ch == KEY_RIGHT && is_movable(ny, nx + 1))
		{
			nx++;
			touch_AorT();
		}
		else if (ch == KEY_UP && is_movable(ny - 1, nx))
		{
			ny--;
			touch_AorT();
		}
		else if (ch == KEY_DOWN && is_movable(ny + 1, nx))
		{
			ny++;
			touch_AorT();
		}
		else if (ch == ESC)
			break;
	}
	endwin();
	return (0);
}
