NAME	=	pipex

CFLAGS	=	-Wall -Wextra -Werror

f		=	-fsanitize=address -g

DEP		=	Makefile pipex.h

FILES	=	pipex.c \
			paths.c \
			childs.c \
			here_doc.c \
			expand.c \
			expand_funcs.c \
			close_and_free.c 

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
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

libs:
	@echo "Helper libs"
	@$(MAKE) $(MAKECMDGOALS) -C $(LIB)
	@$(MAKE) $(MAKECMDGOALS) -C $(PLIB)

re:	fclean all

.PHONY: all clean fclean re libs