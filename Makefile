# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 15:32:02 by kkauhane          #+#    #+#              #
#    Updated: 2024/05/16 13:53:01 by jajuntti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General
NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address

# Sources
SRC_DIR	:= srcs/
MAIN_SRC	:= main.c \
			cmd_list.c \
			data.c \
			signal.c
MAIN_SRCS	:= $(addprefix $(SRC_DIR), $(MAIN_SRC))
#
BI_DIR		:= $(SRC_DIR)builtins/
BI_SRC		:= cd.c \
			echo.c \
			env.c \
			exit.c \
			export.c \
			pwd.c \
			unset.c
BI_SRCS		:= $(addprefix $(BI_DIR), $(BI_SRC))
#
PARSER_DIR	:= $(SRC_DIR)parser/
PARSER_SRC	:= parser.c \
			parsers_utils.c
PARSER_SRCS	:= $(addprefix $(PARSER_DIR), $(PARSER_SRC))
#
VPATH		+= $(SRC_DIR):$(BI_DIR):$(PARSER_DIR)

# Objects
BUILD_DIR	:= build/
MAIN_OBJS	:= $(addprefix $(OBJ_DIR), $(MAIN_SRC:.c=.o))
BI_OBJS		:= $(addprefix $(OBJ_DIR), $(BI_SRC:.c=.o))
PARSER_OBJS	:= $(addprefix $(OBJ_DIR), $(PARSER_SRC:.c=.o))
OBJS		:= $(MAIN_OBJS) $(BI_OBJS) $(PARSER_OBJS)

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

# Links executablle TODO: Add -lft
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

# Make objs directory
$(BUILD_DIR):
	@mkdir $(BUILD_DIR)
	echo $(OBJS)

# Compile object files from sources, recompile also on Makefile changes
%.o: %.c Makefile
	@printf "Compiling: $(notdir $<)\n"
	$(CC) $(CFLAGS) $(INCS) -c $< -o $(BUILD_DIR)$@

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