CC = gcc
CFLAGS = -Wall -Wextra -g

vpath %.c main:communication

OBJSDIR = build
OBJS = radio main
OBJSFULL = 	$(addprefix $(OBJSDIR)/,\
		$(addsuffix .o, $(OBJS)))


radiatorctl: $(OBJSFULL)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJSDIR)/%.o: %.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJSDIR)/*
