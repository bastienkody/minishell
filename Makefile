# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 10:02:31 by aguyon            #+#    #+#              #
#    Updated: 2023/06/28 14:02:07 by aguyon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = ./inc/minishell.h

SRC_DIR = ./src/

SRCS_NAME =	main.c\
			lsttok.c\
			compound_cmd.c\
			printers.c\
			tree_printers.c\
			type_token.c\
			parsing_test.c\
			utils/token_utils.c\
			utils/strjoin.c\
			utils/lsttok_utils.c\
			utils/ft_realloc.c\
			redirection/redirector.c\
			redirection/here_doc.c\
			expansion/basics_expansion.c\
			utils/type_token_utils1.c\
			utils/type_token_utils2.c\
			expansion/utils_expansion.c\
			expansion/dollar_expander.c\
			token_to_leafs.c \
			new_ast.c \
			create_child.c \
			create_complete_command.c \
			create_logical_expression.c \
			create_pipeline.c \
			create_command.c \
			create_redirection.c \
			create_prefixes.c \
			create_suffixes.c \
			utils/parsing_utils.c \
			check_syntax.c \
			free_ast.c

SRCS = 	$(addprefix ${SRC_DIR}, ${SRCS_NAME})

OBJS =	${SRCS:.c=.o}

NAME =	minishell

LIBFT = ./libft/libft.a

LLST = ./llist/libllst.a

BTREE = ./btree/libbtree.a

NTREE = ./ntree/libntree.a

CC =	cc

CFLAGSDEV =	-Wall -Wextra -Werror -g3

CFLAGS =	-Wall -Wextra -Werror

LDFLAGS =	-L./libft -lft -L./llist -lllst -L./btree -lbtree -L./ntree -lntree -lreadline

.c.o:
		@echo "\033[32m\c"
		${CC} ${CFLAGSDEV} -c $< -o ${<:.c=.o}
		@echo "\033[0m\c"

all:	${NAME}

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

re:		fclean all

noob: ${NAME} clean

.PHONY:	all clean re noob
