FT_PRINTF	=	ft_printf

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

all: $(FT_PRINTF)

$(FT_PRINTF) : ft_printf.c main.c Makefile
	$(CC) $(CFLAGS) ft_printf.c main.c -o $(FT_PRINTF) -I.

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(FT_PRINTF)

re : fclean all

.PHONY : all clean fclean re