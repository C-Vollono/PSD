#include <stdio.h>
#include <stdlib.h>

/*-- DEFINIZIONE FUNZIONI MENU --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: operazioneAccesso
 * -----------------------
 * Gestisce le operazioni per l'accesso scelto dall'utente (registrazione login uscita), aggiornando "utente.txt" se necessario
 * 
 * Specifica sintattica:
 * 		operazioneAccesso(char, char**) -> int
 *
 * Parametri:
 * 		operazione: carattere per l'operazione da effettuare ("1, 2, 3")
 * 		nomeUtente: doppio puntatore a char per nomeUtente
 * 
 * Specifica semantica:
 * 		operazioneAccesso(operazione, **nomeUtente) -> int:
 * 		-1: Errore nell'esecuzione
 *  	 1: Accesso corretto
 *  	 0: Utente già registrato
 *  	 2: Utente non registrato
 *  	 3: Operazione non valida  
 * 
 * Pre-condizione:
 * 		il file "utente.txt" deve esistere.
 * 		
 * Post-condizione:
 * 		operazione 1: se il nome utente non risulta registrato ed è valido, viene allocato, aggiunto in appending su file "utente.txt", altrimenti restituisce 0
 * 		operazione 2: se il nome utente esiste su file "utente.txt", viene allocato e viene effettuato l'accesso, altrimenti restituisce 2
 * 		operazione 3: il programma viene terminato senza errori tramite exit(0)
 * 
 * Ritorna:
 * 		-1: Nel caso di errore di allocazione, e/o apertura file
 * 		 0: Se l'utente nel caso di registrazione risulta già presente su file "utente.txt"
 * 		 1: Se l'utente effettua correttamente il login e/o registrazione
 * 		 2: Se l'utente sceglie fare il login ma non risulta registrato
 * 		 3: Se l'utente sceglie un'operazione non valida (Es. fuori all'intervallo [1;3])
 * 
 * Effetti collaterali:
 * 		Nel caso di errori di allocazioni, apertura file, chiusura file, stampa un messaggio di ERRORE
 * 		Stampa un messaggio di feedback, nel caso di uscita da programma
 *      Viene chiesto all'utente di inserire il nome utente, con un messaggio di avviso per il corretto inserimento
 * 		Se l'inserimento non è valido, stampa un messaggio di avviso
 * 		Se il nomeUtente passa tutti i controlli, allora modifica "utente.txt"	
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int operazioneAccesso (char operazione, char **nome_utente); 

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: menuAccesso
 * -----------------------
 * Stampa le opzioni di accesso/uscita per l'utente
 * 
 * Specifica sintattica:
 * 		menuAccesso() -> char*
 *
 * Parametri: 
 * 		Nessuno
 * 
 * Specifica semantica:
 * 		menuAccesso() -> stringa nomeUtente
 * 
 * Pre-condizione:
 * 		La funzione operazioneAccesso deve essere implementata correttamente.
 * 		
 * Post-condizione:
 * 		opzione 1: Se l'utente effettua correttamente la registrazione in operazioneAccesso, allora restituisce il puntatore al nomeUtente  
 * 		opzione 2: Se l'utente effettua correttamente il login in operazioneAccesso, allora restituisce il puntatore al nomeUtente
 * 		opzione 3: Se l'utente inserisce quest'opzione, viene chiamata la funzione operazioneAccesso che chiude il programma e non ritorna a menuAccesso
 *
 *  Ritorna:
 * 		stringa nomeUtente se l'accesso/registrazione da operazioneAccesso viene effettuato/a correttamente
 * 
 * Effetti collaterali:
 * 		Allocazione del nomeUtente in seguito alla chiamata di operazioneAccesso
 * 		Nel caso di input non validi, viene stampato un messaggio di feedback, e si ripete il menu
 * 		Nel caso in cui operazioneAccesso ritorna 0, stampa un messaggio di registrazione già avvenuta
 * 		Nel caso in cui operazioneAccesso ritorna 2, stampa un messaggio di registrazione assente
 * 		Nel caso in cui operazioneAccesso ritorna 3, stampa un messaggio di operazione non valida
 * 		Nel caso in cui operazioneAccesso ritorna un valore fuori dall'intervallo [0;3], stampa un messaggio di errore generico e ripete il menu
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* menuAccesso();

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: menuPrincipale
 * -----------------------
 * Funzione ausiliaria per il ritorno al menu Principale (scelte relative al servizio)
 * 
 * Specifica sintattica:
 * 		menuPrincipale() -> int
 *
 * Parametri: 
 * 		Nessuno
 * 
 * Specifica semantica:
 * 		menuPrincipale() -> 0
 * 
 * Pre-condizione:
 * 		Nessuna.
 * 		
 * Post-condizione:
 * 		Restituisce 0 se l'utente inserisce 'Y' o 'y', altrimenti resta nel ciclo in attesa di un nuovo input, attendendo in loop una scelta positiva
 *
 * Ritorna:
 * 		0, ossia quando l'utente inserisce 'Y' o 'y'
 * 
 * Effetti collaterali:
 * 		Pulisce il buffer con getchar
 * 		Stampa un messaggio di richiesta input
 * 		Stampa messaggi di avviso nel caso di input non validi
 * 		Stampa un messaggio di feedback nel caso in cui l'utente inserisce 'N' o 'n'
 * ---------------------------------------------------------------------------------------------------------------- 
 */
 
int menuPrincipale();
