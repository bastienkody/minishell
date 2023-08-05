/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:57:56 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/05 14:26:19 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	add_prefixes_children(t_llist **children, t_llist **leaf_list,
	t_llist *cmd_name_pos)
{
	t_llist *const	prefixes_leafs
		= llstextract_range(leaf_list, *leaf_list, cmd_name_pos);
	t_llist *const	new_children = create_prefixes(prefixes_leafs);

	if (new_children == NULL)
		return (0);
	llstadd_back(children, new_children);
	return (1);
}

static int	add_cmd_name_child(t_llist **children, t_llist **leaf_list,
	t_llist *cmd_name_pos)
{
	t_llist *const	extract = llstextractone(leaf_list, cmd_name_pos);
	t_llist *const	new_child = create_child(extract, create_cmd_name);

	(void)extract;
	if (new_child == NULL)
		return (0);
	llstadd_back(children, new_child);
	return (1);
}

static int	add_suffixes_children(t_llist **children, t_llist **leaf_list)
{
	t_llist *const	extract = llstextract_range(leaf_list, *leaf_list, NULL);
	t_llist *const	new_children = create_suffixes(extract);

	if (new_children == NULL)
		return (0);
	llstadd_back(children, new_children);
	return (1);
}

t_ntree	*create_command(t_llist	*leaf_list)
{
	t_llist *const	cmd_name_pos = find_cmd_name(leaf_list);
	t_llist			*children;
	int				ok;

	children = NULL;
	ok = 1;
	if (cmd_name_pos == NULL || cmd_name_pos->prev != NULL)
		ok *= add_prefixes_children(&children, &leaf_list, cmd_name_pos);
	if (cmd_name_pos != NULL)
		ok *= add_cmd_name_child(&children, &leaf_list, cmd_name_pos);
	if (leaf_list != NULL)
		ok *= add_suffixes_children(&children, &leaf_list);
	if (ok == 0)
		return (llstclear(&children, ast_free), NULL);
	return (ast_new(SIMPLE_COMMAND, NULL, children));
}
