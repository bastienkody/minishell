/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:09:14 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/23 16:10:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ntree *new_ast_node(t_llist	**tree_list, )
{

}

t_type	get_node_type(t_ntree	*node)
{
	return (((t_node *)node->item)->type);
}

int	is_reductible_complete_command(t_llist	*last, t_llist	*token_list)
{
	const t_type	current_type = get_node_type(last->content);

	if (token_list == NULL && last->prev == NULL)
		if (current_type == COMMAND || current_type == REDIRECTION || current_type == PIPELINE)
			return (1);
	return (0);
}

int is_reductible_redirection(t_llist	*last)
{
	return (last && last->prev && get_node_type(last) == FILENAME && get_node_type(last->prev) == OP);
}

int is_reductible_command(t_llist	*last, t_llist	*token_list)
{
	if (token_list->next == NULL || ((t_token *)token_list->next)->type == and || ((t_token *)token_list->next)->type == and || ((t_token *)token_list->next)->type == ppipe)
	{
		
	}
}

/*
COMPLETE_COMMAND,
REDIRECTION,
COMMAND,
PIPELINE,
*/

int	reduce(t_llist **tree_list, t_llist *token_list)
{
	t_llist	*last;

	last = llstlast(*tree_list);
	if (is_reductible_complete_command(last, token_list))

	else if (is_reductible_redirection(last))




}

t_node	*node_new(t_type type, union u_data data)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	*new = (t_node){type, data};
	return (new);
}

t_ntree	*new_leaf(t_llist	*node, t_llist	*tree_list)
{
	t_token	token = *(t_token *)node->content;
	t_ntree	*last_tree;
	// t_ntree	*leaf;
	t_node	*new_node;
	union u_data data;

	data.token = token;
	if (token.type == great || token.type == less || token.type == dgreat || token.type == dless)
		new_node = node_new(OP, data);
	else if (token.type == word)
	{
		if (llstlast(tree_list) != NULL)
			last_tree = (t_ntree *)llstlast(tree_list)->content;
		else
			last_tree = NULL;
		if (last_tree == NULL)
			new_node = node_new(COMMAND_NAME, data);
		else if (((t_node *)last_tree->item)->type == COMMAND_NAME)
			new_node = node_new(SUFFIX, data);
		else if (((t_node *)last_tree->item)->type == OP)
			new_node = node_new(FILENAME, data);
		else
			new_node = node_new(COMMAND_NAME, data);
	}
	else
		new_node = node_new(token.type, data);
	if (new_node == NULL)
		return (NULL);
	return (ntree_new(new_node));
}

t_llist *create_ast(t_llist *token_list)
{
	t_llist	*tree_list;
	t_ntree	*new_tree;
	t_llist	*new_node;
	t_llist	*current;
	t_llist	*next;

	tree_list = NULL;
	current = token_list;
	while (current != NULL)
	{
		next = current->next;
		new_tree = new_leaf(llstextractone(&token_list, current), tree_list);
		if (new_tree == NULL)
			return (NULL);
		new_node = llstnew(new_tree);
		if (new_node == NULL)
			return (NULL);
		llstadd_back(&tree_list, new_node);
		reduce(&tree_list);
		current = next;
	}
	while (reduce(&tree_list))
		;
	// if (llstsize(tree_list) > 1 || ((t_type)(((t_ntree *)(tree_list->content))->item)) != COMPLETE_COMMAND)
	// 	return (NULL);
	return (tree_list);
}