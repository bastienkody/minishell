/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:03 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/22 14:16:41 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_str_or(const char *str)
{
	return (ft_strcmp(str, "||") == 0);
}

int	is_str_and(const char *str)
{
	return (ft_strcmp(str, "&&") == 0);
}

int	is_str_pipe(const char *str)
{
	return (ft_strcmp(str, "|") == 0);
}

int	is_str_great(const char *str)
{
	return (ft_strcmp(str, ">") == 0);
}

int	is_str_less(const char *str)
{
	return (ft_strcmp(str, "<") == 0);
}
