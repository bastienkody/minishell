/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/13 15:12:23 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_item(void *item)
{
	ft_putendl_fd((char *)item ,1);
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
		printf("--> %s\n", line);
		token_list = lsttok(line, DELIM);
		if (token_list == NULL)
			break ;
		llstiter(token_list, print_item);
		free(line);
		//token_list = lexing()
	}
	llstclear(&token_list, free);
}
