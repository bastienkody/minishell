/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/25 13:02:23 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_token_empty_word(t_token *token)
{
	return (token->type == word && is_str_blank(token->data));
}

t_state	expand_token_list(t_llist **token_list, t_minishell *minishell)
{
	char **const	envp = minishell->envp;
	const int		last_status = minishell->status;
	t_llist			*ambiguous_node;

	if (!llstreplace(token_list,
			llst_expand_dollar(*token_list, envp, last_status), token_free))
		return (EXIT);
	llstremove_if(token_list, (void *)is_token_empty_word, (void *)token_free);
	if (llstsize(*token_list) == 1 && llst_token_get_type(*token_list) == newline)
		return (minishell->status = 0, CONTINUE);
	if (!llstreplace(token_list, llst_word_splitting(*token_list), token_free))
		return (EXIT);
	if (!llstreplace(token_list, llst_expand_wildcard(*token_list), token_free))
		return (EXIT);
	ambiguous_node = llstfind_if(*token_list, (void *)is_token_ambiguous_word);
	if (ambiguous_node != NULL)
		return (print_err_ambiguous(llst_token_get_data(ambiguous_node)), \
			minishell->status = 1, CONTINUE);
	if (!llstreplace(token_list, llst_remove_quote(*token_list), token_free))
		return (EXIT);
	return (OK);
}
