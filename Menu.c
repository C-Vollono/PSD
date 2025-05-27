/*ATTENZIONE: Nel codice sono presenti comandi system
              Implementati per la pulizia del terminale
              Potrebbero creare conflitti o problemi di vari natura
              "Annullarli" nel caso della presenza di quest'ultimi*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: operazioneAccesso
 * -----------------------
 * Gestisce le operazioni per l'accesso scelto dall'utente (registrazione login uscita), aggiornando "utente.txt" se necessario
 * 
 * Specifica sintattica:
 * 
 *      operazioneAccesso(char, char**) -> int
 *
 * Parametri:
 * 
 *      operazione: carattere per l'operazione da effettuare ("1, 2, 3")
 * 		nomeUtente: doppio puntatore a char per nomeUtente
 * 
 * Specifica semantica:
 * 
 * 		operazioneAccesso(operazione, **nomeUtente) -> int:
 * 		  -1: Errore nell'esecuzione
 *  	   1: Accesso corretto
 *  	   0: Utente già registrato
 *  	   2: Utente non registrato
 *  	   3: Operazione non valida  
 * 
 * Pre-condizione:
 * 
 *      il file "utente.txt" deve esistere.
 * 		
 * Post-condizione:
 * 
 *      operazione 1: se il nome utente non risulta registrato ed è valido, viene allocato, aggiunto in appending su file "utente.txt", altrimenti restituisce 0
 * 		operazione 2: se il nome utente esiste su file "utente.txt", viene allocato e viene effettuato l'accesso, altrimenti restituisce 2
 * 		operazione 3: il programma viene terminato senza errori tramite exit(0)
 * 
 * Ritorna:
 * 
 *      -1: Nel caso di errore di allocazione, e/o apertura file
 * 		0: Se l'utente nel caso di registrazione risulta già presente su file "utente.txt"
 * 		1: Se l'utente effettua correttamente il login e/o registrazione
 * 		2: Se l'utente sceglie fare il login ma non risulta registrato
 * 		3: Se l'utente sceglie un'operazione non valida (Es. fuori all'intervallo [1;3])
 * 
 * Effetti collaterali:
 * 
 *      Nel caso di errori di allocazioni, apertura file, chiusura file, stampa un messaggio di ERRORE
 * 		Stampa un messaggio di feedback, nel caso di uscita da programma
 *      Viene chiesto all'utente di inserire il nome utente, con un messaggio di avviso per il corretto inserimento
 * 		Se l'inserimento non è valido, stampa un messaggio di avviso
 * 		Se il nomeUtente passa tutti i controlli, allora modifica "utente.txt"
 * 		
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int operazioneAccesso (char operazione, char **nomeUtente){
  char bufferUtente[1024];
  char bufferFileUtente[1024];
  FILE *utentiRegistrati = fopen("utente.txt", "r");
  FILE *nuovoUtente;
  int corretto; //variabile che verifica la correttezza del nome utente
  int utenteCorrisponde = 0;
  char* ptrUtente;

  if (utentiRegistrati == NULL){
    printf("ERRORE: Apertura del file degli utenti registrati fallita.\n");
    return -1;
 }

  if (operazione == '3'){
	system("cls | clear");
    printf("Uscita dal programma\n");
    exit(0);
  } else if (operazione < '1' || operazione > '3'){
	system("cls | clear");
	return 3;
 }

  while (1){
  	corretto = 1;
	system("cls | clear");
	printf("\nVALIDI SOLO CARATTERI ALFANUMERICI, MAX. 25 CARATTERI\n\n");
 	printf("Inserisca il suo nome utente: "); 
    fgets(bufferUtente, sizeof(bufferUtente), stdin);
	bufferUtente[strcspn(bufferUtente, "\n")] = '\0';

    if (strlen(bufferUtente) > 25) {
    	corretto = 0;
		system("cls | clear");
    	printf("Nome inserito non valido, la lunghezza massima consentita e' di 25 caratteri alfanumerici \n\n");
    } else {
    	for (ptrUtente = bufferUtente; *ptrUtente != '\0'; ptrUtente++){
        	if (!((*ptrUtente  >= 'a' && *ptrUtente  <= 'z') ||
            	(*ptrUtente  >= 'A' && *ptrUtente  <= 'Z') ||
            	(*ptrUtente  >= '0' && *ptrUtente  <= '9'))){
              corretto = 0;
			  system("cls | clear");
              printf("Nome inserito non valido, si possono utilizzare solo caratteri alfanumerici! \n\n");
              break;
            }
        }
    }

    if (corretto) { 
    	while (fgets(bufferFileUtente, sizeof(bufferFileUtente), utentiRegistrati) != NULL){
    		bufferFileUtente[strcspn(bufferFileUtente, "\n")] = '\0';
    		if (strcmp(bufferFileUtente, bufferUtente) == 0){
            	utenteCorrisponde = 1;
                break;
            }
        }

        if (fclose(utentiRegistrati) != 0){
			system("cls | clear");
        	perror ("ERRORE: Chiusura del file degli utenti fallita.\n");
        	return -1;
		}
		int operazioneInt = operazione - '0';

    	switch (operazioneInt){
    		case 1:
      			if (utenteCorrisponde){
					system("cls | clear");
       				return 0;
       			} else {

            		*nomeUtente = malloc((strlen(bufferUtente) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
						system("cls | clear");
        	   			printf("ERRORE: Allocazione registrazione nome utente fallita.\n");
        	   			return -1;
         			}
        			strcpy(*nomeUtente, bufferUtente);
					nuovoUtente = fopen("utente.txt", "a");
             		if (nuovoUtente == NULL){
					system("cls | clear");
            		printf("ERRORE: Apertura del file degli utenti registrati per la creazione del nuovo utente fallita.\n");
					free(*nomeUtente);
            		return -1;
            	}
            	fprintf(nuovoUtente, "%s\n", *nomeUtente);
				if (fclose(nuovoUtente) != 0){
					free(*nomeUtente);
					system("cls | clear");
       				perror ("ERRORE: Chiusura del file degli utenti registrati fallita.\n");
       				return -1;
				}
				system("cls | clear");
        		return 1;

            }
       	    case 2: 
        		if (utenteCorrisponde){ 
         			*nomeUtente = malloc((strlen(bufferUtente) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
					system("cls | clear");
        	   		printf("ERRORE: Allocazione nome utente per l'accesso fallita.\n");
        	   		return -1;
         			}
        	 		strcpy(*nomeUtente, bufferUtente);
					system("cls | clear");
        	 		return 1; 
       			} else {
					system("cls | clear");
         			return 2; 
       			}
       		default:
				system("cls | clear");
       			return 3;
     	}
    }
  }
}


/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: menuAccesso
 * -----------------------
 * Stampa le opzioni di accesso/uscita per l'utente
 * 
 * Specifica sintattica:
 * 
 *      menuAccesso() -> char*
 *
 * Parametri: 
 * 
 * 		Nessuno
 * 
 * Specifica semantica:
 * 
 * 		menuAccesso() -> nomeUtente
 * 
 * Pre-condizione:
 * 
 *      La funzione operazioneAccesso deve essere implementata correttamente.
 * 		
 * Post-condizione:
 * 
 * 		opzione 1: Se l'utente effettua correttamente la registrazione in operazioneAccesso, allora restituisce il puntatore al nomeUtente  
 * 		opzione 2: Se l'utente effettua correttamente il login in operazioneAccesso, allora restituisce il puntatore al nomeUtente
 * 		opzione 3: Se l'utente inserisce quest'opzione, viene chiamata la funzione operazioneAccesso che chiude il programma e non ritorna a menuAccesso
 *
 *  Ritorna:
 * 
 *      stringa nomeUtente se l'accesso/registrazione da operazioneAccesso viene effettuato/a correttamente
 * 
 * Effetti collaterali:
 * 		
 *      Allocazione del nomeUtente in seguito alla chiamata di operazioneAccesso
 * 		Nel caso di input non validi, viene stampato un messaggio di feedback, e si ripete il menu
 * 		Nel caso in cui operazioneAccesso ritorna 0, stampa un messaggio di registrazione già avvenuta
 * 		Nel caso in cui operazioneAccesso ritorna 2, stampa un messaggio di registrazione assente
 * 		Nel caso in cui operazioneAccesso ritorna 3, stampa un messaggio di operazione non valida
 * 		Nel caso in cui operazioneAccesso ritorna un valore fuori dall'intervallo [0;3], stampa un messaggio di errore generico e ripete il menu
 * 
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* menuAccesso(){

	char *nomeUtente;
	char operazione;
	int risultatoOperazione;
	system("cls | clear"); // Pulizia dopo la prima run del programma
	while (1){
		int s2;
		char sceltaIndice[1024];
            while (1){
				printf("=== Menu di accesso utente ===\n");
    			printf(" (1) Registrazione\n");
    			printf(" (2) Login\n");
    			printf(" (3) Esci\n");
 				printf("Digiti l'operazione da effettuare: ");
                fgets(sceltaIndice, sizeof(sceltaIndice), stdin);
				int i=0;
                sceltaIndice[strcspn(sceltaIndice, "\n")] = '\0';
                if (strlen(sceltaIndice) == 1 && sceltaIndice[0] >= '0' && sceltaIndice[0] <= '3'){
					operazione = sceltaIndice[0];
                    break;
                } else {
                    system("cls | clear");
					printf("L'operazione scelta non e' valida, riprovare.\n\n");
                }
    	    }

		risultatoOperazione = operazioneAccesso(operazione, &nomeUtente);

    	switch (risultatoOperazione){
			case 1: return nomeUtente;
			case 0: printf("L'utente risulta gia' registrato, effettuare il login.\n\n"); break;
			case 2: printf("L'utente non risulta registrato, effettuare la registrazione.\n\n"); break;
			case 3: printf("L'operazione scelta non e' valida, riprovare.\n\n"); break;
			default: printf("Si e' verificato un errore ci scusiamo per il disagio, la invitiamo a riprovare l'accesso.\n\n"); break;
		}
	}
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: menuPrincipale
 * -----------------------
 * Funzione ausiliaria per il ritorno al menu Principale (scelte relative al servizio)
 * 
 * Specifica sintattica:
 * 
 *      menuPrincipale() -> int
 *
 * Parametri: 
 * 
 * 		Nessuno
 * 
 * Specifica semantica:
 * 
 * 		menuPrincipale() -> 0
 * 
 * Pre-condizione:
 * 	
 * 		Nessuna.
 * 		
 * Post-condizione:
 * 
 * 		Restituisce 0 se l'utente inserisce 'Y' o 'y', altrimenti resta nel ciclo in attesa di un nuovo input, attendendo in loop una scelta positiva
 *
 * Ritorna:
 * 
 *      0, ossia quando l'utente inserisce 'Y' o 'y'
 * 
 * Effetti collaterali:
 * 		
 *      Pulisce il buffer con getchar
 * 		Stampa un messaggio di richiesta input
 * 		Stampa messaggi di avviso nel caso di input non validi
 * 		Stampa un messaggio di feedback nel caso in cui l'utente inserisce 'N' o 'n'
 *  
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int menuPrincipale(){
	printf ("\nVuole tornare al menu principale? (Y o N): ");
	char scelta;
	while (1){
        if (scanf (" %c", &scelta) != 1 || getchar() != '\n'){
			printf("La scelta inserita per il ritorno al menu principale non e' valida, riprova: ");
			while(getchar() != '\n'); 
		} else if (scelta == 'Y' || scelta == 'y'){
			system("cls | clear");
            return 0;
        } else if (scelta == 'N' || scelta == 'n') {
            printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
        } else {
            printf ("La scelta inserita per il ritorno al menu principale non e' valida, riprova: ");
        }
    }
}
