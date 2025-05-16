#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "Menu.h"

#define HASH_TAGLIA 5
#define VEICOLI_TAGLIA 10

/*
 * funzione controllo menuPrincipale
*/
void main () {

    char* nomeUtente;
    veicolo V[VEICOLI_TAGLIA];

    for (int i=0; i < VEICOLI_TAGLIA; i++){

        V[i] = malloc(sizeof(struct Vettura));

        if (V[i] == NULL){

            perror ("Errore nell'allocazione della memoria.");
            exit (1);
        }

        riempiVeicoli (V[i]);
    }

    nomeUtente = menuAccesso();
    TabellaHash T = NuovaTabellaHash (HASH_TAGLIA);

    printf ("===== BENVENUT* %s NEL NOSTRO CAR-SHARING =====\n", nomeUtente);

    inizio:
        int scelta;
        printf ("=== MENU ===\n");
        printf ("1) Nuova Prenotazione\n2) Visualizza storico prenotazione\n3) Visualizza Sconti\n4) Visualizza Veicoli\n5)Trova Prenotazione\n6) Esci\n");
        printf ("Scelga l'operazione da effettuare (da 1-6): ");
        scanf ("%d", &scelta);

        while (1) {
            if (scelta < 1 || scelta > 6){
                printf ("Scelta non valida, riprovi: ");
                scanf ("%d", &scelta);
            } else {
                break;
            }
        }

        switch (scelta){
            case 1: {
                
                for (int i=0; i<10; i++){
                    stampaVeicolo (V[i]);
                }

                printf ("Bene, innanzitutto scelga il veicolo che le interessa tra quelli in catalogo (da 0 a 9): \n");

                int s1;
                while (1){
                    scanf ("%d", &s1);
                    if (s1 < 0 || s1 > 9){
                        printf ("Indice non valido, riprovi: ");
                    } else {
                        break;
                    }
                }

                printf ("Ora scelga un orario tra quelli disponibili per il noleggio del veicolo: \n");
                stampaOrari (V[s1]);

                int s2;
                while (1){
                    scanf ("%d", &s2);
                    if (s2 < 0 || s2 >8 ){
                        printf ("Indice non valido, riprovi: ");
                    }
                    else {
                        break;
                    }
                }

                srand (time(NULL));
                int ID = rand();

                float c = costoNoleggio (V[s1], s2);
                Prenotazione p1 = NuovaPrenotazione (ID, nomeUtente, V[s1], c, s2);

                printf ("Ecco il riepilogo della sua prenotazione: ");
                stampaPrenotazione (p1);

                char s;
                printf ("Conferma la sua prenotazione? (Y o N)");

                while (1){
                    scanf ("%c", &s);
                    if (s == 'Y' || s== 'y') {
                        int z = InserisciPrenotazione (T, p1);
                        AggiornaStorico (p1);
                        printf ("Bene, la sua prenotazione è completa");
                        printf ("\n\n\n\n\n\n\n");
                        goto inizio;
                    } else if (s == 'n' || s == 'N') {
                        printf ("Mi dispiace, ma la sua prenotazione è annullata.");
                        printf ("\n\n\n\n\n\n\n");
                        goto inizio;
                    } else {
                    printf ("Scelta non valida, riprova: ");
                    }
                }
            }

            case 2: { 
                FILE* file = fopen ("StoricoPrenotazioni.txt", "r");
                char buffer [200];
                if (file == NULL){
                    perror ("Errore nella visualizzazione dello storico.");
                    exit (1);
                }

                printf ("=== STORICO PRENOTAZIONI DI %s ===", nomeUtente);

                while (fgets (buffer, sizeof (buffer), file) != NULL){
                     char *token = strtok (buffer, "-");
                     if (strcmp (token, nomeUtente) == 0){
                         token = strtok (NULL, "-");
                         printf ("DATA: %s", token);
                         token = strtok (NULL, "-");
                         printf ("ORARIO DI INIZIO: %s", token);
                         token = strtok (NULL, "-");
                         printf ("ORARIO DI FINE: %s", token);
                         token = strtok (NULL, "-");
                         printf ("ID: %s", token);
                         token = strtok (NULL, "-");
                         printf ("MODELLO: %s", token);
                         token = strtok (NULL, "-");
                         printf ("TARGA: %s", token);
                     }
                }

                fclose (file);


                char s;
                printf ("Vuole tornare al menu principale? (Y o N)");

                while (1){
                    scanf ("%c",&s);
                    if (s == 'Y' || s == 'y'){
                        goto inizio;
                    } else if (s == 'N' || s == 'n') {
                        printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
                    } else {
                        printf ("Scelta non valida, riprova: ");
                    }
                }
            }

            case 3:{
                printf ("=== SCONTI ===");
                printf ("- Sconto del 30%% se la prenotazione viene effettuata dopo le 20:00\n"); //messo il doppio %% in modo che la printf lo vede come un carattere e non come specificatore di formato
                printf ("- Sconto del 15%% se la prenotazione viene effettuata prima delle 9:00\n");

            char s;
            printf ("Vuole tornare al menu principale? (Y o N)");

            while (1){
                scanf ("%c",&s);
                if (s == 'Y' || s == 'y'){
                    goto inizio;
                } else if (s == 'N' || s == 'n') {
                    printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
                } else {
                    printf ("Scelta non valida, riprova: ");
                }
            }
        }

        case 4: {
            printf ("=== CATALOGO VEICOLI ===\n");

                for (int i=0; i<10; i++){

                    printf ("VEICOLO %d\n", i+1);
                    stampaVeicolo (V[i]);
                }

                char s;
                printf ("Vuole tornare al menu principale? (Y o N): ");

                while (1){
                        getchar ();
                        s = getchar ();
                        if (s == 'Y' || s == 'y'){
                            goto inizio;
                        } else if (s == 'N' || s == 'n') {
                            printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
                        } else {
                            printf ("Scelta non valida, riprova: ");
                    }
                }
        }

        case 5: {

            printf ("Inserisca l'ID della prenotazione che vuole vedere: ");
            int id;
            scanf ("%d", &id);

            Prenotazione p = TrovaPrenotazione (T, id, HASH_TAGLIA);

            if (p == NULL){

                FILE* file = fopen ("StoricoPrenotazioni.txt", "r");

                if (file == NULL){

                    perror ("Errore nell'apertura dello storico.");
                    exit (1);
                }

                char buffer [200];

                while (fgets (buffer, sizeof (buffer), file) != NULL){

                    char* token = strtok (buffer, "-");

                    if (strcmp (token, nomeUtente) == 0){

                        token = strtok (NULL, "-");
                        token = strtok (NULL, "-");
                        token = strtok (NULL, "-");
                        token = strtok (NULL, "-");

                        int tokenID = atoi (token);

                        if (tokenID == id){

                            printf ("Ecco la sua prenotazione con ID %d: ", id);
                            printf ("%s", buffer); //Implementare per questione estetica di nuovo la lettura della riga da file con strtok
                        }

                    }
                    // implementare printf di prenotazione non trovata in base sia all'id che all'utente
                }
            }

            }

            

        case 6: 

            printf ("Grazie mille per aver scelto il nostro servizio!");

            for (int i=0; i < VEICOLI_TAGLIA; i++){

                liberaVeicoli (V[i]);

            }
            LiberaTabellaHash (T);
            exit (0);
        }
    }

