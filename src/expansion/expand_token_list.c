/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/23 14:25:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_token_empty_word(t_token *token)
{
	return (token->type == word && is_str_blank(token->data));
}

// static void	rearange_word(t_llist **token_list)
// {
// 	t_llist	*current;
// 	t_token	*current_token;

// 	current = *token_list;
// 	while (current != NULL)
// 	{
// 		current_token = llst_token_get(current);
// 		if (current_token->type == quoted_word)
// 			current_token->type = word;
// 		current = current->next;
// 	}
// }

// t_state	expand_token_list(t_llist **token_list, t_minishell *minishell)
// {
// 	char **const	envp = minishell->envp;
// 	const int		last_status = minishell->status;

// 	if (!llstreplace(token_list,
// 			llst_expand_dollar(*token_list, envp, last_status), token_free))
// 		return (EXIT);
// 	llstremove_if(token_list, (void *)is_token_empty_word, (void *)token_free);
// 	if (llstsize(*token_list) == 0)
// 		return (CONTINUE);
// 	if (!llstreplace(token_list, llst_rearange_dollar(*token_list), token_free))
// 		return (EXIT);
// 	llstiter(*token_list, (void *)token_print);
// 	rearange_word(token_list);
// 	if (!llstreplace(token_list, llst_expand_wildcard(*token_list), token_free))
// 		return (EXIT);
// 	// if (!llstreplace(token_list, llst_remove_quote(*token_list), token_free))
// 	// 	return (EXIT);
// 	return (OK);
// }

t_state	expand_token_list(t_llist **token_list, t_minishell *minishell)
{
	char **const	envp = minishell->envp;
	const int		last_status = minishell->status;

	if (!llstreplace(token_list,
			llst_expand_dollar(*token_list, envp, last_status), token_free))
		return (EXIT);
	llstremove_if(token_list, (void *)is_token_empty_word, (void *)token_free);
	if (llstsize(*token_list) == 0)
		return (CONTINUE);
	if (!llstreplace(token_list, llst_rearange_dollar(*token_list), token_free))
		return (EXIT);
	if (llstfind_if(*token_list, (void *)is_token_ambiguous_word))
		return (CONTINUE);
	if (!llstreplace(token_list, llst_remove_quote(*token_list), token_free))
		return (EXIT);
	return (OK);
}

/*
1 -> expandre sans retirer les guillemets
2 -> si une donnee est vide alors quitter la commande courante
3 -> creer plusieurs noeud si expansion le permet
4 -> verifier que la phase precedente n'a pas generer des redirections ambigues
5 -> retirer les guillemets qui doivent etre retire
*/
