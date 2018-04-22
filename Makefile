# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mploux <mploux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/06 18:10:48 by mploux            #+#    #+#              #
#    Updated: 2018/04/22 02:04:16 by mploux           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
CC = gcc
FILES =\
graphics/mesh.c\
graphics/models/model.c\
graphics/display.c\
graphics/texture.c\
graphics/shaders/shader.c\
graphics/shaders/uniforms.c\
inputs/keyboard.c\
inputs/mouse.c\
inputs/input.c\
core.c\
error.c\
utils/buffers.c\
maths/projection.c\
maths/mat4.c\
maths/maths.c\
maths/vec2.c\
maths/vec3.c\
maths/vec4.c\
maths/transform.c\
main.c

SRC = srcs/
DIRS = bin

SYSTEM = $(shell uname -s)

WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m

OBJS = $(addprefix bin/,$(FILES:.c=.o))
HDRS = $(addprefix bin/,$(FILES:.c=.d))

LIBFT = deps/libft/libft.a
GLFW = deps/glfw/build/src/libglfw3.a
GLEW = deps/glew/build/cmake/build/lib/libGLEW.a

DEPS = -L deps/libft -L deps/glfw/build/src/ -L deps/glew/build/cmake/build/lib/
INCLUDES = -I includes/ -I deps/libft/ -I deps/glfw/include/ -I deps/glew/include/

# ifeq (SYSTEM, Darwin)
	# DEPSFLAGS = -lft -lglfw3 -lGLEW -framework Cocoa -framework OpenGL\
	# 			-framework IOKit -framework CoreVideo
# else
	DEPSFLAGS = -lft -lglfw3 -lGL -lm -lGLU -lGLEW -lXrandr -lXi -lX11\
				-lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lrt
# endif

CFLAGS = -Wall -Wextra -pedantic -g
FLAGS = $(CFLAGS) $(INCLUDES)

MKDIR = mkdir -p
RMDIR = rm -rf
RM = rm -rf

.PHONY: all clean clean-libs fclean-libs fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(GLFW) $(GLEW) $(DIRS) $(OBJS)
	@printf "\r$(GREEN)Compiling sources: DONE !                      $(NO_COLOR)\n";
	@printf "Building objects...\r"
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(DEPS) $(DEPSFLAGS)
	@printf "\r$(GREEN)Building objects: DONE !$(NO_COLOR)\n";
	@printf "\n$(GREEN)Building done: $(GREEN_BG)$(NAME)$(NO_COLOR)\n"

$(DIRS):
	@$(MKDIR) $(dir $(OBJS))

bin/%.o: srcs/%.c
	@printf "\rCompiling sources: $^                          \r";
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $^ -o $@

$(LIBFT):
	@printf "Building libFT...\r"
	@make -C deps/libft > /dev/null
	@printf "\r$(GREEN)Building libFT: DONE !$(NO_COLOR)\n";

$(GLFW):
	@printf "Building libGLFW...\r"
	@$(MKDIR) deps/glfw/build > /dev/null
	@cd deps/glfw/build && cmake .. > /dev/null
	@make -C deps/glfw/build/ > /dev/null
	@printf "\r$(GREEN)Building libGLFW: DONE !$(NO_COLOR)\n";

$(GLEW):
	@printf "Building libGLEW...\r"
	@$(MKDIR) deps/glew/build/cmake/build > /dev/null
	@cd deps/glew/build/cmake/build && cmake .. > /dev/null
	@make -C deps/glew/build/cmake/build > /dev/null
	@rm -rf deps/glew/build/cmake/build/lib/*.dylib
	@rm -rf deps/glew/build/cmake/build/lib/libGLEW.so.2.1.0
	@printf "\r$(GREEN)Building libGLEW: DONE !$(NO_COLOR)\n";

clean:
	@printf "Cleaning objects..."
	@$(RMDIR) bin
	@printf "\r$(GREEN)Cleaning objects: DONE !$(NO_COLOR)\n";

clean-libs: clean
	@printf "Cleaning libFT..."
	@$(RMDIR) deps/libft/bin
	@printf "\r$(GREEN)Cleaning libFT: DONE !$(NO_COLOR)\n";

	@printf "Cleaning libGLFW..."
	@$(RMDIR) deps/glfw/build
	@printf "\r$(GREEN)Cleaning libGLFW: DONE !$(NO_COLOR)\n";

	@printf "Cleaning libGLEW..."
	@$(RMDIR) deps/glew/build/cmake/build
	@printf "\r$(GREEN)Cleaning libGLEW: DONE !$(NO_COLOR)\n";

fclean: clean clean-libs
	@$(RM) $(NAME)

fclean-src: clean
	@$(RM) $(NAME)

re: fclean-src all

re-libs: fclean all

-include $(HDRS)
