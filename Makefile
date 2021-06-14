FLAGS = -c -Wall -Werror -Wextra

.PHONY: clean real-clean

peter-quest: main.o config.o screen.o hero.o race.o box.o board.o player.o game.o ia.o
	gcc -o $@ $^

main.o: main.c main.h config.h screen.h board.h
	gcc $(FLAGS) $<

config.o: config.c config.h main.h
	gcc $(FLAGS) $<

game.o: game.c game.h board.h player.h screen.h
	gcc $(FLAGS) $<

screen.o: screen.c screen.h main.h
	gcc $(FLAGS) $<

board.o: board.c board.h box.h main.h
	gcc $(FLAGS) $<

box.o: box.c box.h hero.h main.h
	gcc $(FLAGS) $<

hero.o: hero.c hero.h race.h main.h
	gcc $(FLAGS) $<

race.o: race.c race.h main.h
	gcc $(FLAGS) $<

player.o: player.c player.h main.h
	gcc $(FLAGS) $<
	
ia.o: ia.c ia.h main.h board.h player.h
	gcc $(FLAGS) $<

clean:
	rm -f *.o

real-clean:
	rm -f *.o
	rm peter-quest