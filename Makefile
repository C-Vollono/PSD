main.exe: main.o Menu.o Prenotazione.o Veicolo.o
	gcc main.o Menu.o Prenotazione.o Veicolo.o -o main.exe

Menu.o: Menu.c Menu.h
	gcc -c Menu.c

Prenotazione.o: Prenotazione.c Prenotazione.h
	gcc -c Prenotazione.c

Veicolo.o: Veicolo.c Veicolo.h
	gcc -c Veicolo.c

main.o: main.c Menu.o Prenotazione.o Veicolo.o
	gcc -c main.c

clean:
	rm -f *.o *.exe