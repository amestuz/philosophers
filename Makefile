# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 20:26:12 by uurbizu-          #+#    #+#              #
#    Updated: 2024/04/19 20:21:47 by uurbizu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Projects
NAME = philo

# Compiler
CC = cc
CFLAGS = -Wall  -Wextra -Werror  -pthread #-fsanitize=address -fsanitize=thread -g 
MAKE = make

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = inc

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) 
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES)) 

#.SILENT: esto para quitar los @

# all
all: $(NAME)

$(NAME): $(OBJ_FILES) 
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<
	@echo "$(NAME): $(GREEN)$@ object file created$(RESET)"

# clean
clean:
	@rm -r -f $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

# fclean
fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

# re	
re: fclean all

.PHONY: all clean fclean re
