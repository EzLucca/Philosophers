# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 14:15:40 by edlucca           #+#    #+#              #
#    Updated: 2025/09/16 14:16:49 by edlucca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Wunreachable-code -O3
LFLAGS		=	-pthread
MAKEFLAGS	+=	--no-print-directory
RM			=	rm -rf

DIR_INC		=	inc/
DIR_SRC		=	src/
DIR_OBJ		=	obj/
DIR_DEP		=	dep/

INCS		=$(addprefix -I , \
				$(DIR_INC))
SRC			=	$(addprefix $(DIR_SRC), \
				main.c \
				parse.c \
				utils.c)

OBJ			=	$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.o, $(SRC))
DEPS		=	$(patsubst $(DIR_SRC)%.c, $(DIR_DEP)%.d, $(SRC))

GREEN		=	\033[1;32m
RED			=	\033[1;31m
YELLOW		=	\033[1;33m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJ)
	@echo "Build $(GREEN)$(NAME) successfully!"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@) $(patsubst $(DIR_OBJ)%, $(DIR_DEP)%, $(dir $@))
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $@) $(INCS)
	@echo "$(GREEN) + $(COLOR) compiling $@"

clean:
	@if [ -d "$(DIR_OBJ)" ]; then \
		rm -rf $(DIR_OBJ); \
		echo "$(RED) - $(COLOR) removed $(DIR_OBJ)"; \
	fi

fclean: clean
	@if [ -d "$(DIR_DEP)" ]; then \
		rm -rf $(DIR_DEP); \
		echo "$(RED) - $(COLOR) removed $(DIR_DEP)"; \
	fi
	@if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(RED) - $(COLOR) removed $(NAME)"; \
	fi

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS) $(DEPS)

-include $(DEPS)
