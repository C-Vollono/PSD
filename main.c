/*
 * ATTENZIONE
 * Nel codice sono presenti comandi system
 * Implementati per la pulizia del terminale
 * Potrebbero creare conflitti o problemi di vari natura
 * Disabilitarli se necessario
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "Menu.h"

#define VEICOLI_TAGLIA 10

void main () {

    char* nomeUtente;
    veicolo V[VEICOLI_TAGLIA];
    
    nomeUtente = menuAccesso(); 
    
    for (int i=0; i < VEICOLI_TAGLIA; i++){
        V[i] = malloc(sizeof(struct Vettura));
        if (V[i] == NULL){  
            system("cls | clear");
            perror ("ERRORE: Allocazione memoria veicolo fallita\n");
            for (int j=0; j < i; j++){ free(V[j]);}
            free(nomeUtente);
            exit (1);
        }
        if (!riempiVeicoli (V[i])){
            system("cls | clear");
            perror ("ERRORE: Riempimento informazioni veicolo fallito\n");
            for (int j=0; j < i; j++){
                liberaVeicolo(V[j]);
                free(V[j]);
            }
            free(nomeUtente);
            exit(1);
        }
    }

    TabellaHash T = RiempiTabellaHashDaFile(V);
    if (T == NULL){
        printf("ERRORE: Caricamento prenotazioni fallito.\n");
        free(nomeUtente);
        for (int i=0; i < VEICOLI_TAGLIA; i++){
            liberaVeicolo(V[i]);
            free(V[i]);
        }
        exit(1);
    }

    int taglia = ottieniTaglia(T);

inizio:
    printf ("\n===== BENVENUT* %s NEL NOSTRO CAR-SHARING =====\n\n", nomeUtente);
    printf ("1) Nuova Prenotazione\n2) Visualizza storico prenotazione\n3) Visualizza Sconti\n4) Visualizza Veicoli\n5) Trova Prenotazione\n6) Esci\n");
    printf ("Scelga l'operazione da effettuare (da 1-6): ");

    char scelta;
    while (1){
        if (scanf (" %c", &scelta) != 1 || scelta < '1' || scelta > '6'){
			printf("L'operazione scelta non e' valida, riprova: ");
			while (getchar() != '\n');
		} else break;
    }
    
    int sceltaInt = scelta - '0';

    switch (sceltaInt) {
        case 1: { // Nuova Prenotazione
            getchar();
            for (int i=0; i<10; i++){
                printf ("VEICOLO %d\n", i);
                stampaVeicolo (V[i]);
            }

            printf ("Scelga il veicolo che le interessa tra quelli in catalogo (da 0 a 9): ");
            char sceltaIndice[1024];
            int indiceVeicolo;
                
            while (1){
                fgets(sceltaIndice, sizeof(sceltaIndice), stdin);
                sceltaIndice[strcspn(sceltaIndice, "\n")] = '\0';
                if (strlen(sceltaIndice) == 1 && sceltaIndice[0] >= '0' && sceltaIndice[0] <= '9'){
                    break;
                }
                printf("Il veicolo scelto non e' valido, riprova: ");
    	        }
                indiceVeicolo = sceltaIndice[0] - '0';

                LimitaOrariDisponibili (V);
                stampaOrari (V[indiceVeicolo]);
                printf ("\nScelga un orario tra quelli disponibili per il noleggio del veicolo: ");

                int indiceOrario;
                while (1){
                    fgets(sceltaIndice, sizeof(sceltaIndice), stdin);
                    sceltaIndice[strcspn(sceltaIndice, "\n")] = '\0';
                    if (strlen(sceltaIndice) == 1 && sceltaIndice[0] >= '0' && sceltaIndice[0] <= '7'){
                        break;
                    }
                    printf("L'orario scelto non e' valido, riprova: ");
    	        }
                indiceOrario = sceltaIndice[0] - '0';
                
                if (verificaDisponibilita(V[indiceVeicolo], indiceOrario)){
                    srand (time(NULL));
                    int ID = rand();
                    char* dataCorrente = ottieniData();
                    if (dataCorrente == NULL){
                        printf("ERRORE: Ottenimento data locale fallito.\n");
                        free(nomeUtente);
                        for (int i=0; i < VEICOLI_TAGLIA; i++){
                            liberaVeicolo(V[i]);
                            free(V[i]);
                        }
                    LiberaTabellaHash(T);
                    exit(1);
                }

                Prenotazione p1 = NuovaPrenotazione (ID, nomeUtente, V[indiceVeicolo], indiceOrario, dataCorrente);
                if (p1 == NULL){
                    free(nomeUtente);
                    free(dataCorrente);
                    for (int i=0; i < VEICOLI_TAGLIA; i++){
                        liberaVeicolo(V[i]);
                        free(V[i]);
                    }
                    LiberaTabellaHash(T);
                    exit(1);
                }

                system("cls | clear");
                printf ("\nRiepilogo della sua prenotazione: ");
                stampaPrenotazione (p1);
                printf ("Conferma la sua prenotazione? (Y o N): ");

                char s;
                while (1){
                    if (scanf (" %c", &s) != 1 || getchar() != '\n'){
                        printf("Ha inserito una scelta non valida, riprova: ");
                        while(getchar() != '\n');
                    } else if (s == 'Y' || s == 'y') {
                        modificaDisponibilita (V[indiceVeicolo], indiceOrario);
                        if (!AggiornaStorico (p1, indiceVeicolo, indiceOrario) || !InserisciPrenotazione (T, p1)){
                            free(nomeUtente);
                            free(dataCorrente);
                            for (int i=0; i < VEICOLI_TAGLIA; i++){
                                liberaVeicolo(V[i]);
                                free(V[i]);
                            }
                            LiberaTabellaHash(T);
                            exit(1);
                        }

                        system("cls | clear");
                        printf ("La sua prenotazione %d e' stata inserita con successo", ID);
                        printf ("\n\n\n");
                        goto inizio;
                    } else if (s == 'N' || s == 'n') {
                        printf ("Mi dispiace, ma la sua prenotazione e' annullata.");
                        printf ("\n\n\n");
                        goto inizio;
                    } else {
                        printf ("Ha inserito un'opezione non valida, riprova: ");
                    }
                }
                } else {
                    printf("\nIl veicolo da lei selezionato non e' disponibile per l'orario scelto\n");
                    if (menuPrincipale() == 0) goto inizio;
                }
            }
            case 2: { // STORICO PRENOTAZIONI

                system ("cls | clear");
                printf ("\n=== STORICO PRENOTAZIONI DI %s === \n\n", nomeUtente);
                StampaPrenotazioneTabellaHash (T, nomeUtente);

                if (menuPrincipale() == 0) goto inizio;
            }

            case 3:{ // VISUALIZZA SCONTI 

                system("cls | clear");
                printf ("\n=== SCONTI ===\n\n");
                printf ("- 30%% sul costo totale se la prenotazione viene effettuata dopo le 20:00\n"); //messo il doppio %% in modo che la printf lo vede come un carattere e non come specificatore di formato
                printf ("- 15%% sul costo totale se la prenotazione viene effettuata prima delle 9:00\n\n");

                if (menuPrincipale() == 0) goto inizio;
            }

            case 4: { // VISUALIZZA VEICOLI

                system("cls | clear");
                printf ("\n=== CATALOGO VEICOLI ===\n");

                for (int i=0; i<10; i++){
                    printf ("\n--- VEICOLO %d ---\n", i);
                    stampaVeicolo (V[i]);
                }

                if (menuPrincipale() == 0) goto inizio;
            }

            case 5: { // TROVA PRENOTAZIONE

                system ("cls | clear");
                printf ("Inserisca l'ID della prenotazione che vuole vedere: ");
                
                int id;
                
                while(1){
                    if(scanf("%d", &id)==1){
                        break;
                    }else{
                        printf("ID non valido,riprovare: ");
                    }
                while((getchar()) !='\n');
                }

                Prenotazione p = TrovaPrenotazione (T, id, taglia);
                if (p != NULL){
                    system("cls | clear");
                    printf ("Ecco la sua prenotazione con ID %d:\n", id);
                    stampaPrenotazione(p);
                    if (menuPrincipale() == 0) goto inizio;
                }

                printf("Non e' stata trovata la prenotazione con ID scelto a nome di %s\n", nomeUtente);
                getchar();
                if (menuPrincipale() == 0) goto inizio;
            }
            case 6: { // ESCI

                system("cls | clear");
                printf ("Grazie mille per aver scelto il nostro servizio!");
                free(nomeUtente);
                for (int i=0; i < VEICOLI_TAGLIA; i++){
                    liberaVeicolo(V[i]);
                    free(V[i]);
                }
                LiberaTabellaHash(T);
                exit(0);
            }
            default: { // ERRORE GENERICO

                system("cls | clear");
                printf("ERRORE: Associazione dell'operazione fallita.\n");
                free(nomeUtente);
                for (int i=0; i < VEICOLI_TAGLIA; i++){
                    liberaVeicolo(V[i]);
                    free(V[i]);
                }
                LiberaTabellaHash(T);
                exit(1);
            }
        }
}
