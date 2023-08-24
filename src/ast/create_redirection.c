/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 14:34:25 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_redirection(t_llist	*begin, t_llist *end)
{
	const char	*operator_str = llst_token_get_data(begin);

	if (ft_strcmp(operator_str, "<<") == 0)
		return (create_here_doc(begin, end));
	return (create_classic_redirection(begin, end));
}
