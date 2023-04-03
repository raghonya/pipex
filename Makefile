NAME	=	pipex

CFLAGS	=	 #-Wall -Wextra -Werror

f		=	#-fsanitize=address -g

DEP		=	Makefile pipex.h

FILES	=	pipex.c \
			paths.c \
			childs.c \
			here_doc.c \
			

LIB		=	./libft

PLIB	=	./Printf

IFLAGS	=	-I$(LIB) -I$(PLIB) -I.

LFLAGS	=	-L$(PLIB) -lftprintf -L$(LIB) -lft

OBJS	=	$(FILES:.c=.o)

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

.PHONY: all clean fclean re libs