# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/22 13:14:09 by alsaeed           #+#    #+#              #
#    Updated: 2023/11/26 19:51:21 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			../philo

SRCS =			main.c philo_utils.c parse_utils1.c parse_utils2.c \
				parse_utils3.c ft_split.c time_utils.c trigger_utils.c

OBJS_DIR =		objs/
OBJS =			$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CFLAGS =		-Wall -Wextra -Werror -pthread

all:			$(NAME)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@cc $(CFLAGS) -c $< -o $@

$(NAME): 		$(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "philosophers Compilation: \033[1;32mOK\n\033[0m"

norm:
	norminette

clean:
	@if [ -e $(OBJS_DIR) ]; then \
		rm -rf $(OBJS_DIR); \
		echo "philosophers Clean: \033[32mOK\n\033[0m"; \
	fi

fclean: 		clean
	@if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo "philosophers Full-Clean: \033[32mOK\n\033[0m"; \
	fi

re: 			fclean all

.PHONY: 		all clean fclean re

# VALGRIND TEST FLAGS:
#	1) valgrind --tool=helgrind ./philo x y z
#	2) valgrind --tool=helgrind --tool=drd ./philo x y z
#	3) valgrind ./philo x y z for mem leaks
#	4) valgrind --tool=helgrind --history-level=none  ./philo x y z