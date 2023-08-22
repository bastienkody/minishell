/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_expand_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:36:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/22 16:58:37 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_prev_redir_operator(t_llist *node)
{
	t_token	*prev_token;

	if (node->prev == NULL)
		return (0);
	prev_token = node->prev->content;
	return (is_str_redirection(prev_token->data) == 1);
}

int	get_nb_word(const char *str)
{
	int	nb_word;

	nb_word = 0;
	while (*str)
	{
		while (*str && ft_strchr(" 	", *str))
			str++;
		if (*str != '\0')
		{
			nb_word++;
			while (!ft_strchr(" 	", *str))
				str++;
		}
	}
	return (nb_word);
}

char	*ft_strndup(const char *str, size_t n)
{
	char *const	new = malloc(ft_strlen(str) + 1);

	if (new != NULL)
		strncpy(new, str, n);
	return (new);
}

static t_llist	*get_expand_nodes(t_llist *node)
{
	t_llist			*new_nodes;
	char			*next;
	t_llist			*new_node;
	char			*new_str;
	char			*str;

	str = llst_token_get_data(node);
	if (is_str_blank(str))
		return (llst_token_new(word, ft_strdup(str)));
	new_nodes = NULL;
	while (*str)
	{
		while (*str && ft_strchr(" 	", *str))
			str++;
		if (*str != '\0')
		{
			next = strfind_if(str, isblank);
			if (next == NULL)
				next = ft_strchr(str, 0);
			new_str = ft_substr(str, 0, next - str);
			if (new_str == NULL)
				return (llstclear(&new_nodes, token_free), NULL);
			new_node = llst_token_new(word, new_str);
			if (new_node == NULL)
				return (NULL);
			llstadd_back(&new_nodes, new_node);
			str = next;
		}
	}
	return (new_nodes);
}

static t_llist	*get_expand_node(t_llist *node, char **envp, int status)
{
	char	*expanded_str;

	expanded_str = expand_dollar(llst_token_get_data(node), envp, status);
	if (expanded_str == NULL)
		return (NULL);
	return (llst_token_new(llst_token_get_type(node), expanded_str));
}

static int	is_word_ambigous(t_llist *node)
{
	const int	nb_word = get_nb_word(llst_token_get_data(node));

	return (is_prev_redir_operator(node) && nb_word > 1);
}

t_llist	*llst_rearange_dollar(t_llist *token_list)
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
		if (current_token->type == word && is_word_ambigous(current))
			new_node = get_ambigous_node(current);
		else if (current_token->type == word && strfind_if(current_token->data, isblank))
			new_node = get_expand_nodes(current);
		else
			new_node = node_dup(current);
		if (new_node == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_node);
		current = current->next;
	}
	return (new_token_list);
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
		if ((current_token->type == word || current_token->type == quoted_word) && !is_prev_here_operator(current))
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
