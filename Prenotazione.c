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

#define HASH_TAGLIA 30

struct item {

    int ID; //chiave dell'item prenotazione
    char* nomeUtente;
    veicolo v;
    char* data;
    float CostoNoleggioFinale;
    float OrarioSceltoInizio;
    float OrarioSceltoFine;
    struct item *next; 

};

struct hash{

    int taglia;
    struct item **tabella; 
};

int ottieniTaglia (TabellaHash t){
    return t->taglia;
}

char* ottieniData(){ 

    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970

    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla

    char buffer[20];

    strftime (buffer, sizeof (buffer), "%d/%m/%Y", data); //formatta la data nel buffer

    char* dataFormattata = malloc (strlen(buffer) + 1);

    if(dataFormattata == NULL){

        system("cls|clear");
        perror("ERRORE IN DATA!");
        return NULL;
    }

    strcpy(dataFormattata, buffer);

    return dataFormattata;

}
/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: NuovaTabellaHash
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

TabellaHash NuovaTabellaHash (int taglia){

    TabellaHash t = malloc (sizeof (struct hash)); //Alloco memoria per la tabella hash

    if (t == NULL){
        system("cls | clear");
        perror ("Errore nell'allocazione della memoria tabella hash.");
        exit (1);
    }

    t->taglia = taglia+HASH_TAGLIA;

    t->tabella = calloc ((taglia+HASH_TAGLIA), sizeof (struct item *)); 

    if (t->tabella == NULL){

        free (t);
        return NULL;
    }

    return t;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: FunzioneHash
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int FunzioneHash(int ID, int taglia) {

    int hash = 0;
    
    hash = (31 * ID) % taglia;
    
    return hash;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: NuovaPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, int i, char* dataPrenotazione){

    Prenotazione p = malloc (sizeof (struct item));

    if (p == NULL){

        system("cls | clear");
        perror ("Errore nella creazione della prenotazione.");
        exit (1);
    }

    p->ID = ID;

    p->nomeUtente = malloc (strlen (NomeUtente)+1);

    if (p->nomeUtente == NULL){
        system("cls | clear");
        perror ("ERRORE NEL NOME UTENTE!");
        exit (1);
    }

    strcpy (p->nomeUtente, NomeUtente);

    p->v = c;

    p->data = strdup (dataPrenotazione);

    if (p->data == NULL){

        perror ("Errore.");
        free (p->nomeUtente);
        free (p);
        exit(1);
    }
    
    p->OrarioSceltoInizio = p->v->orari[i].inizio;
    
    p->OrarioSceltoFine = p->v->orari[i].fine;
    
    p->CostoNoleggioFinale = costoNoleggio (c, i);

    p->next = NULL;

    return p;

}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: InserisciPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int InserisciPrenotazione (TabellaHash t, Prenotazione p){

    int indice;

    Prenotazione testa, corrente;

    indice = FunzioneHash (p->ID, t->taglia);

    corrente = testa = t->tabella[indice];

    while (corrente){

        if (corrente->ID == p->ID){

            return 0;
        }
        corrente = corrente->next;
    }

    t->tabella[indice] = p;
    t->tabella[indice]->next = testa;

    return 1;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LiberaTabellaHash
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void LiberaTabellaHash (TabellaHash t){

    int i;

    for (int i=0; i< t->taglia; i++){

        LiberaLista (t->tabella[i]);
    }

    free (t->tabella);

    free (t);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LiberaLista
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

static void LiberaLista (Prenotazione p){

    Prenotazione nuovap;

    while (p != NULL){

        nuovap = p->next;

        free(p->nomeUtente);

        free(p->data);

        free (p);

        p = nuovap;
    }
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: AggiornaStorico
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int AggiornaStorico (Prenotazione p, int indiceVeicolo, int indiceOrario){

    FILE* file;

    file = fopen ("StoricoPrenotazioni.txt", "a");

    if (file == NULL){

        system("cls | clear");
        perror ("Errore nell'apertura dello storico");
        return 0;
    }

   
    fprintf (file, "\n%s-%s-%.2f-%.2f-%d-%s-%s-%d-%d", p->nomeUtente, p->data, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->ID, p->v->modello, p->v->targa, indiceVeicolo, indiceOrario); // effettuata modifica per gli indici utili nell'inserimento della tabella hash

    return chiudiFile(file);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */




void stampaPrenotazione (Prenotazione p){ 

    printf("\nID Prenotazione: %d\nData: %s\nModello: %s\nOrario selezionato: %.2f/%.2f\nCosto noleggio: %.2f euro\n", p->ID, p->data, p->v->modello, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->CostoNoleggioFinale);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: TrovaPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

Prenotazione TrovaPrenotazione (TabellaHash t, int ID, int taglia){

    int indice = FunzioneHash (ID, taglia);

    Prenotazione p = t->tabella[indice];

    while (p != NULL){

        if (p->ID == ID){
            return p;
        }

        p = p->next;

    }

    return NULL;
}

TabellaHash RiempiTabellaHashDaFile (veicolo *v){

    FILE* file = fopen ("StoricoPrenotazioni.txt", "r");

    if (file == NULL){

        perror ("Errore nella lettura dello storico.");
        return NULL;
    }

    char buffer [200];
    int contatorePrenotazioni=0;

    while (fgets (buffer, sizeof (buffer), file) != NULL){

        contatorePrenotazioni++;
    }

    rewind (file);


    TabellaHash t = NuovaTabellaHash (contatorePrenotazioni);

    if (contatorePrenotazioni == 0){

        if (!(chiudiFile(file))){
            return NULL;
        }

        return t;
    }

    char* dataCorrente = ottieniData();

    fgets(buffer, sizeof(buffer), file); // leggo a vuoto per partire dalla riga contenente la prenotazione (line 1: "\n")

    while (fgets (buffer, sizeof (buffer), file) != NULL){

        char* token = strtok (buffer, "-");
        if (!(controlloToken (token))){
            chiudiFile(file);
            return NULL;
        }

        char* nomeUtente = strdup (token);

        if (nomeUtente == NULL){
            chiudiFile(file);
            perror ("Errore nell'inserimento del nome utente della prenotazione nella tabella Hash.");
            return NULL;
        }

        token = strtok (NULL, "-");
        if (!(controlloToken (token))){
            chiudiFile(file);
            free(nomeUtente);
            return NULL;
        }
        
        char* dataPrenotazione = strdup (token);

        if (dataPrenotazione == NULL){
            free(nomeUtente);
            chiudiFile(file);
            perror ("Errore nell'inserimento della data della prenotazione nella tabella Hash");
            return NULL;
        }
        for (int k=0; k < 3; k++){
            token = strtok (NULL, "-");
            if (!(controlloToken (token))){
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
            chiudiFile(file);
            free(nomeUtente);
            free(dataPrenotazione);
            return NULL;
            }
        }

        int IndiceVeicoloScelto = atoi (token);

        token = strtok (NULL, "-");
        if (!(controlloToken (token))){
        chiudiFile(file);
        free(nomeUtente);
        free(dataPrenotazione);
        return NULL;
        }

        int IndiceOrarioScelto = atoi (token);

        Prenotazione prenotazioneFile = NuovaPrenotazione (ID, nomeUtente, v[IndiceVeicoloScelto], IndiceOrarioScelto, dataPrenotazione);

        InserisciPrenotazione(t,prenotazioneFile);

        if (strcmp(dataCorrente, dataPrenotazione) == 0){

            modificaDisponibilita(v[IndiceVeicoloScelto], IndiceOrarioScelto);
        }

            free(nomeUtente);

            free(dataPrenotazione);
        }

        if (!(chiudiFile(file))){
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

            if (v[i]->orari[k].inizio <= oraCorrente){

                modificaDisponibilita (v[i], k);
            }
        }
    }

}

void StampaPrenotazioneTabellaHash (TabellaHash t, char* nomeUtente){
    
    
    int g = ottieniTaglia(t);

    int prenotazioniEffettuate = 0;

    for (int i=0; i < g; i++){

    if (t->tabella[i] != NULL){

        Prenotazione P = t->tabella[i];

        if (strcmp (P->nomeUtente, nomeUtente) == 0){

        prenotazioniEffettuate++;

        stampaPrenotazione (P);

        }

        } 
    }

    if (prenotazioniEffettuate == 0){

        printf ("Mi dispiace, non sono presenti prenotazioni a suo nome.\n");
    }

}
