NAME		=	libftprintf.a

SRCS		=	ft_printf.c

OBJS		=	${patsubst %.c,%.o,${SRCS}}

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

LIB			=	ar -rcs

RM			=	rm -rf

all: ${NAME}

${NAME}: Makefile ft_printf.c ft_printf.h
		$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS) -I.
		${LIB} ${NAME} ${OBJS}

re: fclean all

clean:
		@${RM} ${OBJS}

fclean: clean
		@${RM} ${NAME}

.PHONY: all re clean fclean