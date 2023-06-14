/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:47:41 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 16:48:01 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **list, t_list *prev, void (*del)(void *))
{
	t_list	*current;
	t_list	*tmp;

	current = *list;
	tmp = current->next;
	ft_lstdelone(current, del);
	if (prev == NULL)
		*list = tmp;
	else
		prev->next = tmp;
}
