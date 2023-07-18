/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:39:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/26 17:59:21 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*new_ast(t_type	type, void *data, t_llist *children)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (new == NULL)
		return (NULL);
	*new = (t_ast){type, data, children};
	return (new);
}
