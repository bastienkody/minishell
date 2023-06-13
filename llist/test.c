/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:33:58 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 19:41:31 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"
#include <string.h>
#include <stdio.h>

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
	for (t_llist *current = llstlast(llist); current != NULL; current = current->prev)
	{
		printf("%s\n", (char *)current->content);
	}

	llstclear(&llist, free);
}