/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_predicate3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:54:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 14:50:21 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_str_redirection(const char *str)
{
	return (is_str_great(str) || is_str_dgreat(str) || is_str_less(str));
}
