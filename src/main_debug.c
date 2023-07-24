/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:51:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/24 15:10:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_token_error(t_llist *llst)
{
	const t_token	token = *(t_token *)llst;

	return (token.type == error);
}

int	main(int argc, __attribute__((unused))char **argv, char **envp)
{
	char	*line;
	t_llist	*token_list;
	t_llist	*error;
	t_ntree	*ast;

	if (!argc || !envp)
		return (1);
	while (TRUE)
	{
		line = readline("minishell prompt % ");
		if (line == NULL)
			exit(1);
		add_history(line);
		token_list = lexer(line);
		ft_putendl_fd("-----------TOKEN LIST-----------", 1);
		llstiter(token_list, (void (*)(void *))print_token);
		ft_putendl_fd("", 1);
		if (token_list == NULL)
			exit(EXIT_FAILURE); // erreur de malloc
		error = llstfind_if(token_list, (t_predicate)is_token_error);
		if (error != NULL)
		{
			print_token_error(*(t_token *)error->content);
			continue ;
		}
		if (!check_syntax(token_list))
		{
			printf("Syntax error !\n");
			continue ;
		}
		ast = parser(token_list);
		if (ast == NULL)
			exit(EXIT_FAILURE); // erreur de malloc
		// ast_print(ast);
		manage_here_doc(ast, envp);
		manage_redir(ast, envp);
		ft_putendl_fd("-----------AST-----------", 1);
		ast_print(ast);
		ft_putendl_fd("", 1);
		ast_free(ast);
	}
}