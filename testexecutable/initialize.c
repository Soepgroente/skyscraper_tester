#include "sudoku.h"

static void	paste_input(int* clue, char** argv, int x)
{
	int i = 0;

	x++;
	while (argv[x][i] != '\0')
	{
		if (!isdigit(argv[x][i]))
			some_error("Error");
		i++;
	}
	clue[(x - 1) % size] = atoi(argv[x]);
	if (clue[(x - 1) % size] < 1 || clue[(x - 1) % size] > size)
		some_error("Error");
}

void	free_everything(t_grid* grid)
{
	free(grid->col);
	free(grid->rev_col);
	free(grid->row);
	free(grid->rev_row);
	free(grid->sky_down);
	free(grid->sky_up);
	free(grid->sky_left);
	free(grid->sky_right);
	for (int i = 0; i < size * size; i++)
		free_board(grid->board[i]);
	free(grid->board);
}

void	free_board(int*** board)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
			free(board[x][y]);
		free(board[x]);
	}
	free(board);
}

int***	malloc_board(void)
{
	int*** board;

	board = malloc(size * sizeof(int**));
	if (!board)
		some_error("Malloc board error");
	for (int x = 0; x < size; x++)
	{
		board[x] = malloc(size * sizeof(int*));
		if (!board[x])
			some_error("Malloc board error");
		for (int y = 0; y < size; y++)
		{
			board[x][y] = malloc((size + 1) * sizeof(int));
			if (!board[x][y])
				some_error("Malloc board error");
			for (int z = 0; z < size + 1; z++)
				board[x][y][z] = z;
		}
	}
	return (board);
}

static int**	malloc_line(void)
{
	int**	line;
	line = malloc(size * sizeof(int*));
	if (!line)
		some_error("Malloc line error");
	for (int i = 0; i < size; i++)
	{
		line[i] = malloc((size + 1) * sizeof(int));
		if (!line[i])
			some_error("Malloc line error");
	}
	return (line);
}

static void	malloc_the_things(t_grid* grid)
{
	grid->sky_up = malloc(size * sizeof(int));
	grid->sky_down = malloc(size * sizeof(int));
	grid->sky_left = malloc(size * sizeof(int));
	grid->sky_right = malloc(size * sizeof(int));
	if (!grid->sky_up || !grid->sky_down || !grid->sky_left || !grid->sky_right)
		some_error("Malloc error");
	grid->row = malloc_line();
	grid->rev_row = malloc_line();
	grid->col = malloc_line();
	grid->rev_col = malloc_line();
	grid->board = malloc((size * size + 1) * sizeof(int***));
	if (!grid->board)
		some_error("Malloc error");
	for (int x = 0; x < size * size + 1; x++)
		grid->board[x] = malloc_board();
}

void	parse_input(t_grid* grid, char** argv)
{
	int i = 0;

	malloc_the_things(grid);
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_up, argv, i + x);
	i += size;
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_down, argv, i + x);
	i += size;
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_left, argv, i + x);
	i += size;	
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_right, argv, i + x);
	grid->iter = 0;
	grid->iter_count = 0;
}