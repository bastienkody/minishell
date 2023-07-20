#include "../../inc/minishell.h"

void	err_msg(char *str, char *err)
{
	ft_fprintf(2, "minishell: %s: %s\n", str, err);
}

void	err_builtin(char *builtin, char *arg, char *err)
{
	ft_fprintf(2, "minishell: %s: `%s': %s\n", builtin, arg, err);
}
