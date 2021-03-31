#include "game.h"

static MAP game;
pthread_mutex_t mlock;

int main()
{
	int ch;

	// korean
	setlocale(LC_CTYPE, "ko_KR.utf8");
	initscr();
	// input keyboard
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	make_map(&game);

	pthread_t tid;
	pthread_create(&tid, NULL, monster_move, &game);
	while (1)
	{
		curs_set(0);
		if (touch_MorY(game))
			break;
		pthread_mutex_lock(&mlock);
		print_map(game);
		pthread_mutex_unlock(&mlock);
		ch = getch();
		usleep(1000 * 100);
		if (ch == ERR)
			ch = 0;
		if (ch == KEY_LEFT && is_movable(game, game.ny, game.nx - 1) && game.nx--)
			touch_AorT(&game);
		else if (ch == KEY_RIGHT && is_movable(game, game.ny, game.nx + 1) && game.nx++)
			touch_AorT(&game);
		else if (ch == KEY_UP && is_movable(game, game.ny - 1, game.nx) && game.ny--)
			touch_AorT(&game);
		else if (ch == KEY_DOWN && is_movable(game, game.ny + 1, game.nx) && game.ny++)
			touch_AorT(&game);
		else if (ch == ESC)
			break;
	}
	pthread_cancel(tid);
	pthread_join(tid, NULL);
	endwin();
	return (0);
}
