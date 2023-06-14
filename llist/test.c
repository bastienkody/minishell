/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:33:58 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 10:27:38 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"
#include <string.h>
#include <stdio.h>

void	*item_cpy(void *item)
{
	return (strdup((char *)item));
}

int main(void)
{
	t_llist	*llist = NULL;

	llstadd_back(&llist, llstnew(strdup("un")));
	llstadd_back(&llist, llstnew(strdup("trois")));
	llstadd_back(&llist, llstnew(strdup("quatre")));

	llstadd_before(&(llist->next), llstnew(strdup("deux")));
	for (t_llist *current = llist; current != NULL; current = current->next)
	{
		printf("%s\n", (char *)current->content);
	}
	// for (t_llist *current = llstlast(llist); current != NULL; current = current->prev)
	// {
	// 	printf("%s\n", (char *)current->content);
	// }

	t_llist *llist2 = llstrange_map(llist->next, llstlast(llist), item_cpy, free);

	for (t_llist *current = llist2; current != NULL; current = current->next)
	{
		printf("%s\n", (char *)current->content);
	}

	llstremoveone(&(llist), free);
	for (t_llist *current = llist; current != NULL; current = current->next)
	{
		printf("%s\n", (char *)current->content);
	}
	llstclear(&llist, free);
	llstclear(&llist2, free);
}
