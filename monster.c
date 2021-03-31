#include "game.h"

extern pthread_mutex_t mlock;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
char copy[Y][X + 1];

void copy_map(char map[Y][X + 1])
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j <= X; j++)
			copy[i][j] = map[i][j];
	}
}

void *monster_move(void *ptr)
{
	int temp;

	MAP *game = (MAP *)ptr;
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j <= X; j++)
			printf("%c ", game->map[i][j]);
		printf("\n");
	}
	copy_map(game->map);
	srand((unsigned int)time(NULL));
	while (1)
	{
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < X; j++)
			{
				if (game->map[i][j] == 'M')
				{
					temp = rand() % 4;
					// map size check && wall check
					if (i + dy[temp] >= 0 && i + dy[temp] < Y && j + dx[temp] >=0 && j + dx[temp] < X && game->map[i + dy[temp]][j + dx[temp]] != '#')
					{
						game->map[i + dy[temp]][j + dx[temp]] = 'M';
						pthread_mutex_lock(&mlock);
						if (copy[i][j] != 'M')
							game->map[i][j] = copy[i][j];
						else
							game->map[i][j] = ' ';
						pthread_mutex_unlock(&mlock);
					}
				}
			}
		}
		usleep(1000 * 200);
	}
}
