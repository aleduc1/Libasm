# ----- #
# Shell #
# ----- #

SHELL := /bin/sh
ifeq ($(HOSTTYPE),)
  HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# -------------------- #
# Prerequisites & Path #
# -------------------- #

NAME		:= libasm.a
TEST		:= main_test
BTEST		:= bonus_test

SRCDIR	:= srcs/
TESTDIR	:= test/
OBJDIR	:= objs/
INCDIR	:= includes/

HEADER		:=	libasm.h
OBJ_NAME	:=	ft_read.o ft_strcmp.o ft_strcpy.o ft_strdup.o ft_strlen.o ft_write.o
BONUS_NAME:=	$(OBJ_NAME) ft_atoi_base.o ft_list_push_front.o ft_list_remove_if.o ft_list_size.o ft_list_sort.o
OBJ_TEST	:=	main_test.o
BONUS_TEST:=	bonus_test.o
OBJ       :=  $(addprefix $(OBJDIR), $(OBJ_NAME))
OBJ_BONUS	:=  $(addprefix $(OBJDIR), $(BONUS_NAME))

vpath
vpath %.s $(SRCDIR)
vpath %.c $(TESTDIR)
vpath %.o $(OBJDIR)
vpath %.h $(INCDIR)

# -------------------------- #
# Builtin variables override #
# -------------------------- #

CC			:= gcc
CFLAGS	:= -m64 -I $(INCDIR) -Wall -Wextra

AS			:= nasm
ASFLAGS	:= -f elf64
ASFLAGS	+= -w+all

AR			:= ar
ARFLAGS	:= crs

LDLIBS	:= -L .
LDFLAGS	:= -l asm
 
# ----------------- #
# Command variables #
# ----------------- #

RM		:= -rm -rf
PRINT	:= -echo
CREATE:= -mkdir -p

# ------ #
# Colors #
# ------ #

NC		:= '\033[0m'
RED		:= '\033[0;31m'
GREEN	:= '\033[0;32m'
ORANGE:= '\033[0;33m'
BLUE	:= '\033[0;34m'
PURPLE:= '\033[0;35m'

# -------------- #
# Implicit Rules #
# -------------- #

%.o: %.s | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $(OBJDIR)$@ $<
	$(PRINT) $(GREEN)"Object files generated"$(NC)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)$@
	$(PRINT) $(GREEN)"Test object files generated"$(NC)

# -------------- #
# Explicit Rules #
# -------------- #

all: $(NAME)

test: re $(TEST)
btest: fclean bonus $(BTEST)

debug: CFLAGS := $(CFLAGS) -g
debug: btest
	$(PRINT) $(PURPLE)"Added debugging symbols to the GOT"$(NC)

$(OBJDIR):
	$(CREATE) $@

$(NAME): $(OBJ_NAME)
	$(AR) $(ARFLAGS) $@ $(OBJ)
	$(PRINT) $(BLUE)"Static library generated"$(NC)

bonus: $(BONUS_NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_BONUS)
	$(PRINT) $(BLUE)"Static library with bonus generated"$(NC)

$(TEST): $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJDIR)$< -o $@ $(LDLIBS) $(LDFLAGS)
	$(PRINT) $(ORANGE)"Test executable generated"$(NC)

$(BTEST): $(BONUS_TEST)
	$(CC) $(CFLAGS) $(OBJDIR)$< -o $@ $(LDLIBS) $(LDFLAGS)
	$(PRINT) $(ORANGE)"Bonus test executable generated"$(NC)

clean:
	$(RM) $(OBJDIR)
	$(PRINT) $(RED)"Object files deleted"$(NC)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST) $(BTEST)
	$(PRINT) $(RED)"Static library deleted"$(NC)
	$(PRINT) $(RED)"Test executables deleted"$(NC)

re: fclean all

# --------------------- #
# GNU Special Variables #
# --------------------- #

PHONY		:= all debug test btest clean fclean re
SILENT	:= all debug test btest bonus $(NAME) $(OBJ_NAME) $(BONUS_NAME) $(OBJ_TEST) $(BONUS_TEST) $(TEST) $(BTEST) $(OBJDIR) clean fclean re
.PHONY	: $(PHONY)
.SILENT	: $(SILENT)
