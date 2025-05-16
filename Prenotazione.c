#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"

struct item {

    int ID; //chiave dell'elemento (da valutare il tipo, se char* oppure int)
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


//Per commentare queste funzioni e capire il loro funzionamento, fare riferimento al codice della prof su e-learning della lezione sulla tabella hash

TabellaHash NuovaTabellaHash (int taglia){

    TabellaHash t = malloc (sizeof (struct hash)); //Alloco memoria per la tabella hash

    if (t == NULL){

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

int FunzioneHash (int ID, int taglia){

    return ID % taglia;
}

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, float CostoNoleggioFinale, int i){

    Prenotazione p = malloc (sizeof (struct item));

    if (p == NULL){

        perror ("Errore nella creazione della prenotazione.");
        exit (1);
    }

    p->ID = ID;

    p->nomeUtente = malloc (strlen (NomeUtente)+1);

    if (p->nomeUtente == NULL){

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

void LiberaTabellaHash (TabellaHash t){

    int i;

    for (int i=0; i< t->taglia; i++){

        LiberaLista (t->tabella[i]);
    }

    free (t->tabella);

    free (t);
}

static void LiberaLista (Prenotazione p){

    Prenotazione nuovap;

    while (p != NULL){

        nuovap = p->next;
        free (p);
        p = nuovap;
    }
}

void AggiornaStorico (Prenotazione p){

    FILE* file;

    file = fopen ("StoricoPrenotazioni.txt", "a");

    if (file == NULL){

        perror ("Errore nell'apertura dello storico");
        exit (1);
    }

    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970

    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla

    char buffer[20];

    strftime (buffer, sizeof (buffer), "%d / %m / %Y", data); //formatta la data nel buffer

    fprintf (file, "%s-%s-%.2f-%.2f-%d-%s-%s", p->nomeUtente, buffer, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->ID, p->v->modello, p->v->targa);

    if (fclose (file) == 0){

        perror ("Errore nella chiusura dello storico.");
        exit (1);
    }
}

void stampaPrenotazione (Prenotazione p){

    printf ("ID prenotazione: %d\nOrario Selezionato: %.2f-%.2f\nCosto Noleggio: %f\n", p->ID, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->CostoNoleggioFinale);
    
}

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
