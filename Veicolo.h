#ifndef VEICOLO_H
#define VEICOLO_H
#include <stdio.h>

typedef struct Vettura *veicolo;

/*DEFINIZIONE FUNZIONI*/

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: controllotoken
 * ----------------------------------------------------------------------------------------------------------------
 *  Controlla che la stringa letta da file sia tokenizzata correttamente
 * 
 * Specifica sintattica:
 *      void controllotoken(char*) -> int
 *
 * Parametri:
 *      token: stringa
 * 
 * Specifica semantica:
 *      controllotoken(token) -> 0 se token è NULL altrimenti 1 
 *       
 * Pre-condizione:
 *      token deve esistere
 *       
 * Post-condizione:
 *      Se token == NULL restituisce zero
 * 
 * Ritorna: 
 *      0 se token == NULL altrimenti 1     
 * 
 * Effetti collaterali:
 *      Stampa a video il messaggio di ERRORE dell'ottenimento del token
 * ---------------------------------------------------------------------------------------------------------------- 
 */



/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: chiudiFile
 * ----------------------------------------------------------------------------------------------------------------
 *  Funzione di controllo per la chiusura del file
 * 
 * Specifica sintattica:
 *      int chiudiFile(FILE) -> int
 *      
 *
 * Parametri:
 *      file = puntatore a file
 *      
 * 
 * Specifica semantica:
 *      chiudiFile(file) -> 1 se file chiuso correttamente altrimenti 0
 *       
 *       
 * Pre-condizione:
 *      Il file deve essere aperto correttamente 
 *       
 * Post-condizione:
 *      Se la chiusura del file è avvenuta correttamente restituisce 1
 *      
 * 
 * Ritorna: 
 *      Restituisce 0 se la chiusura non è avvenuta correttamente altrimenti 1
 * 
 * Effetti collaterali:
 *      Stampa a video un messaggio di ERRORE in caso la chiusura non è avvenuto con successo
 * ---------------------------------------------------------------------------------------------------------------- 
 */



/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiVeicoli
 * -----------------------
 * Prende in input l'oggetto veicolo e il puntatore al file .txt contenente i dati dei veicoli
 * Riempie l'oggetto veicolo con i dati contenuti nel file 
 * 
 * Specifica sintattica:
 *      int riempiVeicoli(veicolo) -> int
 *
 * Parametri:
 *      v: oggetto veicolo
 * 
 * Specifica semantica:
 *      riempiVeicoli(v) -> 1 se Veicolo riempito correttamente e chiudiFile = 1, altrimenti 0
 * 
 * Pre-condizione:
 *      L'oggetto Veicolo deve essere allocato correttamente 
 * 
 * Post-condizione:
 *      Se Il Veicolo risulta riempito e chiudiFile restituisce 1, restituisce 1
 * 
 * Ritorna:
 *      Restituisce 1 se Veicolo è riempito con successo e file chiuso correttamente, altrimenti 0
 * 
 * Effetti collaterali:
 *      Apre in lettura il file contenente i veicoli, stampa messaggi di ERRORE in caso di mancata apertura del file
 *      e nella tokenizzazione dell'oggetto Veicolo
 *      Viene riempita la struct Veicolo
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int riempiVeicoli (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaVeicolo
 * -----------------------
 * Stampa a video i dati di un oggetto veicolo 
 * 
 * Specifica sintattica:
 *      void stampaVeicolo(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 * 
 * Specifica semantica:
 *      stampaVeicolo(v) -> void
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve contenere dei dati diversi da NULL
 * 
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      Stampa a video i dati contenuti nell'oggetto Veicolo
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaVeicolo (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: liberaVeicolo
 * -----------------------
 *  Libera la memoria dell'oggetto veicolo
 * 
 * Specifica sintattica:
 *      void liberaVeicolo(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *  
 * Specifica semantica:
 *      liberaVeicolo(v) -> void
 * 
 * Pre-condizione:
 *      Memoria allocata per l'oggetto veicolo
 * 
 * Post-condizione:
 *      Memoria liberata correttamente
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      L'oggetto veicolo non ha più dati presenti in memoria
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void liberaVeicolo (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaSconto
 * -----------------------
 * La funzione verifica la possibilità di un sconto in determinati intervalli orari prestabiliti e restituisce un tipo float
 * riguardante lo sconto da applicare al calcolo del costo totale del noleggio
 * 
 * Specifica sintattica:
 *      float verificaSconto(veicolo, int) -> float
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice dell'orario scelto
 * 
 * Specifica semantica:
 *      verificaSconto(v, k) -> Percentuale_di_Sconto
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati sugli intervalli orari
 *      
 * Post-condizione:
 *      Restituisce la percentuale di sconto se l'orario della prenotazione corrisponde all'intervallo
 *      Altrimenti restituisce 1
 * 
 * Ritorna:
 *      Restituisce un tipo float della percentuale di sconto
 *      Altrimenti float di 1.0
 *      
 * Effetti collaterali:
 *      Nessun effetto collaterale 
 * ---------------------------------------------------------------------------------------------------------------- 
 */



/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: costoNoleggio
 * -----------------------
 * Calcola quanto costa il noleggio in un orario scelto dall'utente con eventuale sconto 
 * 
 * Specifica sintattica:
 *      float costoNoleggio(veicolo, int) -> float
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice dell'orario scelto
 * 
 * Specifica semantica:
 *      costoNoleggio(v, k) -> costo_del_Noleggio
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere dati sugli intervalli orari
 *      La funzione verificaSconto deve esistere (oppure eliminata in caso di sconti non applicabili)
 * 
 * Post-condizione:
 *      Restituisce il costo totale del noleggio dell'orario scelto dall'utente
 * 
 * Ritorna:
 *      Ritorna un tipo float del costo totale
 * 
 * Effetti collaterali: 
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */


/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiOrari
 * -----------------------
 * Prende in input l'oggetto veicolo e il puntatore al file .txt contenente i dati degli intervalli orari
 * Riempie l'oggetto veicolo con i dati contenuti nel file 
 * 
 * Specifica sintattica:
 *      void riempiOrari(veicolo,char*)->void
 *
 * Parametri:
 *             v: oggetto veicolo
 *      nomefile: file Orari.tx
 * 
 * Specifica semantica:
 *      riempiOrari(v, nomefile)-> void
 *       
 * Pre-condizione:
 *       Il file txt deve contenere i vari dati degli Orari e l'oggetto veicolo esistere
 * 
 * Post-condizione:
 *      Non ritorna nessun valore, oggetto Orari riempito
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nell'oggetto veicolo
 *      Se il file è vuoto, la funzione potrebbe dare comportamento indefinito senza opportuni controlli
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int riempiOrari (veicolo v);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione:
 * ----------------------------------------------------------------------------------------------------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *       
 *       
 * Pre-condizione:
 *      
 *       
 * Post-condizione:
 *      
 * 
 * Ritorna: 
 *           
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaDisponibilita (veicolo v, int k);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaDisponibilità
 * -----------------------
 * Verifica che un veicolo in un determinato orario sia disponibile attraverso un modulo 2 (se 1 allora non disponibile altrimenti disponibile)
 * Stampa a video disponibile o meno
 * 
 * Specifica sintattica:
 *      void verificaDisponibilità (veicolo, int) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice orario scelto
 * 
 * Specifica semantica:
 *      verificaDisponibilità(v, k) -> void
 *       
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati della struct Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale   
 * ----------------------------------------------------------------------------------------------------------------     
 */


/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: modificaDisponibilità
 * -----------------------
 * Va a modificare nel campo disponibilità il suo valore a 1 quando chiamata
 * 
 * Specifica sintattica:
 *      void modificaDisponibilità(veicolo, int) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice orario scelto
 * 
 * Specifica semantica:
 *       modificaDisponibilità(v, k) -> void
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere dati nella struct Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore, Campo Disponibilità cambiato
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *       Cambiato il valore nel campo Disponibilità della struct Orario
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void modificaDisponibilita (veicolo v, int k);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: stampaOrari
 * ----------------------------------------------------------------------------------------------------------------
 * Stampa a video l'intervallo orario scelto dall'utente con la sua disponibilità (Non disponibile o Disponibile)
 * 
 * Specifica sintattica:
 *      void stampaOrari(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 * 
 * Specifica semantica:
 *      stampaOrari(v) -> void
 *       
 * Pre-condizione:
 *      L'oggetto deve esistere e contenere dati
 *      verificaDisponibilità deve esistere 
 *       
 * Post-condizione:
 *      Nessun valore di ritorno
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale     
 * ---------------------------------------------------------------------------------------------------------------- 
 */


char* ottieniModello(veicolo v);

char* ottieniTarga(veicolo v);

float ottieniOrarioInizio(veicolo v, int k);

float ottieniOrarioFine(veicolo v, int k);

int ottieniDisponibilita(veicolo v, int k);

float ottieniCostoOrario(veicolo v);

veicolo creaVeicolo();

#endif