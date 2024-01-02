# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/22 13:14:09 by alsaeed           #+#    #+#              #
#    Updated: 2024/01/01 18:44:42 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			../philo

SRCS =			check_utils.c clean_utils.c count_utils.c init_utils.c \
				main.c manipul_utils.c parse_utils.c philo_utils.c \
				print_utils.c time_utils.c trigger_utils.c

OBJS_DIR =		objs/
OBJS =			$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CFLAGS =		-Wall -Wextra -Werror -pthread -g3

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