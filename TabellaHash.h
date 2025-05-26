#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prenotazione.h"

typedef struct hash* TabellaHash;

int ottieniTaglia (TabellaHash t);

TabellaHash NuovaTabellaHash (int taglia);

int FunzioneHash(int ID, int taglia);

int InserisciPrenotazione (TabellaHash t, Prenotazione p);

void LiberaTabellaHash (TabellaHash t);

void StampaPrenotazioneTabellaHash (TabellaHash t, char* nomeUtente);

Prenotazione TrovaPrenotazione (TabellaHash t, int ID, int taglia);