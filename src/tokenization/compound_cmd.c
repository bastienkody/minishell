/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:52:53 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/21 17:13:55 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	return str that join content from begin to end	*/
t_llist	*join_token(t_llist *begin, t_llist *end)
{
	t_llist	*tmp;
	char	*s;

	tmp = llstmap_range(begin, end, (t_unary_op)ft_strdup, free);
	if (tmp == NULL)
		return (NULL);
	s = llstfold(tmp, ft_strdup(""), (t_binary_op)strjoin, free);
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
	char	*str;

	new_lst = NULL;
	while (start)
	{
		if (!is_str_op_p(start->content))
		{
			str = ft_strdup(start->content);
			if (str == NULL)
				return (llstclear(&new_lst, &free), NULL);
			new = llstnew(str);
			if (new == NULL)
				return (llstclear(&new_lst, &free), free(str), NULL);
			start = start->next;
		}
		else
		{
			new = handle_parenthese(start);
			start = get_next_node(start);
		}
		llstadd_back(&new_lst, new);
	}
	return (new_lst);
}