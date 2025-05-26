carsharing.exe: main.o Menu.o Prenotazione.o Veicolo.o Utile.o TabellaHash.o
	gcc main.o Menu.o Prenotazione.o Veicolo.o Utile.o TabellaHash.o -o carsharing.exe

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

main.o: main.c Menu.o Prenotazione.o Veicolo.o Utile.o TabellaHash.o
	gcc -c main.c

clean:
	rm -f *.o *.exe