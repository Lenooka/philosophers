NAME = philo
CC = cc
SRC = main.c init_argc.c atoi_check.c set_table.c exit_message.c action_utils.c check_arg.c forks_action.c meal_action.c monitors.c mutex_utils.c sim_start.c simulation.c
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
OBJ_D = obj
OBJS = $(OBJ_D)/main.o $(OBJ_D)/init_arg.o $(OBJ_D)/atoi_check.o $(OBJ_D)/set_table.o $(OBJ_D)/exit_message.o $(OBJ_D)/action_utils.o \
$(OBJ_D)/check_arg.o $(OBJ_D)/forks_action.o  $(OBJ_D)/meal_action.o $(OBJ_D)/monitors.o $(OBJ_D)/mutex_utils.o $(OBJ_D)/sim_start.o  $(OBJ_D)/simulation.o
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

all: $(NAME)


$(OBJ_D)/%.o: %.c | $(OBJ_D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiling...$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)Compiled successfully!$(RESET)"

$(OBJ_D):
	@mkdir -p $(OBJ_D)

clean:
	@$(RM) $(OBJ_D)
	@echo "$(RED)Cleaning... $(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Fcleaning... $(RESET)"

re: fclean all

.PHONY: all clean fclean re