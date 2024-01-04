# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amak <amak@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 02:26:01 by amak              #+#    #+#              #
#    Updated: 2024/01/04 22:31:48 by amak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = cc -g

CFLAGS = -Wall -Wextra -Werror -pthread

INC = -I ./inc/

SRC_PATH = src/
OBJ_PATH = obj/

SRC_FILES = main.c \
			utils.c \
			parsing.c \
			init.c \
			safe_functions.c \
			getters_setters.c \
			print_table.c \
			synchro_utils.c \
			write.c \
			simulation.c \
			monitor.c
			
SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
			
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)


all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo Object files created!
	@echo Executable file created!
	
clean:
	@rm -rf $(OBJ_PATH)
	@echo Deleted object files!

fclean: clean
		@rm -f $(NAME)
		@echo Deleted executable!

re: fclean all

.PHONY: all clean fclean re
