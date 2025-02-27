#include "rush01checker.h"

void	exitError(std::string msg)
{
	std::cerr << msg << std::endl;
	exit(55);
}

void	addInvalidInputs(std::vector<std::string>& args)
{
	std::ifstream	file("invalidInput.txt");

	if (file.is_open() == false)
		exitError("Failed to open file invalidInput.txt");
	while (file.eof() == false)
	{
		std::string	line;

		std::getline(file, line);
		args.push_back(line);
	}
	file.close();
}

void	addValid4x4s(std::vector<std::string>& args)
{
	std::ifstream	file("4x4s.txt");

	if (file.is_open() == false)
		exitError("Failed to open file 4x4s.txt");
	while (file.eof() == false)
	{
		std::string	line;

		std::getline(file, line);
		args.push_back(line);
	}
	file.close();
}

void	addBonus(std::vector<std::string>& args)
{
	std::ifstream	file("bonusInput.txt");

	if (file.is_open() == false)
		exitError("Failed to open file bonusInput.txt");
	while (file.eof() == false)
	{
		std::string	line;

		std::getline(file, line);
		args.push_back(line);
	}
	file.close();
}