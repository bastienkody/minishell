###		SOURCE FILES	###
HEADER		=	./inc/minishell.h

BUILT_DIR	=	builtins/
EXECU_DIR	=	execution/
XPAND_DIR	=	expansion/
REDIR_DIR	=	redirection/
TOKEN_DIR	=	token/
TREE_DIR	=	tree/
UTILS_DIR	=	utils/
MAIN_DIR	=	./
SRC_DIR		=	./src/

BUILT_NAME	=	builtin_basics.c\
				builtin_check.c\
				pwd.c\
				export.c\
				unset.c\
				echo.c\
				env.c\
				exit.c\
				cd.c

EXECU_NAME	=	execution_basics.c

XPAND_NAME	=	utils_expansion.c\
				basics_expansion.c\
				dollar_expander.c\
				quote_removal.c\
				main_expansion.c

REDIR_NAME	=	redirector.c\
				here_doc.c

TOKEN_NAME	=	type_token.c\
				lsttok.c\
				parsing_test.c\
				compound_cmd.c\
				check_syntax.c

TREE_NAME	=	new_ast.c\
				new_ast_child.c\
				free_ast.c\
				token_to_leafs.c\
				tree_printers.c\
				create_complete_command.c\
				create_compound_command.c\
				create_logical_expression.c\
				create_pipeline.c\
				create_command.c\
				create_prefixes.c\
				create_suffixes.c\
				create_redirection.c\
				create_child.c

UTILS_NAME	=	ft_realloc.c\
				strjoin.c\
				printers.c\
				print_env.c\
				print_err_msg.c\
				lsttok_utils.c\
				parsing_utils.c\
				token_utils.c\
				type_token_utils1.c\
				type_token_utils2.c\
				charmatrix_dup.c

MAIN_NAME	=	main_test.c

BUILT_SRC	=	$(addprefix ${BUILT_DIR}, ${BUILT_NAME})
EXECU_SRC	=	$(addprefix ${EXECU_DIR}, ${EXECU_NAME})
XPAND_SRC	=	$(addprefix ${XPAND_DIR}, ${XPAND_NAME})
REDIR_SRC	=	$(addprefix ${REDIR_DIR}, ${REDIR_NAME})
TOKEN_SRC	=	$(addprefix ${TOKEN_DIR}, ${TOKEN_NAME})
TREE_SRC	=	$(addprefix ${TREE_DIR}, ${TREE_NAME})
UTILS_SRC	=	$(addprefix ${UTILS_DIR}, ${UTILS_NAME})
MAIN_SRC	=	$(addprefix ${MAIN_DIR}, ${MAIN_NAME})

SRCS_NAME	=	${EXECU_SRC} ${XPAND_SRC} ${REDIR_SRC}  ${TOKEN_SRC}\
				${TREE_SRC} ${UTILS_SRC} ${MAIN_SRC} ${BUILT_SRC}

SRCS		=	$(addprefix ${SRC_DIR}, ${SRCS_NAME})
OBJS		=	${SRCS:.c=.o}


###		DEFINITIONS		###
NAME		=	minishell

LIBFT		=	./libft/libft.a
LLST		=	./llist/libllst.a
BTREE		=	./btree/libbtree.a
NTREE		=	./ntree/libntree.a

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror
CFLAGSDEV	=	-Wall -Wextra -Werror -g3

LDFLAGS		=	-L./libft -lft -L./llist -lllst -L./btree -lbtree\
				-L./ntree -lntree -lreadline


###		RULES		###
.c.o:
			@echo "\033[32m\c"
			${CC} ${CFLAGSDEV} -c $< -o ${<:.c=.o}
			@echo "\033[0m\c"

all:		${NAME}

${NAME}:	${OBJS} ${HEADER} ${LIBFT} ${LLST} ${BTREE} ${NTREE}
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

${BTREE}:
			@echo "\033[33mbtree compilation ...\033[0m"
			@make --no-print-directory -C btree/
			@echo "\033[33mbtree compiled\033[0m"

${NTREE}:
			@echo "\033[33mntree compilation ...\033[0m"
			@make --no-print-directory -C ntree/
			@echo "\033[33mntree compiled\033[0m"

clean:
			@rm -rf ${OBJS}
			@echo "\033[32m${NAME} obj cleaned"
			@make --no-print-directory clean -C libft/
			@make --no-print-directory clean -C llist/
			@make --no-print-directory clean -C btree/
			@make --no-print-directory clean -C ntree/

fclean:		clean
			@rm -rf ${NAME}
			@echo "\033[32m${NAME} fcleaned"
			@make --no-print-directory fclean -C libft/
			@make --no-print-directory fclean -C llist/
			@make --no-print-directory fclean -C btree/
			@make --no-print-directory fclean -C ntree/

re:			fclean all

noob: 		${NAME} clean

.PHONY:		all clean re noob
