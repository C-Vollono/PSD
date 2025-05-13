#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veicolo.h"

typedef struct hash* TabellaHash;
typedef struct item* Prenotazione;

TabellaHash NuovaTabellaHash (int taglia); //crea e alloca memoria per una tabella hash

int FunzioneHash (int ID, int taglia); //funzione hash che restituisce l'indice nella tabella hash collegato alla chiave, che è l'id

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, float CostoNoleggioFinale, int i); //Crea una nuova prenotazione

int InserisciPrenotazione (TabellaHash t, Prenotazione p, int i); //Inserisce una prenotazione nella tabella hash

Prenotazione EliminaPrenotazione (TabellaHash t, int ID); //Elimina una prenotazione dalla tabella hash

void LiberaTabellaHash (TabellaHash t); //Dealloca la memoria occupata dalla tabella hash

