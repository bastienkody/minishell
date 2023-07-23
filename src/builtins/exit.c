#include "../../inc/minishell.h"

int	check_exit(char **args)
{
	if (args[1] && args[1][0] == '-')
		return (0);
	return (1);
}

int	exit_blt(char **args, char **envp, void *truc)
{
	(void)args;
	(void)envp;
	(void)truc;
	return (0);
}
