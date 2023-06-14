# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 15:10:26 by aguyon            #+#    #+#              #
#    Updated: 2023/06/14 15:38:15 by aguyon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	llstadd_after.c \
		llstadd_back.c \
		llstadd_before.c \
		llstadd_front.c \
		llstall_of.c \
		llstany_of.c \
		llstclear.c \
		llstcomp.c \
		llstdelone.c \
		llstempty.c \
		llstfind.c \
		llstfirst.c \
		llstiter.c \
		llstlast.c \
		llstmap.c \
		llstmax.c \
		llstmin.c \
		llstncomp.c \
		llstnew.c \
		llstnext.c \
		llstnone_of.c \
		llstprev.c \
		llstrange_map.c \
		llstrange_remove.c \
		llstremoveone.c \
		llstsize.c \

SRC_TEST =	main_test.c

OBJ =	$(SRC:.c=.o)

NAME =	libllist.a

CC =	cc

CFLAGS =	-Wall -Wextra -Werror

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
		ar rcs $(NAME) $(OBJ)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re:	fclean all

.PHONY:		all clean fclean re