/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:06:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 16:48:48 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_here_end(t_llist *leaf)
{
	t_token *const	token = get_token(leaf->content);
	char	*here_end;
	t_llist	*new_leaf_node;

	here_end = ft_strdup(token->data);
	if (here_end == NULL)
		return (NULL);
	new_leaf_node = leaf_node_dup(leaf);
	if (new_leaf_node == NULL)
		return (free(here_end), NULL);
	return (ast_new(HERE_END, here_end, new_leaf_node));
}

t_ntree	*create_here_doc(t_llist *begin, t_llist *end)
{
	t_llist	*children;
	t_llist	*child;
	// t_llist	*extract;

	(void)end;
	// llstremoveone(&leaf_list, leaf_list, (t_del_fun)ast_free);
	children = NULL;
	// extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(begin->next, create_here_end);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	return (ast_new(HERE_DOC, NULL, children));
}
