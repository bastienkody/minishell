/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:52:53 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/16 13:52:58 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	return str that join content from begin to end	*/
t_llist	*join_token(t_llist *begin, t_llist *end)
{
	t_llist	*temp;
	char	*str;

	temp = llstmap_range(begin, end, (void *(*)(void *))ft_strdup, free);
	if (temp == NULL)
		return (NULL);
	str = llstfold(temp, ft_strdup(""), (void *(*)(void *, void *))strjoin, free);
	if (str == NULL)
		return (llstclear(&temp, free), NULL);
	return (llstclear(&temp, free), llstnew(str));
}

/*	set begin + end for matching parenthese	*/
t_llist	*handle_parenthese(t_llist *start)
{
	t_llist	*end;
	int	n;

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
	int	n;

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

	new_lst = NULL;
	while (start)
	{
		if (!is_str_op_p(start->content))
		{
			new = llstnew(start->content);
			start = start->next;
		}
		else
		{
			new = handle_parenthese(start);
			start = get_next_node(start);
		}
		if (!new)
			return (llstclear(&new_lst, &free), NULL);
		llstadd_back(&new_lst, new);
	}
	return (new_lst);
}


