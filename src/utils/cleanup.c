/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:42:03 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/03 11:29:07 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	data_cleanup(char **data)
{
	free(*data);
}

void	token_list_cleanup(t_llist **token_list)
{
	llstclear(token_list, token_free);
}

void	ast_cleanup(t_ntree **ast)
{
	ast_free(*ast);
}
