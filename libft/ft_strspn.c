/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:03:35 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 15:43:46 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_strchr(accept, s[i]))
		i++;
	return (i);
}
