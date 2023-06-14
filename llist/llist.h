/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:14:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 14:32:10 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLIST_H
# define LLIST_H

# include <stddef.h>
# include <stdlib.h>

typedef struct s_llist
{
	void			*content;
	struct s_llist	*prev;
	struct s_llist	*next;
}	t_llist;

t_llist	*llstnew(void *content);
size_t	llstsize(t_llist *llst);
t_llist	*llstfirst(t_llist *llst);
t_llist	*llstlast(t_llist *llst);
int		llstempty(t_llist *llst);
void	llstadd_back(t_llist **llst, t_llist *new);
void	llstadd_front(t_llist **llst, t_llist *new);
void	llstadd_after(t_llist **llst, t_llist *new);
void	llstadd_before(t_llist **llst, t_llist *new);
void	llstdelone(t_llist *llst, void (*del)(void *));
void	llstclear(t_llist **llst, void (*del)(void *));
void	ft_lstiter(t_llist *llst, void (*f)(void *));
t_llist	*llstmap(t_llist *llst, void *(*f)(void *), void (*del)(void *));
void	llstremoveone(t_llist **llst, void (*del)(void *));
t_llist	*llstfind(t_llist *llst, void *value, int comp(void *, void *));
t_llist	*llstnext(t_llist *llst, size_t n);
t_llist	*llstprev(t_llist *llst, size_t n);
t_llist	*llstrange_map(t_llist *begin, t_llist *end, void *(*f)(void *),
			void (*del)(void *));
void	llstrange_remove(t_llist *begin, t_llist *end, void (*del)(void *));
int		llstall_of(t_llist *llst, int (*p)(void *));
int		llstany_of(t_llist *llst, int (*p)(void *));
int		llstnone_of(t_llist *llst, int (*p)(void *));
void	*llstmax(t_llist *llst, int (*comp)(void *, void *));
void	*llstmin(t_llist *llst, int (*comp)(void *, void *));
void	*llstcomp(t_llist *llst1, t_llist *llst2, int (*comp)(void *, void *));
void	*llstncomp(t_llist *llst1, t_llist *llst2, size_t n,
			int (*comp)(void *, void *));

#endif
