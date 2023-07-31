/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:29:06 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 15:38:40 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_token_word(t_token *token)
{
	return (token->type == word);
}

int	is_token_redirection(t_token *token)
{
	const t_type	type = token->type;

	return (type == less || type == great || type == dgreat);
}

int	is_token_here_doc(t_token *token)
{
	return (token->type == dless);
}

int	is_token_pipe(t_token *token)
{
	return (token->type == ppipe);
}

int	is_token_logical_operator(t_token *token)
{
	const t_type	type = token->type;

	return (type == and || type == or);
}

int	is_token_operator(t_token *token)
{
	return (is_token_logical_operator(token) || is_token_pipe(token));
}
