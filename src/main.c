/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/28 11:30:31 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_token_error(t_llist *llst)
{
	t_token	token = *(t_token *)llst;

	return (token.type == error);
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_llist *token_list;
	t_llist	*leaf_list;
	t_llist *error;
	t_ast	*ast;

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
		token_list = new_llst_with_compound(token_list);
		if (token_list == NULL)
			break ;
		llstremove_if(&token_list, (int(*)(void *))is_str_blank, free);
		ft_fprintf(1, "-------------------------------\n");
		ft_fprintf(1, "token_list (post compound n blank):\n");
		llstiter(token_list, print_item);
		token_list = type_token(token_list);
		ft_fprintf(1, "-------------------------------\n");
		ft_fprintf(1, "token_list (post typing): \n");
		llstiter(token_list, (void(*)(void *))print_token);
		error = llstfind_if(token_list, (int(*)(void *))is_token_error);
		if (error != NULL)
		{
			print_token_error(*(t_token *)error->content);
			break ;
		}
		if (!check_syntax(token_list))
		{
			printf("Syntax error !\n");
			break ;
		}
		leaf_list = token_to_leaf(token_list);
		(void)leaf_list;
		ast = create_complete_command(leaf_list);
		ft_fprintf(1, "-------------------------------\n");
		ft_fprintf(1, "astree :\n");
		print_ast_text(ast);
		expand_dollar_quotes_on_ast(ast, envp);
		ft_fprintf(1, "-------------------------------\n");
		ft_fprintf(1, "astree (post expansion) :\n");
		print_ast_text(ast);
	}
	llstclear(&token_list, free);
}
