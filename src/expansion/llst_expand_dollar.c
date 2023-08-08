/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:36:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/08 17:12:46 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static int	expand_dollar_word(t_llist *node, char **envp)
// {
// 	char	*word;
// 	char	*expanded_word;
// 	t_token	*token;

// 	token = node->content;
// 	word = token->data;
// 	expanded_word = expand_dollar(word, envp);
// 	if (expanded_word == NULL)
// 		return (0);
// 	free(word);
// 	token->data = expanded_word;
// 	return (1);
// }

int	is_prev_redir_operator(t_llist *node)
{
	t_token	*prev_token;

	if (node->prev == NULL)
		return (0);
	prev_token = node->prev->content;
	return (is_str_redirection(prev_token->data) == 1);
}

// int	manage_dollar_expansion(t_llist *token_list, char **envp)
// {
// 	t_llist	*current;
// 	t_token	*current_token;

// 	current = token_list;
// 	while (current != NULL)
// 	{
// 		current_token = current->content;
// 		if (current_token->type == word && !is_prev_here_operator(current))
// 		{
// 			if (is_prev_redir_operator(current) && !check_amb_redir(current_token->data, envp))
// 				current_token->type = ambigous_word;
// 			if (!expand_dollar_word(current, envp))
// 				return (1);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

static t_llist	*get_expand_node(t_llist *node, char **envp)
{
	t_llist	*new_node;
	char	*new_data;
	t_token	*token;

	new_node = node_dup(node);
	if (new_node == NULL)
		return (NULL);
	token = new_node->content;
	new_data = expand_dollar(token->data, envp);
	if (new_data == NULL)
		return (llstdelone(new_node, (void *)token_free), NULL);
	free(token->data);
	token->data = new_data;
	return (new_node);
}

t_llist	*llst_expand_dollar(t_llist *token_list, char **envp)
{
	t_llist	*new_token_list;
	t_llist	*new_node;
	t_llist	*current;
	t_token	*current_token;

	new_token_list = NULL;
	current = token_list;
	while (current != NULL)
	{
		current_token = current->content;
		if (current_token->type == word && !is_prev_here_operator(current))
		{
			if (is_prev_redir_operator(current) && !check_amb_redir(current_token->data, envp))
				new_node = get_ambigous_node(current);
			else
				new_node = get_expand_node(current, envp);
		}
		else
			new_node = node_dup(current);
		if (new_node == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_node);
		current = current->next;
	}
	return (new_token_list);
}
