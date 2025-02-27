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

static void parseRow(const std::string& buffer, std::vector<int>& row)
{	
	for (size_t i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++)
	{
		if (buffer[i] == ' ')
			continue ;
		if (buffer[i] < '1' || buffer[i] > '9')
		{	
			row.clear();
			return ;
		}
		else
		{
			std::cout << buffer[i] << " " << std::endl;
			row.push_back(buffer[i] - '0');
		}
	}
	std::cout << std::endl;
}

static std::vector<std::vector<int>>	parseBoard(const std::string& buffer)
{
	std::vector<std::vector<int>> board;

	std::cout << "buffer:\n" << buffer << std::endl << std::endl;	
	for (size_t x = 0; buffer[x] != '\0'; x++)
	{
		board.push_back(std::vector<int>());
		parseRow(&buffer[x], board[x]);
		while (buffer[x] != '\n' && buffer[x] != '\0')
			x++;
	}
	return (board);
}

static std::vector<std::vector<int>>	parseClues(const std::string& args)
{
	std::vector<std::vector<int>> clues;
	std::stringstream stream(args);
	
	clues.resize(4);
	for (size_t x = 0; x < 4; x++)
	{
		for (size_t y = 0; y < args.size() / 4; y++)
		{
			stream >> clues[x][y];
		}
	}
	return (clues);
}

static void	validateResult(const std::string& buffer, const std::string& args, bool solvable)
{
	if (solvable == false)
	{
		if (buffer.substr(0, 6) == "Error\n")
			std::cout << GREEN << "OK" << RESET << std::endl;
		else
		{
			std::cout << RED << "KO" << RESET << std::endl << "Input: " << args << std::endl;
			std::cout << "Expected: Error" << std::endl << "Received: " << buffer << std::endl;
		}
		return ;
	}

	std::vector<std::vector<int>> board = parseBoard(buffer);
	std::vector<std::vector<int>> clues = parseClues(args);

	if (buffer == "Error\n")
	{
		std::cout << RED << "KO" << RESET << std::endl << "Input: \"" << args << "\"" << std::endl;
		std::cout << "Possible solution: " << std::endl;
		pid_t pid = forkProcess();
		if (pid == 0)
		{
			char*	argv[] = {strdup("./solver"), strdup(args.c_str()), NULL};

			if (execv("./solver", argv) == -1)
				exitError("Failed to execute solver");
		}
		waitpid(pid, NULL, 0);
	}
	for (size_t x = 0; x < board.size(); x++)
	{
		if (board[x].size() == 0 || board[x].size() != board[0].size())
		{
			std::cout << RED << "KO" << RESET << std::endl << "Input: " << args << std::endl;
			std::cout << "Output is not a valid board, received:" << std::endl << buffer << std::endl;
			return ;
		}
	}
	std::string returnVal = checkSolution(board, clues);
	if (returnVal == "")
		std::cout << GREEN << "OK" << RESET << std::endl;
	else
	{
		std::cout << RED << "KO" << RESET << std::endl << "Input: " << args << std::endl;
		std::cout << returnVal << std::endl;
	}
}

#define BUFFERSIZE 1024

void	test(const std::vector<std::string>& args, bool solvable)
{
	std::string output;
	char buffer[BUFFERSIZE];
	int	pipeFd[2];
	int exitStatus = 0;
	ssize_t readBytes = 1;
	
	for (size_t i = 0; i < args.size(); i++)
	{
		createPipe(pipeFd);
		char*	argv[] = {strdup("./rush-01"), strdup(args[i].c_str()), NULL};
		if (!argv[0] || !argv[1])
			exitError("Failed to strdup");

		pid_t	pid = forkProcess();
		if (pid == 0)
		{
			close(pipeFd[0]);
			duplicate_fd(pipeFd[1], STDOUT_FILENO);
			if (execv("./rush-01", argv) == -1)
				exitError("Failed to execute rush-01");
		}
		close(pipeFd[1]);
		waitpid(pid, &exitStatus, 0);
		if (WEXITSTATUS(exitStatus) == 55)
			exitError("... exiting");
		while (readBytes > 0)
		{
			readBytes = read(pipeFd[0], &buffer[0], BUFFERSIZE);
			if (readBytes == -1)
				exitError("Failed to read from pipe");
			buffer[readBytes] = '\0';
			output += buffer;
		}
		std::cout << "buffer before:\n" << output << std::endl << std::endl;	
		validateResult(output, args[i], solvable);
		close(pipeFd[0]);
	}
}