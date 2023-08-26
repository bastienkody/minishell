/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_predicate1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:58:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 16:41:52 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_token_ambiguous_word(t_token *token)
{
	return (token->type == ambiguous_word);
}

bool	is_token_error(t_token *token)
{
	return (token->type == error);
}

bool	is_token_opening_parenthesis(t_token *token)
{
	return (token->type == opening_parenthesis);
}

bool	is_token_closing_parenthesis(t_token *token)
{
	return (token->type == closing_parenthesis);
}

bool	is_token_logical_operator(t_token *token)
{
	return (token->type == and || token->type == or);
}
