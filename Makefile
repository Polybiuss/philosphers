NAME = philo

SRC = philo.c \
	parsing.c \
	utils.c \
	init.c \
	monitor.c \
	routine.c \
	threads.c \

OBJ_DIR = obj

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
GREEN = \033[0;32m
CYAN = \033[;36m
RESET = \033[0m
GRAY = \033[90m

SUCCESS = $(GREEN)[SUCCESS]$(RESET)
INFO = $(CYAN)[INFO]$(RESET)

all : $(NAME)

$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then \
		echo "$(INFO) create $(OBJ_DIR).....$(GRAY)"; \
		mkdir -p $(OBJ_DIR); \
		echo "$(SUCCESS) $(OBJ_DIR) done !"; \
	fi

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -pthread -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re