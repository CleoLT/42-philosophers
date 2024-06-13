NAME	= philo

CC		= gcc
RMF		= rm -f
RMD		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
DEPFLAG	= -MMD -MP
INCLUDE	= -I./inc
MKDIR	= mkdir -p

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = philo utils

SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS	= $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS):	$(SRCS) Makefile
			$(MKDIR) $(OBJ_DIR)
			$(CC) $(CFLAGS) $(INCLUDE) $(DEPFLAG) -c -o $@ $<

clean:
		$(RMD) $(OBJ_DIR)

fclean:	clean
		$(RMF) $(NAME)

re:		fclean all

-include $(DEPS)
.PHONY: all clean fclean re
