CC			= g++
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL2 -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 02

# Fichiers exercice 01
OBJ_GAME= game.o
EXEC_GAME= game.out

# Regles compilation TD 02

all :

game : $(OBJDIR)$(OBJ_GAME)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_GAME) -o $(BINDIR)$(EXEC_GAME) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
