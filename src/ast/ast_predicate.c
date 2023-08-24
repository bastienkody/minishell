/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_predicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:04:13 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 14:46:00 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_node_opening_parenthesis(t_token *token)
{
	return (is_node_equal(token, opening_parenthesis));
}

bool	is_node_closing_parenthesis(t_token *token)
{
	return (is_node_equal(token, closing_parenthesis));
}

bool	is_node_logical_operator(t_token *token)
{
	return (is_node_inside(token, (t_type[]){or, and}, 2));
}

bool	is_node_pipe(t_token *token)
{
	return (is_node_equal(token, ppipe));
}

bool	is_node_word(t_token *token)
{
	return (is_node_equal(token, word));
}
