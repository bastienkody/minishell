/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:23:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/22 20:28:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*strfind_if(const char *str, int (*f)(int))
{
	while (*str != '\0' && !f(*str))
		str++;
	return ((char *)str);
}

char	*strfind(const char *str, int c)
{
	while (*str != '\0' && *str != c)
		str++;
	return ((char *)str);
}

char	*strfind_not(const char *str, int c)
{
	while (*str != '\0' && *str == c)
		str++;
	return ((char *)str);
}
