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
    char* orarioScelto; //da valutare il tipo di questo campo
    struct item *next; //nodo per gestire eventuali collissioni nelle liste collegate

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