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

struct item {

    int ID; //chiave dell'item prenotazione
    char* nomeUtente;
    veicolo v;
    float CostoNoleggioFinale;
    float OrarioSceltoInizio;
    float OrarioSceltoFine;
    struct item *next; //nodo per gestire eventuali collisioni nelle liste collegate

};

struct hash{

    int taglia;
    struct item **tabella; // Puntatore a un array di puntatori a item, che poi andrà a definire le varie liste collegate
};

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

    t->taglia = taglia;

    t->tabella = calloc (taglia, sizeof (struct item *)); //Alloco memoria e inizializzo a NULL tutti i puntatori a item

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

int FunzioneHash (int ID, int taglia){

    return ID % taglia;
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

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, float CostoNoleggioFinale, int i){ // MODIFICARE IN BASE ALL'IMPLEMENTAZIONE DI CARICA FILE
 
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
        perror ("ERRORE!");
        exit (1);
    }

    strcpy (p->nomeUtente, NomeUtente);

    p->v = c;

    p->CostoNoleggioFinale = CostoNoleggioFinale;

    p->OrarioSceltoInizio = p->v->orari[i].inizio;
    
    p->OrarioSceltoFine = p->v->orari[i].fine;

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

void AggiornaStorico (Prenotazione p){

    FILE* file;

    file = fopen ("StoricoPrenotazioni.txt", "a");

    if (file == NULL){
        system("cls | clear");
        perror ("Errore nell'apertura dello storico");
        exit (1);
    }

    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970

    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla

    char buffer[20];

    strftime (buffer, sizeof (buffer), "%d / %m / %Y", data); //formatta la data nel buffer

    fprintf (file, "\n%s-%s-%.2f-%.2f-%d-%s-%s", p->nomeUtente, buffer, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->ID, p->v->modello, p->v->targa);

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

void stampaPrenotazione (Prenotazione p){ //funzione da sistemare per il caricamento da file della tabella hash
    FILE *filePrenotazioni = fopen("StoricoPrenotazioni.txt", "r");
    char buffer[200];
    while (fgets (buffer, sizeof (buffer), filePrenotazioni) != NULL){
                        char bufferCopia[200];
                        strcpy(bufferCopia,buffer);
                        char* token = strtok (buffer, "-");
                        // controllo token
                            int i=0;
                            while (i < 4){
                            token = strtok (NULL, "-");
                            // controllo token
                            i++;
                            }
                            int tokenID = atoi(token);
                            if (tokenID == p->ID){
                            token = strtok(bufferCopia, "-");
                            token = strtok(NULL, "-");
                            printf("Ecco la sua prenotazione con ID %d: \n", p->ID);
                            printf("%s-%s-%.2f-%.2f-%d-%s-%s\n", p->nomeUtente, token, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->ID, p->v->modello, p->v->targa);
                            return;   
                        }
        }
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
