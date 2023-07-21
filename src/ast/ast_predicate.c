/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_predicate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:04:13 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 17:07:01 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_node_compound(t_ntree *node)
{
	return (is_node_equal(node, compound));
}

int	is_node_logical_operator(t_ntree *node)
{
	return (is_node_inside(node, (t_type[]){or, and}, 2));
}

int	is_node_pipe(t_ntree *node)
{
	return (is_node_equal(node, ppipe));
}

int	is_node_word(t_ntree *node)
{
	return (is_node_equal(node, word));
}

int	is_node_redirection(t_ntree *node)
{
	return (is_node_inside(node, (t_type[]){less, dless, great, dgreat}, 4));
}
