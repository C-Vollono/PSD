#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "TabellaHash.h"

char* ottieniData();

int AggiornaStorico (Prenotazione p, int indiceVeicolo, int indiceOrario);

TabellaHash RiempiTabellaHashDaFile (veicolo *v);

void LimitaOrariDisponibili (veicolo *v);

float verificaSconto (veicolo v, int k);

int verificaDisponibilita(veicolo v, int indiceOrario);

void stampaOrari (veicolo v);

int controlloToken (char* token);

int chiudiFile(FILE* file);