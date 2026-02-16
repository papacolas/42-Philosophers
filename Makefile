# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 16:41:08 by ncrivell          #+#    #+#              #
#    Updated: 2025/05/19 20:35:09 by ncrivell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -Iincludes

BLUE = \033[34m
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

SRC = 	src/main.c \
		src/utils.c \
		src/parsing.c \
		src/time.c \
		src/routine.c \
		src/init.c \
		src/init_mutex.c \
		src/threads.c \
		src/monitoring.c \
		src/monito_check.c \
		src/routine_sub_functions.c \
		src/cleaning.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(OBJS) -o $(NAME) || (echo "$(RED)Compilation error !$(RESET)" && exit 1)
		@echo "$(GREEN)--------------------------------------------------$(RESET)"
		@echo "$(GREEN)The program has successfully compiled! Now Enjoy !$(RESET)"
		@echo "$(GREEN)--------------------------------------------------$(RESET)"

%.o: %.c
		@echo "$(BLUE)compiling$(RESET)  :  $<"
		@$(CC) $(CFLAGS) -c $< -o $@ || (echo "$(RED)--------------------------------\n    /!\ Error compiling /!\ \n-------------------------------- $<$(RESET)" && exit 1)

clean:
	@echo "$(BLUE)~~~~~~~~Cleaning object files...~~~~~~~~$(RESET)"
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@echo "$(BLUE)~~~~~~~~Cleaning executable...~~~~~~~~$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)---------------------------$(RESET)"
	@echo "$(GREEN)Project completely cleaned!$(RESET)"
	@echo "$(GREEN)---------------------------$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
