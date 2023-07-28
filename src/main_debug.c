/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:51:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/28 12:04:51 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int	is_token_error(t_llist *llst)
// {
// 	const t_token	token = *(t_token *)llst;

// 	return (token.type == error);
// }

// int	main(int argc, __attribute__((unused))char **argv, char **envp)
// {
// 	char	*line;
// 	t_llist	*token_list;
// 	t_llist	*error;
// 	t_ntree	*ast;
// 	int		last_status;

// 	if (!argc || !envp)
// 		return (1);
// 	last_status = 0;
// 	while (TRUE)
// 	{
// 		line = readline("minishell prompt % ");
// 		if (line == NULL)
// 			exit(1);
// 		if (is_str_blank(line))
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		token_list = lexer(line);
// 		free(line);
// 		line = NULL;
// 		ft_putendl_fd("-----------TOKEN LIST-----------", 1);
// 		llstiter(token_list, (void (*)(void *))print_token);
// 		ft_putendl_fd("", 1);
// 		if (token_list == NULL)
// 			exit(EXIT_FAILURE); // erreur de malloc
// 		error = llstfind_if(token_list, (t_predicate)is_token_error);
// 		if (error != NULL)
// 		{
// 			print_token_error(*(t_token *)error->content);
// 			continue ;
// 		}
// 		if (!check_syntax(token_list))
// 		{
// 			printf("Syntax error !\n");
// 			continue ;
// 		}
// 		ast = parser(token_list);
// 		if (ast == NULL)
// 			exit(EXIT_FAILURE); // erreur de malloc
// 		manage_dollar_expansion(ast, envp, last_status);
// 		manage_quote_remove(ast);
// 		manage_here_doc(ast, envp, last_status);
// 		manage_redir(ast, envp, last_status);
// 		manage_pipeline(ast, envp);
// 		ft_putendl_fd("-----------AST-----------", 1);
// 		ast_print(ast);
// 		ft_putendl_fd("", 1);
// 		last_status = execute_ast(ast);
// 		ast_free(ast);
// 	}
// }