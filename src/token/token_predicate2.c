/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_predicate2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:45:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 15:45:34 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_token_pipe(t_token *token)
{
	return (token->type == ppipe);
}

bool	is_token_word(t_token *token)
{
	return (token->type == word);
}

bool	is_token_redirection(t_token *token)
{
	const t_type	type = token->type;

	return (type == less || type == dless || type == great || type == dgreat);
}
