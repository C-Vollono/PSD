#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "TabellaHash.h"
#include "Utile.h"


char* ottieniData(){ 
    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970
    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla
    char buffer[20];
    strftime (buffer, sizeof (buffer), "%d/%m/%Y", data); //formatta la data nel buffer
    char* dataFormattata = malloc (strlen(buffer) + 1);

    if(dataFormattata == NULL){
        system("cls|clear");
        perror("ERRORE: Allocazione memoria data formattata fallita.\n");
        return NULL;
    }

    strcpy(dataFormattata, buffer);
    return dataFormattata;
}

int AggiornaStorico (Prenotazione p, int indiceVeicolo, int indiceOrario){
    FILE* file;
    file = fopen ("StoricoPrenotazioni.txt", "a");

    if (file == NULL){
        system("cls | clear");
        perror ("ERRORE: Aggiornamento dello storico da file fallito.\n");
        return 0;
    }

    fprintf (file, "\n%s-%s-%.2f-%.2f-%d-%s-%s-%d-%d", ottieniNomeUtente(p), ottieniDataPrenotazione(p), ottieniInizioPrenotazione(p), ottieniFinePrenotazione(p), ottieniID(p), ottieniModelloPrenotazione(p), ottieniTargaPrenotazione(p), indiceVeicolo, indiceOrario); // effettuata modifica per gli indici utili nell'inserimento della tabella hash

    return chiudiFile(file);
}

TabellaHash RiempiTabellaHashDaFile (veicolo *v){
    FILE* file = fopen ("StoricoPrenotazioni.txt", "r");
    if (file == NULL){
        perror ("ERRORE: Lettura dello storico da file fallito.\n");
        return NULL;
    }

    char buffer [1024];
    int contatorePrenotazioni=0;

    while (fgets (buffer, sizeof (buffer), file) != NULL){ contatorePrenotazioni++; }
    rewind (file);

    TabellaHash t = NuovaTabellaHash (contatorePrenotazioni);
    if (t == NULL){
        return NULL;
    }

    if (contatorePrenotazioni == 0){
        if (!(chiudiFile(file))){
            return NULL;
        }
        return t;
    }

    char* dataCorrente = ottieniData();
    if (dataCorrente == NULL){
        printf("ERRORE: Ottenimento data locale fallito.\n");
        LiberaTabellaHash(t);
        return NULL;
    }
    
    fgets(buffer, sizeof(buffer), file); // Leggo a vuoto per partire dalla riga contenente la prenotazione (line 1: "\n")
    while (fgets (buffer, sizeof (buffer), file) != NULL){
        char* token = strtok (buffer, "-");
        if (!(controlloToken (token))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            return NULL;
        }
        
        char* nomeUtente = strdup (token);
        if (nomeUtente == NULL){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            perror ("ERRORE: Inserimento del nome utente della prenotazione nella tabella hash fallito.\n");
            return NULL;
        }

        token = strtok (NULL, "-");
        if (!(controlloToken (token))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            free(nomeUtente);
            return NULL;
        }
        
        char* dataPrenotazione = strdup (token);
        if (dataPrenotazione == NULL){
            free(dataCorrente);
            LiberaTabellaHash(t);
            free(nomeUtente);
            chiudiFile(file);
            perror ("ERRORE: Inserimento della data della prenotazione nella tabella hash fallito.\n");
            return NULL;
        }

        for (int k=0; k < 3; k++){
            token = strtok (NULL, "-");
            if (!(controlloToken (token))){
                free(dataCorrente);
                LiberaTabellaHash(t);
                chiudiFile(file);
                free(nomeUtente);
                free(dataPrenotazione);
                return NULL;
            }
        }

        int ID = atoi (token);

        for (int k=0; k < 3; k++){
            token = strtok (NULL, "-");
            if (!(controlloToken (token))){
                free(dataCorrente);
                LiberaTabellaHash(t);
                chiudiFile(file);
                free(nomeUtente);
                free(dataPrenotazione);
                return NULL;
            }
        }

        int IndiceVeicoloScelto = atoi (token);

        token = strtok (NULL, "-");
        if (!(controlloToken (token))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            free(nomeUtente);
            free(dataPrenotazione);
            return NULL;
        }

        int IndiceOrarioScelto = atoi (token);

        Prenotazione prenotazioneFile = NuovaPrenotazione (ID, nomeUtente, v[IndiceVeicoloScelto], IndiceOrarioScelto, dataPrenotazione);
        if (prenotazioneFile == NULL){
            printf("ERRORE: Caricamento della prenotazione da file fallito.\n");
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            free(nomeUtente);
            free(dataPrenotazione);
            return NULL;
        }
        InserisciPrenotazione(t,prenotazioneFile);

        if (strcmp(dataCorrente, dataPrenotazione) == 0){
            modificaDisponibilita(v[IndiceVeicoloScelto], IndiceOrarioScelto);
        }
        free(nomeUtente);
        free(dataPrenotazione);
        }

        if (!(chiudiFile(file))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            return NULL;
        }

        free(dataCorrente);

    return t;    
}

void LimitaOrariDisponibili (veicolo *v){
    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970
    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla
    int oraCorrente = data->tm_hour;
    int minutoCorrente = data->tm_min;

    for (int i=0; i<10; i++){
        for (int k=0; k<8; k++){
            if (ottieniOrarioInizio(v[i], k) <= oraCorrente){
                modificaDisponibilita (v[i], k);
            }
        }
    }
}

float verificaSconto (veicolo v, int k){
      float orario = ottieniOrarioInizio(v , k);
      if (orario >= 20.00 ){
        return 0.7; //Sconto del 30% se l'orario prenotato è dalle 20.00 in poi
      } else if (orario < 9) {
        return 0.85; //Sconto del 15% se l'orario prenotato è prima delle 9.00
      } else return 1.0;
}

int verificaDisponibilita(veicolo v, int indiceOrario){
    if (ottieniDisponibilita(v, indiceOrario) == 0){
        return 1;
    }
        return 0;
}

void stampaOrari (veicolo v){
        printf("\nLista degli orari del veicolo scelto\n\n");
        for (int k=0; k<8; k++){
            printf (" (%d) %.2f-%.2f ", k, ottieniOrarioInizio(v, k), ottieniOrarioFine(v, k));
        stampaDisponibilita(v, k);
        }
}

int controlloToken (char* token){ 
    if (token == NULL){
        system("cls | clear");
        printf("ERRORE: Ottenimento token fallito.\n");
        return 0;
    }
    return 1;
}

int chiudiFile(FILE* file){ 
    if (fclose (file) != 0){
        perror ("ERRORE: Chiusura del file fallita.\n");
        return 0;
    }
    return 1;
}