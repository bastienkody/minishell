/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/10 13:46:14 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_item(void *item)
{
	if (!item)
		return ;
	ft_putstr_fd((char *)item, 1);
	ft_putstr_fd("\n", 1);
}

void	print_llist(t_llist *start)
{
	if (!start)
		return ;
	ft_fprintf(1, "------------------\n");
	llstiter(start, &print_item);
	ft_fprintf(1, "------------------\n");
}

void	print_syntax_error(const char *str)
{
	ft_fprintf(2, "%s`%s\'\n", ERR_SYNTAX, str);
}

void	print_signal(int signum)
{
	if (signum == SIGINT)
		ft_putendl_fd("", 2);
	else if (signum == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
}
