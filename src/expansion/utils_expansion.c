/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:30:08 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 16:30:09 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_c_s_quote(char c)
{
	return (c == '\'');
}

int	is_c_d_quote(char c)
{
	return (c == '\"');
}

int	is_c_dollar(char c)
{
	return (c == '$');
}
