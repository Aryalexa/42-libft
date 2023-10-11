CC		= gcc
CFLAGS	= -Wall -Wextra -Werror $(FT_SAN)
# FT_SAN = -fsanitize=address
FT_SAN = 
AR		= ar -rcs
RM		= /bin/rm -rf

NAME	= libftprintf.a

SRCS	= ft_printf.c utils.c
OBJS	= $(SRCS:.c=.o)

LIBFT_PATH  = ./libft
LIBFT		= $(LIBFT_PATH)/libft.a

all:		$(NAME)

#$(NAME):	$(LIBFT) $(OBJS)
$(NAME):	$(LIBFT) $(OBJS)
			cp $(LIBFT) $(NAME)
			$(AR) $(NAME) $(OBJS)

bonus:		all

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

#$(LIBFT):	
#			make -C $(LIBFT_PATH) all

clean:
#			make -C $(LIBFT_PATH) clean
			$(RM) $(OBJS)

fclean:		clean
#			make -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
#.PHONY:		all clean fclean re libft