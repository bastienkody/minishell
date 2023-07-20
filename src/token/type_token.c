/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:42:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 14:44:46 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int (*const	g_type_predicate[])(const char *str)
	= {
	is_str_or,
	is_str_and,
	is_str_pipe,
	is_str_great,
	is_str_less,
	is_str_dgreat,
	is_str_dless,
	is_str_compound,
	is_str_word,
	NULL,
};

static t_type	get_type(const char *text)
{
	t_type	type;

	type = 0;
	while (g_type_predicate[type])
	{
		if (g_type_predicate[type](text))
			break ;
		type++;
	}
	return (type);
}

t_token	*str_to_token(char *str)
{
	const t_type	type = get_type(str);
	t_token	*const	new = malloc(sizeof(t_token));
	char *const		new_data = ft_strdup(str);

	if (new == NULL)
		return (free_token(new), NULL);
	if (new_data == NULL)
		return (free(new_data), NULL);
	*new = (t_token){type, new_data};
	return (new);
}

t_token	*token_new(t_type type, void *data)
{
	t_token *const	new = malloc(sizeof(t_token));

	if (new != NULL)
		*new = (t_token){type, data};
	return (new);
}

t_llist	*type_token(t_llist	*token_list)
{
	return (llstmap(token_list, (t_unary_op)str_to_token,
		(t_del_fun)free_token));
}
