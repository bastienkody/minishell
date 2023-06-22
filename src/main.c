/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/21 21:56:54 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_token_error(t_llist *llst)
{
	t_token	token = *(t_token *)llst;

	return (token.type == error);
}

void	print_token_error(t_token token)
{
	ft_fprintf(1, "syntax error near unexpected token : %s\n", token.text);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_llist *token_list;
	t_btree	*ast;
	t_llist *error;

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
		token_list = type_token(token_list);
		llstiter(token_list, (void(*)(void *))print_token);
		error = llstfind_if(token_list, (int(*)(void *))is_token_error);
		if (error != NULL)
			print_token_error(*(t_token *)error->content);
	//   ast = create_tree(token_list);
	  (void)ast;
  }
	llstclear(&token_list, free);
}
