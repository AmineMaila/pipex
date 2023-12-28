# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/24 17:21:21 by mmaila            #+#    #+#              #
#    Updated: 2023/12/28 16:56:13 by mmaila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
FLAGS= -Wall -Werror -Wextra

OBJS= exit.o main.o command.o here_doc.o srcs/utils/ft_put_fd.o srcs/utils/ft_split.o \
		srcs/utils/ft_strcmp.o srcs/utils/ft_strjoin.o srcs/utils/ft_strlcpy.o srcs/utils/ft_strncmp.o \
		srcs/utils/ft_putendl_fd.o srcs/get_next_line/get_next_line.o srcs/get_next_line/get_next_line_utils.o

NAME= pipex

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c Includes/pipex.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all