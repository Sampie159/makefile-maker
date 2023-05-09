CFLAGS=-Wall -Wextra -g

SRCDIR=src
SRCS=${wildcard $(SRCDIR)/*.c}

OBJDIR=obj
OBJS=${patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS)}

BINDIR=bin

all: $(BINDIR)/mmaker

release: CFLAGS=-Wall -Wextra -DNDEBUG -pipe -march=native -O2
release: $(BINDIR)/mmaker

install: CFLAGS=-Wall -Wextra -DNDEBUG -pipe -march=native -O2
install: $(BINDIR)/mmaker
	sudo mv $(BINDIR)/mmaker /usr/local/bin/
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)

uninstall:
	sudo rm /usr/local/bin/mmaker

run: $(BINDIR)/mmaker
	$(BINDIR)/mmaker

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	cc $(CFLAGS) -c -o $@ $^

$(OBJDIR):
	mkdir -p obj

$(BINDIR)/mmaker: $(OBJS) | $(BINDIR)
	cc $(CFLAGS) -o $@ $^

$(BINDIR):
	mkdir -p bin

clean:
	rm $(OBJDIR)/*
	rm $(BINDIR)/mmaker
