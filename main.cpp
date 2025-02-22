/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/25 11:57:41 by vvan-der      #+#    #+#                 */
/*   Updated: 2025/02/22 19:09:40 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	addInvalidInputs(invalidArgs);
	addValid4x4s(valid4x4s);
	std::cout << "Testing invalid inputs" << std::endl;
	test(invalidArgs, false);
	std::cout << "Testing valid 4x4s" << std::endl;
	test(valid4x4s, true);
	if (bonus.empty() == false)
	{
		std::cout << "Testing bonus" << std::endl;
		test(bonus, true);
	}
	return (0);
}
