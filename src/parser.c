/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:09 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/19 14:42:21 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*parser(t_llist	*token_list)
{
	t_llist	*leaf_list;
	t_ast	*ast;

	leaf_list = token_to_leaf(token_list);
	if (leaf_list == NULL)
		return (NULL);
	llstclear(&token_list, (void (*)(void *))free_token);
	ast = create_complete_command(leaf_list);
	if (ast == NULL)
		return (NULL);
	return (ast);
}
