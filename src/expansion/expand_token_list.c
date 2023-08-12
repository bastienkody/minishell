/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/12 17:38:46 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_token_empty_word(t_token *token)
{
	return (token->type == word && is_str_blank(token->data));
}

int expand_token_list(t_llist **token_list, t_minishell *minishell)
{
	char **const	envp = minishell->envp;
	const int		last_status = minishell->status;

	if (!llstreplace(token_list, llst_expand_dollar(*token_list, envp, last_status), token_free))
		return (EXIT);
	llstremove_if(token_list, (void *)is_token_empty_word, (void *)token_free);
	if (llstsize(*token_list) == 0)
		return (CONTINUE);
	if (!llstreplace(token_list, llst_expand_wildcard(*token_list, envp), token_free))
		return (EXIT);
	if (!llstreplace(token_list, llst_remove_quote(*token_list), token_free))
		return (EXIT);
	return (OK);
}
