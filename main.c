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
            system("cls");
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
        printf ("MENU \n");
        printf ("1) Nuova Prenotazione\n2) Visualizza storico prenotazione\n3) Visualizza Sconti\n4) Visualizza Veicoli\n5) Trova Prenotazione\n6) Esci\n");
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

        switch (scelta) {
            case 1: {
                
                for (int i=0; i<10; i++){
                    stampaVeicolo (V[i]);
                }

                printf ("Bene, innanzitutto scelga il veicolo che le interessa tra quelli in catalogo (da 0 a 9): ");

                int s1;
                while (1){
                    scanf ("%d", &s1);
                    if (s1 < 0 || s1 > 9){
                        printf ("\nIndice non valido, riprovi: ");
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
                        printf ("\nIndice non valido, riprovi: ");
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
                printf ("Conferma la sua prenotazione? (Y o N): ");

                while (1){
                    if (scanf (" %c", &s) != 1 || getchar() != '\n'){
                        printf("Scelta non valida, riprova: ");
                        for (; getchar() != '\n';);
                    } else if (s == 'Y' || s== 'y') {
                        int z = InserisciPrenotazione (T, p1);
                        AggiornaStorico (p1);
                        printf ("Bene, la sua prenotazione e' completa");
                        printf ("\n\n\n\n");
                        goto inizio;
                    } else if (s == 'n' || s == 'N') {
                        printf ("Mi dispiace, ma la sua prenotazione e' annullata.");
                        printf ("\n\n\n\n");
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
                system("cls");
                printf ("=== STORICO PRENOTAZIONI DI %s === \n\n", nomeUtente);

                while (fgets (buffer, sizeof (buffer), file) != NULL){
                    char *token = strtok (buffer, "-");
                    if (strcmp (token, nomeUtente) == 0){
                        token = strtok (NULL, "-");
                        printf ("%s", token);
                        token = strtok (NULL, "-");
                        printf (" ORARIO DI INIZIO/FINE: %s", token);
                        token = strtok (NULL, "-");
                        printf ("-%s", token);
                        token = strtok (NULL, "-");
                        printf (" ID: %s", token);
                        token = strtok (NULL, "-");
                        printf (" MODELLO: %s", token);
                        token = strtok (NULL, "-");
                        printf (" TARGA: %s", token);
                    }
                }

                fclose (file);


                char s;

                if (menuPrincipale(s) == 0){
                    goto inizio;
                }
                
            }

            case 3:{
                system("cls");
                printf ("=== SCONTI ===\n\n");
                printf ("- 30%% off se la prenotazione viene effettuata dopo le 20:00\n"); //messo il doppio %% in modo che la printf lo vede come un carattere e non come specificatore di formato
                printf ("- 15%% off se la prenotazione viene effettuata prima delle 9:00\n\n");

                char s;
                if (menuPrincipale(s) == 0){
                    goto inizio;
                }
            }

            case 4: {
                system("cls");
                printf ("=== CATALOGO VEICOLI ===\n");

                for (int i=0; i<10; i++){

                    printf ("VEICOLO %d\n", i+1);
                    stampaVeicolo (V[i]);
                }

                char s;
                if (menuPrincipale(s) == 0){
                    goto inizio;
                }
            }

            case 5: {

                printf ("Inserisca l'ID della prenotazione che vuole vedere: ");
                int id;
                char s;
                scanf ("%d", &id);

                Prenotazione p = TrovaPrenotazione (T, id, HASH_TAGLIA);
                if (p != NULL){
                    stampaPrenotazione(p);
                }
                if (p == NULL){

                    FILE* file = fopen ("StoricoPrenotazioni.txt", "r");

                    if (file == NULL){

                        perror ("Errore nell'apertura dello storico.");
                        exit (1);
                    }

                    char buffer [200];
                    if (fgetc(file) == EOF){
                        printf("Lo storico non presenta alcuna prenotazione.\n");
                        fclose(file);
                        if (menuPrincipale(s) == 0){
                                goto inizio;
                        }
                    }
                    rewind(file);
                    while (fgets (buffer, sizeof (buffer), file) != NULL){
                        char bufferCopia[200];
                        strcpy(bufferCopia, buffer);
                        char* token = strtok (buffer, "-");
                        // controllo token
                        if (strcmp (token, nomeUtente) == 0){
                            int i=0;
                            while (i < 4){
                            token = strtok (NULL, "-");
                            // controllo token
                            i++;
                            }
                            int tokenID = atoi(token);
                            if (tokenID == id){
                                printf ("Ecco la sua prenotazione con ID %d: \n%s", id, bufferCopia);
                                if (menuPrincipale(s) == 0){
                                goto inizio;
                                }
                            }
                        }
                        }
                         printf("Non e' stata trovata la prenotazione ID %d a nome di %s\n", id, nomeUtente);
                        if (menuPrincipale(s) == 0){
                            goto inizio;
                    }
                }
                break;
            }


            case 6:
                system("cls");
                printf ("Grazie mille per aver scelto il nostro servizio!");

                for (int i=0; i < VEICOLI_TAGLIA; i++){

                    liberaVeicoli (V[i]);

                }
                LiberaTabellaHash (T);
                exit (0);
            default:
                system("cls");
                printf("Vi e' stato qualche errore durante l'associazione dell'operazione da effettuare\n");
                for (int i=0; i < VEICOLI_TAGLIA; i++){

                    liberaVeicoli (V[i]);

                }
                LiberaTabellaHash (T);
                exit (1);
        }
    }

