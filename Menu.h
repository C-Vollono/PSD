#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veicolo.h"
#include "Prenotazione.h"

int operazioneAccesso (int operazione, char **nome_utente); // Elaborazione dell'username dell'utente

char* menuAccesso(); // Funzione principale per l'accesso

int menuPrincipale(char scelta);
