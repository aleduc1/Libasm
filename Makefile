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
#INCDIR	:= includes/

#HEADER		:=	$(shell ls $(INCDIR)))
OBJ_NAME	:=	$(patsubst %.s, %.o, $(shell ls -1 $(SRCDIR)))
OBJ_TEST	:=	$(patsubst %.c, %.o, $(shell ls -1 $(TESTDIR)))
OBJ       :=  $(addprefix $(OBJDIR), $(OBJ_NAME))

vpath
vpath %.s $(SRCDIR)
vpath %.c $(TESTDIR)
vpath %.o $(OBJDIR)

# -------------------------- #
# Builtin variables override #
# -------------------------- #

CC			:= gcc
CFLAGS	:= -m64 -Wall -Wextra

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

%.o: %.s | $(OBJDIR) #$(HEADER)
	$(AS) $(ASFLAGS) -o $(OBJDIR)$@ $<
	$(PRINT) $(GREEN)"Object files generated"$(NC)

%.o: %.c #$(HEADER)
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)$@
	$(PRINT) $(GREEN)"Test object files generated"$(NC)

# -------------- #
# Explicit Rules #
# -------------- #

all: $(NAME)

test: $(NAME) $(TEST)

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

PHONY		:= all debug test clean fclean re
SILENT	:= all debug test $(NAME) $(OBJ_NAME) $(TEST) $(OBJ_TEST) $(OBJDIR) clean fclean re
.PHONY	: $(PHONY)
.SILENT	: $(SILENT)
