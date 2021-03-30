#include "game.h"

static char map[Y][X + 1];
static int ny = 1;
static int nx = 1;
static int hp = 100;

int main()
{
	int ch;

	// korean
	setlocale(LC_CTYPE, "ko_KR.utf8");
	initscr();
	// input keyboard
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	make_map(map);

	while (1)
	{
		curs_set(0);
		if (touch_MorY(map, ny, nx, hp))
			break;
		print_map(map, ny, nx, hp);
		ch = getch();
		usleep(1000 * 100);
		if (ch == ERR)
			ch = 0;
		if (ch == KEY_LEFT && is_movable(map, ny, nx - 1) && nx--)
			touch_AorT(map, ny, nx, &hp);
		else if (ch == KEY_RIGHT && is_movable(map, ny, nx + 1) && nx++)
			touch_AorT(map, ny, nx, &hp);
		else if (ch == KEY_UP && is_movable(map, ny - 1, nx) && ny--)
			touch_AorT(map, ny, nx, &hp);
		else if (ch == KEY_DOWN && is_movable(map, ny + 1, nx) && ny++)
			touch_AorT(map, ny, nx, &hp);
		else if (ch == ESC)
			break;
	}
	endwin();
	return (0);
}
