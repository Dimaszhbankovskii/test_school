NAME		=	mini_paint

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
MATH_FLAGS	=	-lm

$(RM)		=	rm -rf

SRCS		=	mini_paint.c

all : $(NAME)

$(NAME) : Makefile $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(MATH_FLAGS)

fclean :
	$(RM) $(NAME)

.PHONY : all fclean