/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:41:16 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/05 16:55:47 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*ast_dup(t_ntree *ast)
{
	return (ntree_dup(ast, (t_unary_op)token_dup, (t_del_fun)token_free));
}