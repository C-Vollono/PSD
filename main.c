#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "Menu.h"

#define HASH_TAGLIA 5


void main (){

    menuAcccesso ();

    veicolo V[10];

    for (int i=0; i<10; i++){

        riempiVeicoli (V[i], "Veicoli.txt");
    }

    TabellaHash T = NuovaTabellaHash (HASH_TAGLIA);

    printf ("===== BENVENUT* %s NEL NOSTRO CAR-SHARING =====", nome_utente);
    printf ("=== MENU ===");

    printf ("1) Nuova Prenotazione\n2) Visualizza storico prenotazione\n3) Visualizza Sconti\n4) Visualizza Veicoli\n5) Annulla Prenotazione\n6) Logout\n");

    int scelta;

    printf ("Scelga l'operazione da effettuare (da 1-6): ");
    scanf ("%d", &scelta);

    switch (scelta){

        case 1:
            printf ("Bene, innanzitutto scelga il veicolo che le interessa tra quelli in catalogo (da 0 a 9): ");

            for (int i=0; i<10; i++){

                stampaVeicolo (V[i]);
            }

            int s1;
            scanf ("%d", &s1);

            while (1){

                if (s1 < 0 || s1 > 9 ||){

                printf ("Indice non valido, riprovi: ");
                scanf ("%d", &s1);
                }
                else
                break;
            }

            printf ("Ora scelga un orario tra quelli disponibili per il noleggio del veicolo: ");

            stampaOrari (V[s1]);

            int s2;
            scanf ("%d", &s2);

            while (1){

                if (s2 < 0 || s2 >8 ){

                    printf ("Indice non valido, riprovi: ");
                    scanf ("%d", &s2);
                }
                else 
                break;
            }

            srand (time(NULL));
            int ID = rand();

             float c = costoNoleggio (V[s1], s2);

            Prenotazione p1 = NuovaPrenotazione (ID, NomeUtente, V[s1], c, s2);

            printf ("Ecco il riepilogo della sua prenotazione: ");

            //fare funzione di stampa prenotazione 

            printf ("Conferma la sua prenotazione? ")
            

    }
}