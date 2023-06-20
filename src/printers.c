/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/16 15:40:59 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_item(void *item)
{
	ft_putstr_fd((char *)item ,1);
	ft_putstr_fd("\n", 1);
}

void	print_llist(t_llist *start, void f(void *))
{
	ft_fprintf(1, "------------------\n");
	llstiter(start, f);
	ft_fprintf(1, "------------------\n");
}