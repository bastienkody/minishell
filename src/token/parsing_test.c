/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:41:26 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/23 14:54:37 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*llstextract(t_llist **begin, t_llist *llst)
{
	t_llist	*prev;

	if (*begin == NULL || llst == NULL)
		return (NULL);
	if (llst->prev == NULL)
		*begin = NULL;
	else
	{
		prev = llst->prev;
		prev->next = NULL;
		llst->prev = NULL;
	}
	return (llst);
}

// t_llist	*llstextractone(t_llist **begin, t_llist *llst)
// {
// 	t_llist	*prev;
// 	t_llist	*next;

// 	if (*begin == NULL || llst == NULL)
// 		return (NULL);
// 	if (llst->prev == NULL && llst->next == NULL)
// 		*begin = NULL;
// 	else
// 	{
// 		prev = llst->prev;
// 		next = llst->next;
// 		if (prev != NULL)
// 			prev->next = next;
// 		if (next != NULL)
// 			next->prev = prev;
// 	}
// 	return (llst);
// }

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
	t_llist	*right;
	char	*str;

	root = llstfind_if_reverse(token_list, (int (*)(void *))isstroperator);
	if (root == NULL)
		return (btree_create_node(token_list));
	str = ft_strdup(root->content);
	if (str == NULL)
		return (NULL);
	ast = btree_create_node(str);
	root = llstextract(&token_list, root);
	right = llstextract(&root, root->next);
	llstclear(&root, free);
	if (right != NULL)
		ast->right = btree_create_node(right);
	if (token_list != NULL)
		ast->left = create_tree(token_list);
	if (ast->left == NULL)
		return (NULL);
	return (ast);
}
