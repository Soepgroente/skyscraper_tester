#include "sudoku.h"

t_grid* global_grid;

static void	delete_rowcol(int*** board, int x, int y, int num)
{
	for (int i = 0; i < size; i++)
		board[x][i][num] = 0;
	for (int i = 0; i < size; i++)
		board[i][y][num] = 0;
}

/*	Remove all digits from the options that are already placed 
	somewhere in the row or column */

void	clean_up(int*** board)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (board[x][y][0] != 0)
			{
				delete_rowcol(board, x, y, board[x][y][0]);
				for (int z = 1; z <= size; z++)
					board[x][y][z] = 0;
			}
		}
	}
}

/*	Removes any digits that are too high for the skyscraper clue to remain valid	*/

void	remove_options(t_grid* grid, int*** board)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (board[x][y][0] == 0)
			{
				for (int z = size + 2 - grid->sky_left[x] + y; z <= size; z++)
					board[x][y][z] = 0;
				for (int z = size + 1 - grid->sky_right[x] + size - y; z <= size; z++)
					board[x][y][z] = 0;
				for (int z = size + 2 - grid->sky_up[y] + x; z <= size; z++)
					board[x][y][z] = 0;
				for (int z = size + 1 - grid->sky_down[y] + size - x; z <= size; z++)
					board[x][y][z] = 0;
			}
		}
	}
}

static bool	check_row_presence(int*** board, int x, int try)
{
	for (int i = 0; i < size; i++)
		if (board[x][i][0] == try)
			return (true);
	return (false);
}

/*	Find any digits that can only be placed in one place in a row	*/

int	place_single_row(int*** board)
{
	int check = -1;
	int changes = 0;

	for (int try = 1; try <= size; try++)
	{
		for (int x = 0; x < size; x++)
		{
			if (check_row_presence(board, x, try) == false)
			{
				for (int y = 0; y < size; y++)
				{
					if (check == -1 && board[x][y][try] != 0)
						check = y;
					else if (board[x][y][try] != 0)
					{
						check = 0;
						break ;
					}
				}
				if (check == -1)
					return (-1);
				if (check > 0)
				{
					if (check_if_possible(global_grid, board, x, check, try) == true)
					{
						board[x][check][0] = try;
						clean_up(board);
						changes++;
					}
					else
						return (-1);	
				}
			}
			check = -1;
		}
	}
	return (changes);
}

static bool	check_col_presence(int*** board, int y, int try)
{
	for (int i = 0; i < size; i++)
		if (board[i][y][0] == try)
			return (true);
	return (false);
}

/*	Find any digits that can only be placed in one place in a column	*/

int	place_single_col(int*** board)
{
	int check = -1;
	int changes = 0;

	for (int try = 1; try <= size; try++)
	{
		for (int y = 0; y < size; y++)
		{
			if (check_col_presence(board, y, try) == false)
			{
				for (int x = 0; x < size; x++)
				{
					if (check == -1 && board[x][y][try] != 0)
						check = x;
					else if (board[x][y][try] != 0)
					{
						check = 0;
						break ;
					}
				}
				if (check == -1)
					return (-1);
				if (check > 0)
				{
					if (check_if_possible(global_grid, board, check, y, try) == true)
					{
						board[check][y][0] = try;
						clean_up(board);
						changes++;
					}
					else
						return (-1);	
				}
			}
			check = -1;
		}
	}
	return (changes);
}

/*	Find any cells that just have one option left	*/

int	place_single_cell(int*** board)
{
	int check = -1;
	int changes = 0;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (board[x][y][0] == 0)
			{
				for (int try = 1; try <= size; try++)
				{
					if (check == -1 && board[x][y][try] != 0)
						check = try;
					else if (board[x][y][try] != 0)
					{
						check = 0;
						break ;
					}
				}
				if (check == -1)
					return (-1);
				if (check > 0)
				{
					if (check_if_possible(global_grid, board, x, y, check) == true)
					{
						board[x][y][0] = check;
						clean_up(board);
						changes++;
					}
					else
						return (-1);	
				}
			}
			check = -1;
		}
	}
	return (changes);
}

bool	logic_solve(t_grid* grid, int*** board)
{
	int changes = 1;
	int check;

	global_grid = grid;
	clean_up(board);
	while (changes > 0)
	{
		changes = 0;
		check = place_single_cell(board);
		if (check == -1)
			return (false);
		changes += check;
		check = place_single_row(board);
		if (check == -1)
			return (false);
		changes += check;
		check = place_single_col(board);
		if (check == -1)
			return (false);
		changes += check;
	}
	return (true);
}
