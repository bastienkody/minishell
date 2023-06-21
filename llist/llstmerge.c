/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstmerge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:22:35 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/20 19:29:27 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstmerge(t_llist **begin_list1, t_llist *begin_list2)
{
	if (*begin_list1 == NULL)
		*begin_list1 = begin_list2;
	else
		llstlast(*begin_list1)->next = begin_list2;
}

// #include <stdio.h>
// #include <string.h>

// void print_item(void *value)
// {
// 	printf("%s\n", (char *)value);
// }

// int main(void)
// {
// 	t_llist *llist1 = NULL;
// 	t_llist *llist2 = NULL;

// 	llstadd_back(&llist1, llstnew(strdup("Salut")));
// 	llstadd_back(&llist1, llstnew(strdup(" ")));
// 	llstadd_back(&llist1, llstnew(strdup("a")));
// 	llstadd_back(&llist1, llstnew(strdup(" ")));
// 	llstadd_back(&llist2, llstnew(strdup("tout")));
// 	llstadd_back(&llist2, llstnew(strdup(" ")));
// 	llstadd_back(&llist2, llstnew(strdup("le")));
// 	llstadd_back(&llist2, llstnew(strdup(" ")));
// 	llstadd_back(&llist2, llstnew(strdup("monde")));

// 	llstmerge(&llist1, llist2);
// 	llstiter(llist1, print_item);
// 	llstclear(&llist1, free);
// }