##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile
##

SRC	=	src/main.c
SRC	+=	./src/panoramix.c
SRC	+=	./src/parser/parse_flag.c


OBJ	=	$(SRC:.c=.o)

NAME	=	panoramix

CC	=	gcc -g3

CFLAGS	=	-W -Wall -Wextra -Wpedantic

CPPFLAGS	=	-I include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

debug: fclean $(OBJ)
	@$(CC) -g3 -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

.PHONY:	clean fclean re all
