# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2024/05/27 14:03:14 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CC = cc
CFLAGS = -g -pthread -Werror -Wextra -Wall -pedantic -I$(HEADER_DIR)

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH) $(MLX_PATH) $(HEADERS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I/usr/include -I$(HEADER_DIR) -O3 -c $< -o $@

clean:
	@echo "Removing all object files"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Removing all object files and executable"
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
