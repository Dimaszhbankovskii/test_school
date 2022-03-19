NAME		=	micro_paint

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

$(RM)		=	rm -rf

SRCS		=	micro_paint.c

all : $(NAME)

$(NAME) : Makefile $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

fclean :
	$(RM) $(NAME)

.PHONY : all fclean