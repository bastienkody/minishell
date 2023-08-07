/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_predicate2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:58:44 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 16:03:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_token_operator(t_token *token)
{
	return (is_token_logical_operator(token) || is_token_pipe(token));
}

int	is_token_error(t_token *token)
{
	return (token->type == error);
}
