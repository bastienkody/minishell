/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/03 10:54:41 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_token_error(t_llist *llst)
{
	const t_token	token = *(t_token *)llst;

	return (token.type == error);
}

void	print_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ft_fprintf(1, "%s\n", type_to_string(ast->type));
	if (ast->type > 0 && ast->type < 9)
		ft_fprintf(1, ": %s\n", (char *)ast->data);
	llstiter(ast->children, (void (*)(void *))print_ast);
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
		add_history(line);
		token_list = lexer(line);
		if (token_list == NULL)
			return (1);
		error = llstfind_if(token_list, (int(*)(void *))is_token_error);
		if (error != NULL)
		{
			print_token_error(*(t_token *)error->content);
			break ;
		}
		if (!check_syntax(token_list))
		{
			ft_fprintf(1, "Syntax error !\n");
			break ;
		}
		ast = parser(token_list);
		if (ast == NULL)
			return (1);
		ntree_free(ast);
	}
}

// int	main(int argc, __attribute__((unused))char **argv, char **envp)
// {
// 	char	*line;
// 	t_llist	*token_list;
// 	t_llist	*error;
// 	t_ast	*ast;

// 	if (!argc || !envp)
// 		return (1);
// 	line = readline("minishell prompt % ");
// 	add_history(line);
// 	token_list = lexer(line);
// 	if (token_list == NULL)
// 		return (1);
// 	error = llstfind_if(token_list, (int (*)(void *))is_token_error);
// 	if (error != NULL)
// 		return (print_token_error(*(t_token *)error->content), 1);
// 	if (!check_syntax(token_list))
// 		return (printf("Syntax error !\n"), 1);
// 	ast = parser(token_list);
// 	if (ast == NULL)
// 		return (1);
// 	free_ast(ast);
// }
