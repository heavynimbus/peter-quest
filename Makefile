FLAGS = -c -Wall -Werror -Wextra

.PHONY: clean

peter-quest : main.o board.o box.o hero.o game.o race.o joueur.o
	gcc -o $@ $^

main.o: main.c main.h game.h joueur.h
	gcc $(FLAGS) $< 

board.o: board.c board.h main.h box.h
	gcc $(FLAGS) $<

box.o: box.c box.h main.h hero.h
	gcc $(FLAGS) $<

hero.o: hero.c hero.h main.h race.h
	gcc $(FLAGS) $<

game.o: game.c game.h main.h board.h 
	gcc $(FLAGS) $<

race.o: race.c race.h main.h
	gcc $(FLAGS) $<

joueur.o: joueur.c joueur.h main.h
clean:
	rm -f *.o