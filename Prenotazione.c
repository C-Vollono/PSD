#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int InserisciPrenotazione (TabellaHash t, Prenotazione p, int i){

    int indice;
    Prenotazione testa, corrente;

    indice = FunzioneHash (p->ID, t->taglia);

    corrente = testa = t->tabella[indice];

    while (corrente){

        if (strcmp (corrente->ID, p->ID) == 0){

            return 0;
        }
        corrente = corrente->next;
    }

    t->tabella[indice] = NuovaPrenotazione (p->ID, p->nomeUtente, p->v, p->CostoNoleggioFinale, i);
    t->tabella[indice]->next = testa;

    return 1;
}

Prenotazione EliminaPrenotazione (TabellaHash t, int ID){

    int indice;
    Prenotazione precedente, corrente, testa, temporaneo;

    indice = FunzioneHash (ID, t->taglia);

    precedente = corrente = testa = t->tabella[indice];

    
}