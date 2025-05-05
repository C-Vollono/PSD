#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veicolo.h"

typedef struct Orario {

    float inizio;

    float fine;

    int Disponibilità;
}Orario;

struct Veicolo{

    char tipoVeicolo[30];

    char modello[20];

    char colore [20];

    char targa [7];

    Orario orari[10];

    int postiOmologati;

    char Combustibile [20];

    int annoDiImmatricolazione;

    float CostoNoleggioOrario;
};


void stampaVeicolo (veicolo v){

    printf ("VEICOLO:\nTipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f€/h", v->tipoVeicolo, v->modello, v->colore, v->targa, v->postiOmologati, v->Combustibile,v->annoDiImmatricolazione, v->CostoNoleggioOrario);

    printf ("Fasce Orarie: ");
    
    stampaOrari (v);
}

void stampaOrari (veicolo v){

    for (int i=0; i<8; i++){

        printf ("%.2f-%.2f Disponibilità: %s", v->orari->inizio, v->orari->fine, verificaDisponibilità(v));
    }
}
