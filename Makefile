CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
SRCDIR = srcs
OBJDIR = objs
INCDIR = includes
LIBDIR = libs
LIBS = -lmpg123 -lao
LIBNAME = simpleaudio

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

STATIC = $(LIBDIR)/lib$(LIBNAME).a

all: $(STATIC)


$(STATIC): $(OBJDIR) $(LIBDIR) $(OBJ)
	ar rcs $(LIBDIR)/lib$(LIBNAME).a $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(LIBDIR)

re: fclean all

.PHONY: all clean fclean re
