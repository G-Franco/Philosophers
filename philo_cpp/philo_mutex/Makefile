NAME =	philo
DEBUG =	philo_debug
DEBUG_T =	philo_debug_thread
SRC =	src/main.cpp src/Philo.cpp
CC =	@g++
CFLAGS = -Wall -Wextra -Werror -pedantic -Wshadow -std=c++11
CFLAGS_D = -Wall -Wextra -Werror -pedantic -Wshadow -g -std=c++11 -fsanitize=address,undefined
CFLAGS_T = -Wall -Wextra -Werror -pedantic -Wshadow -g -std=c++11 -fsanitize=thread

all:			$(NAME)

$(NAME):	$(SRC)
					$(CC) $(CFLAGS) $^ -o $@

debug:		$(DEBUG)

$(DEBUG):	$(SRC)
					$(CC) $(CFLAGS_D) $^ -o $@

debug_t:	$(DEBUG_T)

$(DEBUG_T):	$(SRC)
					$(CC) $(CFLAGS_T) $^ -o $@

fclean:
					@rm -f $(NAME) $(DEBUG) $(DEBUG_T)

re:				fclean all

.PHONY: all debug debug_t fclean re