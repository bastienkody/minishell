/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/09 19:25:24 by aguyon           ###   ########.fr       */
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

void	print_token_error(t_token *token)
{
	ft_fprintf(1, "syntax error near unexpected token : %s\n", token->data);
}
