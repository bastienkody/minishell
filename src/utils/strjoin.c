#include "../../inc/minishell.h"
#include "../../libft/libft.h"

char	*strjoin(const char s1, const char s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}
