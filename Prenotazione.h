#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"

typedef struct item* Prenotazione;

void LiberaLista (Prenotazione p); // Dealloca una lista collegata nella tabella hash

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, int i, char* dataPrenotazione); //Crea una nuova prenotazione

void stampaPrenotazione (Prenotazione p); // stampa i dettagli di una prenotazione

int ottieniID (Prenotazione p);

struct item *ottieniNext(Prenotazione p);

char* ottieniNomeUtente(Prenotazione p);

char* ottieniDataPrenotazione(Prenotazione p);

float ottieniInizioPrenotazione(Prenotazione p);

float ottieniFinePrenotazione(Prenotazione p);

char* ottieniModelloPrenotazione(Prenotazione p);

char* ottieniTargaPrenotazione(Prenotazione p);

float costoNoleggio (veicolo v, int k);