# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danierod <danierod@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 16:26:20 by danierod          #+#    #+#              #
#    Updated: 2023/05/10 11:52:54 by danierod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH = ./

CC = cc

RM = rm -rf

SOURCES = ./main.c ./utils.c ./ignition.c

OBJECTS = $(SOURCES:.c=.o)

%.o:		%.c
			$(CC) -c $^ -o $@

all: $(NAME)
	
%.o: %.c
	@$(CC)  -Wall -Wextra -Werror  -c $< -o $@ 

$(NAME): $(OBJECTS)
	-@$(CC) $(OBJECTS) -o $(NAME) -lpthread
	
clean:
	$(RM) $(OBJECTS)
	clear

fclean:	clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re