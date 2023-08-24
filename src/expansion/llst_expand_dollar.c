/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_expand_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:36:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 16:40:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_nb_fields(char *str)
{
	int		nb_word;
	bool	is_inside_simple_quote;
	bool	is_inside_double_quote;
	char	*next;

	is_inside_simple_quote = false;
	is_inside_double_quote = false;
	nb_word = 0;
	while (*str)
	{
		next = get_next_split_word_node(str, &is_inside_simple_quote, &is_inside_double_quote);
		if (*str != ' ')
			nb_word++;
		str = next;
	}
	return (nb_word);
}

int	is_prev_redir_operator(t_llist *node)
{
	t_token	*prev_token;

	if (node->prev == NULL)
		return (0);
	prev_token = node->prev->content;
	return (is_str_redirection(prev_token->data) == 1);
}

static t_llist	*get_expand_node(t_llist *node, char **envp, int status)
{
	char *const	str = llst_token_get_data(node);
	char	*new_str;
	t_llist	*new_node;

	new_str = expand_dollar(str, envp, status);
	if (new_str == NULL)
		return (NULL);
	if (get_nb_fields(new_str) > 1 && is_prev_redir_operator(node))
	{
		free(new_str);
		new_str = ft_strdup(str);
		if (new_str == NULL)
			return (NULL);
		new_node = llst_token_new(ambiguous_word, new_str);
	}
	else
		new_node = llst_token_new(word, new_str);
	return (new_node);
}

t_llist	*llst_expand_dollar(t_llist *token_list, char **envp, int status)
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
			new_node = get_expand_node(current, envp, status);
		else
			new_node = node_dup(current);
		if (new_node == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_node);
		current = current->next;
	}
	return (new_token_list);
}
