INCDIR := include
SRCDIR := src
BINDIR := bin
OBJDIR := obj

BASE-NAME := main
CSOURCES := $(wildcard src/*.c)

.PHONY: all clean

all: $(BINDIR) $(OBJDIR) $(BASE-NAME)

$(BASE-NAME): $(CSOURCES:src/%.c=obj/%.o)
	$(CC) $(OBJDIR)/*.o -o $(BINDIR)/$@ -I./$(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ -I./$(INCDIR)

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)
