SRC =	ft_isalnum.c \
		ft_isprint.c \
		ft_memcpy.c \
		ft_putendl_fd.c \
		ft_strchr.c \
		ft_strlcpy.c \
		ft_strrchr.c \
		ft_strspn.c \
		ft_toupper.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_itoa.c \
		ft_memmove.c \
		ft_putnbr_fd.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strtrim.c \
		ft_bzero.c \
		ft_isascii.c \
		ft_memchr.c \
		ft_memset.c \
		ft_putstr_fd.c \
		ft_strjoin.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_substr.c \
		ft_calloc.c \
		ft_isdigit.c \
		ft_memcmp.c \
		ft_putchar_fd.c \
		ft_split.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_tolower.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		ft_fprintf/ft_fprintf.c \
		ft_fprintf/ft_fprintf_printer.c \
		ft_fprintf/ft_fprintf_hexa.c \
		ft_fprintf/ft_fprintf_utils.c\
		free_matrix/free_int_matrix.c\
		free_matrix/free_char_matrix.c\

OBJ =		${SRC:.c=.o}

NAME =		libft.a

CC =		cc

CFLAGS =	-Wall -Wextra -Werror

CFLAGSDEV = -Wall -Wextra -Werror -g3

.c.o:
		@${CC} ${CFLAGSDEV} -c $< -o ${<:.c=.o}

${NAME}:	${OBJ}
		@ar rcs ${NAME} ${OBJ}

all:		${NAME}

clean:
		@rm -rf ${OBJ}
		@echo "\033[33mlibft obj cleaned\033[0m"

fclean:
		@rm -rf ${OBJ}
		@rm -rf ${NAME}
		@echo "\033[33mlibft.a fcleaned\033[0m"

re:		fclean all

.PHONY:		all clean fclean re
