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

struct item { // STRUTTURA PRENOTAZIONE DA RIMANERE
    int ID; //chiave dell'item prenotazione
    char* nomeUtente;
    veicolo v;
    char* data;
    float CostoNoleggioFinale;
    float OrarioSceltoInizio;
    float OrarioSceltoFine;
    struct item *next; 
};

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, int i, char* dataPrenotazione){

    Prenotazione p = malloc (sizeof (struct item));
    if (p == NULL){
        system("cls | clear");
        perror ("ERRORE: Creazione della prenotazione fallita.\n");
        return NULL;
    }

    p->ID = ID;
    p->nomeUtente = malloc (strlen (NomeUtente)+1);

    if (p->nomeUtente == NULL){
        system("cls | clear");
        perror ("ERRORE: Allocazione del nome utente per la prenotazione fallita.\n");
        return NULL;
    }
    strcpy (p->nomeUtente, NomeUtente);

    p->v = c;
    p->data = strdup (dataPrenotazione);

    if (p->data == NULL){
        perror ("ERRORE: Allocazione data per la prenotazione fallita.\n");
        free (p->nomeUtente);
        free (p);
        return NULL;
    }
    
    p->OrarioSceltoInizio = p->v->orari[i].inizio; // DA METTERE GETORARIOINIZIO
    p->OrarioSceltoFine = p->v->orari[i].fine; // GETORARIOFINE
    p->CostoNoleggioFinale = costoNoleggio (c, i);
    p->next = NULL;

    return p;
}

static void LiberaLista (Prenotazione p){ // DA METTERE IN PRENOTAZIONE.C 
    Prenotazione nuovap;
    while (p != NULL){
        nuovap = p->next;

        free(p->nomeUtente);
        free(p->data);
        free (p);

        p = nuovap;
    }
}


void stampaPrenotazione (Prenotazione p){ // GET SOPRA DA METTERE IN PRENOTAZIONE.C
    printf("\nID Prenotazione: %d\nData: %s\nModello: %s\nOrario selezionato: %.2f/%.2f\nCosto noleggio: %.2f euro\n", p->ID, p->data, p->v->modello, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->CostoNoleggioFinale);
}

