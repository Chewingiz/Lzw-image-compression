#  Makefile
#  Auteur : Fares BELHADJ
#  Email  : amsi@ai.univ-paris8.fr
#  Date   : 23/02/2006

#  Modificiation : Mehdi Aghayani
#  Email  : mehdi.aghayani@gmail.com
#  Commentaire : modifié afin de fonctionner avec OpenGL et MacOS X et libpng
#
#  Université Paris VIII

SHELL = /bin/sh

# Définition des commandes utilisees
CC = gcc
MACHINE= $(shell uname -s)

# Déclaration des options du compilateur
#PG_FLAGS = -DOPENGL_1_5

ifeq ($(MACHINE), Darwin)
GL_LDFLAGS = -framework OpenGL -framework GLUT -framework Cocoa
else
GL_LDFLAGS = -lGL -lglut -lGLU
endif

CFLAGS = -Wall -Wextra -Wshadow -Wcast-align -Wstrict-prototypes -fanalyzer -fsanitize=undefined -g
LDFLAGS = -lm $(GL_LDFLAGS) -fsanitize=undefined

# Définition des fichiers et dossiers
PROGNAME = palette
HEADERS = ima.h temporary_lists_gestion.h dictionary_tree.h dictionary_table.h
SOURCES = main.c ppm.c modif.c temporary_lists_gestion.c  dictionary_tree.c dictionary_table.c
OBJ = $(SOURCES:.c=.o)



all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	@$(RM) $(PROGNAME) $(OBJ) *~ gmon.out core.*
