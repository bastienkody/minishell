/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_predicate2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:58:44 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/15 10:46:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_token_operator(t_token *token)
{
	return (is_token_logical_operator(token) || is_token_pipe(token));
}

bool	is_token_ambiguous_word(t_token *token)
{
	return (token->type == ambigous_word);
}

bool	is_token_error(t_token *token)
{
	return (token->type == error);
}
