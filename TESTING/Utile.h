#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "TabellaHash.h"

/*-- DEFINIZIONE FUNZIONI UTILE --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniData
 * -----------------------
 *  Funzione per ottenere la data locale della macchina formattata gg/mm/aaaa
 * 
 * Specifica sintattica:
 *      ottieniData()-> char*
 *
 * Parametri:
 *      Nessun parametro
 * 
 * Specifica semantica:
 *      ottieniData() -> data locale formattata
 * 
 * Pre-condizione:
 *      Includere la libreria time.h
 * 
 * Post-condizione:
 *      Data locale della macchina ottenuta con successo
 * 
 * Ritorna:
 *      Una stringa della data locale formattata gg/mm/aaaa altrimenti NULL
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore in caso di allocazione della memoria per la stringa fallita
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniData();

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: AggiornaStorico
 * -----------------------
 *  Aggiorna il file StoricoPrenotazioni.txt in appending con una nuova prenotazione
 * 
 * Specifica sintattica:
 *      AggiornaStorico(Prenotazione, int, int)-> int
 *
 * Parametri:
 *      p: struct Prenotazione
 *      indiceVeicolo: indice del veicolo
 *      indiceOrario: indice dell'orario
 * 
 * Specifica semantica:
 *      AggiornaStorico(p, indiceVeicolo, indiceOrario) -> 0 se chiudiFile fallito altrimenti 1
 * 
 * Pre-condizione:
 *      Struct Prenotazione deve esistere e diversa da NULL
 *      Indici validi
 *      chiudiFile, ottieniNomeUtente, ottieniDataPrenotazione, ottieniInizioPrenotazione, ottieniFinePrenotazione, ottieniID, ottieniModelloPrenotazione, ottieniTargaPrenotazione devono essere implementate correttamente
 * Post-condizione:
 *      Dati scritti correttamente su file
 *      Chiusura file avvenuta con successo
 * 
 * Ritorna:
 *      0 se la chiusura del file e` fallita altrimenti 1
 * 
 * Effetti collaterali:
 *      In caso di fallimento nell'apertura del file viene stampato un messaggio di errore
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int AggiornaStorico (Prenotazione p, int indiceVeicolo, int indiceOrario);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: RiempiTabellaHashDaFile
 * -----------------------
 *  La funzione legge il file StoricoPrenotazioni.txt, conta il numero di prenotazioni
 *  e crea una tabella hash per contenere tutte le prenotazioni
 *  Se la data corrente corrisponde alla data locale viene aggiornata la disponibilita
 * 
 * Specifica sintattica:
 *      RiempiTabellaHashDaFile(veicolo) -> TabellaHash
 *
 * Parametri:
 *      *v: puntatore a un array di struct veicolo
 * 
 * Specifica semantica:
 *      RiempiTabellaHashDaFile(*v) -> tabella hash aggiornata o NULL (non ci sono prenotazioni)
 * 
 * Pre-condizione:
 *      Il puntatore deve essere diverso da NULL e deve puntare all'array di struct veicolo
 *      La struct veicolo deve esistere e diversa da NULL
 *      Tabella hash allocata correttamente
 *      Formattazione del file corretta
 * 
 * Post-condizione:
 *      Tabella hash creata correttamente con le prenotazioni
 *      Disponibilita` aggiornata in caso data corrente sia uguale a quella locale
 *      Chiusura del file avvenuta correttamente
 *      NuovaTabellaHash, chiudiFile, ottieniData, LiberaTabellaHash, controllotoken, NuovaPrenotazione, modificaDisponibilita devono essere implemetate correttamente    
 * 
 * Ritorna:
 *      La tabella hash aggiornata con i dati o a NULL in caso non vi siano prenotazioni
 * 
 * Effetti collaterali:
 *      Allocata memoria per la tabella hash
 *      Stampa messaggi di errore in caso di: lettura fallita del file, memoria non allocata correttamente, ottenimento data locale fallita, inserimento fallito
 *      Viene liberata memoria in caso di tokenizzazione non corretta
 * ---------------------------------------------------------------------------------------------------------------- 
 */

TabellaHash RiempiTabellaHashDaFile (veicolo *v, int STORICO);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LimitaOrariDisponibili
 * -----------------------
 *  Modifica la disponibilita` degli orari disponibili durante una prenotazione confrontandoli con l'orario locale
 * 
 * 
 * Specifica sintattica:
 *      LimitaOrariDisponibili(veicolo) -> void
 *
 * Parametri:
 *      *v: puntatore a un array di struct veicolo
 * 
 * Specifica semantica:
 *      LimitaOrariDisponibili(*v) -> void
 * 
 * Pre-condizione:
 *      Il puntatore deve essere diverso da NULL e deve puntare all'array di struct veicolo
 *      La struct veicolo deve esistere e diversa da NULL
 *      modificaDisponibilita, ottieniOrarioInizio implementate correttamente
 * 
 * Post-condizione:
 *      Disponibilita` modificata in tempo reale
 * 
 * Ritorna:
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      La disponibilita` viene modificata
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void LimitaOrariDisponibili (veicolo *v);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaSconto
 * -----------------------
 * La funzione verifica la possibilità di un sconto in determinati intervalli orari prestabiliti e restituisce un tipo float
 * riguardante lo sconto da applicare al calcolo del costo totale del noleggio
 * 
 * Specifica sintattica:
 *      verificaSconto(veicolo, int) -> float
 *
 * Parametri:
 *      v: oggetto veicolo
 *      indiceOrario: indice dell'orario scelto
 * 
 * Specifica semantica:
 *      verificaSconto(v, indiceOrario) -> Percentuale di Sconto
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati sugli intervalli orari
 *      IndiceOrario deve essere valido
 *      OttieniOrarioInizio implementato correttamente
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

float verificaSconto (veicolo v, int indiceOrario);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaDisponibilità
 * -----------------------
 * Verifica la disponibilita` di un veicolo in un determinato orario
 * 
 * Specifica sintattica:
 *      int verificaDisponibilità (veicolo, int) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *      verificaDisponibilità(v, indiceOrario) -> 1 se ottieniDisponibilita restituisce 0 altrimenti 0
 *       
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati dell'oggetto orari
 *      IndiceOrario valido
 *       ottieniDisponibilita implemetata correttamente 
 * Post-condizione:
 *      Restituisce un intero se ottieniDisponibilita e` 0 o diverso da 0
 * 
 * Ritorna: 
 *      1 se ottieniDisponibilita restituisce 0 altrimenti 0
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale   
 * ----------------------------------------------------------------------------------------------------------------     
 */

int verificaDisponibilita(veicolo v, int indiceOrario);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: stampaOrari
 * ----------------------------------------------------------------------------------------------------------------
 * Stampa a video l'intervallo orario scelto dall'utente con la sua disponibilità (Non disponibile o Disponibile)
 * 
 * Specifica sintattica:
 *      stampaOrari(veicolo) -> void
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *      stampaOrari(v) -> void
 *       
 * Pre-condizione:
 *      La struct veidolo deve esistere e contenere dati
 *      stampaDisponibilita, ottieniOrarioInizio e ottieniOrarioFine devono esssere implementate correttamente
 *       
 * Post-condizione:
 *      Nessun valore di ritorno
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Stampa a video la lista degli orari e la loro disponibilita del veicolo   
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaOrari (veicolo v);

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: controllotoken
 * ----------------------------------------------------------------------------------------------------------------
 * Controlla se il token e` diverso da NULL (tokenizzazione corretta) 
 * 
 * Specifica sintattica:
 *      void controllotoken(char*)-> int
 *
 * Parametri:
 *      token: stringa
 * 
 * Specifica semantica:
 *      controllotoken(token)-> 1 se token diverso da zero altrimenti 0
 *       
 * Pre-condizione:
 *      token deve esistere
 *       
 * Post-condizione:
 *      Se token diverso NULL restituisce 1 altrimenti 0
 * 
 * Ritorna: 
 *      1 se token e` diverso da NULL altrimenti 0     
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore in caso il token sia NULL
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int controlloToken (char* token);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: chiudiFile
 * -----------------------
 *  Funzione che chiudere un file
 * 
 * Specifica sintattica:
 *      chiudiFile(FILE) -> int
 *
 * Parametri:
 *      *file: puntatore a file
 * 
 * Specifica semantica:
 *      chiudiFile(*file) -> 1 se avvenuto con successo altrimenti 0
 * 
 * Pre-condizione:
 *      Puntatore a file diverso da NULL e deve puntare al file
 * 
 * Post-condizione:
 *      File chiuso correttamente
 * 
 * Ritorna:
 *      1 se avvenuto con successo altrimenti 0
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore in caso di fallimento nella chiusura del file
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int chiudiFile(FILE* file);