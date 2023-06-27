/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_suffixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:21:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 14:32:59 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_node_operator(t_ast	*ast)
{
	const t_type type = ast->type;

	return (type == less || type == great || type == dless || type == dgreat);
}

static int	is_node_word(t_ast	*ast)
{
	return (ast->type == word);
}

static t_ast	*create_cmd_arg(t_llist	*leaf)
{
	return (new_ast(CMD_ARG, NULL, leaf));
}

t_llist	*create_suffixes(t_llist *leaf_list)
{
	t_llist	*suffixes;
	t_llist	*new_child;

	suffixes = NULL;
	while (leaf_list != NULL)
	{
		if (is_node_operator(leaf_list->content))
			new_child = create_child(llstextract_range(&leaf_list, leaf_list, llstnext(leaf_list, 2)), create_redirection);
		else if (is_node_word(leaf_list->content))
			new_child = create_child(llstextractone(&leaf_list, leaf_list), create_cmd_arg);
		else
			new_child = NULL;
		if (new_child == NULL)
			return (NULL);
		llstadd_back(&suffixes, new_child);
	}
	return (suffixes);
}
