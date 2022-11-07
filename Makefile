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

# -------------- #
# Implicit Rules #
# -------------- #

%.o: %.s | $(OBJDIR) #$(HEADER)
	$(AS) $(ASFLAGS) -o $(OBJDIR)$@ $<
	$(PRINT) "Object files generated"

%.o: %.c #$(HEADER)
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)$@
	$(PRINT) "Test object files generated"

# -------------- #
# Explicit Rules #
# -------------- #

all: $(NAME)

test: $(NAME) $(TEST)

$(OBJDIR):
	$(CREATE) $@

$(NAME): $(OBJ_NAME)
	$(AR) $(ARFLAGS) $@ $(OBJ)
	$(PRINT) "Static library generated"

$(TEST): $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJDIR)$< -o $@ $(LDLIBS) $(LDFLAGS)
	$(PRINT) "Test executable generated"

clean:
	$(RM) $(OBJDIR)
	$(PRINT) "Object files deleted"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(PRINT) "Static library deleted"
	$(PRINT) "Test executable deleted"

re: fclean all

# --------------------- #
# GNU Special Variables #
# --------------------- #

PHONY		:= all test clean fclean re
SILENT	:= all test $(NAME) $(OBJ_NAME) $(TEST) $(OBJ_TEST) $(OBJDIR) clean fclean re
.PHONY	: $(PHONY)
#.SILENT	: $(SILENT)
