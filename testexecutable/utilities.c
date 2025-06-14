#include "sudoku.h"

void	some_error(char* msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

static void	print_bot_clues(t_grid* grid)
{
	printf("x | ");
	for (int i = 0; i < size; i++)
		printf("%X ", grid->sky_down[i]);
	printf("| x\n");
}

static void	print_top_clues(t_grid* grid)
{
	printf("x | ");
	for (int i = 0; i < size; i++)
		printf("%X ", grid->sky_up[i]);
	printf("| x\n");
}

void	print_board(t_grid* grid, int*** board)
{
	int x = 0; int y = 0;

	puts("\n");
	print_top_clues(grid);
	for (int i = 0; i < size; i++)
		printf("---");
	printf("\n%X | ", grid->sky_left[x]);
	while (x < size)
	{
		while (y < size)
		{
			printf("%X ", board[x][y][0]);
			y++;
			if (y == size && x < size - 1)
			{
				printf("| %X\n%X | ", grid->sky_right[x], grid->sky_left[x + 1]);
			}
		}
		x++;
		y = 0;
	}
	printf("| %X", grid->sky_right[x - 1]);
	printf("\n");
	for (int i = 0; i < size; i++)
		printf("---");
	printf("\n");
	print_bot_clues(grid);
	puts("\n");
}

void	piscine_output(int*** board)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (y + 1 == size)
				printf("%X", board[x][y][0]);
			else
				printf("%X ", board[x][y][0]);
		}
		printf("\n");
	}
}

void	print_everything(int*** board)
{
	printf("\n");
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			for (int z = 0; z < size + 1; z++)
				printf("%X", board[x][y][z]);
			printf(" | ");
		}
		printf("\n");
	}
	printf("\n");
}

void	update_progress(t_grid* grid, int*** board)
{
	grid->iter_count++;
	grid->iter = 0;
	printf("Iterations: %lu\n", (long) (grid->iter_count * ITER_COUNT + grid->iter));
	print_board(grid, board);
	// print_everything(board);
}

void	print_single_line(int** line)
{
	for (int i = 0; i < size; i++)
		printf("%X", line[i][0]);
	printf("\n");
	for (int y = 0; y < size; y++)
	{
		for (int z = 0; z <= size; z++)
			printf("%X", line[y][z]);
		printf(" | ");
	}
	printf("\n\n");
}

static int	ft_getamount(const char *s, char c)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (*s == c && c != '\0')
		s++;
	if (s[i])
		amount++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			amount++;
		i++;
	}
	return (amount);
}

static void	ft_free(char **s2)
{
	int	x;

	x = 0;
	while (s2[x])
	{
		free(s2[x]);
		x++;
	}
	free(s2);
}

static char	**ft_crearray(char **s2, const char *s, char c, int len)
{
	int	x;

	x = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			return (s2);
		if (strchr(s, c) == NULL)
		{
			s2[x] = strdup(s);
			if (!s2[x])
				return (ft_free(s2), NULL);
			return (s2);
		}
		len = (strchr(s, c)) - s;
		s2[x] = malloc((len + 1) * sizeof(char));
		if (!s2[x])
			return (ft_free(s2), NULL);
		strlcpy(s2[x], s, len + 1);
		s += len;
		x++;
	}
	return (s2);
}

char	**ft_split(const char *s, char c)
{
	char	**out;
	int		amount;
	int		len;

	if (!s)
		return (NULL);
	len = 0;
	amount = ft_getamount(s, c);
	out = malloc((amount + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	if (amount == 0)
		return (*out = NULL, out);
	out = ft_crearray(out, s, c, len);
	if (!out)
		return (NULL);
	out[amount] = NULL;
	return (out);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = strlen(s1);
	s3 = malloc((i + strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	strcpy(s3, (char *)s1);
	strcpy(&s3[i], (char *)s2);
	return (s3);
}
