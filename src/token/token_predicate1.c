/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_predicate1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:58:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 10:00:40 by aguyon           ###   ########.fr       */
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
