NAME	= philo
SRC		= main.c utils.c
CC		= @cc
CFLAGS	= -Wall -Werror -Wextra -g -lpthread

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) $(CFLAGS) $(^) -o $(@) -fsanitize=address
#$(CC) $(CFLAGS) $(^) -o $(@) -fsanitize=thread

clean:
			@rm -f *.o

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re