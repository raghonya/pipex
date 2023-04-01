NAME	=	pipex

CFLAGS	=	# -Wall -Wextra -Werror

f		=	-fsanitize=address -g

DEP		=	Makefile pipex.h

FILES	=	pipex.c \
			parsing.c \
			

LIB		=	./libft

PLIB	=	./Printf

IFLAGS	=	-I$(LIB) -I$(PLIB) -I.

LFLAGS	=	-L$(PLIB) -lftprintf -L$(LIB) -lft

OBJS	=	$(FILES:.c=.o)

ifeq ($(shell uname -s), MINGW64_NT-6.1-7601)
CC	=	gcc
endif

all: libs $(NAME)

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) $(f) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(f) $(IFLAGS) $(LFLAGS) -o $(NAME)

clean: libs
	rm -f *.o

fclean: clean
	rm -f $(NAME)

libs:
	@$(MAKE) $(MAKECMDGOALS) -C $(LIB)
	@$(MAKE) $(MAKECMDGOALS) -C $(PLIB)

re:	fclean all

.PHONY: all clean fclean re run_libs