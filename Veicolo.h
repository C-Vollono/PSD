#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vettura *veicolo;

void stampaVeicolo (veicolo v);

void modificaDisponibilità (veicolo v, int k);

float costoNoleggio (veicolo v, int k);

void riempiVeicoli (veicolo v, char* nomefile);

void riempiOrari (veicolo v, char* nomefile);

void stampaOrari (veicolo v);

void verificaDisponibilità (veicolo v, int k);

float verificaSconto (veicolo v, int k);

void liberaVeicoli (veicolo v);
