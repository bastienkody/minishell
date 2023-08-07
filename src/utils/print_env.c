/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:35:03 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/27 18:09:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(char **envp, char *prefix)
{
	while (envp && *envp)
	{
		if (prefix)
			ft_fprintf(1, "%s", prefix);
		ft_fprintf(1, "%s\n", *envp);
		envp++;
	}
}

void	print_envar_bad(char *var, char **envp)
{
	while (envp && *envp)
	{
		if (!ft_strncmp(*envp, var, ft_strlen(var)))
			return ((void)ft_fprintf(1, "%s\n", *envp));
		envp++;
	}
}
