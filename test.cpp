#include "rush01checker.h"

static void	createPipe(int (&fd)[2])
{
	if (pipe(fd) == -1)
		exitError("Failed to pipe");
}

static void	duplicate_fd(int oldFd, int newFd)
{
	if (dup2(oldFd, newFd) == -1)
		exitError("Failed to dup2");
	close(oldFd);
}

static bool	verifyBuffer(const std::string& buffer)
{
	for (size_t i = 0; i < buffer.size(); i++)
	{
		if (i % 2 == 1)
		{
			if (buffer[i] != ' ' && buffer[i] != '\n')
			{
				std::cout << "place: " << i << "\ncharacter: " << buffer[i] << std::endl;
				puts("Invalid character");
				return (false);
			}
		}
		else if (!(buffer[i] >= '1' && buffer[i] <= '9'))
		{
			std::cout << i << std::endl;
			puts("Invalid number");
			return (false);
		}
	}
	return (true);
}

static std::vector<std::vector<int>>	parseBoard(const std::string& buffer)
{
	std::vector<std::vector<int>>	board;

	if (verifyBuffer(buffer) == false)
		return (board);

	std::istringstream				stream(buffer);
	std::string						line;

	while (std::getline(stream, line))
	{
		std::istringstream	lineStream(line);
		std::vector<int>	row;
		int number;

		while (lineStream >> number)
		{
			row.push_back(number);
		}
		board.push_back(row);
	}
	return (board);
}

static std::vector<std::vector<int>>	parseClues(const std::string& args)
{
	std::vector<std::vector<int>>	clues;
	std::string						arg = args;
	arg.erase(std::remove(arg.begin(), arg.end(), ' '), arg.end());

	for (size_t x = 0; x < 4; x++)
	{
		clues.push_back(std::vector<int>());
		for (size_t y = 0; y < arg.size() / 4; y++)
		{
			clues[x].push_back(std::stoi(arg.substr(x * arg.size() / 4 + y, 1)));
		}
	}
	return (clues);
}

static void	validateResult(const std::string& buffer, const std::string& args, bool solvable)
{
	if (solvable == false)
	{
		if (buffer.substr(0, 6) == "Error\n")
			std::cout << GREEN << "[OK] " << RESET;
		else
		{
			std::cout << RED << "[KO]" << RESET << std::endl << "Input: " << args << std::endl;
			std::cout << "Expected: Error" << std::endl << "Received: " << buffer << std::endl;
		}
		return ;
	}

	std::vector<std::vector<int>> board = parseBoard(buffer);
	std::vector<std::vector<int>> clues = parseClues(args);

	if (buffer == "Error\n" || board.size() == 0)
	{
		std::cout << RED << "[KO]" << RESET << std::endl << "Input: \"" << args << "\"" << std::endl;
		std::cout << "Possible solution: " << std::endl;
		pid_t pid = forkProcess();
		if (pid == 0)
		{
			char*	argv[] = {strdup("./solver"), strdup(args.c_str()), NULL};

			if (execv("./solver", argv) == -1)
				exitError("Failed to execute solver");
		}
		waitpid(pid, NULL, 0);
		return ;
	}
	for (size_t x = 0; x < board.size(); x++)
	{
		if (board[x].size() == 0 || board[x].size() != board[0].size())
		{
			std::cout << RED << "[KO]" << RESET << std::endl << "Input: " << args << std::endl;
			std::cout << "Output is not a valid board, received:" << std::endl << buffer << std::endl;
			return ;
		}
	}
	std::string returnVal = checkSolution(board, clues);
	if (returnVal == "")
		std::cout << GREEN << "[OK] " << RESET;
	else
	{
		std::cout << RED << "[KO]" << RESET << std::endl << "Input: " << args << std::endl;
		std::cout << returnVal << std::endl;
		printBoard(board);
		std::exit(EXIT_FAILURE);
	}
}

#define BUFFERSIZE 1024

void	test(const std::vector<std::string>& args, bool solvable)
{
	std::string output;
	char	buffer[BUFFERSIZE];
	int		stdoutPipe[2];
	int		stderrPipe[2];
	int		exitStatus = 0;
	ssize_t	readBytes = 1;
	
	for (size_t i = 0; i < args.size(); i++)
	{
		if (i != 0 && i % 20 == 0)
			std::cout << std::endl;
		fflush(stdout);
		createPipe(stdoutPipe);
		createPipe(stderrPipe);
		char*	argv[] = {strdup("./rush-01"), strdup(args[i].c_str()), NULL};
		if (!argv[0] || !argv[1])
			exitError("Failed to strdup");

		pid_t	pid = forkProcess();
		if (pid == 0)
		{
			close(stdoutPipe[0]);
			close(stderrPipe[0]);
			duplicate_fd(stdoutPipe[1], STDOUT_FILENO);
			duplicate_fd(stderrPipe[1], STDERR_FILENO);
			if (execv("./rush-01", argv) == -1)
				exitError("Failed to execute rush-01");
		}
		close(stdoutPipe[1]);
		close(stderrPipe[1]);
		waitpid(pid, &exitStatus, 0);
		if (WEXITSTATUS(exitStatus) == 55)
			exitError("... exiting");

		readBytes = read(stdoutPipe[0], &buffer[0], BUFFERSIZE);
		if (readBytes == -1)
			exitError("Failed to read from pipe");
		buffer[readBytes] = '\0';
		output += buffer;
		close(stdoutPipe[0]);

		readBytes = read(stderrPipe[0], &buffer[0], BUFFERSIZE);
		if (readBytes == -1)
			exitError("Failed to read from pipe");
		buffer[readBytes] = '\0';
		output += buffer;
		close(stderrPipe[0]);

		validateResult(output, args[i], solvable);
		output.clear();
	}
}