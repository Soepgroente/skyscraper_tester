#include "rush01checker.h"

static void	print_top_clues(int* top)
{
	printf("x | ");
	for (int i = 0; i < size; i++)
		printf("%d ", top[i]);
	printf("| x\n");
}

static void	print_bot_clues(int* bot)
{
	printf("x | ");
	for (int i = 0; i < size; i++)
		printf("%d ", bot[i]);
	printf("| x\n");
}


void	print_board(int* top, int* bot, int* left, int* right)
{
	int x = 0; int y = 0;

	puts("\n");
	print_top_clues(top);
	printf("--------------------------");
	printf("\n%d | ", left[x]);
	while (x < size)
	{
		while (y < size)
		{
			printf("%d ", board[x][y]);
			y++;
			if (y == size && x < size - 1)
			{
				printf("| %d\n%d | ", right[x], left[x + 1]);
			}
		}
		x++;
		y = 0;
	}
	printf("| %d", right[x - 1]);
	printf("\n--------------------------\n");
	print_bot_clues(bot);
	puts("\n");
}