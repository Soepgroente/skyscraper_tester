#include "rush01checker.h"

int size;

static int	skyscrape_top(const std::vector<std::vector<int>>& board, const std::vector<int>& clues)
{
	int count;
	int vision;

	for (int x = 0; x < clues.size(); x++)
	{
		count = 0;
		vision = 0;
		for (int y = 0; y < clues.size(); y++)
		{
			if (board[y][x] > vision)
			{
				count++;
				vision = board[y][x];
			}
		}
		if (count != clues[x])
			return (x);
	}
	return (0);
}

static int	skyscrape_bottom(const std::vector<std::vector<int>>& board, const std::vector<int>& clues)
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
		if (count != clues[x])
			return (x);
	}
	return (0);
}

static int	skyscrape_left(const std::vector<std::vector<int>>& board, const std::vector<int>& clues)
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
		if (count != clues[x])
			return (x);
	}
	return (0);
}

static int	skyscrape_right(const std::vector<std::vector<int>>& board, const std::vector<int>& clues)
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
		if (count != clues[x])
			return (x);
	}
	return (0);
}

static int	duplicateInCol(const std::vector<std::vector<int>>& board, int col, int num)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (board[i][col] == num)
			count++;
	}
	if (count > 1)
	{
		return (true);
	}
	return (false);
}

static int	duplicateInRow(const std::vector<std::vector<int>>& board, int row, int num)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (board[row][i] == num)
			count++;
	}
	if (count > 1)
	{
		return (true);
	}
	return (false);
}

static int	check_columns(const std::vector<std::vector<int>>& board)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (duplicateInCol(board, y, board[x][y]) == true)
				return (y);
		}
	}
	return (0);
}

static int	check_rows(const std::vector<std::vector<int>>& board)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (board[x][y] > size || duplicateInRow(board, x, board[x][y]) == true)
				return (x);
		}
	}
	return (0);
}

std::string	checkSolution(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& clues)
{
	int	ret;

	size = clues[0].size();
	ret = check_rows(board);
	if (ret != 0)
		return (std::string("Error in row: " + std::to_string(ret)));
	ret = check_columns(board);
	if (ret != 0)
		return (std::string("Error in column: " + std::to_string(ret)));
	ret = skyscrape_top(board, clues[0]);
	if (ret != 0)
		return (std::string("Error from top clue: " + std::to_string(ret)));
	ret = skyscrape_bottom(board, clues[1]);
	if (ret != 0)
		return (std::string("Error from bottom clue: " + std::to_string(ret)));
	ret = skyscrape_left(board, clues[2]);
	if (ret != 0)
		return (std::string("Error from left clue: " + std::to_string(ret)));
	ret = skyscrape_right(board, clues[3]);
	if (ret != 0)
		return (std::string("Error from right clue: " + std::to_string(ret)));
	return ("");
}
