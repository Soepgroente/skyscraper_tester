#include "sudoku.h"

static bool	skyscrape_leftright(t_grid* grid, int x)
{
	if (skyscraper_vision(grid->row, grid->sky_left[x], grid->sky_right[x]) == true)
		return (true);
	return (false);
}

static bool	skyscrape_updown(t_grid* grid, int y)
{
	if (skyscraper_vision(grid->col, grid->sky_up[y], grid->sky_down[y]) == true)
		return (true);
	return (false);
}

static bool	check_row(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < size)
	{
		if (board[x][i][0] == try)
			return (false);
		for (int pos = 0; pos <= size; pos++)
		{
			grid->row[i][pos] = board[x][i][pos];
			grid->rev_row[i][pos] = board[x][size - 1 - i][pos];
		}
		i++;
	}
	grid->row[y][0] = try;
	for (int i = 1; i <= size; i++)
		grid->row[y][i] = 0;
	return (true);
}

static bool	check_column(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < size)
	{
		if (board[i][y][0] == try)
			return (false);
		for (int pos = 0; pos <= size; pos++)
		{
			grid->col[i][pos] = board[i][y][pos];
			grid->rev_col[i][pos] = board[size - 1 - i][y][pos];
		}
		i++;
	}
	grid->col[x][0] = try;
	for (int i = 1; i <= size; i++)
		grid->col[x][i] = 0;
	return (true);
}

bool	check_if_possible(t_grid* grid, int*** board, int x, int y, int try)
{
	if (check_row(grid, board, x, y, try) == true && \
		check_column(grid, board, x, y, try) == true && \
		skyscrape_leftright(grid, x) == true && \
		skyscrape_updown(grid, y) == true)
		return (true);
	return (false);
}