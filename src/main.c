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
	ft_putchar_fd('~', 1);
	ft_putstr_fd((char *)item ,1);
	ft_putchar_fd('~', 1);
	ft_putchar_fd('\n', 1);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_llist *token_list;

	(void)argv;
	if (!argc || !envp)
		return (1);
	while (TRUE)
	{
		line = readline("minishell prompt % ");
		add_history(line);
		token_list = lsttok(line, DELIM);
		free(line);
		if (token_list == NULL)
			break ;
		llstiter(token_list, print_item);
		token_list = new_llst_with_compound(token_list);
		if (token_list == NULL)
			break ;
		ft_fprintf(1, "post compound cmds:\n");
		llstiter(token_list, print_item);
		ft_fprintf(1, "_________________________\n");
	}
	llstclear(&token_list, free);
}
