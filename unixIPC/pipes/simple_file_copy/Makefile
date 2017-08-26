INCDIR := include
SRCDIR := src
BINDIR := bin
OBJDIR := obj
OTHERDIR := others

BASE-NAME := main
CSOURCES := $(wildcard src/*.c)

.PHONY: all clean $(BINDIR) $(OBJDIR) $(OTHERDIR)

all: $(BINDIR) $(OBJDIR) $(OTHERDIR) $(BASE-NAME)

$(BASE-NAME): $(CSOURCES:src/%.c=obj/%.o)
	$(CC) $(OBJDIR)/*.o -o $(BINDIR)/$@ -I./$(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ -I./$(INCDIR)

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

$(OTHERDIR):
	cp $@/* $(BINDIR)/

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)
