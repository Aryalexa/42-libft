NAME = test
SRC = test.c
LIB = ../libftprintf.a
OTHER_OBJ = ../ft_printf.o ../util_cs.o ../util_general.o ../util_numflags.o ../util_print1.o ../util_print2.o

all:	$(NAME)

$(NAME): $(SRC) $(LIB) $(OTHER_OBJ)
		$(MAKE) -C .. all
		cp $(LIB) $(NAME)
#		gcc  $(SRC) $(NAME) 
#		gcc -Wall -Werror -Wextra $(SRC) $(NAME) 
		gcc -Wall -Werror -Wextra -fsanitize=address -g3 $(SRC) $(NAME) 

$(LIB):
		$(MAKE) -C .. all

clean:
		$(MAKE) -C .. clean

fclean: clean
		rm -rf a.out $(NAME)

re: 	fclean
		$(MAKE) all