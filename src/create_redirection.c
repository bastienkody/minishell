/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:24:08 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 14:14:42 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int is_redirection_node(t_ast	*ast)
{
	const t_type	type = ast->type;

	return (type == less || type == great || type == dless || type == dgreat);
}

static int is_word_node(t_ast	*ast)
{
	return (ast->type == word);
}

static t_ast	*create_operator(t_llist *leaf)
{
	return (new_ast(OPERATOR, NULL, leaf));
}

static t_ast	*create_filename(t_llist *leaf)
{
	return (new_ast(FILENAME, NULL, leaf));
}

t_ast	*create_redirection(t_llist	*leaf_list)
{
	t_llist	*children;
	t_llist	*child;

	if (llstsize(leaf_list) != 2)
		return (NULL);
	if (!is_redirection_node(leaf_list->content) || !is_word_node(leaf_list->next->content))
		return (NULL);
	children = NULL;
	child = create_child(llstextractone(&leaf_list, leaf_list), create_operator);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	child = create_child(llstextractone(&leaf_list, leaf_list), create_filename);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	return (new_ast(REDIRECTION, NULL, children));
}
