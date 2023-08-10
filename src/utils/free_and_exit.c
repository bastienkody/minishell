/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:17:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 15:03:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_and_exit(t_info *info, int status)
{
	char ***envp_ptr = get_token(info->root_ast)->data;
	free_char_matrix(*envp_ptr);
	ast_free(info->root_ast);
	exit(status);
}