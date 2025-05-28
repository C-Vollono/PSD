/*ATTENZIONE: Nel codice sono presenti comandi system
              Implementati per la pulizia del terminale
              Potrebbero creare conflitti o problemi di vari natura
              "Annullarli" nel caso della presenza di quest'ultimi*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "Menu.h"
#include "TabellaHash.h"
#include "Utile.h"
#include "Testing.h"

#define VEICOLI_TAGLIA 10

void main () {

    char* nomeUtente;
    veicolo V[VEICOLI_TAGLIA];

    nomeUtente = menuAccesso(); //Richiamo alla funzione menuAccesso per login o registrazione
    
    for (int i=0; i < VEICOLI_TAGLIA; i++){
        V[i] = creaVeicolo(); 
        if (V[i] == NULL){  
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

    TabellaHash T;

    FILE *TC1_Output = fopen("TC1_output.txt", "w"); // pulizia dell'output tc1 dato che e' in appending
inizio:
    printf ("===== BENVENUT* %s NEL NOSTRO CAR-SHARING =====\n\n", nomeUtente);
    printf ("1) TC1 Nuova Prenotazione\n2) TC4 Testing storico prenotazioni\n3) TC2 Testing Costonoleggio\n4) TC3 Testing visualizzazione veicoli\n5) Esci\n");
    printf ("\nScelga l'operazione da effettuare (da 1-5): ");
        
    char scelta[1024];
    while (1){
        fgets(scelta, sizeof(scelta), stdin);
        scelta[strcspn(scelta, "\n")] = '\0';
        if (strlen(scelta) == 1 && scelta[0] >= '1' && scelta[0] <= '5'){
            break;
        }
        printf("Operazione non valida, riprova: ");
    }
    
    int sceltaInt = scelta[0] - '0';

    switch (sceltaInt) {
        case 1: { //TC1, testing nuova prenotazione

        T = NuovaTabellaHash(0);
        if (T == NULL){
        printf("ERRORE: Caricamento prenotazioni fallito.\n");
        free(nomeUtente);
        for (int i=0; i < VEICOLI_TAGLIA; i++){
            liberaVeicolo(V[i]);
            free(V[i]);
        }
        exit(1);
        }

        FILE *file= fopen("TC1_input.txt", "r");
                char buffer[1024];
                int indiceVeicolo, indiceOrario;
                fgets(buffer, sizeof(buffer), file);
                buffer[strcspn(buffer, "\n")] = '\0';
                indiceVeicolo= buffer[0] - '0';
                fgets(buffer, sizeof(buffer), file);
                buffer[strcspn(buffer, "\n")] = '\0';
                indiceOrario= buffer[0] - '0';
                
            if (verificaDisponibilita(V[indiceVeicolo],indiceOrario)){
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


                        int loopOrari = 0;
                        while (loopOrari < 8){
                            if (!stampaDisponibilitaFile(V[indiceVeicolo], loopOrari)){
                                free(nomeUtente);
                                free(dataCorrente);
                                for (int i=0; i < VEICOLI_TAGLIA; i++){
                                    liberaVeicolo(V[i]);
                                    free(V[i]);
                                }
                            LiberaTabellaHash(T);
                            exit(1);
                        }
                        loopOrari++;
                        }

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

                        loopOrari=0;
                        while (loopOrari < 8){
                            if (!stampaDisponibilitaFile(V[indiceVeicolo], loopOrari)){
                                free(nomeUtente);
                                free(dataCorrente);
                                for (int i=0; i < VEICOLI_TAGLIA; i++){
                                    liberaVeicolo(V[i]);
                                    free(V[i]);
                                }
                                LiberaTabellaHash(T);
                                exit(1);
                            }
                        loopOrari++;
                        }

                        if (!confrontofile("TC1_output.txt", "TC1_oracle.txt", 1)){
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
                        printf ("La sua prenotazione %d e' stata inserita con successo.\n", ID);
                        printf("OPERAZIONE PRECEDENTE: nuova prenotazione.\n");
                        goto inizio;
                } 
            }

            case 2: { //Testing storico prenotazioni

            T = RiempiTabellaHashDaFile(V, 4);

                system ("cls | clear");
                if (!controlloStorico(T)){
                    free(nomeUtente);
                    for (int i=0; i < VEICOLI_TAGLIA; i++){
                        liberaVeicolo(V[i]);
                        free(V[i]);
                    }
                LiberaTabellaHash(T);
                exit(1);
                }

                if (!confrontofile("TC4_output.txt", "TC4_oracle.txt", 4)){
                            free(nomeUtente);
                            for (int i=0; i < VEICOLI_TAGLIA; i++){
                                liberaVeicolo(V[i]);
                                free(V[i]);
                            }
                        LiberaTabellaHash(T);
                        exit(1);
                }
                printf("OPERAZIONE PRECEDENTE: storico prenotazioni.\n");
                goto inizio;
                
            }

            case 3:{ //Testing costoNoleggio
                T = NuovaTabellaHash(0);
                char* dataCorrente = ottieniData();
                srand (time(NULL));
                int ID = rand();
                FILE *file= fopen("TC2_input.txt", "r");
                char buffer[1024];
                int indiceVeicolo, indiceOrario;
                fgets(buffer, sizeof(buffer), file);
                buffer[strcspn(buffer, "\n")] = '\0';
                indiceVeicolo= buffer[0] - '0';
                fgets(buffer, sizeof(buffer), file);
                buffer[strcspn(buffer, "\n")] = '\0';
                indiceOrario= buffer[0] - '0';
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

                if (!stampaCostofile(p1)){
                    free(nomeUtente);
                    for (int i=0; i < VEICOLI_TAGLIA; i++){
                        liberaVeicolo(V[i]);
                        free(V[i]);
                    }
                LiberaTabellaHash(T);
                exit(1);
                }
                if (!confrontofile("TC2_output.txt", "TC2_oracle.txt", 2)){
                    free(nomeUtente);
                    for (int i=0; i < VEICOLI_TAGLIA; i++){
                        liberaVeicolo(V[i]);
                        free(V[i]);
                    }
                LiberaTabellaHash(T);
                exit(1);
                }
                system("cls");
                printf("OPERAZIONE PRECEDENTE: preventivo costo noleggio.\n");
                goto inizio;
        }

            case 4: { //Visualizza veicoli
                system("cls | clear");
                if (!StampaVeicoliFile(V)){
                    free(nomeUtente);
                    for (int i=0; i < VEICOLI_TAGLIA; i++){
                        liberaVeicolo(V[i]);
                        free(V[i]);
                    }
                LiberaTabellaHash(T);
                exit(1);
                }
                if (!confrontofile("TC3_output.txt", "TC3_oracle.txt", 3)){
                    free(nomeUtente);
                    for (int i=0; i < VEICOLI_TAGLIA; i++){
                        liberaVeicolo(V[i]);
                        free(V[i]);
                    }
                LiberaTabellaHash(T);
                exit(1);
                }
                printf("OPERAZIONE PRECEDENTE: visualizzazione veicoli.\n");
                goto inizio;
            }

            case 5: { //Esci
                system("cls | clear");
                printf ("Grazie mille per aver scelto il nostro servizio!");

                for (int i=0; i < VEICOLI_TAGLIA; i++){
                    liberaVeicolo (V[i]);
                }
                LiberaTabellaHash (T);
                exit (0);
            }
            default: { //Errore in caso non si inserisca un numero corretto
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

