/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/21 13:25:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_llist *token_list;
	t_btree	*ast;

	(void)argv;
	if (!argc || !envp)
		return (1);
	while (TRUE)
	{
	  line = readline("minishell prompt % ");
	  add_history(line);
	  token_list = lsttok(line);
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
	  llstremove_if(&token_list, (int(*)(void *))is_str_blank, free);
	  llstiter(token_list, print_item);
	  ast = create_tree(token_list);
	  (void)ast;
  }
	llstclear(&token_list, free);
}
