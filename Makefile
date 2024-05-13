# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:32:02 by kkauhane          #+#    #+#              #
#    Updated: 2024/05/13 11:11:47 by jajuntti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Check if readline library is installed on Linux or Mac, if not show message
CURRENT_OS := $(uname -s)
ifeq ($(CURRENT_OS), Linux)
check_readline:
	@test -f /usr/include/readline/readline.h || { echo "Readline library \ 
		not found. Please install it using the following command:"; \
		echo "sudo apt-get install make libreadline-dev"; \
		exit 1; }
check_newline:
	@test -f /usr/include/freetype/freetype.h || { echo "Freetype library \ 
		not found. Please install it."; \
		exit 1; }		
else ifeq ($(CURRENT_OS), Darwin)
	READLINE_DIR := $(shell if [ -d ~/.brew/opt/readline ]; then \
		echo ~/.brew/opt/readline; \
		else if [ -d /usr/local/opt/readline ]; \
		then echo /usr/local/opt/readline; \
		else echo "Readline library not found. Please install it via"; \
			echo "brew install readline"; \
			exit 1; \
		fi; fi)
	INCS += -I $(READLINE_DIR)/include
	LIBS += -L $(READLINE_DIR)/lib
endif

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address

SRC_DIR		:= srcs/
SRC			:= main.c
SRCS		:= $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR		:= objs/
OBJ			:= $(SRC:.c=.o)
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJ))

LIBFT_DIR	:= libft/
LIBFT		:= libft.a
LIBFT_PATH	:= $(LIBFT_DIR)$(LIBFT)

INCS		+= -I inc/ -I $(LIBFT_DIR)

all: $(NAME)

# TODO: Add -lft
$(NAME): $(LIBFT_PATH) $(OBJ_DIR) $(OBJS)
	@printf "Linking\n"
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) $(LIBS) $(LIBFT_PATH) -lreadline -o $@

$(LIBFT_PATH): $(LIBFT)
$(LIBFT):	
	@printf "Making libft\n" && make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS) && printf "Compiling: $(notdir $<)\n"

clean:
	@printf "Performing clean\n"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@printf "Performing full clean\n"
	@rm -rf $(NAME)
	@rm -rf $(LIBFT_PATH)

re: fclean all

.PHONY: all, clean, fclean, re, libft