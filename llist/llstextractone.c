/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstextractone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:29:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/26 19:07:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstextractone(t_llist **begin_llst, t_llist *llst)
{
	t_llist	*prev;
	t_llist	*next;

	if (*begin_llst == NULL || llst == NULL)
		return (NULL);
	if (llst->prev == NULL)
		*begin_llst = (*begin_llst)->next;
	prev = llst->prev;
	next = llst->next;
	if (llst->prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	*llst = (t_llist){llst->content, NULL, NULL};
	return (llst);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	t_llist	*llst;
// 	t_llist	*extract;

// 	llstadd_back(&llst, llstnew(strdup("HELLO")));
// 	llstadd_back(&llst, llstnew(strdup("WORLD")));

// 	extract = llstextractone(&llst, llst);
// 	printf("%s\n", (char *)extract->content);
// }
