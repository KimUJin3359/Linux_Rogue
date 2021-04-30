#include "game.h"

// setting a random map
void make_map(MAP *game)
{
	int t_y, t_x;

	game->ny = 1;
	game->nx = 1;
	game->hp = 100;
	// make a basic setting
	for (int i = 0; i < Y; i++)
	{
		int j;

		for (j = 0; j < X; j++)
		{
			if (i == 0 || i == Y - 1 || j == 0 || j == X - 1)
				game->map[i][j] = '#';
			else
				game->map[i][j] = ' ';
		}
		game->map[i][j] = '\0';
	}
	srand((unsigned int)time(NULL));	

	// make a random wall
	for (int i = 0; i < Y; i++)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = '#';
	}

	// make a random apple
	for (int i = 0; i < Y / 5; i++)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = 'a';
	}

	// make a random thorn
	for (int i = 0; i < Y; i++)
	{
 		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = '^';
	}

	// make a random monster
	for (int i = 0; i < Y / 5; i++)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = 'M';
	}

	// make a random holy grail
	while (true)
	{
		t_y = rand() % (Y - 2) + 1;
		t_x = rand() % (X - 2) + 1;
		if (t_y != 1 && t_x != 1)
		{
			game->map[t_y][t_x] = 'Y';
			break;
		}
	}
}

// print a map
void print_map(MAP game)
{
	clear();
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			if (y==game.ny && x==game.nx)
				printw("%s", "🤺");
			else if (game.map[y][x] == '#')
				printw("%s", "🏔 ");
			else if (game.map[y][x] == 'M')
				printw("%s", "🐉");
			else if (game.map[y][x] == 'Y')
				printw("%s", "🌟");
			else if (game.map[y][x] == 'a')
				printw("%s", "🐟");
			else if (game.map[y][x] == '^')
				printw("%s", "🔥");
			else if (game.map[y][x] == ' ')
				printw("%s", "  ");
		}
		printw("\n");
	}
	printw("\n\n\n HP : %d", game.hp);
	refresh();
}

// judge if movable
bool is_movable(MAP game, int n_y, int n_x)
{
	if (n_y < 0 || n_y >= Y || n_x < 0 || n_x >= X)
		return (false);
	else if (game.map[n_y][n_x] == '#')
		return (false);
	return (true);
}

// judge meeting a monster, a holy grail or a thorn
bool touch_MorY(MAP game)
{
	if (game.map[game.ny][game.nx] == 'M')
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
	else if (game.map[game.ny][game.nx] == 'Y')
	{
		usleep(1000 * 500);
		clear();
		refresh();
		move(10, 20);
		printw("WIN\n");
		move(11, 20);
		printw("HP : %d\n", game.hp);
		refresh();
		sleep(1);
		return (true);
	}
	else if (game.map[game.ny][game.nx] == '^')
	{
		if (game.hp == 0)
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
void touch_AorT(MAP *game)
{
	if (game->map[game->ny][game->nx] == '^') game->hp -= 10;
	else if (game->map[game->ny][game->nx] == 'a')
	{
		game->hp += 10;
		game->map[game->ny][game->nx] = ' ';
	}
}
