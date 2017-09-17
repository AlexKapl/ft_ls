# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/29 11:15:59 by akaplyar          #+#    #+#              #
#    Updated: 2017/04/18 19:45:36 by akaplyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = ft_ls.h
LIB_PATH = ./libft/

CC = @gcc
CFLAGS = -Wall -Wextra -Werror
MAKE_LIB = $(MAKE) -C $(LIB_PATH)

.PHONY: clean fclean re

SRC = main.c ls_print.c ls_process.c ls_sort.c\
		ls_memory.c ls_utils.c ls_flags.c ls_long_info.c
OBJ = $(SRC:.c=.o)

NAME = ft_ls

all:  lib $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -I $(HEADER) $(LIB_PATH)libft.a
	@echo "\x1B[32m\0ft_ls created\x1B[0m\0"

.c.o:
	@printf "\x1B[32m\0Compile %s\x1B[0m\0\n" $<
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

lib:
	$(MAKE_LIB)

clean:
	$(MAKE_LIB) clean
	@rm -rf $(OBJ)
	@echo "\x1B[31m\0ft_ls objects cleared\x1B[0m\0"

fclean: clean
	$(MAKE_LIB) fclean
	@rm -rf $(NAME)
	@echo "\x1B[31m\0ft_ls deleted\x1B[0m\0"

re: fclean all
