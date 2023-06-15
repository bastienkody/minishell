/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstrange_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:14:51 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 16:09:02 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

/*	new features :
	-join le next du chainon previous de begin a end
	-join le prev de end au chainon previous de begin
	-prends l'adresse du ptr sur gebin (bastien a antonin : necessaire ?)
	*/
void	llstrange_remove_2(t_llist **begin, t_llist *end, void (*del)(void *))
{
	t_llist	*current;
	t_llist	*next;

	if ((*begin)->prev)
		llstprev(*begin, 1)->next = end;
	if (end)
		end->prev = (*begin);
	current = *begin;
	while (current != NULL && current != end)
	{
		next = current->next;
		llstremoveone(&current, del);
		current = next;
	}
}
