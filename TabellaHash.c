#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabellaHash.h"
#include "Prenotazione.h"

#define HASH_TAGLIA 30

struct hash{
    int taglia;
    struct item **tabella; 
};

int ottieniTaglia (TabellaHash t){
    return t->taglia;
}


TabellaHash NuovaTabellaHash (int taglia){
    TabellaHash t = malloc (sizeof (struct hash)); //Alloco memoria per la tabella hash
    if (t == NULL){
        system("cls | clear");
        perror ("ERRORE: Allocazione della memoria per la tabella hash fallita.\n");
        return NULL;
    }

    t->taglia = taglia+HASH_TAGLIA;
    t->tabella = calloc ((taglia+HASH_TAGLIA), sizeof (struct item *)); 

    if (t->tabella == NULL){
        free (t);
        return NULL;
    }

    return t;
}

int FunzioneHash(int ID, int taglia) {
    return ((31 * ID) % taglia);
}

int InserisciPrenotazione (TabellaHash t, Prenotazione p){
    int indice;
    Prenotazione testa, corrente, temp;
    indice = FunzioneHash (ottieniID(p), t->taglia);
    corrente = testa = t->tabella[indice];
    while (corrente){
        if (ottieniID(corrente) == ottieniID(p)){
            return 0;
        }
        corrente = ottieniNext(corrente);
    }
    
    t->tabella[indice] = p;
    temp = ottieniNext(t->tabella[indice]);
    temp = testa;


    return 1;
}

void LiberaTabellaHash (TabellaHash t){

    for (int i=0; i< t->taglia; i++){
        LiberaLista (t->tabella[i]);
    }

    free (t->tabella);
    free (t);
}

void StampaPrenotazioneTabellaHash (TabellaHash t, char* nomeUtente){
    int g = ottieniTaglia(t);
    int prenotazioniEffettuate = 0;

    for (int i=0; i < g; i++){
        if (t->tabella[i] != NULL){
            Prenotazione P = t->tabella[i];
            if (strcmp (ottieniNomeUtente(P), nomeUtente) == 0){
                prenotazioniEffettuate++;
                stampaPrenotazione (P);
            }
        } 
    }

    if (prenotazioniEffettuate == 0){
        printf ("Non risultano presenti prenotazioni a suo nome.\n");
    }
}

Prenotazione TrovaPrenotazione (TabellaHash t, int ID, int taglia){
    int indice = FunzioneHash (ID, taglia);
    Prenotazione p = t->tabella[indice];
    while (p != NULL){
        if (ottieniID(p) == ID){
            return p;
        }
        p = ottieniNext(p);
    }
    return NULL;
}