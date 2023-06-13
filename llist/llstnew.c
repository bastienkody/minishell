/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:17:01 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 17:19:03 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstnew(void *content)
{
	t_llist	*new;

	new = malloc(sizeof(t_llist));
	if (new == NULL)
		return (NULL);
	*new = (t_llist){content, NULL, NULL};
	return (new);
}