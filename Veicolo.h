#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vettura *veicolo;

void stampaVeicolo (veicolo v, int i); // Check

void modificaDisponibilità (veicolo v, int i, int k); // Check

float costoNoleggio (veicolo v, int i, int k); // Check

void riempiVeicoli (veicolo v, char* nomefile); // Check

void riempiOrari (veicolo v, char* nomefile); // Check

void stampaOrari (veicolo v, int i); // Check

void verificaDisponibilità (veicolo v, int i, int k); // Check

float verificaSconto (veicolo v, int i, int k); // Check

void aggiornaVeicoli (veicolo v, char* nomefile); // Da disctutere

void aggiornaOrari (veicolo v, char* nomefile, int i, int k); // Check

void liberaVeicoli (veicolo v); // Check
