#include "game.h"

// setting a random map
void make_map(MAP *game)
{
	int t_y, t_x;

	game->ny = 1;
	game->nx = 1;
	game->map = (char **)malloc(sizeof(char *) * game->map_y);
	for (int i = 0; i < game->map_y; i++)
		game->map[i] = (char *)malloc(sizeof(char) * game->map_x);
	game->hp = 100;
	// make a basic setting
	for (int i = 0; i < game->map_y; i++)
	{
		int j;

		for (j = 0; j < game->map_x; j++)
		{
			if (i == 0 || i == game->map_y - 1 || j == 0 || j == game->map_x - 1)
				game->map[i][j] = '#';
			else
				game->map[i][j] = ' ';
		}
		game->map[i][j] = '\0';
	}
	srand((unsigned int)time(NULL));	

	// make a random wall
	for (int i = 0; i < game->map_x; i++)
	{
		t_y = rand() % (game->map_y - 2) + 1;
		t_x = rand() % (game->map_x - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = '#';
	}

	// make a random apple
	for (int i = 0; i < game->map_x / 4; i++)
	{
		t_y = rand() % (game->map_y - 2) + 1;
		t_x = rand() % (game->map_x - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = 'a';
	}

	// make a random thorn
	for (int i = 0; i < (game->map_x * 2); i++)
	{
 		t_y = rand() % (game->map_y - 2) + 1;
		t_x = rand() % (game->map_x - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = '^';
	}

	// make a random monster
	for (int i = 0; i < game->map_x / 4; i++)
	{
		t_y = rand() % (game->map_y - 2) + 1;
		t_x = rand() % (game->map_x - 2) + 1;
		if (t_y != 1 && t_x != 1)
			game->map[t_y][t_x] = 'M';
	}

	// make a random holy grail
	while (true)
	{
		t_y = rand() % (game->map_y - 2) + 1;
		t_x = rand() % (game->map_x - 2) + 1;
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
	for (int y = 0; y < game.map_y; y++)
	{
		for (int x = 0; x < game.map_x; x++)
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
	printw("\n HP : %d", game.hp);
	refresh();
}

// judge if movable
bool is_movable(MAP game, int n_y, int n_x)
{
	if (n_y < 0 || n_y >= game.map_y || n_x < 0 || n_x >= game.map_x)
		return (false);
	else if (game.map[n_y][n_x] == '#')
		return (false);
	return (true);
}

bool game_end(MAP game, int n)
{
	clear();
	refresh();
	usleep(1000 * 500);
	move(game.map_y / 2, game.map_x / 2);
	if (n == 1)
		printw("GAME OVER\n");
	else
	{
		printw("HP : %d\n", game.hp);
		printw("WIN\n");
	}
	refresh();
	sleep(1);
	return (true);
}

// judge meeting a monster, a holy grail or a thorn
bool touch_MorY(MAP game)
{
	if (game.map[game.ny][game.nx] == 'M')
		return (game_end(game, 1));
	else if (game.map[game.ny][game.nx] == 'Y')
		return (game_end(game, 0));
	else if (game.map[game.ny][game.nx] == '^')
		return (game_end(game, 1));
	return (false);
}

// meet apple, or thorn
void touch_AorT(MAP *game)
{
	if (game->map[game->ny][game->nx] == '^') 
		game->hp -= 10;
	else if (game->map[game->ny][game->nx] == 'a')
	{
		game->hp += 10;
		game->map[game->ny][game->nx] = ' ';
	}
}
