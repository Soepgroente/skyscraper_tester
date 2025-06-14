********
Tester has only been tested somewhat rigorously, please remain vigilant and think for youself while using this.
Please do not fail a project just because the tester says so, verify its output first.
********

Make the tester executable by running "make" in terminal.

Execute with "./rush01checker" or "./rush01checker bonus" to include bonus testcases (5x5 up to 9x9).
The executable being tested MUST be named "rush-01" and be located in the root folder for the tester to work.
The tester will stop if a valid testcase is incorrect to display the error (It will show errors on invalid testcases not returning "Error\n" but move on with the valid tests).
The checker will check the output of the executable for validity and run the "solver" executable if it expected a valid output but got "Error\n".

All valid 4x4s are tested, a select few 5x5-9x9s are tested, feel free to add testcases to any of the 3 .txt files.

The "testexecutable" folder holds my own solver you can test with if you don't have a rush executable, simply run "make test" and it'll compile the executable into the root folder.

Feel free to report any bugs you come across so that I may fix them.