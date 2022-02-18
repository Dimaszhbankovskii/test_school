GNL		=	gnl

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -D BUFFER_SIZE=10

all: $(GNL)

$(GNL) : get_next_line.c get_next_line.h main.c Makefile
	$(CC) $(CFLAGS) get_next_line.c main.c -o $(GNL) -I.

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(GNL)

re : fclean all

.PHONY : all clean fclean re