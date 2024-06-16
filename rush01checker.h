#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

extern int size;
extern int board[9][9];
extern int top_clues[9];
extern int bottom_clues[9];
extern int left_clues[9];
extern int right_clues[9];

void	print_board(int* top, int* bot, int* left, int* right);
int		checkBoardValidity();

#endif