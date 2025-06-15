#pragma once

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/wait.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET	"\e[m"

void	exitError(std::string msg);
pid_t	forkProcess();
void	addInvalidInputs(std::vector<std::string>& args);
void	addValid4x4s(std::vector<std::string>& args);
void	addBonus(std::vector<std::string>& args);
void	test(const std::vector<std::string>& args, bool solvable);

std::string	checkSolution(const std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& clues);
void	printBoard(const std::vector<std::vector<int>>& board);