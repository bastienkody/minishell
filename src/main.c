/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/18 19:49:17 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_token_error(t_llist *llst)
{
	t_token	token = *(t_token *)llst;

	return (token.type == error);
}

void	print_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	printf("%s\n", type_to_string(ast->type));
	if (ast->type > 0 && ast->type < 9)
		printf(": %s\n", (char *)ast->data);
	llstiter(ast->children, (void (*)(void *))print_ast);
}

t_llist	*lexer(const char *line)
{
	t_llist *token_list;
	t_llist *temp;

	token_list = lsttok(line);
	if (token_list == NULL)
		return (NULL);
	temp = new_llst_with_compound(token_list);
	llstclear(&token_list, free);
	if (temp == NULL)
		return (NULL);
	token_list = temp;
	llstremove_if(&token_list, (int(*)(void *))is_str_blank, free);
	temp = type_token(token_list);
	llstclear(&token_list, free);
	if (temp == NULL)
		return (NULL);
	token_list = temp;
	return (token_list);
}

t_ast	*parser(t_llist	*token_list)
{
	t_llist	*leaf_list;
	t_ast	*ast;

	leaf_list = token_to_leaf(token_list);
	if (leaf_list == NULL)
		return (NULL);
	llstclear(&token_list, (void (*)(void *))free_token);
	ast = create_complete_command(leaf_list);
	if (ast == NULL)
		return (NULL);
	// free(leaf_list);
	ft_fprintf(1, "-------------------------------\n");
	ft_fprintf(1, "astree :\n");
	print_tree(ast);
	// print_ast_full(ast);
	// ft_fprintf(1, "-------------------------------\n");
	// ft_fprintf(1, "expansion :\n");
	// expand_dollar_quotes_on_aest(ast, envp);
	// ft_fprintf(1, "-------------------------------\n");
	// ft_fprintf(1, "astree (post expansion) :\n");
	// print_ast_full(ast);
	return (ast);
}

int	main(int argc, __attribute__((unused))char **argv, char **envp)
{
	char	*line;
	t_llist	*token_list;
	t_llist	*error;
	t_ast	*ast;

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
			printf("Syntax error !\n");
			break ;
		}
		ast = parser(token_list);
		if (ast == NULL)
			return (1);
		free_ast(ast);
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
// 	error = llstfind_if(token_list, (int(*)(void *))is_token_error);
// 	if (error != NULL)
// 		return (print_token_error(*(t_token *)error->content), 1);
// 	if (!check_syntax(token_list))
// 		return (printf("Syntax error !\n"), 1);
// 	ast = parser(token_list);
// 	if (ast == NULL)
// 		return (1);
// 	free_ast(ast);
// }