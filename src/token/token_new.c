/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:07:40 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 16:03:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*token_new(t_type type, void *data)
{
	t_token *const	new = malloc(sizeof(t_token));

	if (new != NULL)
		*new = (t_token){type, data};
	return (new);
}
