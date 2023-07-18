/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_leafs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:53:16 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 19:11:15 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ast	*new_leaf(t_token *token)
{
	char *const	text = ft_strdup(token->text);

	if (text == NULL)
		return (NULL);
	return (new_ast(token->type, text, NULL));
}

t_llist	*token_to_leaf(t_llist	*token_list)
{
	return (llstmap(token_list, (void *(*)(void *))new_leaf, free));
}
