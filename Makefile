# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorros <gmorros@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 20:23:10 by gmorros           #+#    #+#              #
#    Updated: 2021/07/17 18:31:30 by gmorros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = prog

CC = clang++
SRC_TEST_DIR = tests/
SRC_DIR = ft_containers/
OBJ_DIR = obj/
INC_DIR = ft_containers/


SRC_FILES = tree.cpp
SRC_TEST_FILES = main.cpp \
			test_list.cpp \
			test_vector.cpp \
			test_deque.cpp \
			test_queue.cpp \
			test_stack.cpp \
			test_map.cpp \
			test_tree.cpp \
			test_set.cpp \
			test_multiset.cpp \
			test_multimap.cpp

OBJ_TEST_FILES = $(SRC_TEST_FILES:.cpp=.o)
OBJ_FILES = $(SRC_FILES:.cpp=.o)
DEP_TEST_FILES = $(SRC_TEST_FILES:.cpp=.d)
DEP_FILES = $(SRC_FILES:.cpp=.d)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES)) $(addprefix $(SRC_TEST_DIR), $(SRC_TEST_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES)) $(addprefix $(OBJ_DIR), $(OBJ_TEST_FILES))
DEP = $(addprefix $(OBJ_DIR), $(DEP_FILES)) $(addprefix $(OBJ_DIR), $(DEP_TEST_FILES))

INC = $(addprefix -I, $(INC_DIR)) 
CXX_FLAGS = -Wall -Werror -Wextra -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(INC) $(CXX_FLAGS) $^ -o $@ 

-include $(DEP)

list:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D LIST -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_list.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

list_print:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D LIST -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -D PRINT -c tests/test_list.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

vector:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D VECTOR -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_vector.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

vector_print:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D VECTOR -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -D PRINT -c tests/test_vector.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

deque:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D DEQUE -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_deque.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

deque_print:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D DEQUE -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -D PRINT -c tests/test_deque.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

queue:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D QUEUE -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_queue.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

queue_print:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D QUEUE -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -D PRINT -c tests/test_queue.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

stack:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D STACK -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_stack.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

stack_print:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D STACK -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -D PRINT -c tests/test_stack.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o -o tmp
	@./tmp
	@rm tmp

map:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D MAP -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_map.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) -c ft_containers/tree.cpp -o obj/tmp3.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o obj/tmp3.o -o tmp
	@./tmp
	@rm tmp

tree:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D TREE -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_tree.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) -c ft_containers/tree.cpp -o obj/tmp3.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o obj/tmp3.o -o tmp
	@./tmp
	@rm tmp

set:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D SET -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_set.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) -c ft_containers/tree.cpp -o obj/tmp3.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o obj/tmp3.o -o tmp
	@./tmp
	@rm tmp

multiset:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D MULTISET -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_multiset.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) -c ft_containers/tree.cpp -o obj/tmp3.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o obj/tmp3.o -o tmp
	@./tmp
	@rm tmp

multimap:
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D MULTIMAP -c tests/main.cpp -o obj/tmp1.o
	@$(CC) $(INC) $(CXX_FLAGS) -c tests/test_multimap.cpp -o obj/tmp2.o
	@$(CC) $(INC) $(CXX_FLAGS) -c ft_containers/tree.cpp -o obj/tmp3.o
	@$(CC) $(INC) $(CXX_FLAGS) obj/tmp1.o obj/tmp2.o obj/tmp3.o -o tmp
	@./tmp
	@rm tmp

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D LIST -D VECTOR -D DEQUE -D QUEUE -D STACK -D MAP -D SET -D MULTIMAP -D MULTISET -D TREE -c $< -o $@ -MMD

$(OBJ_DIR)%.o: $(SRC_TEST_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INC) $(CXX_FLAGS) -D LIST -D VECTOR -D DEQUE -D QUEUE -D STACK -D MAP -D SET -D MULTIMAP -D MULTISET -D TREE -c $< -o $@ -MMD

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re 
