# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 19:43:05 by lboulang          #+#    #+#              #
#    Updated: 2023/10/24 22:59:22 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	cub3D

SRCS_NAMES 		=	main.c\
					error.c\
					map_parsing.c\
					parsing.c

LIBFT			=	libft.a

MLX				= 	libmlx.a

MLX_LINUX		= 	libmlx_Linux.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft -Imlx -Imlx_linux

LIB				=	-Llibft -lft -Lminilibx-linux

CC				=	cc

CDFLAGS 		= -MMD -MP

CFLAGS			=	-g3 -Wall -Werror -Wextra

MAKEFLAGS		=	--no-print-directory

MLX_FLAGS =	-lm -lmlx -lXext -lX11

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) ${INC} $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[31;5mcub3D\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	make clean -C libft
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${NAME}


re:	fclean all

# -include $(DEPS)

.PHONY:	all clean fclean re 