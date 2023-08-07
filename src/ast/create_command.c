/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:57:56 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 17:08:38 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	add_prefixes_children(t_llist **children, t_llist *begin, t_llist *end)
{
	// t_llist *const	prefixes_leafs
	// 	= llstextract_range(leaf_list, *leaf_list, cmd_name_pos);
	t_llist *const	new_children = create_prefixes(begin, end);

	if (new_children == NULL)
		return (0);
	llstadd_back(children, new_children);
	return (1);
}

static int	add_cmd_name_child(t_llist **children, t_llist *leaf)
{
	// t_llist *const	extract = llstextractone(leaf_list, cmd_name_pos);
	t_llist *const	new_child = create_child(leaf, create_cmd_name);

	if (new_child == NULL)
		return (0);
	llstadd_back(children, new_child);
	return (1);
}

static int	add_suffixes_children(t_llist **children, t_llist *begin, t_llist *end)
{
	// t_llist *const	extract = llstextract_range(leaf_list, *leaf_list, NULL);
	t_llist *const	new_children = create_suffixes(begin, end);

	if (new_children == NULL)
		return (0);
	llstadd_back(children, new_children);
	return (1);
}

t_ntree	*create_command(t_llist	*begin, t_llist *end)
{
	t_llist *const	cmd_name_pos = find_cmd_name(begin, end);
	t_llist			*children;
	int				ok;

	children = NULL;
	ok = 1;
	if (cmd_name_pos == NULL || cmd_name_pos != begin)
		ok *= add_prefixes_children(&children, begin, cmd_name_pos);
	if (cmd_name_pos != NULL)
		ok *= add_cmd_name_child(&children, cmd_name_pos);
	if (cmd_name_pos && cmd_name_pos->next != end)
		ok *= add_suffixes_children(&children, cmd_name_pos->next, end);
	if (ok == 0)
		return (llstclear(&children, ast_free), NULL);
	return (ast_new(SIMPLE_COMMAND, NULL, children));
}
