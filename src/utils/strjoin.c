/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:00:17 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/16 18:00:20 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

/*	join 2 strings, free s1	*/
char	*strjoin(const char *s1, const char *s2)
{
	char	*ret;

	if (!s1 || !s2)
		return (free((void *)s1), NULL);
	ret = ft_strjoin(s1, s2);
	free((void *)s1);
	return (ret);
}

/*	join 3 strings, free none	*/
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	return (free((void *)tmp), ret);
}

/*	append a signle char to the end of str
	str==NULL -> returns "c"
	str is malloc -> init str is freed
	str is stacked -> error	*/
char	*str_one_char_join(char *str, char c)
{
	int	str_len;

	if (!str)
	{
		str_len = 0;
		str = malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
	}
	else
	{
		str_len = ft_strlen(str);
		str = ft_realloc(str, (str_len + 1 + 1) * sizeof(char));
		if (!str)
			return (NULL);
	}
	str[str_len + 1] = '\0';
	str[str_len] = c;
	return (str);
}

/*int	main(void)
{
	//char	*ret = ft_strdup("salut");
	char	*ret = NULL;
	char	c = 'y';

	ft_fprintf(1, "%s\n", ret);
	ret = str_one_char_join(ret, c);
	ft_fprintf(1, "%s\n", ret);
	free(ret);
}*/