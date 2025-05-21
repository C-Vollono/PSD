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
    struct item *next; //nodo per gestire eventuali collisioni nelle liste collegate

};

struct hash{

    int taglia;
    struct item **tabella; // Puntatore a un array di puntatori a item, che poi andrà a definire le varie liste collegate
};

// funzione per ottenere la taglia della tabella hash, nel caso anche se in reallocazione, per rispettare l'information hiding

int ottieniTaglia (TabellaHash t){
    return t->taglia;
}


// Funzione che permette di ottenere la data locale gia' formattata

char* ottieniData(){ 

    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970

    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla

    char buffer[20];

    strftime (buffer, sizeof (buffer), "%d/%m/%Y", data); //formatta la data nel buffer

    char* dataFormattata = malloc (strlen(buffer) + 1);

    if(dataFormattata == NULL){
        system("cls|clear");
        perror("ERRORE IN DATA!");
        exit(1);
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

    t->tabella = calloc ((taglia+HASH_TAGLIA), sizeof (struct item *)); //Alloco memoria e inizializzo a NULL tutti i puntatori a item

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

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, int i){ // MODIFICARE IN BASE ALL'IMPLEMENTAZIONE DI CARICA FILE
 
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

    p->data = ottieniData();
    
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

void AggiornaStorico (Prenotazione p, int indiceVeicolo, int indiceOrario){

    FILE* file;

    file = fopen ("StoricoPrenotazioni.txt", "a");

    if (file == NULL){
        system("cls | clear");
        perror ("Errore nell'apertura dello storico");
        exit (1);
    }

   
    fprintf (file, "\n%s-%s-%.2f-%.2f-%d-%s-%s-%d-%d", p->nomeUtente, p->data, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->ID, p->v->modello, p->v->targa, indiceVeicolo, indiceOrario); // effettuata modifica per gli indici utili nell'inserimento della tabella hash

    if (fclose (file) != 0){
        system("cls | clear");
        perror ("Errore nella chiusura dello storico.");
        exit (1);
    }
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




void stampaPrenotazione (Prenotazione p){ // da aggiungere le operazioni per la stampa relativa allo storico, e quella relativa alla conferma prenotazione

        // Caso in cui stampo i dati per confermare la prenotazione
        printf("\nID Prenotazione: %d\nOrario selezionato: %.2f/%.2f\nCosto noleggio: %.2f euro\n", p->ID, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->CostoNoleggioFinale);
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
        exit (1);
    }

    char buffer [200];
    int z=0; // variabile che viene incrementata ogni volta che legge una prenotazione dal file, così alla fine si ha la grandezza necessaria per contenere le prenotazioni precedenti 

    while (fgets (buffer, sizeof (buffer), file) != NULL){

        z++;
    }

    rewind (file);


    TabellaHash t = NuovaTabellaHash (z);

    if (z == 0){
        fclose(file);
        return t;
    }
    char* dataCorrente = ottieniData();
    fgets(buffer, sizeof(buffer), file); // leggo a vuoto per partire dalla riga contenente la prenotazione (line 1: "\n")
    while (fgets (buffer, sizeof (buffer), file) != NULL){
        char* token = strtok (buffer, "-");
        // controllo token (senza veicolo)

        char* nomeUtente = strdup (token);

        if (nomeUtente == NULL){

            perror ("Errore tabellahash nome utente.");
            exit (1);
        }

        token = strtok (NULL, "-");
        //controllo token liberare utente nel caso da qui in poi
        
        char* dataPrenotazione = strdup (token);

        if (dataPrenotazione == NULL){
            perror ("Errore. tabella hash data prenotazione");
            exit (1);
        }

        token = strtok (NULL, "-");
        //controllo token liberare utente e dataprenotazione da qui in poi
        
        token = strtok (NULL, "-");
        //controllo token

        token = strtok (NULL, "-");
        //controllo token

        int ID = atoi (token);

        token = strtok (NULL, "-");
        //controllo token

        token = strtok (NULL, "-");
        //controllo token

        token = strtok (NULL, "-");
        //controllo token

        int IndiceVeicoloScelto = atoi (token); // Primo indice aggiunto dopo la targa

        token = strtok (NULL, "-");
        //controllo token

        int IndiceOrarioScelto = atoi (token); // Secondo indice aggiunto dopo la targa

        Prenotazione prenotazioneFile = NuovaPrenotazione (ID, nomeUtente, v[IndiceVeicoloScelto], IndiceOrarioScelto);
        InserisciPrenotazione(t,prenotazioneFile);

        if (strcmp(dataCorrente, dataPrenotazione) == 0){
            modificaDisponibilita(v[IndiceVeicoloScelto], IndiceOrarioScelto);
        }
            free(nomeUtente);
            free(dataPrenotazione);
        }
        fclose(file);
        free(dataCorrente);
    return t;    
}

