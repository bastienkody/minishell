/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremove_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:00:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/20 19:17:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremove_if(t_llist **llst, int (*p)(void *), void (*del)(void *))
{
	t_llist	*current;
	t_llist	*next;
	t_llist	*prev;

	current = *llst;
	while (current != NULL)
	{
		prev = current->prev;
		next = current->next;
		if (p(current->content))
		{
			prev->next = next;
			next->prev = prev;
			llstdelone(current, del);
		}
		current = next;
	}
}

// #include <string.h>
// #include <stdio.h>

// void print_item(void *item)
// {
// 	printf("%s\n", (char *)item);
// }

// int isstrspace(char *str)
// {
// 	return (strcmp(str, " ") == 0);
// }

// int main(void)
// {
// 	t_llist	*llist = NULL;

// 	llstadd_back(&llist, llstnew(strdup("Salut")));
// 	llstadd_back(&llist, llstnew(strdup(" ")));
// 	llstadd_back(&llist, llstnew(strdup("a")));
// 	llstadd_back(&llist, llstnew(strdup(" ")));
// 	llstadd_back(&llist, llstnew(strdup("tous")));

// 	llstiter(llist, print_item);
// 	llstremove_if(&llist, (int(*)(void *))isstrspace, free);
// 	llstiter(llist, print_item);
// 	llstclear(&llist, free);
// }