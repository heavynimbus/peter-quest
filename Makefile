FLAGS = -c -Wall -Werror -Wextra

.PHONY: clean real-clean

peter-quest: main.o config.o screen.o hero.o race.o box.o board.o
	gcc -o $@ $^

main.o: main.c main.h config.h screen.h board.h
	gcc -c $(FLAGS) $<

config.o: config.c config.h
	gcc -c $(FLAGS) $<

screen.o: screen.c screen.h
	gcc -c $(FLAGS) $<

board.o: board.c board.h box.h
	gcc -c $(FLAGS) $<

box.o: box.c box.h hero.h
	gcc -c $(FLAGS) $<

hero.o: hero.c hero.h race.h
	gcc -c $(FLAGS) $<

race.o: race.c race.h
	gcc -c $(FLAGS) $<

#peter-quest : main.o board.o box.o hero.o game.o race.o player.o screen.o
#	gcc -o $@ $^
#
#main.o: main.c main.h game.h
#	gcc $(FLAGS) $< 
#
#board.o: board.c board.h main.h box.h screen.h
#	gcc $(FLAGS) $<
#
#box.o: box.c box.h main.h hero.h
#	gcc $(FLAGS) $<
#
#hero.o: hero.c hero.h main.h race.h
#	gcc $(FLAGS) $<
#
#game.o: game.c game.h main.h board.h player.h
#	gcc $(FLAGS) $<
#
#race.o: race.c race.h main.h
#	gcc $(FLAGS) $<
#
#player.o: player.c player.h main.h
#	gcc $(FLAGS) $<
#
#screen.o: screen.c screen.h
#	gcc $(FLAGS) $<
	
clean:
	rm -f *.o

real-clean:
	rm -f *.o
	rm peter-quest