/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/09 16:18:24 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*expand_token_list(t_llist *token_list, char **envp)
{
	// llstiter(token_list, (void *)token_print);
	if (!llstreplace(&token_list, llst_expand_dollar(token_list, envp), token_free))
		return (NULL);
	if (!llstreplace(&token_list, llst_expand_wildcard(token_list, envp), token_free))
		return (NULL);
	if (!llstreplace(&token_list, llst_remove_quote(token_list), token_free))
		return (NULL);
	return (token_list);
}
