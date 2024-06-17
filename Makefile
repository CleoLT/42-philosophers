NAME	= philo

CC		= gcc
RMF		= rm -f
RMD		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -pthread -g -fsanitize=thread 
DEPFLAG	= -MMD -MP
INCLUDE	= -I./inc
MKDIR	= mkdir -p

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = philo init utils execute

SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS	= $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c Makefile
				$(MKDIR) $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INCLUDE) $(DEPFLAG) -c -o $@ $<

clean:
		$(RMD) $(OBJ_DIR)

fclean:	clean
		$(RMF) $(NAME)

re:		fclean all

-include $(DEPS)
.PHONY: all clean fclean re
