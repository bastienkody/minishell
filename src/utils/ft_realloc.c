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

/* not tested yet*/
void	*ft_realloc(void *ptr, size_t size)
{
	char	new;

	if (!ptr)
		return (malloc(size));
	new = malloc(size + (ft_strlen((char *)ptr) * sizeof(char)));
	if (!new)
		return (NULL);
	ft_strlcpy((char *)new, (char *)ptr, ft_strlen(ptr));
	free(ptr);
	return (new);
}
