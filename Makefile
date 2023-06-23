HEADER = ./inc/minishell.h

SRC_DIR = ./src/

SRCS_NAME =	main.c\
			lsttok.c\
			compound_cmd.c\
			printers.c\
			utils/token_utils.c\
			utils/strjoin.c\
			utils/lsttok_utils.c\
			type_token.c\
			utils/type_token_utils1.c\
			utils/type_token_utils2.c\
			parsing_test.c

SRCS = 	$(addprefix ${SRC_DIR}, ${SRCS_NAME})

OBJS =	${SRCS:.c=.o}

NAME =	minishell

LIBFT = ./libft/libft.a

LLST = ./llist/libllst.a

BTREE = ./btree/libbtree.a

CC =	cc

CFLAGSDEV =	-Wall -Wextra -Werror -g3

CFLAGS =	-Wall -Wextra -Werror

LDFLAGS =	-L./libft -lft -L./llist -lllst -L./btree -lbtree -lreadline

.c.o:
		@echo "\033[32m\c"
		${CC} ${CFLAGSDEV} -c $< -o ${<:.c=.o}
		@echo "\033[0m\c"

all:	${NAME}

${NAME}:	${OBJS} ${HEADER} ${LIBFT} ${LLST} ${BTREE}
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
			@echo "\033[33mllst compilation ...\033[0m"
			@make --no-print-directory -C btree/
			@echo "\033[33mllst.a compiled\033[0m"

clean:
		@rm -rf ${OBJS}
		@echo "\033[32m${NAME} obj cleaned"
		@make --no-print-directory clean -C libft/
		@make --no-print-directory clean -C llist/
		@make --no-print-directory clean -C btree/

fclean:		clean
		@rm -rf ${NAME}
		@echo "\033[32m${NAME} fcleaned"
		@make --no-print-directory fclean -C libft/
		@make --no-print-directory fclean -C llist/
		@make --no-print-directory fclean -C btree/

re:		fclean all

noob: ${NAME} clean

.PHONY:	all clean re noob
