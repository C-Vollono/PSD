#ifndef VEICOLO_H
#define VEICOLO_H
#include <stdio.h>

/*DEFINIZIONE STRUCT ORARIO*/
typedef struct Orario {

    float inizio; //inizio dell'intervallo orario della possibile prenotazione
    float fine; //fine dell'intervallo orario della possibile prenotazione
    int Disponibilita; // 0 = disponibile oppure 1 = non disponibile

}Orario;

/*DEFINIZIONE STRUCT VETTURA*/
struct Vettura{

    char* tipoVeicolo;
    char* modello;
    char* colore;
    char* targa;
    Orario orari[8]; //Struct annidata per gli orari
    int postiOmologati;
    char* Combustibile;
    int annoDiImmatricolazione;
    float CostoNoleggioOrario; // Costo ad ORA
};

typedef struct Vettura *veicolo;

/*-- FUNZIONI RELATIVE AI VEICOLI --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiVeicoli
 * -----------------------
 * Prende in input l'oggetto veicolo e il puntatore al file .txt contenente i dati dei veicoli
 * Riempie l'oggetto veicolo con i dati contenuti nel file 
 * 
 * Specifica sintattica:
 *      void riempiVeicoli(veicolo, char*) -> void
 *
 * Parametri:
 *      v:        oggetto veicolo
 *      nomefile: file Veicoli.txt
 * 
 * Specifica semantica:
 *      riempiVeicoli(v, nomefile) -> void
 * 
 * Pre-condizione:
 *      Il file txt deve contenere i vari dati dei Veicoli e l'oggetto veicolo esistere
 * 
 * Post-condizione:
 *      Non ritorna nessun valore, oggetto veicolo riempito
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nell'oggetto veicolo
 *      Se il file è vuoto, la funzione potrebbe dare comportamento indefinito senza opportuni controlli
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void riempiVeicoli (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaVeicoli
 * -----------------------
 * Stampa a video i dati di un oggetto veicolo tra cui anche gli intervalli orari con la loro disponibilità (richiamo ad altre due funzioni) 
 * 
 * Specifica sintattica:
 *      void stampaVeicoli(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 * 
 * Specifica semantica:
 *      stampaVeicoli(v) -> void
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve contenere dei dati diversi da NULL
 *      La funzione stampaOrari deve esistere
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

void stampaVeicolo (veicolo v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: liberaVeicoli
 * -----------------------
 *  Libera la memoria dell'oggetto veicolo
 * 
 * Specifica sintattica:
 *      void liberaVeicoli(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *  
 * Specifica semantica:
 *      liberaVeicoli(v) -> void
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

void liberaVeicoli (veicolo v);

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

float costoNoleggio (veicolo v, int k);

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

float verificaSconto (veicolo v, int k);

/*-- FUNZIONI RELATIVE AGLI ORARI --*/

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

void riempiOrari (veicolo v);

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

void verificaDisponibilita (veicolo v, int k);

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

void stampaOrari (veicolo v);

/*--Funzioni di supporto--*/

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: controllotoken
 * ----------------------------------------------------------------------------------------------------------------
 * Controllo di eventuali errori nella funzione strtok della libreria string.h 
 * 
 * Specifica sintattica:
 *      void controllotoken(char*, veicolo, FILE*)-> void
 *
 * Parametri:
 *      token: stringa
 *      v: oggetto veicolo
 *      file: puntatore a file
 * 
 * Specifica semantica:
 *      controllotoken(token, v, file)-> void 
 *       
 * Pre-condizione:
 *      token deve esistere
 *       
 * Post-condizione:
 *      Se token == NULL, libera memoria e chiude file
 * 
 * Ritorna: 
 *      Nessun valore     
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void controlloToken (char* token, veicolo v, FILE* file);

#endif