# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 10:45:33 by gdetourn          #+#    #+#              #
#    Updated: 2024/01/24 21:45:32 by gwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CFLAGS	= -Wall -Wextra -Werror
CC		= cc

BONUS 	= pipex_bonus

SRC_1	= 	ft_printf_pi.c \
			ft_split.c \
			ft_str.c \
			ft_strjoin.c \
			init.c \
			pipex.c \

SRC_BONUS	= 	ft_printf_pi.c \
				ft_split.c \
				ft_str.c \
				ft_strjoin.c \
				get_next_line.c \
				heredoc_bonus.c \
				init_bonus.c \
				pipex_bonus.c \

OBJ_1		= $(SRC_1:.c=.o)
OBJ_BONUS	= $(SRC_BONUS:.c=.o)

all : $(NAME) $(BONUS)

$(NAME): $(OBJ_1)
	$(CC) $(CFLAGS) $(OBJ_1) -o $(NAME)

$(BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS)

clean:
		rm -rf $(OBJ_1) $(OBJ_BONUS)

fclean: clean
		rm -rf $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus