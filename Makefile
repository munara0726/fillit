# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iklimov <iklimov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 18:14:59 by iklimov           #+#    #+#              #
#    Updated: 2019/12/06 20:07:37 by iklimov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
CFLG = -Wextra -Wall -Werror
SRCS = fillit.c error.c reader.c


.PHONY: all clean fclean re

all: $(NAME)
		make -C libft
		gcc -g -o $(NAME) $(CFLG) $(SRCS)

clean:	make -C libft clean

fclean: rm -f $(NAME)
		make -C libft fclean

re:	make -C libft fclean
	all
