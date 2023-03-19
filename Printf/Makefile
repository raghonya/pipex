NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

FILES = $(wildcard *.c)

OBJ = $(FILES:.c=.o)

ifeq ($(shell uname -s), MINGW64_NT-6.1-7601)
CC	=	gcc
endif

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	
clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
