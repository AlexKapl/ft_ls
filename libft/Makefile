# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/29 11:15:59 by akaplyar          #+#    #+#              #
#    Updated: 2017/04/30 16:31:49 by akaplyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = $(PRINTF_PATH)ft_printf.h stack_queue/stack_queue.h libft.h

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

PRINTF_PATH = ./ft_printf/

vpath %.c $(PRINTF_PATH)

vpath %.h $(PRINTF_PATH) stack_queue/


OBJECT = ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o\
		 ft_memcpy.o ft_memcmp.o ft_memchr.o ft_memmove.o ft_memset.o ft_memccpy.o\
		 ft_strcat.o ft_strchr.o ft_strcpy.o ft_strlcat.o ft_strdup.o ft_strlen.o\
		 ft_strncpy.o ft_strnstr.o ft_strstr.o ft_strrchr.o ft_strstr.o ft_strcmp.o\
		 ft_strncmp.o ft_toupper.o ft_tolower.o ft_atoi.o ft_strncat.o ft_memalloc.o\
		 ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o\
		 ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o\
		 ft_strtrim.o ft_strsplit.o ft_putchar.o ft_putstr.o ft_putnbr.o ft_putendl.o\
		 ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o\
		 ft_lstnew.o ft_lstadd.o ft_lstmap.o ft_lstiter.o ft_lstdelone.o\
		 ft_lstdel.o ft_isspace.o ft_realloc.o ft_abs.o ft_int_sort.o ft_strrev.o\
		 ft_lst_push_back.o get_next_line.o ft_lstcount.o ft_strcapitalizer.o\
		 ft_atoi_base.o hsv.o hsv_colors.o ft_llitoa.o ft_lst_sort.o ft_strconcat.o\
		 ft_dir_path.o ft_tabdel.o ft_tabcount.o ft_lstnew_struct.o\
		 stack_queue/stack.o stack_queue/queue.o


P_OBJECT = ft_printf.o help_int.o parse_int.o parse_str.o finder.o type_finder.o\
			helper.o parse_wstr.o parse_brackets.o

P_OBJ = $(addprefix $(PRINTF_PATH),$(P_OBJECT))

.PHONY: clean fclean re

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJECT) $(P_OBJ)
	@ar rcs $(NAME) $(OBJECT) $(P_OBJ) $(HEADER)
	@ranlib $(NAME)
	@echo "\x1B[32m\0lib_created\x1B[0m\0"

clean:
	@rm -rf $(OBJECT) $(P_OBJ)
	@echo "\x1B[31m\0objects cleared\x1B[0m\0"

fclean: clean
	@rm -rf $(NAME)
	@echo "\x1B[31m\0lib deleted\x1B[0m\0"

re: fclean all
