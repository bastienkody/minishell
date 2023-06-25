/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:06:17 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 19:06:19 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stddef.h>

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!ptr)
		return (malloc(size));
	new = malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, ft_strlen(ptr));
	free(ptr);
	return (new);
}

/*int	main(void)
{
	char	*str;
	char	*new_str;

	str = ft_strdup("salut");
	ft_fprintf(1, "%s\n", str);
	new_str = ft_realloc(str, 10 * sizeof(char));
	new_str[5] = ' ';
	new_str[6] = 't';
	new_str[7] = 'o';
	new_str[8] = 'i';
	new_str[9] = '\0';
	ft_fprintf(1, "%s\n", new_str);
	//free(str);
	free(new_str);
}*/
