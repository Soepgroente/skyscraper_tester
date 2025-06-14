#include "rush01checker.h"

int	main(int argc, char** argv)
{
	std::vector<std::string>	invalidArgs;
	std::vector<std::string>	valid4x4s;
	std::vector<std::string>	bonus;

	if (argc > 2)
	{
		std::cerr << "Usage: \"./rush01checker\" or \"./rush01checker bonus\"" << std::endl;
		return (1);
	}
	if (argc == 2 && std::string(argv[1]) == "bonus")
	{
		addBonus(bonus);
	}
	if (std::filesystem::exists("./rush-01") == false)
	{
		std::cerr << "Error: rush-01 file not found." << std::endl;
		return (1);
	}
	addInvalidInputs(invalidArgs);
	addValid4x4s(valid4x4s);
	std::cout << "Testing invalid inputs" << std::endl;
	test(invalidArgs, false);
	std::cout << "\nTesting valid 4x4s" << std::endl;
	test(valid4x4s, true);
	if (bonus.empty() == false)
	{
		std::cout << "\nTesting bonus" << std::endl;
		test(bonus, true);
	}
	std::cout << std::endl;
	return (0);
}
