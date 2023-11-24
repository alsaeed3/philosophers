# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/22 13:14:09 by alsaeed           #+#    #+#              #
#    Updated: 2023/10/22 13:47:10 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(NAME): all

all: 
	@make all -C srcs

clean:
	@make clean -C srcs

fclean: clean
	@make fclean -C srcs

re: fclean all