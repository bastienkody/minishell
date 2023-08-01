/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:51:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 16:00:17 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	main(int argc, __attribute__((unused))char **argv, char **envp)
// {
// 	char	*line;
// 	t_llist	*token_list;
// 	t_llist	*error;
// 	t_ntree	*ast;
// 	int		last_status;
// 	int		return_code;

// 	if (!argc || !envp)
// 		return (1);
// 	last_status = 0;
// 	while (TRUE)
// 	{
// 		line = NULL;
// 		return_code = read_command(&line);
// 		if (return_code == EOF)
// 			break ;
// 		if (return_code == LINE_EMPTY)
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		(token_list = tokenization(line), free(line));
// 		// ft_putendl_fd("-----------TOKEN LIST-----------", 1);
// 		// llstiter(token_list, (void (*)(void *))print_token);
// 		// ft_putendl_fd("", 1);
// 		return_code = expand_token_list(&token_list, envp, last_status);
// 		if (return_code == 0)
// 			exit(1);
// 		if (return_code == 42)
// 		{
// 			llstclear(&token_list, token_free));
// 			ft_fprintf(1, "%s\n", ERR_AMB_REDIR);
// 			continue ;
// 		}
// 		// ft_putendl_fd("-------TOKEN LIST EXPAND-------", 1);
// 		// llstiter(token_list, (void (*)(void *))print_token);
// 		// ft_putendl_fd("", 1);
// 		if (check_syntax != 0)
// 			continue ;
// 		(ast = parser(token_list), llstclear(&token_list, token_free)));
// 		if (ast == NULL)
// 			break ; // erreur de malloc
// 		manage_here_doc(ast, envp, last_status);
// 		manage_redir(ast, envp, last_status);
// 		manage_pipeline(ast, envp);
// 		// ft_putendl_fd("-----------AST-----------", 1);
// 		// ast_print(ast);
// 		// ft_putendl_fd("", 1);
// 		last_status = execute_ast(ast);
// 		ast_free(ast);
// 	}
// 	return (0);
// }

// void	reader_loop(char **envp)
// {
// 	int		last_status;
// 	int		return_code;
// 	char	*line;

// 	line = NULL;
// 	last_status = 0;
// 	while (1)
// 	{
// 		return_code = read_command(&line);
// 		if (return_code != 0)
// 		{
// 			free(line);
// 			if (return_code == EOF)
// 				break ;
// 			if (return_code == LINE_EMPTY)
// 				continue ;
// 		}
// 		add_history(line);
// 		return_code = interpret_command(line, envp, last_status);
// 		free(line);
// 		if (return_code == EXIT)
// 			break ;
// 		if (return_code == CONTINUE)
// 			continue ;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	((void)argc, (void)argv);
	reader_loop(envp, 0);
	return (0);
}
