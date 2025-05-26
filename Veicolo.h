#ifndef VEICOLO_H
#define VEICOLO_H
#include <stdio.h>

typedef struct Vettura *veicolo;

/*DEFINIZIONE FUNZIONI*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiVeicoli
 * -----------------------
 * Prende in input la struct veicolo
 * Riempie la struct veicolo con i dati contenuti nel file Veicolo.txt  
 * 
 * Specifica sintattica:
 *      riempiVeicoli(veicolo) -> int
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *      riempiVeicoli(v) -> 0 se chiusura del file corretta altrimenti 1
 * 
 * Pre-condizione:
 *      Veicolo.txt deve esistere e contenere i dati dei veicoli
 *      La struct veicolo deve esistere
 * 
 * Post-condizione:
 *      La struct veicolo e` riempita con successo
 * 
 * Ritorna:
 *      0 se chiusura del file corretta altrimenti 1
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nella struct veicolo
 *      Se il file è vuoto, la struct veicolo risulta NULL
 *      Stampa errore per apertura del file fallita, per l'allocazione dei vari campi della struct e riempimento fallito
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int riempiVeicoli (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaVeicolo
 * -----------------------
 * Stampa a video i dati della struct veicolo
 * 
 * Specifica sintattica:
 *      stampaVeicoli(veicolo) -> void
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *      stampaVeicoli(v) -> void
 * 
 * Pre-condizione:
 *      La struct veicolo deve contenere dei dati diversi da NULL
 *      
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      Stampa a video i dati della struct veicolo
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaVeicolo (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: liberaVeicolo
 * -----------------------
 *  Libera la memoria della struct veicolo
 * 
 * Specifica sintattica:
 *      liberaVeicolo(veicolo) -> void
 *
 * Parametri:
 *      v: struct veicolo
 *  
 * Specifica semantica:
 *      liberaVeicolo(v) -> void
 * 
 * Pre-condizione:
 *      Memoria allocata per la struct veicolo
 * 
 * Post-condizione:
 *      Memoria liberata correttamente
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      La struct veicolo non ha più dati presenti in memoria
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void liberaVeicolo (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiOrari
 * -----------------------
 * Prende in input la struct veicolo
 * Riempi la struct annidata Orari con i dati contenuti nel file Orari.txt
 * 
 * Specifica sintattica:
 *      riempiOrari(veicolo) -> int
 *
 * Parametri:
 *      v: struct veicolo
 *      
 * Specifica semantica:
 *      riempiOrari(v) -> 0 se chiusura del file corretta altrimenti 1
 *       
 * Pre-condizione:
 *      La struct veicolo esistere
 *      Orari.txt deve esistere e contenere i dati degli intervalli orari e il loro status di disponibilita`
 * 
 * Post-condizione:
 *      La struct annidata Orari riempito con successo
 * 
 * Ritorna: 
 *      0 se chiusura del file corretta altrimenti 1
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nella struct annidata orari
 *      Se il file è vuoto, la struct veicolo risulta NULL
 *      File viene chiuso in caso in cui controllotoken fallisce
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int riempiOrari (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaDisponibilita
 * -----------------------
 * Stampa a video lo status di disponibilita di un veicolo
 * 
 * Specifica sintattica:
 *      stampaDisponibilita(veicolo, int) -> void
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       stampaDisponibilità(v, indiceOrario) -> void
 * 
 * Pre-condizione:
 *      La struct veicolo deve esistere e contenere dati della struct annidata Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *       Stampa a video la disponibilita ("Non disponibile" o "Disponibile")
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaDisponibilita (veicolo v, int indiceOrario);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: modificaDisponibilità
 * -----------------------
 * Va a modificare nel campo disponibilità il suo valore a 1 quando chiamata
 * 
 * Specifica sintattica:
 *      modificaDisponibilità(veicolo, int) -> void
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       modificaDisponibilità(v, indiceOrario) -> void
 * 
 * Pre-condizione:
 *      La struct veicolo deve esistere e contenere dati nella struct annidata Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore, Campo Disponibilità cambiato
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *       Cambiato il valore nel campo Disponibilità della struct annidata Orari
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void modificaDisponibilita (veicolo v, int indiceOrario);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniModello
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce la stringa del campo modello della struct veicolo 
 * 
 * Specifica sintattica:
 *      ottieniModello(veicolo) -> char*
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *       ottieniModello(v) -> stringa del modello veicolo
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuta la stringa nel campo modello della struct veicolo
 * 
 * Ritorna: 
 *      Una stringa del campo modello della struct veicolo altrimenti NULL
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniModello(veicolo v);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniTarga
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce la stringa del campo targa della struct veicolo 
 * 
 * Specifica sintattica:
 *      ottieniTarga(veicolo) -> char*
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *       ottieniTarga(v) -> stringa della targa veicolo
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuta la stringa nel campo targa della struct veicolo
 * 
 * Ritorna: 
 *      Una stringa del campo targa della struct veicolo altrimenti NULL
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniTarga(veicolo v);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniOrarioInizio
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce il float del campo inizio della struct annidata orari
 * 
 * Specifica sintattica:
 *      ottieniOrariInizio(veicolo, int) -> float
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       ottieniOrariInizio(v , indiceOrario ) -> float della struct annidata orari
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto il float del campo inizio della struct annidata orari
 * 
 * Ritorna: 
 *      Un float del campo inzio della struct annidata orari altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniOrarioInizio(veicolo v, int indiceOrario);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniOrarioFine
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce il float del campo fine della struct annidata orari
 * 
 * Specifica sintattica:
 *      ottieniOrariFine(veicolo, int) -> float
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       ottieniOrariFine(v , indiceOrario ) -> float della struct annidata orari
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto il float del campo fine della struct annidata orari
 * 
 * Ritorna: 
 *      Un float del campo fine della struct annidata orari altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniOrarioFine(veicolo v, int indiceOrario);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniDisponibilita
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce l'int del campo Disponibilita della struct annidata orari
 * 
 * Specifica sintattica:
 *      ottieniDisponibilita(veicolo, int) -> int
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       ottieniDisponibilita(v , indiceOrario ) -> int della struct annidata orari
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto l'int del campo Disponibilita della struct annidata orari
 * 
 * Ritorna: 
 *      Un int del campo Disponibilita della struct annidata orari altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int ottieniDisponibilita(veicolo v, int indiceOrario);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniCostoOrario
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce il float del campo CostoNoleggioOrario della struct veicolo
 * 
 * Specifica sintattica:
 *      ottieniCostoOrario(veicolo) -> float
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *       ottieniCostoOrario(v) -> float della struct veicolo
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto il float del campo CostoNoleggioOrario della struct veicolo
 * 
 * Ritorna: 
 *      Un float del campo CostoNoleggioOrario della struct veicolo altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniCostoOrario(veicolo v);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: creaVeicolo
 * ----------------------------------------------------------------------------------------------------------------
 *  Alloca memoria per la struct veicolo
 * 
 * Specifica sintattica:
 *      creaVeicolo() -> veicolo
 *
 * Parametri:
 *     
 * 
 * Specifica semantica:
 *       creaVeicolo() -> struct veicolo
 *        
 * Pre-condizione:
 *      Nessuna pre-condizione
 *       
 * Post-condizione:
 *      Memoria allocata correttamente per la struct veicolo
 * 
 * Ritorna: 
 *      La struct veicolo allocata correttamente altrimenti NULL 
 * 
 * Effetti collaterali:
 *      Stampa a video un messaggio di errore in caso di allocazione fallita
 * ---------------------------------------------------------------------------------------------------------------- 
 */

veicolo creaVeicolo();

#endif