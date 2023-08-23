/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_rearange_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:16:28 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/23 14:22:52 by aguyon           ###   ########.fr       */
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

size_t ft_strspn(const char *s, const char *accept)
{
    size_t  i;

    i = 0;
    while (s[i] && ft_strchr(accept, s[i]))
        i++;
    return (i);
}

static char	*get_next(char *str, bool *is_inside_simple_quote, bool *is_inside_double_quote)
{
	if (isblank(*str))
		return(str + ft_strspn(str, " 	"));
	else
	{
		while (*str)
		{
			if (*str == '\"' && !*is_inside_simple_quote)
				*is_inside_double_quote = !*is_inside_double_quote;
			else if (*str == '\'' && !*is_inside_double_quote)
				*is_inside_simple_quote = !*is_inside_simple_quote;
			if (isblank(*str) && !*is_inside_simple_quote && !*is_inside_double_quote)
				 return (str);
			str++;
		}
	}
	return (str);
}

int	get_nb_word(char *str)
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

static int	is_word_ambigous(t_llist *node)
{
	const int	nb_word = get_nb_word(llst_token_get_data(node));

	return (is_prev_redir_operator(node) && nb_word > 1);
}

t_llist	*new_str_node(char *str, size_t start, size_t len)
{
	char	*new_str;

	new_str = ft_substr(str, start, len);
	if (new_str == NULL)
		return (NULL);
	return (llst_token_new(word, new_str));
}

t_llist	*rearange_node(t_llist *node)
{
	char	*str = llst_token_get_data(node);
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
			new_node = new_str_node(str, 0, next - str);
			if (new_node == NULL)
				return (llstclear(&new_nodes, token_free), NULL);
			llstadd_back(&new_nodes, new_node);
		}
		str = next;
	}
	return (new_nodes);
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
		else if (current_token->type == word)
			new_node = rearange_node(current);
		else
			new_node = node_dup(current);
		if (new_node == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_node);
		current = current->next;
	}
	return (new_token_list);
}
