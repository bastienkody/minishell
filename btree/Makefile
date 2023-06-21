# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 12:56:22 by aguyon            #+#    #+#              #
#    Updated: 2023/06/21 13:17:44 by aguyon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	btree_apply_by_level.c\
		btree_apply_infix.c\
		btree_apply_prefix.c\
		btree_apply_suffix.c\
		btree_create_node.c\
		btree_insert_data.c\
		btree_level_count.c\
		btree_search_item.c

OBJ =	$(SRC:.c=.o)

NAME =	libbtree.a

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
	@echo "\033[33mbtree obj cleaned\033[0m"

fclean:
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@echo "\033[33mbtree.a fcleaned\033[0m"

re:	fclean all

.PHONY:		all clean fclean re
