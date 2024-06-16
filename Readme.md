To use:

Take the usual rush input and use it as input for this program. Use a pipe to send the output of their program as input to the checker.

For example:

$ARG="4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2" ./rush01 $ARG | ./rush01_checker $ARG

It will give an error if anything is wrong with some information, it will print "Correct!" and the board if all is well.