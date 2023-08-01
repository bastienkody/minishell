/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:09 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 12:02:14 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ntree	*parser(t_llist	*token_list)
{
	t_llist	*leaf_list;

	leaf_list = token_to_leaf(token_list);
	if (leaf_list == NULL)
		return (NULL);
	return (create_complete_command(leaf_list));
}
