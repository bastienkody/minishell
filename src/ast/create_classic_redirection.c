/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_classic_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:10:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:11:40 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*create_operator(t_llist *leaf)
{
	return (ast_new(OPERATOR, NULL, leaf));
}

static t_ntree	*create_filename(t_llist *leaf)
{
	t_token *const	token = get_token(leaf->content);
	char *const		filename = ft_strdup(token->data);

	if (filename == NULL)
		return (NULL);
	return (ast_new(FILENAME, filename, leaf));
}

t_ntree	*create_classic_redirection(t_llist *leaf_list)
{
	t_llist	*children;
	t_llist	*child;
	t_llist	*extract;

	children = NULL;
	extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(extract, create_operator);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	extract = llstextractone(&leaf_list, leaf_list);
	child = create_child(extract, create_filename);
	if (child == NULL)
		return (NULL);
	llstadd_back(&children, child);
	return (ast_new(REDIRECTION, NULL, children));
}
