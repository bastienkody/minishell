# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 15:10:26 by aguyon            #+#    #+#              #
#    Updated: 2023/06/15 12:56:50 by aguyon           ###   ########.fr        #
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
		llstextract.c\
		llstextract_range.c\
		llstfind_if.c \
		llstfind.c \
		llstfirst.c \
		llstfold.c \
		llstiter.c \
		llstlast.c \
		llstmap_range.c \
		llstmap.c \
		llstmax.c \
		llstmin.c \
		llstncomp.c \
		llstnew.c \
		llstnext.c \
		llstnone_of.c \
		llstprev.c \
		llstremove_range.c \
		llstremoveone.c \
		llstsize.c \

SRC_TEST =	main_test.c

OBJ =	$(SRC:.c=.o)

NAME =	libllst.a

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
	@echo "\033[33mllst obj cleaned\033[0m"

fclean:
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@echo "\033[33mllst.a fcleaned\033[0m"

re:	fclean all

.PHONY:		all clean fclean re
