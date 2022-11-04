# ----- #
# Shell #
# ----- #

SHELL	:= /bin/sh
ifeq ($(HOSTTYPE),)
  HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

AS = nasm
ASFLAGS = -f elf64
AR = ar
ARFLAGS = crs

NAME = libasm.a
SRC = hello_world.asm
OBJ = hello_world.o

PRINT = echo
DEL = rm -f

PHONY		:=	all clean fclean re
SILENT	:=	all clean fclean re

# ----- #
# Rules #
# ----- #

all:
	$(AS) $(ASFLAGS) -o $(OBJ) $(SRC)
	$(PRINT) object files generated
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	$(PRINT) static library generated

clean:
	$(DEL) $(OBJ)
	$(PRINT) object files removed

fclean: clean
	$(DEL) $(NAME)
	$(PRINT) static library removed

re: fclean all

.PHONY 	: $(PHONY)
.SILENT	:	$(SILENT)
