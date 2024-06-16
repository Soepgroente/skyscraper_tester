#include "rush01checker.h"

static bool	skyscrape_top()
{
	int count;
	int vision;

	for (int x = 0; x < size; x++)
	{
		count = 0;
		vision = 0;
		for (int y = 0; y < size; y++)
		{
			if (board[y][x] > vision)
			{
				count++;
				vision = board[y][x];
			}
		}
		if (count != top_clues[x])
			return (false);
	}
	return (true);
}

static bool	skyscrape_bottom()
{
	int count;
	int vision;

	for (int x = 0; x < size; x++)
	{
		count = 0;
		vision = 0;
		for (int y = size - 1; y >= 0; y--)
		{
			if (board[y][x] > vision)
			{
				count++;
				vision = board[y][x];
			}
		}
		if (count != bottom_clues[x])
			return (false);
	}
	return (true);
}

static bool	skyscrape_left()
{
	int count;
	int vision;

	for (int x = 0; x < size; x++)
	{
		count = 0;
		vision = 0;
		for (int y = 0; y < size; y++)
		{
			if (board[x][y] > vision)
			{
				count++;
				vision = board[x][y];
			}
		}
		if (count != left_clues[x])
			return (false);
	}
	return (true);
}

static bool	skyscrape_right()
{
	int count;
	int vision;

	for (int x = 0; x < size; x++)
	{
		count = 0;
		vision = 0;
		for (int y = size - 1; y >= 0; y--)
		{
			if (board[x][y] > vision)
			{
				count++;
				vision = board[x][y];
			}
		}
		if (count != right_clues[x])
			return (false);
	}
	return (true);
}

static bool	duplicateInCol(int col, int num)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (board[i][col] == num)
			count++;
	}
	if (count > 1)
	{
		printf("col: %d, count: %d\n", col, count);
		return (true);
	}
	return (false);
}

static bool	duplicateInRow(int row, int num)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (board[row][i] == num)
			count++;
	}
	if (count > 1)
	{
		printf("row: %d, count: %d\n", row, count);
		return (true);
	}
	return (false);
}

static bool	check_columns()
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (duplicateInCol(y, board[x][y]) == true)
				return (false);
		}
	}
	return (true);
}

static bool	check_rows()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (board[x][y] > size)
				return (false);
			if (duplicateInRow(x, board[x][y]) == true)
				return (false);
		}
	}
	return (true);
}

int	checkBoardValidity()
{
	if (check_rows() == false)
		return (1);
	if (check_columns() == false)
		return (2);
	if (skyscrape_top() == false)
		return (3);
	if (skyscrape_bottom() == false)
		return (4);
	if (skyscrape_left() == false)
		return (5);
	if (skyscrape_right() == false)
		return (6);
	return (0);
}
