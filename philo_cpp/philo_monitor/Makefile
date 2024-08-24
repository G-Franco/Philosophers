# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/24 09:44:07 by gacorrei          #+#    #+#              #
#    Updated: 2024/08/24 09:52:49 by gacorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo
DEBUG =	philo_debug
SRC =	main.cpp
CC =	@c++
CFLAGS = -Wall -Wextra -Werror -pedantic -Wshadow
CFLAGS_D = -Wall -Wextra -Werror -pedantic -Wshadow -fno-limit-debug-info -g -fsanitize=address

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) $(CFLAGS) $^ -o $@

debug:		$(DEBUG)

$(DEBUG):	$(SRC)
			$(CC) $(CFLAGS_D) $^ -o $@

fclean:
			@rm -f $(NAME)

re:			fclean all

.PHONY: all fclean re