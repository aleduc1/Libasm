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
SRCDIR	:= srcs/
OBJDIR	:= objs/
#INCDIR	:= includes/

#HEADER		:=	$(shell ls $(INCDIR)))
OBJ_NAME	:=	$(patsubst %.s, %.o, $(shell ls -1 $(SRCDIR)))
OBJ       :=  $(addprefix $(OBJDIR), $(OBJ_NAME))

vpath
vpath %.s $(SRCDIR)
vpath %.o $(OBJDIR)

# -------------------------- #
# Builtin variables override #
# -------------------------- #

AS			:= nasm
ASFLAGS	:= -f elf64
AR			:= ar
ARFLAGS	:= crs
 
# ----------------- #
# Command variables #
# ----------------- #

PRINT	:= -echo
DEL		:= -rm -rf
CREATE:= -mkdir -p

# -------------- #
# Implicit Rules #
# -------------- #

%.o: %.s | $(OBJDIR) #$(HEADER)
	$(AS) $(ASFLAGS) -o $(OBJDIR)$@ $<
	$(PRINT) "Object files generated"

# -------------- #
# Explicit Rules #
# -------------- #

all: $(NAME)

$(OBJDIR):
	$(CREATE) $@

$(NAME): $(OBJ_NAME)
	$(AR) $(ARFLAGS) $@ $(OBJ)
	$(PRINT) "Static library generated"

clean:
	$(DEL) $(OBJDIR)
	$(PRINT) "Object files deleted"

fclean: clean
	$(DEL) $(NAME)
	$(PRINT) "Static library deleted"

re: fclean all

# --------------------- #
# GNU Special Variables #
# --------------------- #

PHONY		:= all clean fclean re
SILENT	:= all $(NAME) $(OBJ_NAME) $(OBJDIR) clean fclean re
.PHONY	: $(PHONY)
.SILENT	: $(SILENT)
