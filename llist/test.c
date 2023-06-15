/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:33:58 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 00:04:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"
#include "../libft/libft.h"
#include <string.h>
#include <stdio.h>

void	*item_cpy(void *item)
{
	return (strdup((char *)item));
}

void *join(void *value1, void *value2)
{
	return ((void *)ft_strjoin((const char *)value1, (const char *)value2));
}

void print(const char *str)
{
	puts(str);
}

int main(void)
{
	t_llist	*llist = NULL;

	llstadd_back(&llist, llstnew(strdup("un")));
	llstadd_back(&llist, llstnew(strdup("trois")));
	llstadd_back(&llist, llstnew(strdup("quatre")));

	llstadd_before(&(llist->next), llstnew(strdup("deux")));
	llstiter(llist, (void(*)(void *))print);
	char *str = llstfold(llist, ft_strdup(""), join, free);
	printf("%s\n", str);
	llstextract(llist);
	llstclear(&llist, free);
}
