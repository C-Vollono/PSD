#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vettura *veicolo;

void stampaVeicolo (veicolo v);

void modificaDisponibilità (veicolo v, int inizio, int fine);

int costoNoleggio (int inizio, int fine, veicolo v);

void riempiVeicoli (veicolo v, char* nomefile);

void salvaOrari (veicolo v, char* nomefile);

void stampaOrari (veicolo v);

char* verificaDisponibilità (veicolo v);
