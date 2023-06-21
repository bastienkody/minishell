/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:41:26 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/21 13:29:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_llist	*llstextract(t_llist *llst)
{
	t_llist	*prev;

	if (llst->prev == NULL)
		return (llst);
	prev = llst->prev;
	prev->next = NULL;
	llst->prev = NULL;
	return (llst);
}

int	isstroperator(char *str)
{
	return (strcmp(str, "&&") == 0 || strcmp(str, "||") == 0);
}

t_llist	*gtollist(void *value)
{
	return ((t_llist *)value);
}

t_btree	*create_tree(t_llist *token_list)
{
	t_btree	*ast;
	t_llist	*root;

	root = llstfind_if_reverse(llstlast(token_list),
			(int (*)(void *))isstroperator);
	if (root == NULL)
		return (btree_create_node(llstextract(token_list)));
	ast = btree_create_node(root->content);
	ast->right = btree_create_node(llstextract(llstextract(root)->next));
	ast->left = create_tree(token_list);
	return (ast);
}
