#include "rush01checker.h"

pid_t	forkProcess()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exitError("Forking failed");
	return (pid);
}