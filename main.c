#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "Menu.h"

#define HASH_TAGLIA 5


void main () {

    char* nomeUtente;

    nomeUtente = menuAcccesso();

    veicolo V[10];

    for (int i=0; i<10; i++){

        riempiVeicoli (V[i], "Veicoli.txt");
    }

    TabellaHash T = NuovaTabellaHash (HASH_TAGLIA);

    printf ("===== BENVENUT* %s NEL NOSTRO CAR-SHARING =====", nomeUtente);

    inizio:

    printf ("=== MENU ===");

    printf ("1) Nuova Prenotazione\n2) Visualizza storico prenotazione\n3) Visualizza Sconti\n4) Visualizza Veicoli\n5) Annulla Prenotazione\n6) Logout\n");

    int scelta;

    printf ("Scelga l'operazione da effettuare (da 1-6): ");
    scanf ("%d", &scelta);

    while (1){

        if (scelta < 1 || scelta > 6){

            printf ("Scelta non valida, riprovi: ");
            scanf ("%d", &scelta);
        }
        else
        break;
    }

    switch (scelta){

        case 1: {
            printf ("Bene, innanzitutto scelga il veicolo che le interessa tra quelli in catalogo (da 0 a 9): ");

            for (int i=0; i<10; i++){

                stampaVeicolo (V[i]);
            }

            int s1;
            scanf ("%d", &s1);

            while (1){

                if (s1 < 0 || s1 > 9){

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

            Prenotazione p1 = NuovaPrenotazione (ID, nomeUtente, V[s1], c, s2);

            printf ("Ecco il riepilogo della sua prenotazione: ");

            stampaPrenotazione (p1);

            char s;

            printf ("Conferma la sua prenotazione? (Y o N)");

            scanf ("%c", &s);

            while (1){

            if (s == 'Y' || s== 'y'){

                int z = InserisciPrenotazione (T, p1);
                printf ("Bene, la sua prenotazione è completa");
                printf ("\n\n\n\n\n\n\n");
                goto inizio;
            }

            else if (s == 'n' || s == 'N'){

                printf ("Mi dispiace, ma la sua prenotazione è annullata.");
                printf ("\n\n\n\n\n\n\n");
                goto inizio;
            }
            else{
                printf ("Scelta non valida, riprova: ");
                scanf ("%s", &s);
            }
        }
    }

        case 2: { // da implementare la visualizza delle prenotazioni odierne (tramite tabella hash) o passate (tramite file)

            printf ("=== STORICO PRENOTAZIONI DI %s ===", nomeUtente);
            
            FILE* file = fopen ("StoricoPrenotazioni.txt", "r");

            if (file == NULL){

                perror ("Errore nella visualizzazione dello storico.");
                exit (1);
            }

            char buffer [200];

             while (fgets (buffer, sizeof (buffer), file) != EOF){

                if (strcmp (buffer, nomeUtente) == 0){

                    char* token;

                    token = strtok (buffer, "-");

                    token = strtok (NULL, "-");

                    printf ("DATA: %s", token);

                    token = strtok (NULL, "-");

                    printf ("ORARIO SELEZIONATO: %s", token);

                    token = strtok (NULL, "-");

                    printf ("MODELLO: %s", token);

                    token = strtok (NULL, "-");

                    printf ("TARGA: %s", token);
                }
             }

             char s;

             printf ("Vuole tornare al menu principale? (Y o N)");
             scanf ("%c",&s);

             while (1){

             if (s == 'Y' || s == 'y'){
                goto inizio;
             }
             else if (s == 'N' || s == 'n'){

                printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
                scanf ("%c", &s);
             }
             else {
                printf ("Scelta non valida, riprova: ");
                scanf ("%c", &s);
            }
        }
        }

        case 3:{ 

            printf ("=== SCONTI ===");
            printf ("- Sconto del 30%% se la prenotazione viene effettuata dopo le 20:00"); //messo il doppio %% in modo che la printf lo vede come un carattere e non come specificatore di formato
            printf ("- Sconto del 15%% se la prenotazione viene effettuata prima delle 9:00");

            char s;

            printf ("Vuole tornare al menu principale? (Y o N)");
             scanf ("%c",&s);

             while (1){

             if (s == 'Y' || s == 'y'){
                goto inizio;
             }
             else if (s == 'N' || s == 'n'){

                printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
                scanf ("%c", &s);
             }
             else {
                printf ("Scelta non valida, riprova: ");
                scanf ("%c", &s);
            }
        }

    }

        case 4: {

            printf ("=== CATALOGO VEICOLI ===");

            for (int i=0; i<10; i++){

                printf ("VEICOLO %d", i+1);

                stampaVeicolo (V[i]);
            }

            char s;

            printf ("Vuole tornare al menu principale? (Y o N)");
             scanf ("%c",&s);

             while (1){

             if (s == 'Y' || s == 'y'){
                goto inizio;
             }
             else if (s == 'N' || s == 'n'){

                printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
                scanf ("%c", &s);
             }
             else {
                printf ("Scelta non valida, riprova: ");
                scanf ("%c", &s);
            }
         }
        }

        case 5: {


        }
    }

}