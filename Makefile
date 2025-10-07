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
CFLAGS		=	-g -Wall -Wextra -Werror -Wunreachable-code
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
				philos_checks.c \
				philos_dinner.c \
				philos_event.c \
				philos_init.c \
				philos_main.c \
				philos_parse.c \
				philos_utils.c)

OBJ			=	$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.o, $(SRC))
DEPS		=	$(patsubst $(DIR_SRC)%.c, $(DIR_DEP)%.d, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJ)
	@echo "Build $(NAME) successfully!"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@) $(patsubst $(DIR_OBJ)%, $(DIR_DEP)%, $(dir $@))
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $@) $(INCS)
	@echo "compiling $@"

clean:
	@if [ -d "$(DIR_OBJ)" ]; then \
		rm -rf $(DIR_OBJ); \
		echo "removed $(DIR_OBJ)"; \
	fi

fclean: clean
	@if [ -d "$(DIR_DEP)" ]; then \
		rm -rf $(DIR_DEP); \
		echo "removed $(DIR_DEP)"; \
	fi
	@if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "removed $(NAME)"; \
	fi

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS) $(DEPS)

-include $(DEPS)
