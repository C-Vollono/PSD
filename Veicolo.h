#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vettura *veicolo;

void stampaVeicolo (veicolo v);

void modificaDisponibilità (veicolo v); 

float costoNoleggio (veicolo v);

void riempiVeicoli (veicolo v, char* nomefile);

void riempiOrari (veicolo v, char* nomefile);

void stampaOrari (veicolo v);

void verificaDisponibilità (veicolo v);

float verificaSconto (veicolo v);

void aggiornaVeicoli (veicolo v, char* nomefile);

void aggiornaOrari (veicolo v, char* nomefile);

void liberaVeicoli (veicolo v);
