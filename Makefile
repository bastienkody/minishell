###		SOURCE FILES	###
HEADER		=	./inc/minishell.h

BUILD_DIR	=	./build
BUILT_DIR	=	builtins/
EXECU_DIR	=	execution/
XPAND_DIR	=	expansion/
REDIR_DIR	=	redirection/
TOKEN_DIR	=	token/
AST_DIR		=	ast/
UTILS_DIR	=	utils/
MAIN_DIR	=	./
SRC_DIR		=	./src/
OTHER_DIR	=	./

BUILT_NAME	=	builtin_basics.c\
				builtin_check.c\
				pwd.c\
				export.c\
				unset.c\
				echo.c\
				env.c\
				exit.c\
				cd.c

EXECU_NAME	=	execution_basics.c\
				pipe_execution.c\
				execute_ast.c\
				execute_ast_utils.c

XPAND_NAME	=	utils_expansion.c\
				basics_expansion.c\
				dollar_expander.c\
				quote_removal.c\
				wildcard.c\
				wildcard_match.c\
				wildcard_utils.c\

REDIR_NAME	=	redirector.c\
				redirector_utils.c\
				here_doc.c

TOKEN_NAME	=	type_token.c\
				lsttok.c\
				compound_cmd.c\
				check_syntax.c

AST_NAME	=	ast_new.c\
				ast_print.c\
				ast_free.c\
				ast_predicate.c\
				ast_predicate_utils.c\
				token_to_leaf.c\
				create_complete_command.c\
				create_compound_command.c\
				create_logical_expression.c\
				create_pipeline.c\
				create_command.c\
				create_prefixes.c\
				create_suffixes.c\
				create_redirection.c\
				create_classic_redirection.c\
				create_here_doc.c\
				create_child.c\
				utils.c\

UTILS_NAME	=	ft_realloc.c\
				strjoin.c\
				printers.c\
				print_env.c\
				print_err_msg.c\
				lsttok_utils.c\
				parsing_utils.c\
				token_utils.c\
				str_predicate1.c\
				str_predicate2.c\
				str_predicate3.c\
				free_token.c\
				token_predicate1.c\
				token_predicate2.c\
				create_command_utils.c\
				charmatrix_dup.c

OTHER_NAME =	parser.c\
				lexer.c\
				manage_pipeline.c\
				manage_dollar_expansion.c\
				manage_quote_remove.c\
				pipex_info.c\
				pipex_info_utils1.c\
				pipex_info_utils2.c\
				pipex_cmd.c\
				expand_token_list.c\

MAIN_NAME	=	main_debug.c

BUILT_SRC	=	$(addprefix ${BUILT_DIR}, ${BUILT_NAME})
EXECU_SRC	=	$(addprefix ${EXECU_DIR}, ${EXECU_NAME})
XPAND_SRC	=	$(addprefix ${XPAND_DIR}, ${XPAND_NAME})
REDIR_SRC	=	$(addprefix ${REDIR_DIR}, ${REDIR_NAME})
TOKEN_SRC	=	$(addprefix ${TOKEN_DIR}, ${TOKEN_NAME})
AST_SRC		=	$(addprefix ${AST_DIR}, ${AST_NAME})
UTILS_SRC	=	$(addprefix ${UTILS_DIR}, ${UTILS_NAME})
MAIN_SRC	=	$(addprefix ${MAIN_DIR}, ${MAIN_NAME})
OTHER_SRC	=	$(addprefix ${OTHER_DIR}, ${OTHER_NAME})

SRCS_NAME	=	${BUILT_SRC} ${EXECU_SRC} ${XPAND_SRC} ${REDIR_SRC}  ${TOKEN_SRC}\
				${AST_SRC} ${UTILS_SRC} ${MAIN_SRC} ${OTHER_SRC}

SRCS		=	$(addprefix ${SRC_DIR}, ${SRCS_NAME})
OBJS		=	${SRCS:.c=.o}


###		DEFINITIONS		###
NAME		=	minishell

LIBFT		=	./libft/libft.a
LLST		=	./llist/libllst.a
NTREE		=	./ntree/libntree.a

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror
CFLAGSDEV	=	-Wall -Wextra -Werror -g3

LDFLAGS		=	-L./libft -lft -L./llist -lllst -L./ntree -lntree -lreadline

###		RULES		###
.c.o:
			@echo "\033[32m\c"
			${CC} ${CFLAGSDEV} -c $< -o ${<:.c=.o}
			@echo "\033[0m\c"

all:		${NAME}


${NAME}:	${OBJS} ${HEADER} ${LIBFT} ${LLST} ${NTREE}
			@echo "\033[32m\c"
			${CC} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo "Link complete for exec --> \033[4;36;1m${NAME}\033[0m"

${LIBFT}:
			@echo "\033[33mlibft compilation ...\033[0m"
			@make --no-print-directory -C libft/
			@echo "\033[33mlibft compiled\033[0m"

${LLST}:
			@echo "\033[33mllst compilation ...\033[0m"
			@make --no-print-directory -C llist/
			@echo "\033[33mllst.a compiled\033[0m"

${NTREE}:
			@echo "\033[33mntree compilation ...\033[0m"
			@make --no-print-directory -C ntree/
			@echo "\033[33mntree.a compiled\033[0m"

clean:
			@rm -rf ${OBJS}
			@echo "\033[32m${NAME} obj cleaned"
			@make --no-print-directory clean -C libft/
			@make --no-print-directory clean -C llist/
			@make --no-print-directory clean -C ntree/


fclean:		clean
			@rm -rf ${NAME}
			@echo "\033[32m${NAME} fcleaned"
			@make --no-print-directory fclean -C libft/
			@make --no-print-directory fclean -C llist/
			@make --no-print-directory fclean -C ntree/

re:			fclean all

noob: 		${NAME} clean

.PHONY:		all clean re noob
