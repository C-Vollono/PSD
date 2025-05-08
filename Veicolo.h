#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vettura *veicolo;

void stampaVeicolo (veicolo v); // Check

void modificaDisponibilità (veicolo v, int k); // Check

float costoNoleggio (veicolo v, int k); // Check

void riempiVeicoli (veicolo v, char* nomefile); // Check

void riempiOrari (veicolo v, char* nomefile); // Check

void stampaOrari (veicolo v); // Check

void verificaDisponibilità (veicolo v, int k); // Check

float verificaSconto (veicolo v, int k); // Check

void aggiornaOrari (veicolo v, char* nomefile, int i, int k); // Check

void liberaVeicoli (veicolo v); // Check
