/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:32:40 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 19:32:42 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	err_msg(char *str, char *err)
{
	ft_fprintf(2, "minishell: %s: %s\n", str, err);
}

void	err_builtin(char *builtin, char *arg, char *err)
{
	ft_fprintf(2, "minishell: %s: `%s': %s\n", builtin, arg, err);
}
