#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"

typedef struct hash* TabellaHash;
typedef struct item* Prenotazione;

TabellaHash NuovaTabellaHash (int taglia); //crea e alloca memoria per una tabella hash

int FunzioneHash (int ID, int taglia); //funzione hash che restituisce l'indice nella tabella hash collegato alla chiave, che è l'id

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, int i); //Crea una nuova prenotazione

int InserisciPrenotazione (TabellaHash t, Prenotazione p); //Inserisce una prenotazione nella tabella hash

void LiberaTabellaHash (TabellaHash t); //Dealloca la memoria occupata dalla tabella hash

static void LiberaLista (Prenotazione p); // Dealloca una lista collegata nella tabella hash

void AggiornaStorico (Prenotazione p, int indiceVeicolo, int indiceOrario); //Aggiorna lo storico prenotazioni con l'ultima prenotazione effettuata

void stampaPrenotazione (Prenotazione p); // stampa i dettagli di una prenotazione, da aggiormare con operazione: 1 indica lo stampa per la conferma, 2 indica lo stampa per lo storico

Prenotazione TrovaPrenotazione (TabellaHash t, int ID, int taglia); //cerca una prenotazione nella tabella hash in base all'id

TabellaHash RiempiTabellaHashDaFile (veicolo *v); //riempie la tabella hash leggendo le prenotazione dal file StoricoPrenotazioni

int ottieniTaglia (TabellaHash t); // ottiene la taglia della tabella hash

char* ottieniData(); // restituisce la data formattata
