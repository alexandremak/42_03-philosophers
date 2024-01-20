# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amak <amak@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 18:44:03 by amak              #+#    #+#              #
#    Updated: 2024/01/19 22:05:53 by amak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc -g

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

INC = -I ./inc/

SRC_PATH = src/

OBJ_PATH = obj/

SRC_FILES = main.c \
			check_parse.c \
			table.c \
			utils.c \
			get_set.c \
			synchro.c \
			write.c \
			monitor.c \
			dinner.c

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
	@echo Deleted objected files!

fclean: clean
	@rm -f $(NAME)
	@echo Deleted executable!
	
re: fclean all

.PHONY: all clean fclean re
