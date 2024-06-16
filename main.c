/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 11:57:41 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/16 19:39:29 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rush01checker.h"

int size;
int	board[9][9];
int	top_clues[9];
int	bottom_clues[9];
int	left_clues[9];
int	right_clues[9];

static bool	ft_isdigit(char c)
{
	if (c >= '1' && c <= '9')
		return (true);
	return (false);
}

static void	exit_error(char* msg)
{
	puts(msg);
	exit(EXIT_FAILURE);
}

static void	insert_line(char* buffer, int y)
{
	int i = 0;

	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		if ((ft_isdigit(buffer[i]) == false && buffer[i] != '\n' && buffer[i] != '\0') || ft_isdigit(buffer[i + 1]) == true)
			exit_error("invalid number in input");
		board[y][i / 2] = buffer[i] - '0';
		i++;
		if (buffer[i] == ' ')
			i++;
	}
}

static void	read_output()
{
	char	buffer[100];

	for (int i = 0; i < size; i++)
	{
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			exit_error("line parsing failed");
		}
		insert_line(buffer, i);
	}
}

static void	parse_row(char* clues, int array[9])
{
	for (int i = 0; i < size; i++)
		array[i] = clues[i * 2] - '0';
}

static void	parse_clues(char* clues)
{
	parse_row(clues, top_clues);
	parse_row(&clues[size * 2], bottom_clues);
	parse_row(&clues[size * 4], left_clues);
	parse_row(&clues[size * 6], right_clues);	
}

/*	Add one (last argument has no space following it) and divide by 8 (one space per argument, 4 rows of clues) */

static void	check_input(char* input)
{
	for (int i = 0; input[i]; i++)
	{
		if (i % 2 == 0 && ft_isdigit(input[i]) == false)
			exit_error("invalid input (1)");
		else if (i % 2 == 1 && input[i] != ' ')
			exit_error("invalid input (2)");
	}
	size = strlen(input) + 1;
	if (size % 8 != 0)
		exit_error("invalid input (3)");
	size /= 8;
	if (size > 9 || size < 4)
		exit_error("invalid size");
}

int	main(int argc, char** argv)
{
	int	validity;

	if (argc != 2)
		return (perror("incorrect number of arguments"), 1);
	check_input(argv[1]);
	parse_clues(argv[1]);
	read_output();
	validity = checkBoardValidity();
	if (validity == 0)
		puts("Correct!");
	else
	{
		puts("Incorrect solution");
		printf("error code: %d\n", validity);
	}
	print_board(top_clues, bottom_clues, left_clues, right_clues);
}
