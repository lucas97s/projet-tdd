vpath %.c src/
vpath %.h include/
vpath %.o obj/
vpath main bin/

.PHONY: clean doc doc_clean

CC = gcc 
CFLAGS = -Wall -std=c99 -g
O_REP = obj/
B_REP = bin/
L_REP = lib/
D_REP = doc/

main: clean main.o main_g.o libjeu.a
ifeq ($(MODE),TEXTE)
	$(CC) $(CFLAGS) $(O_REP)main.o -Llib -ljeu -o $(B_REP)main
else
	$(CC) $(CFLAGS) $(O_REP)main_g.o -Llib -ljeu -lcairo -lX11 -o $(B_REP)main
endif

libjeu.a: grille.o io.o io_g.o jeu.o
ifeq ($(MODE),TEXTE)
	ar -rcs $(L_REP)libjeu.a $(O_REP)grille.o $(O_REP)io.o $(O_REP)jeu.o
else
	ar -rcs $(L_REP)libjeu.a $(O_REP)grille.o $(O_REP)io_g.o $(O_REP)jeu.o
endif

grille.o: grille.c grille.h
io.o: io.c io.h
io_g.o: io_g.c io_g.h
jeu.o: jeu.c jeu.h
main.o: main.c
main_g.o: main_g.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I /usr/include/cairo -I include -o $(O_REP)$@ 

archive: src/ include/ obj/ bin/ lib/ doc/ Doxyfile makefile explication.txt
	tar czf lucas_schott_projet_tdd.tar.gz $^

clean:
	rm -f $(O_REP)*.o $(B_REP)main $(L_REP)libjeu.a

doc: 
	doxygen

doc_clean:
	rm -r $(D_REP)*

#$(patsubst %,$(O_REP)%,$^)
