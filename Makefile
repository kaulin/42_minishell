# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:32:02 by kkauhane          #+#    #+#              #
#    Updated: 2024/09/09 14:11:21 by jajuntti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General
NAME		:= minishell
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g #-fsanitize=address

# Sources
SRC_DIR		:= srcs/
MAIN_SRC	:= main.c \
			error.c \
			cmd_list.c \
			data.c \
			signal.c \
			paths.c \
			execute.c \
			exec_utils.c \
			redirection.c \
			redir_list.c \
			heredocs.c \
			utils.c \
			var_list.c \
			var_list_edits.c \
			var_list_utils.c
#
BINS_DIR	:= $(SRC_DIR)builtins/
BINS_SRC	:= check_builtins.c \
			cd.c \
			echo.c \
			env.c \
			exit.c \
			export.c \
			pwd.c \
			unset.c
#
PARSER_DIR	:= $(SRC_DIR)parser/
PARSER_SRC	:= parser.c \
			parser_utils.c \
			expander.c \
			expander_utils.c \
			str_list.c \
			token_list.c \
			token_utils.c \
			splitjoin.c \
			tokenizer.c
#
VPATH		+= $(SRC_DIR):$(BINS_DIR):$(PARSER_DIR)

# Objects
BUILD_DIR	:= build/
OBJ			:= $(MAIN_SRC:.c=.o) $(BINS_SRC:.c=.o) $(PARSER_SRC:.c=.o)
OBJS		:= $(addprefix $(BUILD_DIR), $(OBJ)) 

# Libraries & headers
RL_DIR := ~/.brew/opt/readline# Hardcoded for now
INCS		+= -I $(RL_DIR)/include
LIBS		+= -L $(RL_DIR)/lib
#
LIBFT_DIR	:= libft/
LIBFT		:= libft.a
LIBFT_PATH	:= $(LIBFT_DIR)$(LIBFT)
#
INCS		+= -I inc/ -I $(LIBFT_DIR)

# Links executable TODO: Add -lft
all: $(NAME)
$(NAME): $(LIBFT_PATH) $(BUILD_DIR) $(OBJS)
	@printf "Linking executable\n"
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) $(LIBS) $(LIBFT_PATH) -lreadline -o $@
	@printf "Done\n"

# Runs make in the libft directory
$(LIBFT_PATH): $(LIBFT)
$(LIBFT):
	@printf "Making libft\n"
	@make -C $(LIBFT_DIR)

# Make build directory for objects
$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

# Compile object files from sources, recompile also on Makefile changes
$(BUILD_DIR)%.o: %.c Makefile
	@printf "Compiling: $(notdir $<)\n"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Remove object files
clean:
	@printf "Performing clean\n"
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean

# Remove program and created libraries
fclean: clean
	@printf "Performing full clean\n"
	@rm -rf $(NAME)
	@rm -rf $(LIBFT_PATH)

re: fclean all

.PHONY: all, clean, fclean, re, libft