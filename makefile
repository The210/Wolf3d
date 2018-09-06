# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smerelo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/30 18:18:49 by smerelo           #+#    #+#              #
#    Updated: 2018/09/04 23:23:47 by dhorvill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = wolf

CFLAGS = -Wall -Werror -Wextra

SRCS = wolf3d.c get_next_line.c init_vars.c events.c collision.c SDLpixels.c trace_ray.c render_frame.c secret.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME):
		make -C libft
			gcc -o $(NAME) $(SRCS) -Ilibft libft/libft.a -Iinclude -L lib -l SDL2-2.0.0
clean:
		make clean -C libft
			rm -f $(OBJS)

fclean: clean
		rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re
