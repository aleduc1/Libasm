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
TEST		:= functiontests
SRCDIR	:= srcs/
TESTDIR	:= test/
OBJDIR	:= objs/
BONUSDIR:= bonus/
INCDIR	:= includes/

HEADER		:=	libasm.h
OBJ_NAME	:=	$(patsubst %.s, %.o, $(shell ls -1 $(SRCDIR)))
BONUS_NAME:=	$(OBJ_NAME) $(patsubst %.s, %.o, $(shell ls -1 $(BONUSDIR)))
OBJ_TEST	:=	$(patsubst %.c, %.o, $(shell ls -1 $(TESTDIR)))
OBJ       :=  $(addprefix $(OBJDIR), $(OBJ_NAME))
OBJ_BONUS	:=  $(addprefix $(OBJDIR), $(BONUS_NAME))

vpath
vpath %.s $(SRCDIR)
vpath %.s $(BONUSDIR)
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

test: bonus $(TEST)

debug: CFLAGS := $(CFLAGS) -g
debug: $(NAME) $(TEST)
	$(PRINT) $(PURPLE)"Added debugging symbols to the GOT"$(NC)

$(OBJDIR):
	$(CREATE) $@

$(NAME): $(OBJ_NAME)
	$(AR) $(ARFLAGS) $@ $(OBJ)
	$(PRINT) $(BLUE)"Static library generated"$(NC)

$(TEST): $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJDIR)$< -o $@ $(LDLIBS) $(LDFLAGS)
	$(PRINT) $(ORANGE)"Test executable generated"$(NC)

bonus: $(BONUS_NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_BONUS)
	$(PRINT) $(BLUE)"Static library with bonus function generated"$(NC)

clean:
	$(RM) $(OBJDIR)
	$(PRINT) $(RED)"Object files deleted"$(NC)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(PRINT) $(RED)"Static library deleted"$(NC)
	$(PRINT) $(RED)"Test executable deleted"$(NC)

re: fclean all

# --------------------- #
# GNU Special Variables #
# --------------------- #

PHONY		:= all debug test bonus clean fclean re
SILENT	:= all debug test bonus $(NAME) $(OBJ_NAME) $(BONUS_NAME) $(TEST) $(OBJ_TEST) $(OBJDIR) clean fclean re
.PHONY	: $(PHONY)
.SILENT	: $(SILENT)
