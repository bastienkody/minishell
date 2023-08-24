/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_word_splitting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:16:28 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 12:52:59 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_next(char *str, bool *is_inside_simple_quote,
	bool *is_inside_double_quote)
{
	if (isblank(*str))
		return (str + ft_strspn(str, " 	"));
	else
	{
		while (*str)
		{
			if (*str == '\"' && !*is_inside_simple_quote)
				*is_inside_double_quote = !*is_inside_double_quote;
			else if (*str == '\'' && !*is_inside_double_quote)
				*is_inside_simple_quote = !*is_inside_simple_quote;
			if (isblank(*str) && !*is_inside_simple_quote
				&& !*is_inside_double_quote)
				return (str);
			str++;
		}
	}
	return (str);
}

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
		next = get_next(str, &is_inside_simple_quote, &is_inside_double_quote);
		if (*str != ' ')
			nb_word++;
		str = next;
	}
	return (nb_word);
}

static int	is_var_expansion_ambigous(t_llist *node)
{
	const int	nb_word = get_nb_fields(llst_token_get_data(node));

	return (is_prev_redir_operator(node) && nb_word > 1);
}

t_llist	*split_word_node(char *str)
{
	bool	is_inside_simple_quote;
	bool	is_inside_double_quote;
	char	*next;
	t_llist	*new_nodes;
	t_llist	*new_node;

	is_inside_simple_quote = false;
	is_inside_double_quote = false;
	new_nodes = NULL;
	while (*str)
	{
		next = get_next(str, &is_inside_simple_quote, &is_inside_double_quote);
		if (*str != ' ')
		{
			new_node = new_field_node(str, 0, next - str);
			if (new_node == NULL)
				return (llstclear(&new_nodes, token_free), NULL);
			llstadd_back(&new_nodes, new_node);
		}
		str = next;
	}
	return (new_nodes);
}

t_llist	*llst_word_splitting(t_llist *token_list)
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
		if (current_token->type == word && is_var_expansion_ambigous(current))
			new_node = ambigous_node_new(current);
		else if (current_token->type == word)
			new_node = split_word_node(current_token->data);
		else
			new_node = node_dup(current);
		if (new_node == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_node);
		current = current->next;
	}
	return (new_token_list);
}
