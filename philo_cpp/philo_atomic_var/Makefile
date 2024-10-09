# Project
NAME =	philo
DEBUG =	philo_debug
DEBUG_T =	philo_debug_thread
SRC =	src/main.cpp src/Philo.cpp src/philo_helper.cpp
CC =	@g++
CFLAGS = -Wall -Wextra -Werror -pedantic -Wshadow -std=c++11
CFLAGS_D = -Wall -Wextra -Werror -pedantic -Wshadow -g -std=c++11 -fsanitize=address,undefined
CFLAGS_T = -Wall -Wextra -Werror -pedantic -Wshadow -g -std=c++11 -fsanitize=thread

# Tests
TEST =	philo_test
TEST_SRC =	tests/test.cpp
GTEST_DIR =	../../googletest/googletest
GTEST_SRC =	$(GTEST_DIR)/src/gtest-all.cc
GTEST_HEADERS =	$(GTEST_DIR)/include $(GTEST_DIR)
CFLAGS_TEST =	-I$(GTEST_HEADERS) -pthread

all:			$(NAME)

$(NAME):	$(SRC)
					$(CC) $(CFLAGS) $^ -o $@

debug:		$(DEBUG)

$(DEBUG):	$(SRC)
					$(CC) $(CFLAGS_D) $^ -o $@

debug_t:	$(DEBUG_T)

$(DEBUG_T):	$(SRC)
					$(CC) $(CFLAGS_T) $^ -o $@

test:	$(TEST)

$(TEST):	$(SRC) $(TEST_SRC) $(GTEST_SRC)
					$(CC) $(CFLAGS) $(CFLAGS_TEST) $^ -o $@

fclean:
					@rm -f $(NAME) $(DEBUG) $(DEBUG_T)

re:				fclean all

.PHONY: all debug debug_t test fclean re