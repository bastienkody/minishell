#include "../../inc/minishell.h"

void	err_msg(char *str, char *err)
{
	ft_fprintf(2, "minishell: %s: %s\n", str, err);
}
