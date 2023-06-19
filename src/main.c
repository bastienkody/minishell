/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/17 14:35:52 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_item(void *item)
{
	ft_putstr_fd((char *)item ,1);
	ft_putstr_fd("\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_llist *token_list;

	(void)argv;
	if (!argc || !envp)
		return (1);
	// while (TRUE)
	// {
		line = readline("minishell prompt % ");
		add_history(line);
		token_list = lsttok(line);
		free(line);
		if (token_list == NULL)
			// break ;
		llstiter(token_list, print_item);
		token_list = new_llst_with_compound(token_list);
		if (token_list == NULL)
			// break ;
		ft_fprintf(1, "post compound cmds:\n");
		llstiter(token_list, print_item);
		ft_fprintf(1, "_________________________\n");
		token_list = remove_blank(token_list);
		llstiter(token_list, print_item);
	// }
	llstclear(&token_list, free);
}
