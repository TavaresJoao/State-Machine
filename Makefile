
# specify the shell, in case the SHELL variable is not set or is not
# inherited from the environment
SHELL = /bin/bash

# set suffix list, to prevent confusion between different make programs
# line 7 clears an implied suffix list, and line 8 sets a new one
.SUFFIXES:
.SUFFIXES: .c .h .o

# project set up and directories
GCC	= gcc
INCLDIR	= include/
BINDIR	= bin/
OBJDIR	= obj/
SRCDIR	= src/

# final executable name
_BIN	= main.exec
BIN	= $(addprefix $(BINDIR), $(_BIN))

# files; here all object files will be stored in $(OBJDIR), with the
# same base names as corresponding c files from SRCDIR
SRC	= $(wildcard src/*.c)
_OBJS	= $(patsubst src/%.c, %.o, $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(_OBJS))

# compilation flags
CFLAGS = -Wall -pedantic -g -I$(INCLDIR)
OFLAGS =

# compile binary and object files
.PHONY: all
all: $(BIN)

$(BIN): $(BINDIR) $(OBJS)
	$(GCC) $(OFLAGS) $(OBJS) -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJS): $(OBJDIR) $(SRC)
	$(GCC) $(CFLAGS) -c src/sm.c -o obj/sm.o
	$(GCC) $(CFLAGS) -c src/main.c -o obj/main.o

$(OBJDIR):
	mkdir -p $(OBJDIR)

# clean entire project directory
.PHONY: clean
clean:
	- rm -rf $(BINDIR) $(OBJDIR)


# check code quality
.PHONY: cppcheck memcheck
cppcheck:
	cppcheck --enable=all --language=cpp --inconclusive \
	--suppress=missingInclude $(SRC) -i $(INCLDIR)

memcheck: all
	valgrind -v --show-leak-kinds=all --leak-check=full --track-origins=yes \
	./$(BIN)

# debugging make
print-% :
	@echo $* = $($*)
