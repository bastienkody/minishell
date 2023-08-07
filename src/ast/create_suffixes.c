/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_suffixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 15:54:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_cmd_arg(t_llist	*leaf)
{
	return (ast_new(CMD_ARG, NULL, leaf));
}

t_llist	*create_suffixes(t_llist *leaf_list)
{
	t_llist	*suffixes;
	t_llist	*new_child;
	t_llist	*extract;

	suffixes = NULL;
	while (leaf_list != NULL)
	{
		if (is_node_redirection(leaf_list->content))
		{
			extract = llstextract_range(&leaf_list, leaf_list,
					llstnext(leaf_list, 2));
			new_child = create_child(extract, create_redirection);
		}
		else if (is_node_word(leaf_list->content))
		{
			extract = llstextractone(&leaf_list, leaf_list);
			new_child = create_child(extract, create_cmd_arg);
		}
		else
			new_child = NULL;
		if (new_child == NULL)
			return (llstclear(&suffixes, ast_free), NULL);
		llstadd_back(&suffixes, new_child);
	}
	return (suffixes);
}
