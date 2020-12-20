# Variables
CC = gcc
CFLAGS = -Wall -O0 -std=c11 -DDEBUG -g
ODUMP = objdump
ODFLAGS = -d
OBJCOPY = objcopy
OBJFLAGS = -O binary
MKDIRARGS = --parents

# Directories
OBJDIR := obj
TGTDIR := target
SRCDIR := src
TSTDIR := tests

# Target name
target = vk

# Sources
sources := $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*/*.c)

# Objects list
objects = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(sources))

# Tests
tests := $(wildcard $(TSTDIR)/*.c)

# Tests list
tests_list := $(patsubst $(TSTDIR)/%.c,$(OBJDIR)/%.exe,$(tests))

# Includes
includes := $(wildcard $(SRCDIR)/*.h $(SRCDIR)/*/*.h)

all: test run | test

# Run rules.
run: $(TGTDIR)/$(target)
	@echo "success"

$(TGTDIR)/$(target) : $(objects)
	$(CC) $(CFLAGS) $^ -o $@
	$@

# Test rules.
# TODO:: get the recipe to fail on failed test.
test: $(tests_list)
	@$(foreach f,$^,./$(f);)

$(OBJDIR)/%.exe: $(TSTDIR)/%.c $(objects)
	$(CC) $(CFLAGS) -o $@ $< $(filter-out $(@D)/main.o,$(objects))

# Shared build rules.
$(OBJDIR)/%.o: $(SRCDIR)/%.c | folders
	@mkdir $(MKDIRARGS) $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<

folders:
	@mkdir $(MKDIRARGS) $(OBJDIR)
	@mkdir $(MKDIRARGS) $(TGTDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TGTDIR)
