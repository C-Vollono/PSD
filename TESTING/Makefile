testing.exe: main.o Menu.o Prenotazione.o Veicolo.o Utile.o TabellaHash.o Testing.o
	gcc main.o Menu.o Prenotazione.o Veicolo.o Utile.o TabellaHash.o Testing.o -o testing.exe

Menu.o: Menu.c Menu.h
	gcc -c Menu.c

Prenotazione.o: Prenotazione.c Prenotazione.h
	gcc -c Prenotazione.c

Veicolo.o: Veicolo.c Veicolo.h
	gcc -c Veicolo.c

TabellaHash.o: TabellaHash.c TabellaHash.h
	gcc -c TabellaHash.c

Utile.o: Utile.c Utile.h
	gcc -c Utile.c

Testing.o: Testing.c Testing.h
	gcc -c Testing.c

main.o: main.c Menu.o Prenotazione.o Veicolo.o Utile.o TabellaHash.o Testing.o
	gcc -c main.c

clean:
	rm -f *.o *.exe