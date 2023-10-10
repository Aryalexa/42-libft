NAME = test
SRC = test.c

all:	$(NAME)

$(NAME):
	$(MAKE) -C .. all
	cp ../libftprintf.a $(NAME)
	gcc $(SRC) $(NAME)

clean:
	$(MAKE) -C .. clean

fclean: clean
	rm -rf a.out $(NAME)

re: fclean
	$(MAKE) all