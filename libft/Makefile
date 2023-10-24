# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:31:43 by lboulang          #+#    #+#              #
#    Updated: 2023/07/10 14:58:25 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME =	libft.a
#SOURCES
SRCS =	ft_atoi_itoa.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_len.c\
		ft_lst1.c\
		ft_lst2.c\
		ft_mem.c\
		ft_put_fd.c\
		ft_put.c\
		ft_split.c\
		ft_str_operation.c\
		ft_strchr.c\
		ft_strl.c\
		ft_strn.c\
		ft_strtrim.c\
		ft_free_tab.c\
		./ft_printf/ft_printf.c\
		./ft_printf/printf_text.c\
		./ft_printf/printf_nbr.c\
#OBJECTS
OBJ = $(SRCS:.c=.o)
#COMPILER
CC = @ gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I.
#VISUAL
BOLD_TEXT = \033[1m
RESET_TEXT = \033[0m

$(NAME):$(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(BOLD_TEXT)LIBFT$(RESET_TEXT) MAKED ✅\n"

all: $(NAME)

clean : 
	@rm -f $(OBJ)
	@echo "$(BOLD_TEXT)LIBFT$(RESET_TEXT) CLEANED 🚮\n"

fclean : clean
	@rm -f $(NAME)
	@echo "$(BOLD_TEXT)LIBFT$(RESET_TEXT) FCLEANED 🚮\n"

re : fclean $(NAME)

.PHONY : all clean fclean re