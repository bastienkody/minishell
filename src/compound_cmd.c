/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:52:53 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/19 15:32:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	return str that join content from begin to end	*/
t_llist	*join_token(t_llist *begin, t_llist *end)
{
	t_llist	*tmp;
	char	*s;

	tmp = llstmap_range(begin, end, (void *(*)(void *))ft_strdup, free);
	if (tmp == NULL)
		return (NULL);
	s = llstfold(tmp, ft_strdup(""), (void *(*)(void *, void *))strjoin, free);
	if (s == NULL)
		return (llstclear(&tmp, free), NULL);
	return (llstclear(&tmp, free), llstnew(s));
}

/*	set begin + end for matching parenthese	*/
t_llist	*handle_parenthese(t_llist *start)
{
	t_llist	*end;
	int		n;

	n = 1;
	end = start->next;
	while (end && n)
	{
		if (is_str_op_p(end->content))
			n += 1;
		else if (is_str_cl_p(end->content))
			n -= 1;
		end = end->next;
	}
	return (join_token(start, end));
}

/*	return the matching closing parenthese (or null)	*/
static t_llist	*get_next_node(t_llist *start)
{
	t_llist	*end;
	int		n;

	n = 1;
	end = start->next;
	while (end && n)
	{
		if (is_str_op_p(end->content))
			n += 1;
		else if (is_str_cl_p(end->content))
			n -= 1;
		end = end->next;
	}
	return (end);
}

/*	return a new list with compound commands on single node	*/
t_llist	*new_llst_with_compound(t_llist *start)
{
	t_llist	*new_lst;
	t_llist	*new;
	t_llist	*current;
	char	*str;

	new_lst = NULL;
	current = start;
	while (current)
	{
		if (!is_str_op_p(current->content))
		{
			str = ft_strdup(current->content);
			if (str == NULL)
				new = NULL;
			else
			{
				new = llstnew(str);
				current = current->next;
			}
		}
		else
		{
			new = handle_parenthese(current);
			current = get_next_node(current);
		}
		if (!new)
			return (llstclear(&new_lst, &free), NULL);
		llstadd_back(&new_lst, new);
	}
	return (llstclear(&start, free), new_lst);
}
