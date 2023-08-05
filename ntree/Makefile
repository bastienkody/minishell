# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 15:53:05 by aguyon            #+#    #+#              #
#    Updated: 2023/08/05 16:35:17 by aguyon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ntree_free.c\
		ntree_new.c\
		ntree_dup.c\
		ntree_print.c\

OBJ =	$(SRC:.c=.o)

NAME =	libntree.a

CC =	cc

CFLAGS =	-Wall -Wextra -Werror

CFLAGSDEV = -Wall -Wextra -Werror -g3

.c.o:
	@$(CC) $(CFLAGSDEV) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
		@ar rcs $(NAME) $(OBJ)

all:	$(NAME)

clean:
	@rm -rf $(OBJ)
	@echo "\033[33mntree obj cleaned\033[0m"

fclean:
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@echo "\033[33mntree.a fcleaned\033[0m"

re:	fclean all

.PHONY:		all clean fclean re