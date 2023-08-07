/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:14:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 17:44:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLIST_H
# define LLIST_H

# include <stddef.h>
# include <stdlib.h>

typedef void	*(*t_funptr)();
typedef int		(*t_predicate)(void *);
typedef void	(*t_unary_fun)(void *);
typedef void	*(*t_unary_op)(void *);
typedef void	*(*t_binary_op)(void *, void *);
typedef void	(*t_del_fun)(void *);

typedef struct s_llist
{
	void			*content;
	struct s_llist	*prev;
	struct s_llist	*next;
}	t_llist;

t_llist	*llstnew(void *content);
size_t	llstsize(t_llist *llst);
size_t	llstsize_range(t_llist *begin, t_llist *end);
t_llist	*llstfirst(t_llist *llst);
t_llist	*llstlast(const t_llist *llst);
int		llstempty(t_llist *llst);
void	llstadd_back(t_llist **llst, t_llist *new);
void	llstadd_front(t_llist **llst, t_llist *new);
void	llstadd_after(t_llist **llst, t_llist *new);
void	llstadd_before(t_llist **llst, t_llist *new);
void	llstdelone(t_llist *llst, void (*del)(void *));
void	llstclear(t_llist **llst, void *del);
void	llstiter(t_llist *llst, void (*f)(void *));
t_llist	*llstmap(t_llist *llst, void *(*f)(void *), void (*del)(void *));
t_llist	*llstfind(t_llist *llst, void *value, int comp(void *, void *));
t_llist	*llstfind_if(t_llist *llst, int (*p)(void *));
t_llist	*llstfind_if_range(t_llist *begin, t_llist *end, int (*p)(void *));
t_llist	*llstfind_if_not(t_llist *llst, int (*p)(void *));
t_llist	*llstfind_if_reverse(const t_llist *llst, int (*p)(void *));
t_llist	*llstfind_if_reverse_range(const t_llist *rbegin, const t_llist *rend, int (*p)(void *));
t_llist	*llstnext(t_llist *llst, size_t n);
t_llist	*llstprev(t_llist *llst, size_t n);
t_llist	*llstmap_range(t_llist *begin, t_llist *end, void *(*f)(void *),
			void (*del)(void *));
void	llstremove_range(t_llist **begin_llst, t_llist *begin, t_llist *end,
			void (*del)(void *));
void	llstremoveone(t_llist **begin, t_llist *llst, void (*del)(void *));
int		llstall_of(t_llist *llst, int (*p)(void *));
int		llstany_of(t_llist *llst, int (*p)(void *));
int		llstnone_of(t_llist *llst, int (*p)(void *));
void	*llstmax(t_llist *llst, int (*comp)(void *, void *));
void	llstmerge(t_llist **begin_list1, t_llist *begin_list2);
void	*llstmin(t_llist *llst, int (*comp)(void *, void *));
void	*llstfold(t_llist *llst, void *acc, void *(*f)(void *, void *),
			void del(void *));
t_llist	*llstextract_range(t_llist **begin_llst, t_llist *begin, t_llist *end);
t_llist	*llstextractone(t_llist **begin_llst, t_llist *llst);
void	llstremove_if(t_llist **llst, int (*p)(void *), void (*del)(void *));
void	llstmerge(t_llist **begin_list1, t_llist *begin_list2);
int		llstreplace(t_llist **original_list, t_llist *new_list, void *del);

#endif
