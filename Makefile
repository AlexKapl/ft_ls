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

LIB_HEADER = $(LIB_PATH)libft.h

CC = @gcc

LIB_PATH = ./libft/

CFLAGS = -Wall -Wextra -Werror

MAKE_LIB = $(MAKE) -C $(LIB_PATH)

OBJ = main.o ls_print.o ls_process.o ls_sort.o ls_utils.o

.PHONY: clean fclean re

NAME = ft_ls

all:  lib $(OBJ) $(NAME)

$(NAME):
	$(CC) -o $(NAME) $(OBJ) -I $(HEADER) $(LIB_PATH)libft.a
	@echo "\x1B[32m\0ft_ls created\x1B[0m\0"

$(OBJ): $(HEADER)

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
