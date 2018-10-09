# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smerelo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 19:57:28 by smerelo           #+#    #+#              #
#    Updated: 2018/09/30 20:46:59 by smerelo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CFLAGS = -Wall -Werror -Wextra

SRCS = wolf3d.c get_next_line.c init_vars.c events.c collision.c sdlpixels.c trace_ray.c render_frame.c secret.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft
			gcc -o $(NAME) $(OBJS) -Ilibft libft/libft.a -Iinclude -L lib -l SDL2-2.0.0 -g
clean:
		make clean -C libft
			rm -f $(OBJS)

fclean: clean
		rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re
