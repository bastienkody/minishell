/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:11:15 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/11 18:10:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_type_inside(t_type type, const t_type types[])
{
	size_t	i;

	i = 0;
	while (types[i] != (t_type)-1)
	{
		if (types[i] == type)
			return (1);
		i++;
	}
	return (0);
}