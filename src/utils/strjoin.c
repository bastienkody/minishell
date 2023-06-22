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

char	*strjoin(const char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free((void *)s1);
	return (ret);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	return (free((void *)tmp), ret);
}

/*int	main(void)
{
	char	*str;

	str = ft_strjoin3_bis("salut ", "a ", "tous!");
	write(1, str, ft_strlen(str));
	free(str);
}*/
