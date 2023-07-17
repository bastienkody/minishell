/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/17 09:30:02 by aguyon           ###   ########.fr       */
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

const char *type_to_string(t_type type)
{
	return (g_type_str[type]);
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

	token_list = lsttok(line);
	if (token_list == NULL)
		return (NULL);
	// llstiter(token_list, print_item);
	token_list = new_llst_with_compound(token_list);
	if (token_list == NULL)
		return (NULL);
	// ft_fprintf(1, "post compound cmds:\n");
	// llstiter(token_list, print_item);
	// ft_fprintf(1, "_________________________\n");
	llstremove_if(&token_list, (int(*)(void *))is_str_blank, free);
	// llstiter(token_list, print_item);
	token_list = type_token(token_list);
	// llstiter(token_list, (void(*)(void *))print_token);
	return (token_list);
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
		token_list = lexer(line);
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
		print_ast_full(ast);
		ft_fprintf(1, "-------------------------------\n");
		ft_fprintf(1, "expansion :\n");
		expand_dollar_quotes_on_ast(ast, envp);
		ft_fprintf(1, "-------------------------------\n");
		ft_fprintf(1, "astree (post expansion) :\n");
		print_ast_full(ast);
	}
	llstclear(&token_list, free);
}
