/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:55:39 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 15:48:16 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_leaf_word(t_ast	*leaf)
{
	return (leaf->type == word);
}

static t_ast	*create_cmd_name(t_llist *leaf)
{
	return (new_ast(CMD_NAME, NULL, leaf));
}

static int	is_node_word(t_ast	*ast)
{
	return (ast->type == word);
}

t_llist	*find_cmd_name(t_llist	*leaf_list)
{
	while (leaf_list != NULL)
	{
		if (is_node_word(leaf_list->content))
			return (leaf_list);
		leaf_list = llstnext(leaf_list, 2);
	}
	return (NULL);
}

t_ast	*create_command(t_llist	*leaf_list)
{
	t_llist	*cmd_name_pos;
	t_llist	*children;
	t_llist	*new_children;

	children = NULL;
	cmd_name_pos = find_cmd_name(leaf_list);
	if (cmd_name_pos == NULL)
		return (NULL);
	if (cmd_name_pos->prev != NULL)
	{
		new_children = create_prefixes(llstextract_range(&leaf_list, leaf_list, cmd_name_pos));
		if (new_children == NULL)
			return (NULL);
		llstadd_back(&children, new_children);
	}
	new_children = create_child(llstextractone(&leaf_list, leaf_list), create_cmd_name);
	if (new_children == NULL)
		return (NULL);
	llstadd_back(&children, new_children);
	if (leaf_list != NULL)
	{
		new_children = create_suffixes(llstextract_range(&leaf_list, leaf_list, NULL));
		if (new_children == NULL)
			return (NULL);
		llstadd_back(&children, new_children);
	}
	return (new_ast(SIMPLE_COMMAND, NULL, children));
}
