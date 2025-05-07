#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vettura *veicolo;

void stampaVeicolo (veicolo v, int i);

void modificaDisponibilità (veicolo v, int i, int k); 

float costoNoleggio (veicolo v, int i, int k);

void riempiVeicoli (veicolo v, char* nomefile);

void riempiOrari (veicolo v, char* nomefile);

void stampaOrari (veicolo v, int i);

void verificaDisponibilità (veicolo v, int i, int k);

float verificaSconto (veicolo v);

void aggiornaVeicoli (veicolo v, char* nomefile);

void aggiornaOrari (veicolo v, char* nomefile);

void liberaVeicoli (veicolo v);
