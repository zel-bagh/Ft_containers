COMPILER = c++
FLAGS = --std=c++98 -Wall -Wextra -Werror
SRC = main.cpp
NAME = simple_test

all: $(NAME)

$(NAME) : $(SRC)
	@$(COMPILER) $(SRC) $(FLAGS) -o $@

clean:
	@rm -rf simple_test

fclean: clean
re: fclean all