# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 19:43:05 by lboulang          #+#    #+#              #
#    Updated: 2023/11/07 18:56:31 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	cub3D

SRCS_NAMES 		=	assets_parsing.c\
					cub_parsing.c\
					error.c\
					gnl.c\
					main.c\
					map_parsing.c\
					parsing.c\
					utils.c\
					exec_main.c \
					exec_init.c \
					exec_utils.c \
					exec_utils2.c \
					exec_movement.c \
					exec_define_wallx.c \
					exec_free.c \
					exec_do_calc.c \
					exec_key.c \

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
	$(CC) $(CFLAGS) $(OBJS) ${INC} minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -L. -lXext -lX11 -lm $(LIB) -o $(NAME)
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