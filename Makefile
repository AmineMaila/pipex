# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/24 17:21:21 by mmaila            #+#    #+#              #
#    Updated: 2023/12/27 16:09:24 by mmaila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
FLAGS= -Wall -Werror -Wextra

OBJS= exit.o main.o command.o here_doc.o srcs/libft/ft_put_fd.o srcs/libft/ft_split.o srcs/libft/ft_strcmp.o srcs/libft/ft_strjoin.o srcs/libft/ft_strlcpy.o srcs/libft/ft_strncmp.o srcs/get_next_line/get_next_line.o srcs/get_next_line/get_next_line_utils.o

NAME= pipex

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c Includes/pipex.h
	$(CC) $(FLAGS) -c $< -o $@ -g

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all