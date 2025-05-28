#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"

/*-- DEFINIZIONE STRUCT PRENOTAZIONE --*/
typedef struct item* Prenotazione;

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: NuovaPrenotazione
 * -----------------------
 *  Crea una nuova prenotazione nella struct item (prenotazione)
 * 
 * Specifica sintattica:
 *      NuovaPrenotazione(int, char*, veicolo, int, char*) -> Prenotazione
 *
 * Parametri:
 *      ID: indice (key) prenotazione
 *      NomeUtente: nome utente prenotazione
 *      c: struct veicolo
 *      i: indice orario
 *      dataPrenotazione: data prenotazione
 * 
 * Specifica semantica:
 *      NuovaPrenotazione(ID, NomeUtente, c, i, dataPrenotazione) -> Prenotazione altrimenti NULL
 * 
 * Pre-condizione:
 *      Struct veicolo deve esistere
 *      NomeUtente e dataPrenotazione allocate correttamente
 *      ottieniOrarioInizio, ottieniOrarioFine, costoNoleggio devono essere implementate correttamente
 * 
 * Post-condizione:
 *      Prenotazione allocata e creata correttamente altrimenti NULL     
 * 
 * Ritorna:
 *      Prenotazione
 * 
 * Effetti collaterali:
 *      Stampa a video dei messaggi di errore in caso di mancata allocazione di NomeUtente, dataPrenotazione e prenotazione stessa
 * ---------------------------------------------------------------------------------------------------------------- 
 */

Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, int indiceOrario, char* dataPrenotazione);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LiberaLista
 * -----------------------
 *  Libera memoria dalla struct prenotazione
 * 
 * Specifica sintattica:
 *      LiberaLista(Prenotazione) -> void
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      LiberaLista(p) -> void
 * 
 * Pre-condizione:
 *      Memoria allocata per la struct prenotazione
 * 
 * Post-condizione:
 *      Memoria liberata correttamente
 * 
 * Ritorna:
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      La struct prenotazione non ha piu` dati presenti in memoria
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void LiberaLista (Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaPrenotazione
 * -----------------------
 *  Stampa a video i dati della struct prenotazione
 * 
 * Specifica sintattica:
 *      stampaPrenotazione(Prenotazione) -> void
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      stampaPrenotazione(p) -> void
 * 
 * Pre-condizione:
 *      La struct prenotazione deve contenere dei dati diversi da NULL
 *      ottieniModelloPrenotazione deve essere implementata correttamente
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

void stampaPrenotazione (Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniID
 * -----------------------
 *  Restituisce l'intero del campo ID della struct prenotazione
 * 
 * Specifica sintattica:
 *      ottieniID(Prenotazione) -> int
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      ottieniID(p) -> intero dell'ID prenotazione
 * 
 * Pre-condizione:
 *      La struct prenotazione deve esistere
 * 
 * Post-condizione:
 *      Ottenuto l'ID della prenotazione
 * 
 * Ritorna:
 *      Un intero del campo ID della struct prenotazione altrimenti -1
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int ottieniID (Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniNext
 * -----------------------
 *  Restituisce il puntatore al prossimo elemento nella lista concatenata
 * 
 * Specifica sintattica:
 *      ottieniNext(Prenotazione p) -> struct item*
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      ottieniNext(p) -> puntatore al prossimo elemento nella lista concatenata altrimenti NULL
 * 
 * Pre-condizione:
 *      Struct prenotazione deve esistere
 * 
 * Post-condizione:
 *      Ottenuto il puntatore al prossimo elemento nella lista concatenata
 * 
 * Ritorna:
 *      puntatore al prossimo elemento nella lista concatenata
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

struct item *ottieniNext(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniNomeUtente
 * -----------------------
 *  Restituisce la stringa del campo nomeUtente della struct prenotazione
 * 
 * Specifica sintattica:
 *      ottieniNomeUtente(Prenotazione) -> char*
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      ottieniNomeUtente(p) -> stringa del nomeUtente
 * 
 * Pre-condizione:
 *      La struct prenotazione deve esistere
 * 
 * Post-condizione:
 *      Ottenuta la stringa del campo nomeUtente della struct prenotazione
 * 
 * Ritorna:
 *      Una stringa del campo nomeUtente della struct prenotazioni altrimenti NULL
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniNomeUtente(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniDataPrenotazione
 * -----------------------
 *  Restituisce la stringa del campo data della struct prenotazione
 * 
 * Specifica sintattica:
 *      ottieniDataPrenotazione(Prenotazione) -> char*
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      ottieniDataPrenotazione(p) -> stringa della data prenotazione
 * 
 * Pre-condizione:
 *      La struct prenotazione deve esistere
 * 
 * Post-condizione:
 *      Ottenuta la stringa del campo data della struct prenotazione altrimenti NULL
 * 
 * Ritorna:
 *      Una stringa del campo data della struct prenotazione altrimenti NULL
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniDataPrenotazione(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniInizioPrenotazione
 * -----------------------
 *  Restituisce il float del campo OrarioSceltoInizio della struct prenotazione
 * 
 * Specifica sintattica:
 *      ottieniInizioPrenotazione(Prenotazione) -> float
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      ottieniInizioPrenotazione(p) -> float dell'inizio prenotazione
 * 
 * Pre-condizione:
 *      La struct prenotazione deve esistere
 * 
 * Post-condizione:
 *      Ottenuto il float del campo OrarioSceltoInizio della struct prenotazione
 * 
 * Ritorna:
 *      Un float del campo OrarioSceltoInizio della struct prenotazione altrimenti -1
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniInizioPrenotazione(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniFinePrenotazione
 * -----------------------
 *  Restituisce il float del campo OrarioSceltoFine della struct prenotazione
 * 
 * Specifica sintattica:
 *      ottieniFinePrenotazione(Prenotazione) -> float
 *
 * Parametri:
 *      p: struct prenotazione
 * 
 * Specifica semantica:
 *      ottieniFinePrenotazione(p) -> float della fine prenotazione
 * 
 * Pre-condizione:
 *      La struct prenotazione deve esistere
 * 
 * Post-condizione:
 *      Ottenuto il float del campo OrarioSceltoFine della struct prenotazione
 * 
 * Ritorna:
 *      Un float del campo OrarioSceltoFine della struct prenotazione altrimenti -1
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniFinePrenotazione(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniModelloPrenotazione
 * -----------------------
 *  Restituisce la stringa del modello del veicolo
 * 
 * Specifica sintattica:
 *      ottieniModelloPrenotazione(Prenotazione) -> char*
 *
 * Parametri:
 *      p: struct veicolo
 * 
 * Specifica semantica:
 *      ottieniModelloPrenotazione(p) -> stringa del modello veicolo
 * 
 * Pre-condizione:
 *      La struct prenotazione deve esistere
 *      ottieniModello deve essere implementato correttamente
 * 
 * Post-condizione:
 *      Ottenuta la stringa del modello del veicolo     
 * 
 * Ritorna:
 *      Una stringa del modello del veicolo dalla struct veicolo
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniModelloPrenotazione(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniTargaPrenotazione
 * -----------------------
 *  Restituisce la stringa della targa del veicolo
 * 
 * Specifica sintattica:
 *      ottieniTargaPrenotazione(Prenotazione) -> char*
 *
 * Parametri:
 *      p: struct veicolo
 * 
 * Specifica semantica:
 *      ottieniTargaPrenotazione(p) -> stringa della targa veicolo
 * 
 * Pre-condizione:
 *      La struct prenotazione deve esistere
 *      ottieniTarga deve essere implementato correttamente
 * 
 * Post-condizione:
 *      Ottenuta la stringa della targa del veicolo     
 * 
 * Ritorna:
 *      Una stringa della targa del veicolo dalla struct veicolo
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniTargaPrenotazione(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: costoNoleggio
 * -----------------------
 * Calcola il costo noleggio di un intervallo orario (con eventuale sconto)
 * 
 * Specifica sintattica:
 *      costoNoleggio(veicolo, int) -> float
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice dell'orario scelto
 * 
 * Specifica semantica:
 *      costoNoleggio(v, indiceOrario) -> float del costo noleggio
 * 
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *      ottieniOrarioInizio, ottieniOrarioFine, ottieniCostoOrario, verificaSconto devono essere implementate correttamente
 * 
 * Post-condizione:
 *      Restituisce il costo totale del noleggio dell'intervallo orario (con eventuale sconto)
 * 
 * Ritorna:
 *      Un float del costo totale
 * 
 * Effetti collaterali: 
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float costoNoleggio (veicolo v, int indiceOrario);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: assegnaNext
 * -----------------------
 * 
 * 
 * Specifica sintattica:
 *      assegnaNext(Prenotazione, Prenotazione) -> Prenotazione
 *
 * Parametri:
 *      p: struct prenotazione
 *      next: struct prenotazione
 * 
 * Specifica semantica:
 *      assegnaNext(p, next) -> restituisce la prenotazione successiva
 * 
 * Pre-condizione:
 *      p deve esistere e diversa da NULL
 *      
 * 
 * Post-condizione:
 *      Ottenuta la prossima prenotazione altrimenti NULL
 * 
 * Ritorna:
 *      la prossima prenotazione altrimenti NULL
 * 
 * Effetti collaterali: 
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

Prenotazione assegnaNext(Prenotazione p, Prenotazione next);